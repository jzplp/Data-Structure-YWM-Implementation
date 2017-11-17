/***************************************************************************
 *  @file       HeapSort.cpp
 *  @author     jz
 *  @date       03 Mar. 2016
 *  @remark     数据结构 c语言版 严蔚敏 第十章
 *  @note	堆排序
 ***************************************************************************/
//实现用
#include<stdlib.h>
#include<stdio.h>
//#include<math.h>
//#include<limits.h>
//#include<string.h>
//测试用

#include "DataStructure.h" //本书需要的一些定义

#define MAXSIZE 20 //顺序表的最大长度
typedef int KeyType; //关键字类型说明
typedef int InfoType; //其它数据项类型说明
struct RedType //记录类型定义
{
	KeyType key; //关键字域
	InfoType data; //其它数据项
};
struct SqList
{
	RedType r[MAXSIZE+1]; //r[0]闲置或用作哨兵单元
	int length; //顺序表长度
};

//对两个关键字的比较约定 数值型关键字
#define EQ(a,b) ((a)==(b))
#define LT(a,b) ((a)<(b))
#define LQ(a,b) ((a)<=(b))

void PrintSL(SqList *L)
//输出顺序表
{
	int i;
	printf("Put: ");
	for(i=1;i<=L->length;++i)
		printf("%d ",L->r[i]);
	putchar('\n');
}//PrintSL

void CreateSL(SqList *L)
//构造顺序表
{
	int i;
	int a[10]={49,38,65,97,76,13,27,49,55,4};
	L->length=10;
	for(i=1;i<=L->length;++i)
		L->r[i].key=a[i-1];
}//CreateSL

typedef SqList HeapType; //堆采用顺序表存储表示

void HeapAdjust(HeapType &H,int s,int m)
//已知h.r[s...m]中记录的关键字除H.r[s].key之外均满足堆的定义，
//本函数调整H.r[s]的关键字，使H.r[s...m]成为一个大顶堆
{
	RedType rc=H.r[s];
	int j;
	for(j=2*s;j<=m;j*=2) //沿key较大的孩子结点向下筛选
	{
		if(j<m &&LT(H.r[j].key,H.r[j+1].key))
			++j; //j为较大的记录的下标
		if(!LT(rc.key,H.r[j].key))
			break; //rc应插入在位置S上
		H.r[s]=H.r[j];
		s=j;
	}
	H.r[s]=rc; //插入
}//HeapAdjust

void HeapSort(HeapType &H)
{
	int i;
	RedType r;
	for(i=H.length/2;i>0;--i) //把H[1...H.length]建成大顶堆
		HeapAdjust(H,i,H.length);
	for(i=H.length;i>1;--i)
	{
		//将堆顶记录和当前未经排序子序列H.r[1...i]中最后一个记录相互交换
		r=H.r[1];
		H.r[1]=H.r[i];
		H.r[i]=r;
		HeapAdjust(H,1,i-1); //将H.r[1...i-1]重新调整为大顶堆
	}
}//HeapSort

//main函数做测试用
int main()
{
	SqList l;
	CreateSL(&l);
	PrintSL(&l);
	HeapSort(l);
	PrintSL(&l);
	return 0;
}
