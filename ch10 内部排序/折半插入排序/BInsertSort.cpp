/***************************************************************************
 *  @file       BInsertSort.cpp
 *  @author     jz
 *  @date       2 Mar. 2016
 *  @remark     数据结构 c语言版 严蔚敏 第十章
 *  @note	折半插入排序
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
	int a[9]={1,2,5,7,8,9,10,12,8};
	L->length=9;
	for(i=1;i<=L->length;++i)
		L->r[i].key=a[i-1];
}//CreateSL
void BInsertSort(SqList &L)
//对顺序表L作折半插入排序
{
	int i,j,low,high,m;
	for(i=1;i<=L.length;++i)
	{
		L.r[0]=L.r[i]; //将L.r[i]暂存到L.r[0]
		low=1;
		high=i-1;
		while(low<=high) //在r[low...high]中折半查找有序位置
		{
			m=(low+high)/2; //折半
			if(LT(L.r[0].key,L.r[m].key)) //插入点在低半区
				high=m-1;
			else //插入点在高半区
				low=m+1;
		}
		for(j=i-1;j>=high+1;--j)
			L.r[j+1]=L.r[j]; //记录后移
		L.r[high+1]=L.r[0]; //插入
	}
}//BInsertSort


//main函数做测试用
int main()
{
	SqList l;
	CreateSL(&l);
	PrintSL(&l);
	BInsertSort(l);
	PrintSL(&l);
	return 0;
}
