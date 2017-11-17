/***************************************************************************
 *  @file       RadixSort.cpp
 *  @author     jz
 *  @date       05 Mar. 2016
 *  @remark     数据结构 c语言版 严蔚敏 第十章
 *  @note	基数排序
 ***************************************************************************/
//实现用
#include<stdlib.h>
#include<stdio.h>
//#include<math.h>
//#include<limits.h>
//#include<string.h>
//测试用

#include "DataStructure.h" //本书需要的一些定义

#define MAX_NUM_OF_KEY 8//关键字项数的最大值
#define RADIX 10 //关键字基数，此时是十进制整数的基数
#define MAX_SPACE 100
typedef int KeyType; //关键字类型说明
typedef int InfoType; //其它数据项类型说明
struct SLCell //静态链表的结点类型
{
	KeyType keys[MAX_NUM_OF_KEY]; //关键字
	InfoType otheritems; //其他数据项
	int next;
};
struct SLList //静态链表类型
{
	SLCell r[MAX_SPACE]; //静态链表的可利用空间，r[0]为头结点
	int keynum; //记录的当前关键字个数
	int recnum; //静态链表的当前长度
};
typedef int ArrType[RADIX]; //指针数组类型

void Distribute(SLCell *r,int i,ArrType &head,ArrType &tail)
//静态链表的r域中的记录已按(keys[0],...,keys[i-1])有序
//算法按第i个关键字keys[i]建立RADIX个子表，使同一个子表中记录的keys[i]相同
//head[0...RADIX-1]和tail[0...RADIX-1]分别指向子表中的第一个和最后一个记录
{
	int j,p;
	for(j=0;j<RADIX;++j)
		head[j]=0; //各子表初始化为空表
	for(p=r[0].next;p;p=r[p].next)
	{
		j=r[p].keys[i];
		if(!head[j])
			head[j]=p;
		else
			r[tail[j]].next=p;
		tail[j]=p; //插到末尾
	}
}//Distribute

void Collect(SLCell *r,int i,ArrType head,ArrType tail)
//本算法按keys[i]自小至大地将f[0...RADIX-1]所指各子表依次链接成一个链表
//head[0...RADIX-1]和tail[0...RADIX-1]分别指向子表中的第一个和最后一个记录
{
	int t,j;
	for(j=0;!head[j];++j)
		; //找到第一个非空子表
	r[0].next=head[j]; //r[0].next指向一个非空子表中第一个结点
	t=tail[j];
	while(j<RADIX)
	{
		for(++j;j<RADIX-1 && !head[j];++j)
			; //找到下一个非空子表
		if(head[j] && j<RADIX) //链接两个非空子表
		{
			r[t].next=head[j];
			t=tail[j];
		}
	}
	r[t].next=0; //t指向最后一个非空子表中的最后一个结点
}//Collect

void RadixSort(SLList &L)
//L是采用静态链表表示的顺序表，对L所基数排序，
//使得L成为按关键字由小到大的有序静态链表，L.r[0]为头结点
{
	int i;
	ArrType head;
	ArrType tail;
	for(i=0;i<L.recnum;++i)
		L.r[i].next=i+1;
	L.r[L.recnum].next=0; //将L改造为静态链表
	for(i=0;i<L.keynum;++i) 
	{ //按最低位优先依次对关键字进行分配和收集
		Distribute(L.r,i,head,tail);
		Collect(L.r,i,head,tail);
	}
}//RadixSort

void CreateSLL(SLList *L)
//构造表
{
	int i,j,b,c;
	int a[10]={115,258,746,754,316,543,217,981,155,414};
	L->recnum=10; //10个排序数字
	L->keynum=3; //3位
	for(i=1;i<=L->recnum;++i)
	{
		L->r[i].otheritems=a[i-1];
		b=RADIX;
		for(j=0;j<L->keynum;++j)
		{
			L->r[i].keys[j]=(L->r[i].otheritems%b)/(b/RADIX);
			b=b*RADIX;
		}
	}
}//CreateSLL

void PrintSLL(SLList *L)
//输出顺序表
{
	int i,j;
	printf("Put: ");
	for(i=1;i<=L->recnum;++i)
		printf("%d ",L->r[i].otheritems);
	putchar('\n');
}//PrintSLL

void ShowSLL(SLList *L)
//输出排序结果
{
	int i,j;
	printf("Show: ");
	i=L->r[0].next;
	while(i)
	{
		printf("%d ",L->r[i].otheritems);
		i=L->r[i].next;
	}
	putchar('\n');
}//ShowSLL

//main函数做测试用
int main()
{

	SLList l;
	CreateSLL(&l);
	PrintSLL(&l);
	RadixSort(l);
	ShowSLL(&l);
	return 0;
}
