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

struct node                            //создание дерева операций
{
	char f, ch, op, *str;
	double z;
	node * left, * right;
};

struct tree
{
    node * root;
    void   init()
    {
        root = NULL;
    }
    void add(char *s,  int N, node ** n)                        //добавление элемента
    {
        if ((*n) == NULL)
        {
            node *n1=(node *)malloc(sizeof(node));
            
            n1->data=data;
            n1->left=NULL;
            n1->right=NULL;
            (*n)=n1;
        }
        else
        {
        	if (data>=(*n)->data)
        		add(data, &((*n)->right));
        	else
        		add(data, &((*n)->left));      
        }     
    }
	void clean(node ** n)                                //очистка памяти
	{
		if ((*n)!=NULL)
		{
			clean(&(*n)->left);
			clean(&(*n)->right);
			free(*n);
			if ((*n)==root)
				(*n)=NULL;
		}
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
	while (s[i]!='\n')
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
	m[i]='\0';	                                           
	length = i;
	
	
	tree T;
    T.init();
    
	printf("%s\n", m);
	system("pause");
	free(m);
	return 0;
}
