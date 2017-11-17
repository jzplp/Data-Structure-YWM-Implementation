/***************************************************************************
 *  @file       StaticLinkList.cpp
 *  @author     jz
 *  @date       20 Oct. 2015
 *  @remark     数据结构 c语言版 严蔚敏 第二章
 *  @note	线性表链式存储结构的实现 静态链表
 ***************************************************************************/
//实现用
#include<stdlib.h>
#include<stdio.h>
//测试用

#include "DataStructure.h" //本书需要的一些定义

typedef int ElemType; //数据元素的类型，测试用，可更改

//线性表的静态单链表存储结构
#define MAXSIZE 1000 //链表的最大长度
struct ListNode
{
	ElemType data;
	int cur;
};
typedef ListNode StaticLinkList[MAXSIZE];

//此函数与同一文件下其它函数不配套，无法执行
int LocateElem_StaticLink(StaticLinkList S,ElemType e)
//在静态单链线性表L中查找第一个值为e的元素
//若找到，则返回他在L中的位序，否则返回0
{
	int i=S[0].cur; //i指示表中第一个结点
	while(i&&S[i].data!=e) //在表中顺链查找
		i=S[i].cur;
	return i;
}//LocateElem_StaticLink

void InitSpace_StaticLink(StaticLinkList &space)
//将空一维数组space的各分量链成一个备用链表
//space[0].cur为备用链表头指针，“0”为空指针
{
	for(int i=0;i<MAXSIZE-1;++i)
		space[i].cur=i+1;
	space[MAXSIZE-1].cur=0;
}//InitSpace_StaticLink

int Malloc_StaticLink(StaticLinkList &space)
//若备用空间的链表非空，则返回分配的结点下标，否则返回0
{
	int i=space[0].cur;
	if(space[0].cur)
		space[0].cur=space[i].cur;
	return i;
}//Malloc_StaticLink

void Free_StaticLink(StaticLinkList &space,int k)
//将下标为k的空闲结点回收到备用链表
{
	space[k].cur=space[0].cur;
	space[0].cur=k;
}//Free_StaticLink

void difference(StaticLinkList &space,int &S)
//依次输入集合A和B的元素，在一维数组space中建立表示集合(A-B)||(B-A)的静态链表，S为头指针
//假设备用空间足够大，space为为初始化的静态链表，space[0].cur为备用链表头指针
{
	InitSpace_StaticLink(space); //初始化备用空间
	S=Malloc_StaticLink(space); //生成S的头结点
	int r=S; //r指向S的当前为集合A的最后结点
	int m,n; //m为A元素的个数，n为B元素的个数
	puts("输入A,B的元素个数 空格分隔");
	scanf("%d %d",&m,&n);
	int i,j; //循环用变量
	puts("输入A的元素值");
	for(j=1;j<=m;++j) //建立集合A的链表
	{
		i=Malloc_StaticLink(space); //分配结点
		scanf("%d",&space[i].data); //输入A的元素值 （随着ElemType的不同本语句会有变化）
		space[r].cur=i; //插入到表尾
		r=i;
	}//for
	space[r].cur=0; //尾结点的指针为空
	ElemType b;
	int p,k; 
	puts("输入B的元素值");
	for(j=1;j<=n;++j)
	//依次输入B的元素，若不在当前表中，则插入，否则删除
	{
		scanf("%d",&b); //输入B的元素值（随着ElemType的不同本语句会有变化）
		k=space[S].cur; //k指向集合A中第一个结点
		while(k!=space[r].cur&&space[k].data!=b) 
		//在当前表中查找 p为当前结点的前驱结点的指针 k为当前节点指针
		{
			p=k; 
			k=space[k].cur;
		}//while
		if(k==space[r].cur)
		//当前表中不存在该元素，插入在r所指结点之后，且r的位置不变
		{
			i=Malloc_StaticLink(space);
			space[i].data=b;
			space[i].cur=space[r].cur;
			space[r].cur=i;
		}//if
		else //该元素已在表中，删除之
		{
			space[p].cur=space[k].cur;
			Free_StaticLink(space,k);
			if(r==k)
				r=p; //若删除的是尾结点，则须修改尾指针
		} //else
	}//for
}//difference

//自己实现的
void Show_StaticLink(const StaticLinkList &space,int S)
//输出静态链表space中所有的元素值，S为头结点
{
	int r=space[S].cur; //r为当前结点
	puts("当前静态链表中全部元素为：");
	while(r) //遍历静态链表
	{
		printf("%d ",space[r].data); //输出元素值（随着ElemType的不同本语句会有变化）
		r=space[r].cur;
	}
	putchar('\n');
}//Show_StaticLink

//main函数做测试用
int main()
{
	StaticLinkList S1;
	int i=0;
	difference(S1,i);
	Show_StaticLink(S1,i);
	return 0;
}

