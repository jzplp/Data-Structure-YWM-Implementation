/***************************************************************************
 *  @file       Polynomial.cpp
 *  @author     jz
 *  @date       28 Oct. 2015
 *  @remark     数据结构 c语言版 严蔚敏 第二章
 *  @note	用单链表表示 一元多项式 
 ***************************************************************************/
//实现用
#include<stdlib.h>
#include<stdio.h>

#include "DataStructure.h"//本书需要的一些定义

typedef struct 
//項的表示 多项式的项作为LinkList的数据元素
{
	double coef; //系数
	int expn; //指数
} ElemType; //数据元素的类型

//__BEGIN -----复制自LinkList.cpp-----
//线性表的单链表存储结构
struct ListNode
{
	ElemType data;
	ListNode *next;
};
//头指针
typedef ListNode * LinkList;

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

//__END -----复制自LinkList.cpp-----

//用带头结点的有序链表表示多项式
typedef LinkList Polynomial;

//链表中节点的位置指针
typedef ListNode * Position;

//自己实现的
ListNode * GetHead(LinkList P)
//返回单链表的头指针
{
	return P;
}

//自己实现的
Status LocateElem(LinkList L,ElemType e,Position &q,int (*compare)(ElemType,ElemType))
//若有序链表L中存在与e满足判定函数compare()中取值为0 的元素，则q指示L中第一个值
//为e的节点的位置，并返回ture，否则指示第一个与e满足判定函数compare()取值>0
//的元素的前驱位置,并返回false
{

	ListNode *p=L->next; //初始化p指向第一个结点
	ListNode *pre=L; //初始化pre指向p的前驱结点
	while(p!=NULL&&compare(p->data,e)<0)
	{
		pre=p;
		p=p->next;
	}
	if(p==NULL||compare(p->data,e)>0)
	//若整个链表都与e满足判定函数compare()取值<0或者
	//找到第一个与e满足判定函数compare()取值>0的元素的前驱位置
	{
		q=pre;
		return false;
	}
	q=p;
	return true;
}

//自己实现的
int cmp(ElemType a,ElemType b)
//依照a的指数值<或=或>b的指数值，分别返回-1，0，1
{
	if(a.expn<b.expn)
		return -1;
	else if(a.expn==b.expn)
		return 0;
	return 1;
}

void CreatePolyn(Polynomial &P,int m)
//输入m项的系数和指数，建立表示一元多项式的有序链表P P未被初始化
{
	InitList_Link(P);
	ListNode *h=GetHead(P); //得到头结点的指针
	ElemType e={0.0,-1};
	h->data=e; //设置头结点的数据元素
	Position pos; //插入位置
	puts("please 依次输入多项式中的非零项");
	for(int i=1;i<=m;++i)//依次输入m个非零项
	{
		scanf("%lf %d",&e.coef,&e.expn);
		if(!LocateElem(P,e,pos,cmp))
		//如果链表中不存在该项
		{
			ListNode *s=(ListNode *)malloc(sizeof(ListNode)); //生成新结点
			if(!s) //存储分配失败
				exit(OVERFLOW);
			s->data=e; //生成结点
			s->next=pos->next;
			pos->next=s; //插入链表
		}//if 若链表中存在该项则什么都不做...
	}	
}
void ShowList_Link(Polynomial P)
//输出带头结点的单链线性表L的所有元素的值
{
	ListNode *p=P->next; //p为当前结点
	puts("当前链表中全部元素为：");
	while(p!=NULL)
	{
		//输出元素值（随着ElemType的不同本语句会有变化）
		printf("||%lf %d ",p->data.coef,p->data.expn);  
		p=p->next;
	}
	putchar('\n');
}

void AddPolyn(Polynomial &Pa,Polynomial &Pb)
//多项式加法：Pa=Pa+Pb 利用两个多项式的结点构成“和多项式”，函数结束后Pb已被销毁
{
	ListNode *ha=Pa,*hb=Pb; //ha和hb分别指向Pa和Pb的头结点
	ListNode *qa=ha->next,*qb=hb->next; //qa和qb分别指向Pa和Pb中当前结点
	ListNode * temp;
	while(qa&&qb) //qa和qb均非空
	{
		switch(cmp(qa->data,qb->data))
		{
			case -1: //多项式Pa中当前结点指数小
				ha=qa;
				qa=qa->next;
				break;
			case 0: //两者的指数值相等
				qa->data.coef+=qb->data.coef;
				if(qa->data.coef!=0)
				{
					ha=qa;
					qa=qa->next;
				}else //删除多项式Pa中当前结点
				{
					ha->next=qa->next;
					free(qa);
					qa=ha->next;
				}
				temp=qb;
				qb=qb->next;
				free(temp); //删除Pb中当前结点
				break;
			case 1: //多项式Pb中当前结点指数小
				temp=qb->next;
				qb->next=qa;
				ha->next=qb;
				ha=qb;
				qb=temp;
				break;
		}//switch
	}//while
	if(qb) //链接Pb中剩余结点
		ha->next=qb;
	free(hb); //释放Pb的头结点
}//AddPolyn

//main函数做测试用
int main()
{
	Polynomial p1,p2;
	CreatePolyn(p1,3);
	CreatePolyn(p2,3);
	AddPolyn(p1,p2);
	ShowList_Link(p1);
	DestroyList_link(p1);
	DestroyList_link(p2);
	return 0;
}
