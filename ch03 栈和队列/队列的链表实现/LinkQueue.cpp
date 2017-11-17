/***************************************************************************
 *  @file       LinkQueue.cpp
 *  @author     jz
 *  @date       01 Dec. 2015
 *  @remark     数据结构 c语言版 严蔚敏 第三章
 *  @note	队列的链表表示与实现
 ***************************************************************************/
//实现用
#include<stdlib.h>
//测试用
#include<stdio.h>

#include "DataStructure.h" //本书需要的一些定义

typedef int ElemType; //数据元素的类型，测试用，可更改

struct QNode
{
	ElemType data;
	struct QNode * next;
};

typedef QNode * QueuePtr;

struct LinkQueue
{
	QueuePtr front; //队头指针
	QueuePtr rear; //队尾指针
};

Status InitQueue(LinkQueue &Q)
//构造一个空队列Q
{
	Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode));
	if(!Q.front) //存储分配失败
		exit(OVERFLOW);
	Q.front->next=NULL;
	return OK;
}//InitQueue

Status DestroyQueue(LinkQueue &Q)
//销毁队列Q
{
	while(Q.front)
	{
		Q.rear=Q.front->next;
		free(Q.front);
		Q.front=Q.rear;
	}
	return OK;
}//DestroyQueue

Status EnQueue(LinkQueue &Q,ElemType e)
//插入元素e为队列Q的新的队尾元素
{
	QueuePtr p=(QueuePtr)malloc(sizeof(QNode));
	if(!p)
		exit(OVERFLOW); //存储分配失败
	p->data=e;
	p->next=NULL;
	Q.rear->next=p;
	Q.rear=p;
	return OK;
}//EnQueue

Status DeQueue(LinkQueue &Q,ElemType &e)
//若队列不空，则删除Q的队头元素，用e返回其值，并返回OK
//否则返回ERROR
{
	if(Q.front==Q.rear) //队列为空
		return ERROR;
	QueuePtr p=Q.front->next;
	e=p->data;
	Q.front->next=p->next;
	if(Q.rear==p) //队列中仅有一个元素
		Q.rear=Q.front;
	free(p);
	return OK;
}//DeQueue

//__BEGIN -----复制自Bank_Simulation.cpp-----

//自己实现的
int QueueLength(LinkQueue &Q)
//返回链式队列Q的元素个数，即队列的长度
{
	int i=1;
	QueuePtr lq=Q.front->next;
	if(lq==NULL)
		return 0;
	while(lq!=Q.rear)
	{
		i++;
		lq=lq->next;
	}
	return i;
}//QueueLength

//自己实现的
Status QueueEmpty(LinkQueue Q)
//若队列Q为空队列，则返回true，否则返回false
{
	return (Q.front==Q.rear);
}//QueueEmpty

//自己实现的
Status Gethead(LinkQueue Q,ElemType &e)
//若队列不空，则用e返回Q的队头元素，并返回OK，否则返回error
{
	if(Q.front==Q.rear)
		return ERROR;
	e=Q.front->next->data;
	return OK;
}//Gethead

//__END -----复制自Bank_Simulation.cpp----

//main函数做测试用
int main()
{
	LinkQueue Q1;
	InitQueue(Q1);
	ElemType temp;
	for(int i=1;i<10;i++)
	{
		EnQueue(Q1,i);
	}
	for(int i=1;i<10;i++)
	{
		DeQueue(Q1,temp);
		printf("%d ",temp);
	}
	DestroyQueue(Q1);
	return 0;
}

