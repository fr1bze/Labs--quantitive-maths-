#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

double func(double x)
{
    double y = cos(x);
    return y;
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
	splines[0].c = 0;
    splines[N - 1].c = 0;

    double matA[N][N];
    double matB[N];
    double x[N];
    for (int i = 0; i < N; i++)
        x[i] = xArr[i];
    cout<<N<<": ";
    for (int i = 0; i < N; i++)
        cout<<x[i]<<' ';
    cout<<endl;

    for (int i = 1; i < N; i++)
        matB[i-1] = 6 * ((func(x[i+1]) - func(x[i]))/(x[i+1] - x[i]) - (func(x[i]) - func(x[i-1]))/(x[i] - x[i-1]))/(x[i+1] - x[i-1]);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            matA[i][j] = 0;

    for (int i = 0; i < N; i++)
        matA[i][i] = 2;
    for (int i = 2; i <= N; i++)
        matA[i-1][i-2] = (x[i-1] - x[i-2])/(x[i] - x[i-2]);
    for (int i = 2; i <= N; i++)
        matA[i-2][i-1] = (x[i] - x[i-1])/(x[i] - x[i-2]);

    double y, a[N], B[N], matRes[N];
    y = matA[0][0];
    a[0] = -matA[0][1] / y;
    B[0] = matB[0] / y  ;
    for (int i = 1; i < N - 1; i++)
    {
        y = matA[i][i] + matA[i][i - 1] * a[i - 1];
        a[i] = -matA[i][i + 1] / y;
        B[i] = (matB[i] - matA[i][i - 1] * B[i - 1]) / y;
    }
    matRes[N - 1] = (matB[N - 1] - matA[N - 1][N - 2] * B[N - 2]) / (matA[N - 1][N - 1] + matA[N - 1][N - 2] * a[N - 2]);
    for (int i = N - 2; i >= 0; i--)
    {
        matRes[i] = a[i] * matRes[i + 1] + B[i];
    }

	for (int i = 1; i < N - 1; i++)
		splines[i].c = matRes[i];

    for (int i = N - 1; i > 0; --i)
	{
        splines[i].d = (splines[i].c - splines[i-1].c)/(xArr[i] - xArr[i-1]);
        splines[i].b = splines[i].c*(xArr[i] - xArr[i-1])/3 + splines[i-1].c/6*(xArr[i] - xArr[i-1]) + (yArr[i] - yArr[i-1])/(xArr[i] - xArr[i-1]);
    }
}

 double CubicSpline::interpolate(double x) const
{
	spline_struct *s;
	for (int i = 0; i < N; i++)
    {
        if (x <= splines[0].x)
        {
            s = &splines[0];
            break;
        }
        else if (x >= splines[N - 1].x)
        {
            s = &splines[N - 1];
            break;
        }
		else if ((x > splines[i].x) && (x <= splines[i+1].x))
        {
            s = &splines[i+1];
            break;
        }
    }

	double dx = (x - s->x);
	return s->a + s->b * dx + s->c * dx * dx / 2 + s->d * dx * dx* dx / 6;
	delete[] s;
}

int main()
{
    ofstream fout("data3.txt");
    int a = 0, b = 3;
    int am[] = {2, 4, 8, 16, 32, 64, 128};
    double am1[] = {2, 4, 8, 16, 32, 64, 128};
    for (int k = 0; k < 7; k++)
    {
        double x[am[k]];
        double y[am[k]];
        for (int i = 0; i < am[k]; i++)
        {
            x[i] = 3./(am1[k]-1)*i;
            y[i] = func(x[i]);
        }
        CubicSpline spline(x,y,am[k]);
        for (int i = 0; i < 1000; i++)
        {
            double x_0 = 3./999.*i;
            fout<<std::setprecision(16)<<spline.interpolate(x_0)<<' ';
        }
        fout << '\n';
    }
    for (int i = 0; i < 1000; i++) {
    double x_0 = 3./999.*i;
        fout <<std::setprecision(16) << std::cos(x_0) << ' ';
    }
    fout.close();
    return 0;
}
