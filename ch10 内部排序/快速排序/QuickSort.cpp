/***************************************************************************
 *  @file       QuickSort.cpp
 *  @author     jz
 *  @date       03 Mar. 2016
 *  @remark     数据结构 c语言版 严蔚敏 第十章
 *  @note	快速排序
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

int Partition(SqList &L,int low,int high)
//交换顺序表中子表r[low....high]的记录，中轴记录到位，并返回其所在位置
{
	L.r[0]=L.r[low]; //用子表的第一个记录作为中轴记录
	int pivotkey=L.r[low].key; //中轴记录关键字
	while(low<high) //从表的两端交替的向中间扫描
	{
		while(low<high && L.r[high].key>=pivotkey)
			--high;
		L.r[low]=L.r[high]; //将比中轴记录小的记录移动到低端
		while(low<high && L.r[low].key<=pivotkey)
			++low; 
		L.r[high]=L.r[low]; //将比中轴记录大的记录移动到高端
	}
	L.r[low]=L.r[0]; //中轴记录到位
	return low; //返回中轴位置
}//Partition

void QSort(SqList &L,int low,int high)
//对顺序表L中子序列L.r[low...high]做快速排序
{
	if(low<high) //长度大于1
	{
		int pivotloc=Partition(L,low,high); //一分为二
		QSort(L,low,pivotloc-1); //对低子表递归排序
		QSort(L,pivotloc+1,high); //对高子表递归排序
	}
}//QSort

void QuickSort(SqList &L)
//对顺序表L做快速排序
{
	QSort(L,1,L.length);
}//QuickSort

//main函数做测试用
int main()
{
	SqList l;
	CreateSL(&l);
	PrintSL(&l);
	QuickSort(l);
	PrintSL(&l);
	return 0;
}
