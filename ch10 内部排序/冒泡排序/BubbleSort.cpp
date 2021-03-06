/***************************************************************************
 *  @file       BubbleSort.cpp
 *  @author     jz
 *  @date       03 Mar. 2016
 *  @remark     数据结构 c语言版 严蔚敏 第十章
 *  @note	冒泡排序
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

void BubbleSort(SqList &L)
//对顺序表L做冒泡排序
{
	int i,j;
	RedType r;
	bool tag;
	for(i=L.length;i>=1;--i)
	{
		tag=false;
		for(j=1;j<i;++j)
		{
			if(LT(L.r[j+1].key,L.r[j].key))
			{
				r=L.r[j+1];
				L.r[j+1]=L.r[j];
				L.r[j]=r;
				tag=true;
			}
		}
		if(tag==false)
			break;
	}
}//BubbleSort


//main函数做测试用
int main()
{
	SqList l;
	CreateSL(&l);
	PrintSL(&l);
	BubbleSort(l);
	PrintSL(&l);
	return 0;
}
