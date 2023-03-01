#include <iostream>
#include <cmath>
#include <functional>
#include <fstream>
#include <vector>

//Интеграл косинуса от 0 до 10 с точностью до 6 знаков включительно 
double actual_val = std::sin(10);

double func(double x)
{
	return cos(x);

}

 double integrateOneSeg(
    double a,
    double b,
    unsigned n,
    const std::function<double(double)> & func)
{
    double xi_1 = (a + b)/2;
    double xi_2 = (b - a)/2;
    double I = 0;
    std::vector<double> x(n);
    std::vector<double> w(n);
    switch (n)
    {
    case 2:
        x[0] = (-1)/sqrt(3.);
        x[1] = 1/sqrt(3.);
        w[0] = w[1] = 1.000000000;
        break;
    case 3:
        x[0] = sqrt(3.)/sqrt(5.);
        x[1] = 0;
        x[2] = (-1.)*x[0];
        w[0] = w[2] = double(5.)/9.;
        w[1] = double(8.)/9.;
        break;
    case 4:
        x[0] = (-1)*sqrt(double(3)/7+double(2)/7*sqrt(double(6)/5));
        x[1] = -sqrt(double(3)/7 - double(2)/7*sqrt(double(6)/5));
        x[2] = (-1)*x[1];
        x[3] = x[0]*(-1);
        w[0] = w[3] = (18-sqrt(30))/36;
        w[1] = w[2] = (18+sqrt(30))/36;
        break;
    case 5:
        x[0] = double((-1))/3*sqrt(5+2*sqrt(double(10)/7));
        x[1] = double((-1))/3*sqrt(5-2*sqrt(double(10)/7));
        x[2] = 0;
        x[3] = double(1)/3*sqrt(5-2*sqrt(double(10)/7));
        x[4] = double(1)/3*sqrt(5+2*sqrt(double(10)/7));
        w[0] = w[4] = double(322-13*sqrt(70))/900;
        w[1] = w[3] = double(322+13*sqrt(70))/900;
        w[2] = double(128)/225;
        break;
    }
    for(int i = 0; i < n; i++)
    {
        x[i] = xi_1 + xi_2*x[i];
    }
    for(int i = 0; i < n; i++)
    {
        I += func(x[i])*w[i];
    }
    I = I*xi_2;
    return I;
}

 double integrate(
    double a,
    double b,
    unsigned n,
    unsigned s,
    const std::function<double(double)> & func)
{
    double I = 0;
    for(int i = 0; i < s; i++)
    {
        I += integrateOneSeg(a + ((b - a)*i)/s, a + (b - a)*(i + 1.)/s, n, func);
    }
    return I;
}
int main()
{
    std::vector<int> steps(100);
    std::vector<double> mistakes_2(100);
    std::vector<double> mistakes_3(100);
    std::vector<double> mistakes_4(100);
    std::vector<double> mistakes_5(100);
    for(int i = 0; i < 100; i++)
    {
        steps[i] = i;
        mistakes_2[i] = abs(integrate(0, 10, 2, i, func) - actual_val);
        mistakes_3[i] = abs(integrate(0, 10, 3, i, func) - actual_val);
        mistakes_4[i] = abs(integrate(0, 10, 4, i, func) - actual_val);
        mistakes_5[i] = abs(integrate(0, 10, 5, i, func) - actual_val);
    }
    std::cout << "2      "<< "3              " << "4         " << "5 " << std::endl;
    for (int i = 0; i < steps.size(); i++)
    {
        std::cout << steps[i] + 1 << " " <<  mistakes_2[i] << " " << mistakes_3[i] << " " << mistakes_4[i] << " " << mistakes_5[i] << std::endl;
    }
    return 0;
}
