/***************************************************************************
 *  @file       SqQueue.cpp
 *  @author     jz
 *  @date       01 Dec. 2015
 *  @remark     数据结构 c语言版 严蔚敏 第三章
 *  @note	循环队列 队列的顺序存储结构
 ***************************************************************************/
//实现用
#include<stdlib.h>
//测试用
#include<stdio.h>

#include "DataStructure.h" //本书需要的一些定义

typedef int ElemType; //数据元素的类型，测试用，可更改

#define MAXQSIZE 100 //最大队列长度

struct SqQueue
{
	ElemType *base; //初始化的动态分配存储空间
	int front; //头指针，若队列不空，则指向队头元素
	int rear; //尾指针，若队列不空，则指向队列尾元素的下一位置
};

Status InitQueue(SqQueue &Q)
//构造一个空队列Q
{
	Q.base=(ElemType *)malloc(MAXQSIZE*sizeof(ElemType));
	if(!Q.base) //存储分配失败
		exit(OVERFLOW);
	Q.front=Q.rear=0;
	return OK;
}//InitQueue

int QueueLength(SqQueue Q)
//返回Q中的元素个数，即队列的长度
{
	return (Q.rear-Q.front+MAXQSIZE)%MAXQSIZE;
}//QueueLength

Status EnQueue(SqQueue &Q,ElemType e)
//插入元素e为Q的新的队尾元素
{
	if((Q.rear+1)%MAXQSIZE==Q.front) //队列满
		return ERROR;
	Q.base[Q.rear]=e;
	Q.rear=(Q.rear+1)%MAXQSIZE;
	return OK;
}//EnQueue

Status DeQueue(SqQueue &Q,ElemType &e)
//若队列不空，则删除Q的队头元素，用e返回其值，并返回OK
//否则返回ERROR
{
	if(Q.front==Q.rear) //队列空
		return ERROR;
	e=Q.base[Q.front];
	Q.front=(Q.front+1)%MAXQSIZE;
	return OK;
}//DeQueue

//main函数做测试用
int main()
{
	SqQueue q1;
	InitQueue(q1);
	for(int i=0;i<=75;i++)
		EnQueue(q1,i);
	int temp;
	for(int i=0;i<=50;i++)
	{
		DeQueue(q1,temp);
		printf("%d ",temp);
	}
	putchar('\n');
	for(int i=0;i<=50;i++)
		EnQueue(q1,75+i);
	for(int i=0;i<=75;i++)
	{
		DeQueue(q1,temp);
		printf("%d ",temp);
	}
	return 0;
}
