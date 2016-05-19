#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#define CASH 30

double test(double x)
{
	//return (-1)*x*x + x + sin(x) + exp((-1)*x) + log(x + 3*x*x + 1);
	//return sin(x);
	return x*sin(x);
}

double RectangleMethod(double a, double b, int n)                //метод прямоугольников
{
	double s = 0, h = (b-a) / (double)n ;
	for (int i = 0 ; i < n-1 ; i++)
		s += test(a + ((double)i + 0.5) * h);
	s +=  test(b - h * 0.5);
	return s * h;
}

double TrapezeMethod(double a, double b, int n)                 //метод трапеций
{
	double s = 0, h = (b-a) / (double)n ;
	for (int i = 0 ; i < n-1 ; i++)
		s += (test(a + (double)i * h) + test(a + ((double)i + 1.0) * h)) / 2.0;
	s += (test(b - h) + test(b)) / 2.0;
	return s * h;
}

double ParabolMethod(double a, double b, int n)                 //метод парабол
{
	double s = 0, h = (b-a) / (double)n ;
	for (int i = 0 ; i < n-1 ; i++)
		s += test(a + (double)i * h) + 4.0 * test(a + ((double)i + 0.5) * h) + test(a + ((double)i + 1.0) * h);
	s += test(b - h ) + 4.0 * test(b - h / 2.0) + test(b);
	return s * h / 6.0;
}

double GaussMethod(double a, double b, int n)                    //метод Гаусса
{
	double s = 0, h = (b-a) / (double)n ;
	for (int i = 0 ; i < n-1 ; i++)
		s += (test(a + ((double)i + 0.5) * h - (h / 2.) / sqrt(3)) + test(a + ((double)i + 0.5) * h + (h / 2.) / sqrt(3))) / 2.0;
	s += (test(b - 0.5 * h - (h / 2.) / sqrt(3)) + (test(b - 0.5 * h + (h / 2.) / sqrt(3)))) / 2.0;
	return s * h;
}

double MonteKarloMethod(double a, double b, int n)                    //метод Монте-Карло
{
	double min, max, f, h;
	min = 0;                     //поиск максимума и минимума
	max = 0;
	int N = 1000000 * (int)(b - a);
	h = (b - a) / N;                       
	for (int i = 0 ; i < N ; i++)
	{
		f = test(a + (double)i * h);
		if (max < f)
			max = f;
		if (min > f)
			min = f;
	}
	f = test(b);
	if (max < f)
		max = f;
	if (min > f)
		min = f;  		                      
	//printf("max %lf  min %lf\n", max, min);
	
	srand(time(NULL));
	int k = 0;
	double x, y;
	for (int i = 0; i < n; i++)
	{
		x = (rand() / (double)RAND_MAX) * (b - a) + a;
		y = (rand() / (double)RAND_MAX) * (max - min) + min;
		f = test(x);
		if (f >= 0)
		{
				if ((y <= f)&&(y >= 0))
					k++;
		}
		else
		{
			if ((y >= f)&&(y <= 0))
				k--;
		}			
	}	
	return ((double)k / (double)n) * (b - a) * (max - min);
}

int main(void)
{
	int n;
	
	//printf("%s\n", m);
	scanf("%d", &n);
	double x;
	scanf("%lf", &x);
	srand(time(NULL));
	printf("%.13lf RectangleMethod\n", RectangleMethod(0. , x, n));
	printf("%.13lf TrapezeMethod\n", TrapezeMethod(0. , x, n));
	printf("%.13lf ParabolMethod\n", ParabolMethod(0. , x, n));
	printf("%.13lf GaussMethod\n", GaussMethod(0. , x, n));
	printf("%.13lf MonteKarloMethod\n", MonteKarloMethod(0. , x, n));
	system("pause");
	return 0;
}
