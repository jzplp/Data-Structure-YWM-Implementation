/***************************************************************************
 *  @file       LinkList.cpp
 *  @author     jz
 *  @date       19 Oct. 2015
 *  @remark     数据结构 c语言版 严蔚敏 第二章
 *  @note	线性表链式存储结构的实现 单链表
 ***************************************************************************/
//实现用
#include<stdlib.h>
#include<stdio.h>

#include "DataStructure.h"//本书需要的一些定义

typedef int ElemType; //数据元素的类型，测试用，可更改

//线性表的单链表存储结构
struct ListNode
{
	ElemType data;
	ListNode *next;
};
//头指针
typedef ListNode * LinkList;

Status GetElem_Link(LinkList L,int i,ElemType &e)
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

Status ListInsert_Link(LinkList &L,int i,ElemType e)
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

Status ListDelete_Link(LinkList &L,int i,ElemType &e)
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

void CreateList_Link(LinkList &L,int n)
{
//逆位序输入n个元素的值，建立起带头结点的单链线性表L
//L为为初始化的单链线性表 n的合法值为n>=1
	L=(LinkList)malloc(sizeof(ListNode));
	if(!L) //存储分配失败
		exit(OVERFLOW);
	L->next=NULL; //先建立起一个带头结点的单链表
	ListNode * p=NULL;
	for(int i=n;i>0;--i)
	{
		p=(ListNode *)malloc(sizeof(ListNode)); //生成新结点
		if(!p) //存储分配失败
			exit(OVERFLOW);
		scanf("%d",&p->data); //输入元素值（随着ElemType的不同本语句会有变化）
		p->next=L->next;
		L->next=p;
	}
}//CreateList_Link

void MergeList_Link(LinkList &La,LinkList &Lb,LinkList &Lc)
{
//已知单链线性表La和Lb的元素按值非递减排列，Lc为为初始化的单链线性表
//归并La和Lb得到新的单链线性表Lc，Lc的元素也按非递减排列
//函数结束后La和Lb已经不存在 Lc不申请额外的空间
	ListNode *pa=La->next,*pb=Lb->next;
	ListNode *pc=La;
	Lc=pc; //用La的头结点作为Lc的头结点
	while(pa&&pb) //归并过程
		if(pa->data<=pb->data)
		{
			pc->next=pa;
			pc=pa;
			pa=pa->next;
		}else
		{
			pc->next=pb;
			pc=pb;
			pb=pb->next;
		}
	pc->next=pa?pa:pb; //插入剩余段
	free(Lb); //释放Lb的头结点
}//MergeList_Link

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

//__BEGIN -----复制自Bank_Simulation.cpp-----

//自己实现的
Status ListEmpty(LinkList L)
//若链表为空表，则返回true，否则返回false
{
	if(L->next==NULL)
		return true;
	return false;
}//ListEmpty

//__END -----复制自Bank_Simulation.cpp----

//main函数做测试用
int main()
{
	LinkList L1;
	InitList_Link(L1);
	ElemType temp;
	
	LinkList L2;
	//CreateList_Link(L2,10);
	
	LinkList L3,L4,L5;
	InitList_Link(L3);
	InitList_Link(L4);
	for(int i=1;i<=10;i++)
	{
		ListInsert_Link(L1,i,10-i);
	//	GetElem_Link(L1,i,temp);
	//	printf("%d",temp);
		
		ListInsert_Link(L3,i,2*i);
		ListInsert_Link(L4,i,3*i);
		GetElem_Link(L3,i,temp);
	//	printf("%d ",temp);
		GetElem_Link(L4,i,temp);
	//	printf("*%d ",temp);
	
	//	ListDelete_Link(L2,11-i,temp);
	//	printf(" *%d ",temp);
	}
	putchar('\n');

	MergeList_Link(L3,L4,L5);
	for(int i=1;i<=20;++i)
	{
		GetElem_Link(L5,i,temp);
		printf("%d ",temp);
	}
	putchar('\n');
	
	return 0;
}
