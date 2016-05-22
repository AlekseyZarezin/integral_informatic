#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#define CASH 30

char *str;                        //указатель на строку с формулой
int L;                           //длина строки

struct node1                            //для проверки корректности скобок
{
    char data;
    node1 * next;
};

struct stechscob                             
{
    node1 * head;
    void   init(){head = NULL;}
    char push(char data)
    {        
        if (deep()>0&&(data==')'))
        {
        	if (data==')'&&head->data=='(')
        	{
				pop();
				return 1;
			}
			else
				return 0;
		}
        else
		{  
			node1 *n=(node1 *)malloc(sizeof(node1));  	
        	n->data=data;
        	n->next=head;    
        	head = n; 
        	return 1;
		}
    }
    void pop()
    {
        node1 *h=head;
        head=head->next;
        free(h);
    }
    int deep()
    {
        int i=0;
        node1 *h=head;
        while (h!=NULL)
        {
            i++;
            h=h->next;
        }
        return i;
    }
    void clean()                  //очистка памяти
    {
    	while (deep()!=0)
    	{
    		node1 *h=head;
        	head=head->next;
        	free(h);
		}
		head = NULL;
	}
};

double funct(char *s, int n, double x)
{
	if (s[0]=='x')                                                                                                //x
	{
		if (n==1)
			return x;
		else 
		{
			switch(s[1])
			{
				case '+':
					return x + funct(s+2, n-2, x);
					break;
				case '-':
					return x - funct(s+2, n-2, x);
					break;
				case '*':
					return x * funct(s+2, n-2, x);
					break;
				case '/':
					return x / funct(s+2, n-2, x);
					break;
				case '^':
					return pow(x, funct(s+2, n-2, x));
					break;
				default : 
					return 1.0;
				}
		}
	}
	if ((s[0]=='0')||(s[0]=='1')||(s[0]=='2')||(s[0]=='3')||(s[0]=='4')||(s[0]=='5')||(s[0]=='6')||(s[0]=='7')||(s[0]=='8')||(s[0]=='9'))               //число
	{
		double z=(double)(s[0]-'0');
		double k=10.0;
		int j=1, l=0;
		while ((s[j]=='0')||(s[j]=='1')||(s[j]=='2')||(s[j]=='3')||(s[j]=='4')||(s[j]=='5')||(s[j]=='6')||(s[j]=='7')||(s[j]=='8')||(s[j]=='9')||(s[j]=='.'))
		{
			if (s[j]!='.')
			{
				z=z*k + (double)(s[j]-'0');
			}
			else
			{
				l=j;
			}
			j++;			
		}
		z/=pow(10.0, (double)(j-l-1));
		if (n==j)
			return z;
		else 
		{
			switch(s[j])
			{
				case '+':
					return z + funct(s+j+1, n-j-1, x);
					break;
				case '-':
					return z - funct(s+j+1, n-j-1, x);
					break;
				case '*':
					return z * funct(s+j+1, n-j-1, x);
					break;
				case '/':
					return z / funct(s+j+1, n-j-1, x);
					break;
				case '^':
					return pow(z, funct(s+j+1, n-j-1, x));
					break;
				default : 
					return 1.0;
			}
		}
	}
	if (s[0]=='(')                                              //  ()
	{
		int j=1, i;
		for (i=1;j!=0;i++)
		{
			if (s[i]=='(')
			{
				++j;
			}
			if (s[i]==')')
			{
				--j;
			}
		}
		if (n==i)
			return funct(s+1,n-2,x);
		else 
		{
			switch(s[i])
			{
				case '+':
					return funct(s+1, i-2, x) + funct(s+i+1, n-i-1, x);
					break;
				case '-':
					return funct(s+1, i-2, x) - funct(s+i+1, n-i-1, x);
					break;
				case '*':
					return funct(s+1, i-2, x) * funct(s+i+1, n-i-1, x);
					break;
				case '/':
					return funct(s+1, i-2, x) / funct(s+i+1, n-i-1, x);
					break;
				case '^':
					return pow(funct(s+1, i-2, x), funct(s+i+1, n-i-1, x));
					break;
				default : 
					return 1.0;
			}
		}
	}
}

double test(double x)
{
	return funct(str, L, x);
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
	int j=0, i=0, l=CASH, n;
	char c, *s;   
	s = (char*)malloc(CASH*sizeof(char));                //ввод строки    
	i=0;
	c=getchar();
	while (c!='\n')
	{
		s[i]=c;
		i++;
		c=getchar();
		if (i+2==l)
		{
			l+=CASH;
			s=(char*)realloc(s, l*sizeof(char));
		}
	}
	s[i]='\0';	                                           
	int length = i;	
	
	stechscob st;                              //проверка на корректность
    st.init();
    char f=1;
	for (int i=0; i<length; i++)
	{
		if (((s[i])=='(')||((s[i])==')'))
			if (!st.push(s[i]))
			{
				f=0;
				break;
			}
	}
	if (st.deep()>0)
		f=0;
	if (f)
		printf("correct\n");
	else
		printf("error\n");
	st.clean();
	
	if (f)
	{
		i=0;                                           //удаление пробелов
		j=0;
		l=CASH;
		char *m = (char*)malloc(CASH*sizeof(char)); 
		while (s[i]!='\0')
		{
			if (s[i]!=' ')
			{
				m[j]=s[i];
				j++;
				if (j+2==l)
				{
					l+=CASH;
					m=(char*)realloc(m, l*sizeof(char));
				}	
			}
			i++;
		}
		m[j]='\0';	                                           
		L=j;
		str=m;	
		
		free(m);	
	}

	free(s);
	system("pause");
	return 0;
}
