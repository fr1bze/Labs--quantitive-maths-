#include <iostream>
#include <cmath>
#include <functional>
#include <fstream>

double pi = M_PI;

double func1(double x)
{
    return (x - 0.1 * std::sin(x) - pi / 4);
}

double func2(double x)
{
    return (std::tan(x) - 4 * x / pi);
}

double func3(double x)
{
    return std::log(std::cosh(x));
}

double dfunc(const std::function<double(double)> & func, double x, double h)
{
    return (func(x + h)- func(x - h))/(2 * h);
}

double bisectionMethod(double a, double b, const std::function<double(double)> & func, unsigned numberOfIterations) noexcept
{
    unsigned k = 0;
    while (k < numberOfIterations)
    {
        double c = (a+b)/2;
        if (func(c) == 0)
        {
            return c;
        }
        else
        {
            if (func(c)*func(b) < 0)
                a = c;
            else
                b = c;
        }
        k++;
    }
    return (a+b)/2;
}

double simpleIterationMethod(double inital, const std::function<double(double)> & func, double tau, unsigned numberOfIterations) noexcept
{
    double res = inital;
    for (int i = 0; i < numberOfIterations; i++)
        res += tau * func(res);
    return res;
}

double newtonMethod(double inital, const std::function<double(double)> & func, unsigned numberOfIterations, double h) noexcept
{
    double res = inital;
    for (int i = 0; i < numberOfIterations; i++)
        res -= func(res)/dfunc(func, res, h);
    return res;
}

int main()
{
    std::ofstream out;          
    out.open("/Users/mikhail/Desktop/secondFunc.txt");
    for (double i = 0; i <= 100; i++)
    {
        // out << i << ": " << func1(bisectionMethod(0, 10, func1, i)) << std::endl;     
        // out << i << ": " << func1(newtonMethod(1, func1, i, 0.05)) << std::endl;      
       // out << i << ": " << func2(bisectionMethod(0.5, 1.5, func2, i)) << std::endl;  
     //   out << i << ": " << func2(simpleIterationMethod(1, func2, -0.5, i)) << std::endl; 
       // out << i << ": " << func2(newtonMethod(1, func2, i, 0.05)) << std::endl;      
        // out << i << ": " << func3(bisectionMethod(0, 5, func3, i)) << std::endl;               
        // out << i << ": " << func3(simpleIterationMethod(1, func3, -1, i)) << std::endl;
        // out << i << ": " << func3(newtonMethod(1, func3, i, 0.05)) << std::endl;         
        // out << i << ": " << newtonMethod(5, func3, i, 0.05) << std::endl; 
       // out << i << ": " << func3(simpleIterationMethod(1, func3, i, 10)) << std::endl;
       std::cout << i << ": " << simpleIterationMethod(1, func2, -0.5, i) << std::endl;  
    }
    return 0;
}
