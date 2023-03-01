#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <optional>

double func(double x)
{
    double y = x*x;
    return y;
}

double dif(double x)
{
    double dy = 2*x;
    return dy;
}


double factorial (int n)
{
    int f = 1;
    for (int i = 1; i <= n; i++)
        f *= i;
    return f;
}
std::vector<double>  find_coeffs (std::vector <double>& vec, int n)
{
    double d, s, a[n+1][n+1], b[n+1], x[n+1];
    std::vector <double> res(n);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            {
                a[i][j] = std::pow(vec[j-1], i-1);
            }
        if (i == 2)
            b[i] = 1;
        else
            b[i] = 0;
    }

    for (int k = 1; k <= n; k++)
    {
        for (int j = k + 1; j <= n; j++)
            {
                d = a[j][k] / a[k][k];
                for (int i = k; i <= n; i++)
                    {
                        a[j][i] = a[j][i] - d * a[k][i];
                    }
            b[j] = b[j] - d * b[k];
            }
    }

    for (int k = n; k >= 1; k--)
    {
        d = 0;
        for (int j = k + 1; j <= n; j++)
            {
                s = a[k][j] * x[j];
                d = d + s;
            }
    x[k] = (b[k] - d) / a[k][k];
    }
    for (int i = 1; i <= n; i++)
        res[i - 1] = x[i];
    return res;
}

void rec (std::vector <double> &vec, int n)
{   double pi = 3.141529;
    double error1, error;
    std::ofstream out("/Users/mikhail/Desktop/test.txt");
    for (double i = 0.2; i < 10; i+= 0.01)
    {
        error1 = (find_coeffs(vec,n)[0]*func(pi + vec[0] * i) + find_coeffs(vec,n)[1]*func(pi+ vec[1] * i)+ find_coeffs(vec,n)[2] * func(pi + vec[2] * i))/i;
        error = std::abs(error1 - dif(pi));
        if (out.is_open())
        {
            out<<i<<" "<<error<<std::endl;
        }
    }
    out.close();
}


int main()
{
    int n;
    double sum1 = 0, sum2 = 0;
    std::cout<<"enter # of nodes"<<std::endl;
    std::cin >> n;
    std::vector <double> vec(n);
    std::cout<<"enter nodes"<<std::endl;
    for (int i = 0; i < n; i++)
    {
        std::cin>>vec[i];
    }
    std::cout<<"result:"<<std::endl;
    for (int i = 0; i < n; i++)
    {
        std::cout<<find_coeffs(vec, n)[i]<<" ";
    }
    for( int i = 0; i < n; i++)
    {
        sum1 += find_coeffs(vec, n)[i] * std::pow(vec[i], n);
        sum2 += std::abs(find_coeffs(vec, n)[i]);
    }
    sum1 = sum1/factorial(n);
    rec(vec, n);
    return 0;
}

