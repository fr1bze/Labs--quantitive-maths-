#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>


struct State {
    std::vector<double> state;
    double t;
};

template <unsigned s>
struct ButcherTable
{
    double **matrix = new double*[s];
    std::vector<double> column;
    std::vector<double> String;
};

[[nodiscard]] std::vector<double> rightPart_point(const double time, const std::vector<double> state) noexcept
{

    double r = sqrt(state[0]*state[0] + state[1]*state[1] + state[2]*state[2]);
    double C = -3.986004415e14/r/r/r;

    std::vector<double> F;
    F.push_back(state[3]);
    F.push_back(state[4]);
    F.push_back(state[5]);
    F.push_back(C * state[0]);
    F.push_back(C * state[1]);
    F.push_back(C * state[2]);
    return F;
}

template <unsigned s>
[[nodiscard]] std::vector<double> explicitRK(const State& initial, double step, unsigned iterations, const std::function<std::vector<double> (const double, const std::vector<double>)> &f, ButcherTable<s>& table) noexcept 
{
        for (int i = 0; i < s; i++)
        {
            table.matrix[i] = new double[s];
            for (int j = 0; j < s; j++)
            {
                if (i <= j) table.matrix [i][j] = 0;
            }
        }

        table.matrix [0][0] = 0;
        table.matrix [1][0] = 0.5;
        table.matrix [1][1] = 0;
        table.matrix [2][0] = 0;
        table.matrix [2][1] = 0.5;
        table.matrix [3][0] = 0;
        table.matrix [3][1] = 0;
        table.matrix [3][2] = 1;
        table.matrix [3][3] = 0;

        table.column.push_back(0);
        table.column.push_back(0.5);
        table.column.push_back(0.5);
        table.column.push_back(1);

        table.String.push_back(1.0/6.0);
        table.String.push_back(1.0/3.0);
        table.String.push_back(1.0/3.0);
        table.String.push_back(1.0/6.0);

        std::vector<double> K1;
        std::vector<double> K2;
        std::vector<double> K3;
        std::vector<double> K4;

        std::vector<double> K11;
        std::vector<double> K22;
        std::vector<double> K33;

        std::vector<double> res;

        K1 = f(initial.t, initial.state);
        for (int i = 0; i < 6; ++i)
        {
            K11.push_back(initial.state[i] + step * table.matrix[1][0] * K1[i]);
        }

        K2 = f(initial.t + table.column[1] * step, K11);
        for (int i = 0; i < 6; ++i)
        {
            K22.push_back(initial.state[i] + step * table.matrix[2][1] * K2[i]);
        }
        K3 = f(initial.t + table.column[2] * step, K22);
         for (int i = 0; i < 6; ++i)
        {
            K33.push_back(initial.state[i] + step * table.matrix[3][2] * K3[i]);
        }
        K4 = f(initial.t + table.column[3] * step, K33);

        for (int i = 0; i < 6; ++i)
        {
            res.push_back(initial.state[i] + step * (table.String [0] * K1[i] + table.String [1] * K2[i] + table.String [2] * K3[i] + table.String [3] * K4[i]));
        }
        return(res);
}

int main()
{
    struct State initial;
    struct ButcherTable <4> table;
    std::cin >> initial.t;

    double ex;
    for (int i = 0; i < 6; ++i)
    {
        std::cin >> ex;
        initial.state.push_back(ex);
    }
    unsigned iterations;

    std::cin >> iterations;

    double step = 50;

    std::function<std::vector<double>(const double,const std::vector<double>)> F(rightPart_point);
    std::vector<double> y_theory;
    double mu, V0, R0 = 6800e3, w;
    mu = 398600.4415;
    std::vector<double> y_n_plus_1;

    V0 = sqrt((initial.state[3] * initial.state[3]) + initial.state[4] * initial.state[4] + initial.state[5] * initial.state[5]);
    R0 = mu / (V0*V0);
    w = V0*V0*V0 / mu;

double max_e;
std::ofstream error;
error.open("/Users/mikhail/Desktop/error.txt");
        for (int i = 0; i < iterations; ++i)
        {
           y_n_plus_1 = explicitRK(initial, step, i, F, table);
            y_theory.push_back(R0 * sin(w * (initial.t + step)));
            y_theory.push_back(R0 * cos(w * (initial.t + step)));
            y_theory.push_back(0);

            max_e = sqrt((y_theory[0] - y_n_plus_1[0]) * (y_theory[0] - y_n_plus_1[0]) + (y_theory[1] - y_n_plus_1[1])*(y_theory[1] - y_n_plus_1[1]));
            error << max_e << std::endl;
            //std::cout << max_e << std::endl;
            y_theory.clear();

        }
    return 0;
}
