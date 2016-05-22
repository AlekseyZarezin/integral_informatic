#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define CASH 30

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
					return funct(s+1, i-2, x) + funct(s+2, n-2, x);
					break;
				case '-':
					return funct(s+1, i-2, x) - funct(s+2, n-2, x);
					break;
				case '*':
					return funct(s+1, i-2, x) * funct(s+2, n-2, x);
					break;
				case '/':
					return funct(s+1, i-2, x) / funct(s+2, n-2, x);
					break;
				case '^':
					return pow(funct(s+1, i-2, x), funct(s+2, n-2, x));
					break;
				default : 
					return 1.0;
			}
		}
	}
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
	//printf("length %d\n", length);
	
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
	free(s);
	m[j]='\0';	                                           
	length = j;
		
	double x=funct(m, length, 1.0);
    
	printf("%s\n", m);
	//printf("length %d\n", length);
	printf("%lf\n", x);
	system("pause");
	free(m);
	return 0;
}
