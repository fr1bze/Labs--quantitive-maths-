#include <cmath>
#include <iostream>
#include <vector>


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

    double alpha[N];
	double beta[N];
	double C, F, z;
	alpha[0] = beta[0] = 0;
	for (int i = 1; i < N - 1; ++i)
	{
		C = 2 * (xArr[i] - xArr[i - 1] + xArr[i + 1] - xArr[i]);
		F = 6 * ((yArr[i + 1] - yArr[i]) / (xArr[i + 1] - xArr[i]) - (yArr[i] - yArr[i - 1]) / (xArr[i] - xArr[i - 1]));
		z = ((xArr[i] - xArr[i - 1]) * alpha[i - 1] + C);
		alpha[i] = -(xArr[i + 1] - xArr[i]) / z;
		beta[i] = (F - (xArr[i] - xArr[i - 1]) * beta[i - 1]) / z;
	}

	splines[N - 1].c = (F -  (xArr[N-2] - xArr[N-3])* beta[N - 2]) / (C + (xArr[N-2] - xArr[N-3]) * alpha[N - 2]);


	for (int i = N - 2; i > 0; --i)
		splines[i].c = alpha[i] * splines[i + 1].c + beta[i];

    for (int i = N - 1; i > 0; --i)
	{
        splines[i].d = (splines[i].c - splines[i-1].c)/(xArr[i] - xArr[i-1]);
        splines[i].b = splines[i].c*(xArr[i] - xArr[i-1])/3 + splines[i-1].c/6*(xArr[i] - xArr[i-1]) + (yArr[i] - yArr[i-1])/(xArr[i] - xArr[i-1]);
    }
	splines[N-1].c = 0;
}

 double CubicSpline::interpolate(double x) const
{

	spline_struct *s;
	if (x <= splines[0].x) 
		s = splines + 1;
	else if (x >= splines[N - 1].x) 
		s = splines + N - 1;
	else 
	{
		std::size_t i = 0, j = N - 1;
		while (i + 1 < j)
		{
			std::size_t index = i + (j - i) / 2;
			if (x <= splines[index].x)
				j = index;
			else
				i = index;
		}
		s = splines + j;
	}

	double dx = (x - s->x);
	return s->a + s->b * dx + s->c * dx * dx / 2 + s->d * dx * dx* dx / 6;
	delete[] s;
}

double fun(double x)
{
	return cos(x);
}

int main()
{
    int a = 0, b = 3;
	std::cout <<"Функция " << cos(M_PI/2) << std::endl;
    int num = 4;
    double x[] = {1,M_PI/2,M_PI/4, M_PI/8};
    double y[] = {cos(x[0]), cos(x[1]),cos(x[2]),cos(x[3])};
    CubicSpline spline(x,y,num);
    std::cout << "Сплайн " << spline.interpolate(M_PI/2) << std::endl;
}