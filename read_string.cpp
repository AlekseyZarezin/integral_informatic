#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define CASH 30

struct node
{
    char data;
    node * next;
};

struct stech
{
    node * head;
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
			node *n=(node *)malloc(sizeof(node));  	
        	n->data=data;
        	n->next=head;    
        	head = n; 
        	return 1;
		}
    }
    void pop()
    {
        node *h=head;
        head=(*head).next;
        free(h);
    }
    int deep()
    {
        int i=0;
        node *h=head;
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
    		node *h=head;
        	head=head->next;
        	free(h);
		}
		head = NULL;
	}
};

int main(void)
{
	int N, j=0, i=0, l=CASH, n;
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
	stech st;                              //проверка на корректность
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
		printf("yes\n");
	else
		printf("no\n");
	st.clean();
	
	//printf("%s\n", s);
	system("pause");
	free(s);
	return 0;
}
