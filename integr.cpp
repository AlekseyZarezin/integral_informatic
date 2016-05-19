#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#define CASH 3000

double test(double x)
{
	//return (-1)*x*x + x + sin(x) + exp((-1)*x) + log(x + 3*x*x + 1);
	//return sin(x);
	return x*sin(x);
}

double RectangleMethod(double a, double b, int n)                //ìåòîä ïðÿìîóãîëüíèêîâ
{
	double s = 0, h = (b-a) / (double)n ;
	for (int i = 0 ; i < n-1 ; i++)
		s += test(a + ((double)i + 0.5) * h);
	s +=  test(b - h * 0.5);
	return s * h;
}

double TrapezeMethod(double a, double b, int n)                 //ìåòîä òðàïåöèé
{
	double s = 0, h = (b-a) / (double)n ;
	for (int i = 0 ; i < n-1 ; i++)
		s += (test(a + (double)i * h) + test(a + ((double)i + 1.0) * h)) / 2.0;
	s += (test(b - h) + test(b)) / 2.0;
	return s * h;
}

double ParabolMethod(double a, double b, int n)                 //ìåòîä ïàðàáîë
{
	double s = 0, h = (b-a) / (double)n ;
	for (int i = 0 ; i < n-1 ; i++)
		s += test(a + (double)i * h) + 4.0 * test(a + ((double)i + 0.5) * h) + test(a + ((double)i + 1.0) * h);
	s += test(b - h ) + 4.0 * test(b - h / 2.0) + test(b);
	return s * h / 6.0;
}

double GaussMethod(double a, double b, int n)                    //ìåòîä Ãàóññà
{
	double s = 0, h = (b-a) / (double)n ;
	for (int i = 0 ; i < n-1 ; i++)
		s += (test(a + ((double)i + 0.5) * h - (h / 2.) / sqrt(3)) + test(a + ((double)i + 0.5) * h + (h / 2.) / sqrt(3))) / 2.0;
	s += (test(b - 0.5 * h - (h / 2.) / sqrt(3)) + (test(b - 0.5 * h + (h / 2.) / sqrt(3)))) / 2.0;
	return s * h;
}

double MonteKarloMethod(double a, double b, int n, int N)                    //ìåòîä Ìîíòå-Êàðëî
{
	double min, max, f, h;
	min = 0;                     //ïîèñê ìàêñèìóìà è ìèíèìóìà
	max = 0;
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
	int N, j=0, i=0, l=CASH, n;
	char c, *m;   
	m = (char*)malloc(CASH*sizeof(char));                //ââîä ñòðîêè    
	i=0;
	//c=getchar();
	c = '\n';
	while (c!='\n')
	{
		m[i]=c;
		i++;
		c=getchar();
		if (i+2==l)
		{
			l+=CASH;
			m=(char*)realloc(m, l*sizeof(char));
		}
	}
	m[i]='\0';                                           //ââîä ñòðîêè
	
	//printf("%s\n", m);
	scanf("%d", &n);
	double x;
	scanf("%lf", &x);
	srand(time(NULL));
	printf("%lf RectangleMethod\n", RectangleMethod(0. , x, n));
	printf("%lf TrapezeMethod\n", TrapezeMethod(0. , x, n));
	printf("%lf ParabolMethod\n", ParabolMethod(0. , x, n));
	printf("%lf GaussMethod\n", GaussMethod(0. , x, n));
	printf("%lf MonteKarloMethod\n", MonteKarloMethod(0. , x, n, 1000000));
	system("pause");
	free(m);
	return 0;
}
