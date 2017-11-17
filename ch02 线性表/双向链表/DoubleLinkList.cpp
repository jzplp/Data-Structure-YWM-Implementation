/***************************************************************************
 *  @file       DoubleLinkList.cpp
 *  @author     jz
 *  @date       20 Oct. 2015
 *  @remark     数据结构 c语言版 严蔚敏 第二章
 *  @note	线性表链式存储结构的实现 双向链表
 ***************************************************************************/
//实现用
#include<stdlib.h>
#include<stdio.h>
//测试用

#include "DataStructure.h" //本书需要的一些定义

typedef int ElemType; //数据元素的类型，测试用，可更改

//线性表的双向链表存储结构
struct DoubleLinkNode
{
	ElemType data;
	struct DoubleLinkNode *prior; //直接前驱的指针
	struct DoubleLinkNode *next; //直接后继的指针
};
typedef DoubleLinkNode *DoubleLinkList;

//自己实现的
DoubleLinkNode *GetElemPtr_DoubleLink(DoubleLinkList L,int i)
//返回双链循环线性表L中第i个结点的指针，若不存在则返回NULL i的合法值为1<=i<=表长
{
	int count=1; //计数器
	DoubleLinkNode *p=L->next; //p为当前位置的指针
	while(p&&count<i)
	{
		p=p->next;
		++count;
	}
	if(p&&count==i)
		return p;
	else
		return NULL;
}

Status ListInsert_DoubleLink(DoubleLinkList &L,int i,ElemType e)
//在带头结点的双链循环线性表L中第i个位置之前插入元素e
//i的合法值为1<=i<=表长+1 由于GetElemPtr_DoubleLink函数，暂时无法处理表长+1的情况
{
	DoubleLinkNode *p=GetElemPtr_DoubleLink(L,i); //p为插入位置的指针
	if(!p)
		return ERROR; //p=NULL 即插入位置不合法
	DoubleLinkNode *s=(DoubleLinkNode *)malloc(sizeof(DoubleLinkNode)); //分配存储空间
	if(!s)
		return ERROR; //分配存储失败
	s->data=e;
	s->prior=p->prior;
	p->prior->next=s;
	s->next=p;
	p->prior=s;
	return OK;
}//ListInsert_DoubleLink

Status ListDelete_DoubleLink(DoubleLinkList &L,int i,ElemType &e)
//删除带头结点的双链循环线性表L的第i个元素，并用e返回其值，i的合法值为1<=i<=表长
{

	DoubleLinkNode *p=GetElemPtr_DoubleLink(L,i); //p为插入位置的指针
	if(!p)
		return ERROR;
	e=p->data;
	p->prior->next=p->next;
	p->next->prior=p->prior;
	free(p); //释放结点
	return OK;
}//ListDelete_DoubleLink

//自己实现的
void InitList_DoubleLink(DoubleLinkList &L,ElemType e)
//构造一个带头节点的空的线性表L
//由于上述函数的限制，再输入第一个元素e
{
	L=(DoubleLinkList)malloc(sizeof(DoubleLinkNode));
	if(!L) //存储分配失败
		exit(OVERFLOW);
	DoubleLinkNode * p=(DoubleLinkList)malloc(sizeof(DoubleLinkNode));
	if(!p) //存储分配失败
		exit(OVERFLOW);
	p->data=e;
	L->next=p;
	L->prior=p;
	p->prior=L;
	p->next=L;
}

//自己实现的
void Show_DoubleLink(DoubleLinkList L)
//输出带头结点的双链循环线性表L的所有元素的值
{
	DoubleLinkNode *p=L->next; //p为当前结点
	puts("当前链表中全部元素为：");
	while(p!=L)
	{
		printf("%d ",p->data);  //输出元素值（随着ElemType的不同本语句会有变化）
		p=p->next;
	}
	putchar('\n');
}

//自己实现的
void DestroyList_Doublelink(DoubleLinkList &L)
{
//销毁单链线性表L，L不再存在
	DoubleLinkNode *p=L->next,*q;
	while(p!=L)
	{
		q=p->next;
		free(p);
		p=q;
	}
	free(L);
}
//main函数做测试用
int main()
{
	DoubleLinkList D1;
	InitList_DoubleLink(D1,12345);
	ListInsert_DoubleLink(D1,1,1234);
	ListInsert_DoubleLink(D1,1,123);
	ElemType e;
	ListDelete_DoubleLink(D1,2,e);
	Show_DoubleLink(D1);


	return 0;
}
