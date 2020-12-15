#include<stdio.h>
#include <malloc.h>
#include <conio.h>
#include <stdlib.h>
#include<string.h>
#include<math.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT  10
#define OK 1
#define ERROR 0

int flag1=0;
typedef struct 
{
	char* base;
	char* top;
	int stacksize;
}SqStackchar;
typedef struct 
{
	double* base;
	double* top;
	int stacksize;
}SqStackdouble;
int InitStackchar(SqStackchar& S)
{
	S.base = (char*)malloc(STACK_INIT_SIZE * sizeof(char));
	if (!S.base) return 0;
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
}
int InitStackdouble(SqStackdouble& S)
{
	S.base = (double*)malloc(STACK_INIT_SIZE * sizeof(double));
	if (!S.base) return 0;
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
}

char GetTopchar(SqStackchar S)//操作符顶端元素 
{
	char e;
	if (S.top == S.base)
	{
		printf("ERROR_03");
		return 0;
	}
	e = *(S.top - 1);
	return e;
}
double GetTopdouble(SqStackdouble S)
{
	double e;
	if (S.top == S.base)
	{
		printf("ERROR_03");
		return 0;
	}
	e = *(S.top - 1);
	return e;
}
int Pushchar(SqStackchar& S, char e)
{
	if (S.top - S.base >= S.stacksize)
	{
		S.base = (char*)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(char));
		if (!S.base) return 0;
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*S.top++ = e;
}
int Pushdouble(SqStackdouble& S, double e)
{
	if (S.top - S.base >= S.stacksize)
	{
		S.base = (double*)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(double));
		if (!S.base) return 0;
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*S.top++ = e;
	return OK;
}
int Popchar(SqStackchar& S, char& e){ 
	if (S.top == S.base)
		return ERROR;
	e = *--S.top;
	return OK;
}
int Popdouble(SqStackdouble& S, double& e)
{
	if (S.top == S.base)
		return ERROR;
	e = *--S.top;
	return OK;
}
int In(char c) //是运算数字 
{
	if(c<='9'&&c>='0') return 1;
	else return ERROR;
} 
int isOP(char c) {
	if (c == '+' || c == '-' || c == '*' || c == '/' ||
		c == '(' || c == ')' || c == '#' || c == '^' || c == '[' || c == ']' ||c=='.') {
		return OK;       //是运算符
	}
	else {
		return ERROR;
	}
}
int check(char a[])//判断是否出现字符串的语法错误 
{
	int flag =1;//定义flag判断是否出错 ,flag=0出错 
	SqStackchar S;//初始化字符栈检验括号匹配 
	int i = 0, j = 0;
	char e1 = '0', e2 = '0';
	InitStackchar(S);
	for (i = 0; i < strlen(a); i++)
	{
		e1 = a[i];
		if ((e1 == '(') || (e1 == '['))
			Pushchar(S, e1);//左括号进栈 
		else if ((e1 == ')') || (e1 == ']'))//右括号开始匹配 
			if ((Popchar(S, e2) == ERROR) || (e1 == ')' && e2 != '(') || (e1 == ']' && e2 != '['))
			{
				printf("%s","ERROR_02");
				return 0;
			}
	}
	if (S.base!=S.top)//栈不为空 
	{
		printf("%s","ERROR_02");
		return 0;
	}
	for (i = 0; i < strlen(a)-1; i++)
	{
		if (In(a[i])||isOP(a[i]));
			
		else {
			printf("%s","ERROR_02");
			return 0;
		}
		
	}
	for (i = 0; i+1 <strlen(a); i++)//判断两个运算符相邻的情况 
	{
		if (a[i] <= '/' && a[i]>'*'){
			if (a[i+1] <='/' && a[i+1]>='*')
			{
				printf("%s","ERROR_02");
				return ERROR;
			}
		}
			
	}
	return OK; 
}
char precede(char p, char q)//定义运算符之间的优先关系 
{
	int i = 0, j = 0;
	int comp[7][7] =
	{
		{1,1,-1,-1,-1,1,1},
		{1,1,-1,-1,-1,1,1},
		{1,1,1,1,-1,1,1},
		{1,1,1,1,-1,1,1},
		{-1,-1,-1,-1,-1,0,2},
		{1,1,1,1,2,1,1},
		{-1,-1,-1,-1,-1,2,0}
	};
	switch (p)
	{
	case'+':i = 0;
		break;
	case'-':i = 1;
		break;
	case'*':i = 2;
		break;
	case'^':i = 2;
		break;
	case'/':i = 3;
		break;
	case'(':i = 4;
		break;
	case'[':i = 4;
		break;
	case')':i = 5;
		break;
	case']':i = 5;
		break;
	case'#':i = 6;
		break;
	}
	switch (q)
	{
	case'+':j = 0;
		break;
	case'-':j = 1;
		break;
	case'*':j = 2;
		break;
	case'^':j = 2;
		break;
	case'/':j = 3;
		break;
	case'(':j = 4;
		break;
	case'[':j = 4;
		break;
	case')':j = 5;
		break;
	case']':j = 5;
		break;
	case'#':j = 6;
		break;
	}//1为大于，-1为小于，其他为相等 
	if (comp[i][j] == 1)
		return '>';
	else if (comp[i][j] == -1)
		return '<';
	else
		return '=';
}


double operate(double x, char z, double y)//操作运算 
{
	switch (z)
	{
	case'+':
		return (x + y);
		break;
	case'-':
		return (x - y);
		break;
	case'*':
		return (x * y);
		break;
	case'^':
		return (pow(x, y)); //乘方运算
		break;
	case'/':
		if (y != 0)
			return(x / y);
		else
		{
			flag1=-1;
			return 0;
			
		}
		break;
	}
}
double Evaluate(char str[])
{
	SqStackchar OPTR;//初始化操作符栈 
	InitStackchar(OPTR);
	SqStackdouble OPND;//初始化操作数栈 
	InitStackdouble(OPND);
	Pushchar(OPTR, '#');//在开始时填入’#‘ 
	int i = 0, j = 0, cou = 0;
	double m = 0, x = 0, y = 0;
	char c = '0', s = '0', theta = '0';
	c = str[i];
	while (c != '#' || GetTopchar(OPTR) != '#')//没有读到末尾，和没有运算完全时 
	{
		if (In(c))//是字符数字 
		{
			j = i + 1; 
			if (str[j] == '.')
			{
				m = (str[j + 1] - '0'); //判断数字为小数，并将其转化为小数 
				m = m / 10;
				m = m + str[i] - '0';
				//m = (a[j + 1] - '0') / 10 + (a[i]-'0');
				Pushdouble(OPND, m);
				i = i + 3;
				c = str[i];
			}
			else if (In(str[j]))// 判断为多位小数 
			{
				int m1 = j + 1, n1 = 2;
				m = (str[i] - '0') * 10 + (str[j] - '0');
				while (In(str[m1]))
				{
					n1++;
					m = m * 10 + str[m1] - '0';
					m1++;
				}
				Pushdouble(OPND, m);
				i = i + n1;
				c = str[i];
			}
			else
			{
				m = str[i] - '0'; //只是单个数字 
				Pushdouble(OPND, m);
				i++;
				c = str[i];
			}
		}
		else
			switch (precede(GetTopchar(OPTR), c))//读到了运算字符 
			{
			case'<':
				Pushchar(OPTR, c);
				c = str[++i];
				break;
			case'=':
				Popchar(OPTR, s);
				c = str[++i];
				break;
			case'>':
				Popchar(OPTR, theta);
				Popdouble(OPND, y);
				Popdouble(OPND, x);
				Pushdouble(OPND, operate(x, theta, y));
				break;
			}
	}
	return GetTopdouble(OPND);
}

int main(){
	char str[50];
	gets(str);
	double ans = 0;//结果为ans 
	int  i = 0, j = 0;
	char turn[100] = { '\0' };
	if (!check(str)){//检查是否有语法错误 
		return 0; 
	} 
	for (i = 0; i<strlen(str); i++)
	{
		turn[i]=str[i];
	}
	turn[strlen(str)]='#';
	turn[strlen(str)+1]='\0';
	ans = Evaluate(turn);
	if (flag1==-1){
		printf("%s","ERROR_03");
		return 0;
	}
	else{
		
		printf("%g", ans);//%g可以控制输出的格式 
		return 0;
	}
	
}
/*int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("ERROR_01");
		return 0;
	}//输入多个表达式时报错ERROR_01
	double ans = 0;//结果为ans 
	int  i = 0, j = 0;
	char turn[100] = { '\0' };
	if (!check(argv[1])){//检查是否有语法错误 
		//printf("%s","ERROR_02");
		return 0; 
	} 
	for (i = 0; i<strlen(argv[1]); i++)
	{
		turn[i]=argv[1][i];
	}
	turn[strlen(argv[1])]='#';
	ans = Evaluate(turn);
	if (flag1==-1){
		printf("%s","ERROR_03");
		return 0;
	}
	else{
		printf("%g", ans);//%g可以控制输出的格式 
		return 0;
	}
	
}*/ 
