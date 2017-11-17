/***************************************************************************
 *  @file       EvaluateExpression.cpp
 *  @author     jz
 *  @date       07 Nov. 2015
 *  @remark     数据结构 c语言版 严蔚敏 第三章
 *  @note	栈的应用 表达式求值 算符优先法 
 ***************************************************************************/
//实现用
#include<stdlib.h>
#include<stdio.h>
//测试用

#include "DataStructure.h" //本书需要的一些定义 
//本应一个用char，一个用int 本代码用到了一些隐式char与int的转换

typedef int ElemType; //数据元素的类型

//__BEGIN -----复制自SqStack.cpp----

#define STACK_INIT_SIZE 100 //存储空间初始分配量
#define STACK_INCREMENT 10 //存储空间分配增量

struct SqStack
{
	ElemType * base; //在构造之前和销毁之后，base的值为null
	ElemType * top; //栈顶指针
	int StackSize; //当前已分配的存储空间，以元素为单位
};

Status InitStack (SqStack &S)
//构造一个空栈
{
	S.base=(ElemType *)malloc(STACK_INIT_SIZE*sizeof(ElemType));
	if(!S.base) //存储分配失败
		exit(OVERFLOW);
	S.top=S.base;
	S.StackSize=STACK_INIT_SIZE;
	return OK;
}//InitStack

Status Push(SqStack &S,ElemType e)
//插入元素e为新的栈顶元素
{
	if(S.top-S.base>=S.StackSize)//栈满，追加存储空间
	{
		S.base=(ElemType *)realloc(S.base,(S.StackSize+STACK_INCREMENT)*sizeof(ElemType));
		if(!S.base)  //存储分配失败
			exit(OVERFLOW);
		S.top=S.base+S.StackSize;
		S.StackSize+=STACK_INCREMENT;
	}
	*S.top++=e;
	return OK;
}//Push

Status Pop(SqStack &S,ElemType &e)
//若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK，否则返回ERROR
{
	if(S.top==S.base) //空栈
		return ERROR;
	e=*--S.top;
	return OK;
}//Pop

//自己实现的
Status DestroyStack(SqStack &S)
//销毁栈S，S不再存在
{
	free(S.base);
	S.base=S.top=NULL;
	S.StackSize=0;
	return OK;
}//DestroyStack

//__END -----复制自SqStack.cpp----

//__BEGIN -----复制自Conversion.cpp-----

//自己实现的
Status StackEmpty(SqStack S)
//若栈S为空栈，则返回ture，否则返回false
{
	if(S.top==S.base) //空栈
		return true;
	return false;
}//StackEmpty

//__END -----复制自Conversion.cpp-----

//__BEGIN -----复制自LineEdit.cpp-----

//自己实现的
void ClearStack(SqStack &S)
//把S置为空栈
{
	S.top=S.base;
}//ClearStack

//__END -----复制自LineEdit.cpp-----

//与别处定义不一样
ElemType GetTop(SqStack S)
//若栈不空 则返回S的栈顶元素
{
	if(S.top==S.base) //栈为空
		return ERROR;
	return *(S.top-1);
}//GetTop

//OP为运算符集合
char *OP="+-*/()#";

//自己实现的
bool In(char c,char *op)
//若字符c在字符串op中存在，则返回true，否则返回false
{
	while(*op)
	{
		if(c==*op)
			return true;
		op++;
	}
	return false;
}//In

//自己实现的
int Operate(int a,char theta,int b)
{
	//从ASCII码转换到数值
	a=a-48;
	b=b-48;
	switch(theta)
	{
		case'+':
			return a+b;
		case'-':
			return a-b;
		case'*':
			return a*b;
		case '/':
			return a/b;
		default:
			exit(EXIT_FAILURE);
	}//switch
}//Operate

char Precede(char a,char b)
//返回a,b 算符之间的优先关系
{
	if(!In(a,OP))
		exit(EXIT_FAILURE);
	if(!In(b,OP))
		exit(EXIT_FAILURE);
	if(a=='('&&b==')'||a=='#'&&b=='#')
		return '=';
	if(a=='('||a=='#'||b=='(')
		return '<';
	if(a==')'||b=='#'||b==')')
		return '>';
	if(b=='+'||b=='-')
		return '>';
	if(a=='+'||a=='-')
		return '<';
	return '>';
}//Precede

int EvaluateExpression()
//算术表达式求值的算符优先算法，输入的表达式为中操作数为10以下整数
{
	SqStack OPTR,OPND;
	InitStack(OPTR); //OPTR位运算符栈
	Push(OPTR,'#');
	InitStack(OPND); //OPND为操作数栈
	int theta,c=getchar();
	int a,b;
	while(c!='#'||GetTop(OPTR)!='#')
	{
		if(!In(c,OP)) //不是运算符则进栈
		{
			Push(OPND,c);
			c=getchar();
		}
		else
			switch (Precede(GetTop(OPTR),c))
			{
				case '<': //栈顶元素优先权低
					Push(OPTR,c);
					c=getchar();
					break;
				case'=': //脱括号并接收下一个字符
					Pop(OPTR,c);
					c=getchar();
					break;
				case'>': //退栈并将结果入栈
					Pop(OPTR,theta);
					Pop(OPND,b);
					Pop(OPND,a);
					//48作为ascii和int的转换
					Push(OPND,48+Operate(a,theta,b)); 
					break;
			}//switch
	}//while
	int ret=GetTop(OPND)-48;
	DestroyStack(OPTR);
	DestroyStack(OPND);
	return ret;
}//EvaluateExpression

//main函数做测试用
int main()
{
	printf("%d",EvaluateExpression());
	return 0;
}
