/***************************************************************************
 *  @file       LineEdit.cpp
 *  @author     jz
 *  @date       07 Nov. 2015
 *  @remark     数据结构 c语言版 严蔚敏 第三章
 *  @note	栈的应用 行编辑程序
 ***************************************************************************/
//实现用
#include<stdlib.h>
#include<stdio.h>
//测试用

#include "DataStructure.h" //本书需要的一些定义

typedef char ElemType; //数据元素的类型

//__BEGIN -----复制自SqStack.cpp-----

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

Status GetTop(SqStack S,ElemType &e)
//若栈不空 则返回e的栈顶元素
{
	if(S.top==S.base) //栈为空
		return ERROR;
	e=*(S.top-1);
	return OK;
}//GetTop

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

//__END -----复制自SqStack.cpp-----

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

//自己实现的
void ClearStack(SqStack &S)
//把S置为空栈
{
	S.top=S.base;
}//ClearStack

void LineEdit()
//利用字符栈S，从终端接收一行并传送至调用过程的数据区
{
	SqStack S;
	InitStack(S); //构造空栈S
	char c,ch=getchar(); //从终端接收第一个字符
	while(ch!=EOF) //EOF为全文结束符
	{
		while(ch!=EOF&&ch!='\n')
		{
			switch(ch)
			{
				case'#':
					Pop(S,c); //仅当栈非空时退栈
					break;
				case'@':
					ClearStack(S); //重置S为空栈
					break;
				default:
					Push(S,ch); //有效字符进栈
					break;
			}//switch
			ch=getchar();
		}//while
		//将从栈底到栈顶的栈内字符传送至调用过程的数据区
		puts("刚输入的一行为：(倒序)");
		while(!StackEmpty(S))
		{
			Pop(S,c);
			putchar(c);
		}
		putchar('\n');

		ClearStack(S); //重置S为空栈
		if(ch!=EOF)
			ch=getchar();
	
	}//while
	DestroyStack(S);
}//LineEdit

//main函数做测试用
int main()
{
	LineEdit();
	return 0;
}
