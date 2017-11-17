/***************************************************************************
 *  @file       ShellSort.cpp
 *  @author     jz
 *  @date       02 Mar. 2016
 *  @remark     数据结构 c语言版 严蔚敏 第十章
 *  @note	Shell排序
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

void ShellInsert(SqList &L,int dk)
//对顺序表L作一趟shell插入排序
//和一趟直接插入排序相比做了如下修改
// 1.前后记录位置的增量是dk，而不是1
// 2.r[0]知识暂存单元，不是哨兵。当j<=0时，插入位置已找到。
{
	int i,j;
	for(i=dk+1;i<=L.length;++i)
	{
		if(LT(L.r[i].key,L.r[i-dk].key)) //需将L.r[i]插入有序增量子表
		{
			L.r[0]=L.r[i]; //暂存在L.r[0]
			for(j=i-dk;j>0 && LT(L.r[0].key,L.r[j].key);j-=dk)
				L.r[j+dk]=L.r[j]; //记录后移，查找插入位置
			L.r[j+dk]=L.r[0];
		}
	}
}//ShellInsert

void ShellSort(SqList &L)
//按照增量序列dlta[0...t-1]对顺序表L做Shell排序
//对书上的格式进行了改动
{
	//改动begin
	int dlta[20]; //最大20，可修改
	int i=L.length,count=0;
	while(i>=1)
	{
		dlta[count]=i/3;
		i=i/3;
		count++;
	}
	int t=count-1;
	//改动end
	int k;
	for(k=0;k<t;++k)
		ShellInsert(L,dlta[k]);
}//ShellSort


//main函数做测试用
int main()
{
	SqList l;
	CreateSL(&l);
	PrintSL(&l);
	ShellSort(l);
	PrintSL(&l);
	return 0;
}
