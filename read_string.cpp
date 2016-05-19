#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define CASH 30

int main(void)
{
	int N, j=0, i=0, l=CASH, n;
	char c, *m;   
	m = (char*)malloc(CASH*sizeof(char));                //ввод строки    
	i=0;
	c=getchar();
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
	m[i]='\0';	                                           //ввод строки
	int length = i;
	
	printf("%s\n", m);
	system("pause");
	free(m);
	return 0;
}
