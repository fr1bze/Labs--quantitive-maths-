#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
#include<algorithm>
#include <fstream>
#include <iomanip>

struct State
{
    std::vector<double> state;
    double t;
};

[[nodiscard]] std::vector<double> rightPart_point(const double time, const std::vector<double> state) noexcept
{

    std::vector<double> F;
    long double mu = 398600.4415;
    long double r2 = state[0]*state[0] + state[1]*state[1] + state[2]*state[2];
    long double r = sqrt(state[0]*state[0] + state[1]*state[1] + state[2]*state[2]);
    long double r3 = r2 * r;;
    for (int i = 0; i < 3; ++i)
    {
        F.push_back(state[i + 3]);
    }
    for (int i = 0; i < 3; ++i)
    {
        F.push_back(-mu * state[i] / r3);
    }

    return F;
}

[[nodiscard]] std::vector<double> rightPart_Arien(const double time, const std::vector<double> state) noexcept
{
    //задача јриенсторфа (нач. услови€ - 0.994 0 0 0 -2.00158510637908252240537862224 0)

    std::vector<double> F;
    double mu_A = 0.012277471;
    double eta_A = 1 - mu_A;
    double A = sqrt(((state[0] + mu_A) * (state[0] + mu_A) + state[1] * state[1]) * ((state[0] + mu_A) * (state[0] + mu_A) + state[1] * state[1]) * ((state[0] + mu_A) * (state[0] + mu_A) + state[1] * state[1]));
    double B = sqrt(((state[0] - eta_A) * (state[0] - eta_A) + state[1] * state[1]) * ((state[0] - eta_A) * (state[0] - eta_A) + state[1] * state[1]) * ((state[0] - eta_A) * (state[0] - eta_A) + state[1] * state[1]));

    F.push_back(state[3]);
    F.push_back(state[4]);
    F.push_back(0);
    F.push_back(state[0] + 2*state[4] - eta_A * (state[0] + mu_A) / A - mu_A * (state[0] - eta_A) / B);
    F.push_back(state[1] - 2*state[3] - eta_A * state[1] / A - mu_A * state[1] / B);
    F.push_back(0);

    return F;
}

[[nodiscard]] std::vector<double> add(const std::vector<double> a, const std::vector<double> b) noexcept
{
    std::vector<double> res;
    for (int i = 0; i < 6; i++)
        res.push_back(a[i] + b [i]);
    return res;
}

[[nodiscard]] std::vector<double> mult(const std::vector<double> x, double a) noexcept
{
    std::vector<double> res;
    for (int i = 0; i < 6; i++)
        res.push_back(x[i] * a);
    return res;
}


[[nodiscard]] std::vector<double> explicitRK(const State& initial, double step, const std::function<std::vector<double> (const double, const std::vector<double>)> &f) noexcept
{
    std::vector<double> K1;
    std::vector<double> K2;
    std::vector<double> K3;
    std::vector<double> K4;

    std::vector<double> res;

    K1 = f(initial.t, initial.state);
    K2 = f(initial.t + step/2, add(initial.state, mult(K1, step / 2)));
    K3 = f(initial.t + step/2, add(initial.state, mult(K2, step / 2)));
    K4 = f(initial.t + step, add(initial.state, mult(K3, step)));

    res = add(f(initial.t, initial.state), mult(add(add(K1, K2), add(K3, K4)), step/6));

    return(res);
}

int main()
{
    struct State initial;
    std::cout << "time" << std:: endl;
    std::cin >> initial.t;

    double ex;
    std::cout << "coords" << std:: endl;
    for (int i = 0; i < 6; ++i)
    {
        std::cin >> ex;
        initial.state.push_back(ex);
    }
    unsigned iterations = 100;

    double step = 1;

    std::function<std::vector<double>(const double,const std::vector<double>)> F(rightPart_Arien);
    std::vector<double> y_theory, y_n_plus_1;;
    double mu = 398600.4415, V0, R0 = 6800, w;

    w = sqrt(mu/(R0*R0*R0));

// double max_e;
// std::ofstream error;
// error.open("/Users/mikhail/Desktop/error.txt");
// for (int i = 0; i < iterations; ++i)
//     {
//         y_n_plus_1 = explicitRK(initial, step, F);
//         y_theory.push_back(R0 * w * std::cos(w * (initial.t + step)));
//         y_theory.push_back(- R0 * w * std::sin(w * (initial.t + step)));
//         y_theory.push_back(0);
//         y_theory.push_back(R0 * std::sin(w * (initial.t + step)));
//        // std::cout << R0 * std::sin(w * (initial.t + step)) << std::endl;
//         y_theory.push_back(R0 * std::cos(w * (initial.t + step)));
//         y_theory.push_back(0);
//         max_e = sqrt((y_theory[0] - y_n_plus_1[0]) * (y_theory[0] - y_n_plus_1[0]) + (y_theory[1] - y_n_plus_1[1])*(y_theory[1] - y_n_plus_1[1]));
//         error << max_e << std::endl;
//         std::cout << max_e << std::endl;
//         y_theory.clear();
//         step++;
//     }
    std::ofstream file1, file2;
    file1.open("/Users/mikhail/Desktop/x.txt");
    file2.open("/Users/mikhail/Desktop/y.txt");
    if (file1.is_open() && file2.is_open())
    {
        for (int i = 0; i < 4000; ++i)
        {
            y_n_plus_1 = explicitRK(initial, step, iterations, F, table);
            initial.t += step;
            initial.state = y_n_plus_1;

            file1 << y_n_plus_1[0] << std::endl;
            file2 << y_n_plus_1[1] << std::endl;
        }
    }

    file1.close();
    file2.close();

//error.close();
return 0;
}
