#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

template <typename T>
void recvec(vector <T> arr, ostream &out = cout)
{
    for (int i = 0; i < arr.size(); i++) {
        out << arr[i] << ' ';
    }
    out << '\n';
}

class NewtonianInterpolator
{
    public:
    vector <double> x, y;
    vector <double> diff;
    int dim;

    void div_diffs()
    {
        for(int i = 0; i < dim - 1; i++)
        {
            double f = (y[i] - y[i + 1])/(x[i] - x[i + 1]);
            diff[i] = f;
        }
        diff[dim - 1] = diff[0];
        for(int i = 1; i < dim; i++)
        {
            for(int j = 0; j < dim - i - 1; j++)
            {
                diff[j] = (diff[j] - diff[j + 1])/(x[j] - x[j + i + 1]);
            }
            diff[dim - i - 1] = diff[0];
        }
        diff[0] = y[0];
        reverse(diff.begin()+1, diff.end());
    }

    NewtonianInterpolator(vector <double> &x, vector <double> &y)
    {
        dim = x.size();
        this->x.resize(dim);
        this->y.resize(dim);
        diff.resize(dim, 0);
        for (int i = 0; i < dim; i++)
        {
            this->x[i] = x[i];
            this->y[i] = y[i];
        }
        div_diffs();
    }

    double interpolate(double x, int n = 0)
    {
        if (n == dim-1)
        {
            return diff[n];
        }
        return diff[n] + (x-this->x[n])*interpolate(x, n+1);
    }
};

double func(double x)
{
    double y = cos(x);
    return y;
}

double error(NewtonianInterpolator &I, double len, int n = 1000)
{
    double error = 0;
    for (int i = 0; i < n; i++)
    {
        double x = len/(n-1)*i;
        error = max(abs(func(x) - I.interpolate(x)), error);
    }
    return error;
}
vector<double> cheb (double a, double b, int n)
{
    vector<double> x(n);
    for (int i = 0; i < n; i++)
        x[i] = ((a+b)/2 + ((b - a)/2)*cos(((2*i + 1)*3.14)/(2*n)));
    return x;
}

int main()
{
    ofstream fout("rez2.txt");
    vector <int> amount = {3, 5, 10};
    vector <double> length = {8, 4, 2, 1, 0.5, 0.25, 0.125};
    recvec(amount, fout);
    recvec(length, fout);
    for (int am : amount)
    {
        for (double len : length)
        {
            vector <double> x(am);
            vector <double> y(am);
            for (int i = 0; i < am; i++)
            {
                x[i] = len/(am-1)*i;
                y[i] = func(len/(am-1)*i);
            }
            NewtonianInterpolator I(x, y);
            fout<<error(I, len)<<' ';
            cout<<'['<<len<<']'<<error(I, len)<<endl;
        }
        fout << '\n';
        cout << '\n';
    }
    fout.close();
    ofstream chout("chebpoints.txt");
    for (double len : length)
        {
            vector<double> x(5);
            x = cheb(0, len, 5);
            vector <double> y(5);
            for (int i = 0; i < 5; i++)
            {
                y[i] = func(x[i]);
            }
            NewtonianInterpolator Ch(x, y);
            chout<<error(Ch, len)<<' ';
            cout<<error(Ch, len)<<endl;
        }
    chout << '\n';
    cout << '\n';
    return 0;
}
