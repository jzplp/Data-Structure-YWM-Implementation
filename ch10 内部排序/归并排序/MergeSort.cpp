/***************************************************************************
 *  @file       MergeSort.cpp
 *  @author     jz
 *  @date       03 Mar. 2016
 *  @remark     数据结构 c语言版 严蔚敏 第十章
 *  @note	归并排序
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

void Merge(RedType *SR,RedType *TR,int left,int middle,int right)
//将有序的SR[left...middle]和SR[middle+1...right]归并为有序的SR[left...right]
//TR为辅助数组，和书上比有改动
{
	int i=left,j=middle+1,k=left;
	while(i<=middle && j<=right)
	{
		if(LQ(SR[i].key,SR[j].key))
			TR[k++]=SR[i++];
		else
			TR[k++]=SR[j++];
	}
	while(i<=middle)
		TR[k++]=SR[i++];
	while(j<=right)
		TR[k++]=SR[j++];
	for(i=left;i<=right;++i)
		SR[i]=TR[i];
}//Merge

void MSort(RedType *SR,RedType *TR,int left,int right)
//将SR[left...right]归并排序
//TR为辅助数组，和书上比有改动
{
	if(left<right)
	{
		int middle=(left+right)/2;
		MSort(SR,TR,left,middle);
		MSort(SR,TR,middle+1,right);
		Merge(SR,TR,left,middle,right);
	}
}//MSort

void MergeSort(SqList &L)
//对顺序表L做归并排序
{
	RedType r[L.length+1];
	MSort(L.r,r,1,L.length);
}//MergeSort
	


//main函数做测试用
int main()
{
	SqList l;
	CreateSL(&l);
	PrintSL(&l);
	MergeSort(l);
	PrintSL(&l);
	return 0;
}
