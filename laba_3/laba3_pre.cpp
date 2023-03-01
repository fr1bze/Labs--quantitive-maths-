#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

double func(double x)
{

    double y = std::cos(x);
    return y;
}

double func2(double x)
{
    if (x <= 1.5)
        return -x+1.5;
    else
        return x-1.5;
}

class CubicSpline
{
private:
	struct spline_struct
	{
		double a, b, c, d, x;
	};
	spline_struct *splines;
	std::size_t N;


public:
	explicit CubicSpline(const double *xArr, const double *yArr,int N);
	~CubicSpline();
	double interpolate(double x) const;
    double* get_spline()
    {   
        double mas[4];
        mas[0] = this->splines->a;
        mas[1] = this->splines->b;
        mas[2] = this->splines->c;
        mas[3] = this->splines->d;
        return mas;
    }
};


CubicSpline::~CubicSpline()
{
	delete[] splines;
}

CubicSpline::CubicSpline(const double *xArr, const double *yArr, int N)
{
	this->N = N;
	splines = new spline_struct[N];
	for (std::size_t i = 0; i < N; ++i)
	{
		splines[i].x = xArr[i];
		splines[i].a = yArr[i];
	}

    double matA[N-2][N-2];
    double matB[N-2];
    double x[N];
    for (int i = 0; i < N; i++)
        x[i] = xArr[i];

    for (int i = 0; i < N - 2; i++)
        for (int j = 0; j < N - 2; j++)
            matA[i][j] = 0;

    for (int i = 0; i < N - 2; i++)
        matA[i][i] = 2;
    for (int i = 1; i < N - 1; i++)
        matA[i-1][i-2] = (x[i] - x[i-1])/(x[i+1] - x[i-1]);
    for (int i = 1; i < N - 1; i++)
        matA[i-2][i-1] = (x[i+1] - x[i])/(x[i+1] - x[i-1]);

    for (int i = 1; i < N - 1; i++)
        matB[i-1] = 6 * ((yArr[i+1] - yArr[i])/(x[i+1] - x[i]) - (yArr[i] - yArr[i-1])/(x[i] - x[i-1]))/(x[i+1] - x[i-1]);

    double y, a[N-2], B[N-2], matRes[N-2];
    y = matA[0][0];
    a[0] = -matA[0][1] / y;
    B[0] = matB[0] / y  ;
    for (int i = 1; i < N - 3; i++)
    {
        y = matA[i][i] + matA[i][i - 1] * a[i - 1];
        a[i] = -matA[i][i + 1] / y;
        B[i] = (matB[i] - matA[i][i - 1] * B[i - 1]) / y;
    }
    matRes[N - 3] = (matB[N - 3] - matA[N - 3][N - 4] * B[N - 4]) / (matA[N - 3][N - 3] + matA[N - 3][N - 4] * a[N - 4]);
    for (int i = N - 4; i >= 0; i--)
    {
        matRes[i] = a[i] * matRes[i + 1] + B[i];
    }

	for (int i = 0; i < N - 2; i++)
		splines[i + 1].c = matRes[i];

    splines[0].b = 0;
    splines[0].c = 0;
    splines[0].d = 0;
    splines[N - 1].c = 0;

    for (int i = 1; i < N; i++)
	{
        splines[i].d = (splines[i].c - splines[i-1].c)/(splines[i].x - splines[i-1].x);
        splines[i].b = splines[i].c*(splines[i].x - splines[i-1].x)/3 + splines[i-1].c*(splines[i].x - splines[i-1].x)/6 + (splines[i].a - splines[i-1].a)/(splines[i].x - splines[i-1].x);
        //std::cout<<N<<": "<<splines[i].c<<" "<<splines[i].d<<std::endl;
    }
}

 double CubicSpline::interpolate(double x) const
{
	int s = 0;
    if (x == splines[0].x)
    {
        s = 0;
    }
	for (int i = 1; i < N; i++)
	{
        if ((x > splines[i-1].x) && (x <= splines[i].x))
        {
            s = i;
            break;
        }
	}

	double dx = x - splines[s].x;
	double I;
	I = splines[s].a + splines[s].b * dx + (splines[s].c * dx * dx )/ 2 + (splines[s].d * dx * dx* dx )/ 6 ;
	//std::cout<<N<<": "<<splines[s].a<<" "<<splines[s].b<<" "<<splines[s].c<<" "<<splines[s].d<<std::endl;
	return I;
}

int main()
{
    // std::ofstream fout("data3.txt");
    // int a = 0, b = 3;
    // int am[] = {2, 4, 8, 16, 32, 64, 128};
    // double am1[] = {2, 4, 8, 16, 32, 64, 128};
    // for (int k = 0; k < 7; k++)
    // {
    //     double x[am[k]];
    //     double y[am[k]];
    //     for (int i = 0; i < am[k]; i++)
    //     {
    //         x[i] = 3./(am1[k]-1)*i;
    //         y[i] = func(x[i]);
    //     }
    //     CubicSpline spline(x,y,am[k]);
    //     for (int i = 0; i < 1000; i++)
    //     {
    //         double x_0 = 3./999.*i;
    //         fout<<std::setprecision(16)<<spline.interpolate(x_0)<<' ';
    //     }
    //     fout << '\n';
    // }
    // fout.close();
     int N = 4;
    double x[4] = {0,1,2,3};
    double y[4] = {1,2,3,4};
    int a = 0, b = 3;
    CubicSpline spline(x,y,N);
    for (int i = 0; i < 4;i++)
       std::cout << spline.get_spline()[i] << " ";
    return 0;
}
