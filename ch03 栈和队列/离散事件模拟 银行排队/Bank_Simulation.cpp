/***************************************************************************
 *  @file       Bank_Simulation.cpp
 *  @author     jz
 *  @date       21 Dec. 2015
 *  @remark     数据结构 c语言版 严蔚敏 第三章
 *  @note	离散事件模拟 银行排队
 ***************************************************************************/
//实现用
#include<stdlib.h>
#include<stdio.h>

#include "DataStructure.h"//本书需要的一些定义

struct Event
{
	int OccurTime; //事件发生时刻
	int NType; //事件类型 0表示到达事件，1至4表示四个窗口的离开时间
};

struct Person
{
	int ArrivalTime; //到达时间
	int Duration; //办理事务所需时间
};

typedef Event ElemType_List; //单链表数据元素的类型
typedef Person ElemType_Queue; //链表队列数据元素的类型


//__BEGIN -----复制自LinkList.cpp-----

//线性表的单链表存储结构
struct ListNode
{
	ElemType_List data;
	ListNode *next;
};

//头指针
typedef ListNode * LinkList;

Status GetElem_Link(LinkList L,int i,ElemType_List &e)
{
//L为带头结点的单链表的头指针
//当第i个元素存在时，其值赋给e并返回OK,否则返回ERROR
	ListNode *p=L->next; //初始化p指向第一个结点
	int j=1; //j为计数器
	while(p&&j<i)
	//顺序向后查找，直到p指向第i个元素或者p为空
	{
		p=p->next;
		++j;
	}
	if(!p||j>i) //第i个元素不存在
		return ERROR;
	e=p->data;
	return OK;
}//GetElem_Link

Status ListInsert_Link(LinkList &L,int i,ElemType_List e)
{
//在带头结点的单链线性表中第i个位置之前插入元素e
//i的合法值为1<=i<=表长+1
	ListNode * p=L;  //初始化p指向头结点
	int j=0;   //j为计数器
	while(p&&j<i-1)
	//寻找第i-1个结点
	{
		p=p->next;
		++j;
	}
	if(!p||j>i-1)
	//i<1或者大于表长+1
		return ERROR;
	ListNode *s=(ListNode *)malloc(sizeof(ListNode)); //生成新结点
	if(!s) //存储分配失败
		exit(OVERFLOW); 
	s->data=e;
	s->next=p->next; //插入L中
	p->next=s;
	return OK;
}//ListInsert_Link

//自己实现的
Status InitList_Link(LinkList &L)
{
//构造一个带头结点的空的线性表L
	L=(ListNode *)malloc(sizeof(ListNode));
	if(!L) //存储分配失败
		exit(OVERFLOW);
	L->next=NULL;
	return OK;
}//InitList_Link

Status ListDelete_Link(LinkList &L,int i,ElemType_List &e)
{
//在带头结点的单链线性表L中，删除第i个元素，并用e返回其值
//i的合法值为1<=i<=表长
	ListNode *p=L; //初始化p指向头结点
	int j=0; //j为计数器
	while(p->next&&j<i-1)
	{
	//寻找第i个结点，并令p指向其前驱
		p=p->next;
		++j;
	}
	if(!(p->next)||j>i-1) //删除位置不合理
		return ERROR;
	ListNode *q=p->next; //q为要删除的结点
	p->next=q->next; //删除结点
	e=q->data;
	free(q); //释放结点
	return OK;
}//ListDelete_Link

//自己实现的
void DestroyList_link(LinkList &L)
{
//销毁单链线性表L，L不再存在
	ListNode *p;
	while(L)
	{
		p=L->next;
		free(L);
		L=p;
	}
}

//__END -----复制自LinkList.cpp----

//自己实现的
Status ListEmpty(LinkList L)
//若链表为空表，则返回true，否则返回false
{
	if(L->next==NULL)
		return true;
	return false;
}//ListEmpty


//__BEGIN -----复制自LinkQueue.cpp-----

struct QNode
{
	ElemType_Queue data;
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

Status EnQueue(LinkQueue &Q,ElemType_Queue e)
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

Status DeQueue(LinkQueue &Q,ElemType_Queue &e)
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

//__END -----复制自LinkList.cpp----

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
Status Gethead(LinkQueue Q,ElemType_Queue &e)
//若队列不空，则用e返回Q的队头元素，并返回OK，否则返回error
{
	if(Q.front==Q.rear)
		return ERROR;
	e=Q.front->next->data;
	return OK;
}//Gethead

//全局变量
int TotalTime; //累计客户逗留时间
int CustomerNum; //客户数
LinkList ev; //事件表
Event en; //事件
LinkQueue q[5]; //4个客户队列 q[0]不用
int CloseTime =50; //银行关闭时间，测试用，可更改
Person customer; //客户记录

//自己实现的
int cmp(Event a,Event b)
//依事件a发生的时刻<或=或>事件b发生的时刻分别返回-1，0，1
{
	if(a.OccurTime<b.OccurTime)
		return -1;
	else if(a.OccurTime==b.OccurTime)
		return 0;
	else
		return 1;
}//cmp

//自己实现的
void OrderInsert(LinkList &L,Event e)
//带头结点的单链线性表L中的元素与e用cmp函数比较，在L中元素大于e的位置之前插入元素e
{
	ListNode *p=L;  //初始化p指向头结点
	while((p->next)!=NULL&&cmp(e,p->next->data)>=0)
	{
		p=p->next;
	}
	ListNode *s=(ListNode *)malloc(sizeof(ListNode)); //生成新结点
	if(!s) //存储分配失败
		exit(OVERFLOW); 
	s->data=e;
	s->next=p->next; //插入L中
	p->next=s;
}

void OpenForDay()
//初始化操作
{
	TotalTime=0;
	CustomerNum=0;
	InitList_Link(ev); //初始化事件链表为空表
	en.OccurTime=0; //设定第一个客户到达事件
	en.NType=0;
	OrderInsert(ev,en); //插入事件表
	for(int i=1;i<=4;++i)
		InitQueue(q[i]); //初始化各个队列
}//OpenForDay

//自己实现的
int Minimum_Queue(LinkQueue *L)
//L为队列数组，函数返回长度最短的队列的序号
{
	int q1=QueueLength(L[1]),q2=QueueLength(L[2]),q3=QueueLength(L[3]),q4=QueueLength(L[4]);
	printf("%d %d %d %d \n",q1,q2,q3,q4);
	if(q1<=q2&&q1<=q3&&q1<=q4)
		return 1;
	if(q2<=q1&&q2<=q3&&q2<=q4)
		return 2;
	if(q3<=q1&&q3<=q2&&q3<=q4)
		return 3;
	return 4;
}

void CustomerArrived()
//处理用户到达事件，en.NType=0
{
	++CustomerNum;
	int durtime=rand()%5+10; //办理事务所需时间1-5分钟 测试用，可更改
	int intertime=rand()%5+1; //客户到达的间隔时间1-5分钟 测试用，可更改
	//printf("durtime %d intertime: %d  \n",durtime,intertime);
	int t=en.OccurTime+intertime; //下一个客户到达时刻
	Event Etemp; //临时变量
	if(t>=CloseTime)
	{
		printf("银行已经下班，不接受customer了\n");
	}else
	{
		Etemp.OccurTime=t;
		Etemp.NType=0;
		OrderInsert(ev,Etemp); //插入事件表
	}
	int i=Minimum_Queue(q);
	Person Ptemp;
	Ptemp.ArrivalTime=en.OccurTime;
	Ptemp.Duration=durtime;
	EnQueue(q[i],Ptemp); //放入队列
	if(QueueLength(q[i])==1)
	{ //设定第i队列的一个离开事件并插入事件表
		Etemp.OccurTime=en.OccurTime+durtime;
		Etemp.NType=i;
		OrderInsert(ev,Etemp);
	}
}//CustomerArrived

void CustomerDepature()
{
	int i=en.NType;
	DeQueue(q[i],customer); //删除第i队列的排头客户
	//printf("i: %d en.OccurTime-customer.ArrivalTime: %d  \n",i,en.OccurTime-customer.ArrivalTime);
	TotalTime+=en.OccurTime-customer.ArrivalTime; //累计客户逗留时间
	Event Etemp; //临时变量
	if(!QueueEmpty(q[i]))
	{
		Gethead(q[i],customer);
		Etemp.OccurTime=en.OccurTime+customer.Duration;
		Etemp.NType=i;
		OrderInsert(ev,Etemp);
	}
}//CustomerDepature

void Bank_Simulation()
{
	OpenForDay();
	while(!ListEmpty(ev))
	{
		ListDelete_Link(ev,1,en);
		if(en.NType==0)
			CustomerArrived();
		else
			CustomerDepature();
	}
	printf("\nTotalTime: %d CustomerNum: %d\n",TotalTime,CustomerNum);
	printf("The Average Time is %f\n",(float)TotalTime/CustomerNum);
}//Bank_Simulation

int main()
{
	Bank_Simulation();
	return 0;
}

