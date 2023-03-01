#include <cstdlib>
#include <cmath>
#include <limits>
#include <vector>
#include <iostream>

class cubic_spline
{
private:
	// Структура, описывающая сплайн на каждом сегменте сетки
	struct spline_tuple
	{
		double a, b, c, d, x;
	};

	spline_tuple *splines; // Сплайн
	std::size_t n; // Количество узлов сетки

	void free_mem(); // Освобождение памяти

public:
	cubic_spline(); //конструктор
	~cubic_spline(); //деструктор

	// Построение сплайна
	// x - узлы сетки, должны быть упорядочены по возрастанию, кратные узлы запрещены
	// y - значения функции в узлах сетки
	// n - количество узлов сетки
	void build_spline(const double *x, const double *y, std::size_t n);

	// Вычисление значения интерполированной функции в произвольной точке
	double f(double x) const;
};

cubic_spline::cubic_spline() : splines(NULL)
{

}

cubic_spline::~cubic_spline()
{
	free_mem();
}

void cubic_spline::build_spline(const double *x, const double *y, std::size_t n)
{
	free_mem();

	this->n = n;

	// Инициализация массива сплайнов
	splines = new spline_tuple[n];
	for (std::size_t i = 0; i < n; ++i)
	{
		splines[i].x = x[i];
		splines[i].a = y[i];
	}
	splines[0].c = 0.;
	splines[n-1].c = 0;

	// Решение СЛАУ относительно коэффициентов сплайнов c[i] методом прогонки для трехдиагональных матриц
	// Вычисление прогоночных коэффициентов - прямой ход метода прогонки
	double *alpha = new double[n - 1];
	double *beta = new double[n - 1];
	double A, B, C, F, h_i, h_i1, z;
	alpha[0] = beta[0] = 0.;
	for (std::size_t i = 1; i < n - 1; ++i)
	{
		h_i = x[i] - x[i - 1], h_i1 = x[i + 1] - x[i];
		A = h_i;
		C = 2. * (h_i + h_i1);
		B = h_i1;
		F = 6. * ((y[i + 1] - y[i]) / h_i1 - (y[i] - y[i - 1]) / h_i);
		z = (A * alpha[i - 1] + C);
		alpha[i] = -B / z;
		beta[i] = (F - A * beta[i - 1]) / z;
	}

	splines[n - 1].c = (F - A * beta[n - 2]) / (C + A * alpha[n - 2]);

	// Нахождение решения - обратный ход метода прогонки
	for (std::size_t i = n - 2; i > 0; --i)
		splines[i].c = alpha[i] * splines[i + 1].c + beta[i];

	// Освобождение памяти, занимаемой прогоночными коэффициентами
	delete[] beta;
	delete[] alpha;

	// По известным коэффициентам c[i] находим значения b[i] и d[i]
	for (std::size_t i = n - 1; i > 0; --i)
	{
		double h_i = x[i] - x[i - 1];
		splines[i].d = (splines[i].c - splines[i - 1].c) / h_i;
		splines[i].b = h_i * (2. * splines[i].c + splines[i - 1].c) / 6. + (y[i] - y[i - 1]) / h_i;
	}
}

double cubic_spline::f(double x) const
{
	spline_tuple *s;
	if (x <= splines[0].x) // Если x меньше точки сетки x[0] - пользуемся первым эл-том массива
		s = splines + 1;
	else if (x >= splines[n - 1].x) // Если x больше точки сетки x[n - 1] - пользуемся последним эл-том массива
		s = splines + n - 1;
	else // Иначе x лежит между граничными точками сетки - производим бинарный поиск нужного эл-та массива
	{
		int index = 0;
		for (int i = 0; i < n; i ++) {
		if (x < splines[i].x)
			{
			index = i;
			}
		else if (x >= splines[i].x)
		{	
			index = i+1;
		}
		}

	}

	double dx = (x - s->x);
	return s->a + (s->b + (s->c / 2. + s->d * dx / 6.) * dx) * dx; // Вычисляем значение сплайна в заданной точке.
}

void cubic_spline::free_mem()
{
	delete[] splines;
	splines = NULL;
}


int main()
{
    int a = 0, b = 3;
    int num = 4;
    double x[] = {b/2,2*b/4,3*b/8,4*b/8};
    double y[] = {cos(x[0]), cos(x[1]),cos(x[2]),cos(x[3])};
    cubic_spline spline;
	spline.build_spline(x,y,num);
	for (int i = 0; i < 4; i ++) {
    std::cout << "Сплайн " << spline.f(x[i]) << std::endl;
	std::cout << "Функция " << y[i] << std::endl;
	std::cout << "\n" << std::endl;
	}
}