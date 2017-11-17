/***************************************************************************
 *  @file       Rearrange.cpp
 *  @author     jz
 *  @date       07 Mar. 2016
 *  @remark     数据结构 c语言版 严蔚敏 第十章
 *  @note	地址向量 重排记录
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
	int a[8]={49,65,38,27,97,13,76,49};
	L->length=8;
	for(i=1;i<=L->length;++i)
		L->r[i].key=a[i-1];
}//CreateSL

void Rearrange(SqList &L,int adr[])
//adr给出顺序表L的有序次序，即L.r[adr[i]]是第i小的记录
//本算法按adr重排L.r,使其有序
{
	int i,j,k;
	for(i=1;i<L.length;++i)
	{
		if(adr[i]!=i)
		{
			j=i;
			L.r[0]=L.r[i]; //暂存记录L.r[i]
			while(adr[j]!=i)
			{ //调整L.r[adj[r]]的记录到位直到adr[j]=i为止
				k=adr[j];
				L.r[j]=L.r[k];
				adr[j]=j;
				j=k;
			}
			L.r[j]=L.r[0];
			adr[j]=j;
		}
	}
}//Rearrange



//main函数做测试用
int main()
{
	SqList l;
	CreateSL(&l);
	PrintSL(&l);
	int adr[MAXSIZE]={0,6,4,3,1,8,2,7,5};
	Rearrange(l,adr);
	PrintSL(&l);
	return 0;
}
