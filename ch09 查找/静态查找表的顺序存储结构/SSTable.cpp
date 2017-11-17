/***************************************************************************
 *  @file       SSTable.cpp
 *  @author     jz
 *  @date       31 Jan. 2016
 *  @remark     数据结构 c语言版 严蔚敏 第九章
 *  @note	静态查找表的顺序存储结构
 ***************************************************************************/
//实现用
#include<stdlib.h>
#include<stdio.h>
//#include<limits.h>
//#include<string.h>
//测试用

#include "DataStructure.h" //本书需要的一些定义

#define MAXSIZE 200 //假设表中元素个数的最大值为200 可更改
typedef int KeyType; //关键字类型说明
struct SElemType //数据元素类型定义
{
	KeyType key; //关键字域
	int data; //自定义的域
};
//对两个关键字的比较约定 数值型关键字
#define EQ(a,b) ((a)==(b))
#define LT(a,b) ((a)<(b))
#define LQ(a,b) ((a)<=(b))
//静态查找表的顺序存储结构
struct SSTable
{
	//数据元素存储空间基址，建表时按实际长度分配，0号单元留空
	SElemType *elem;
	int length; //表长度
};

int Search_Seq(SSTable ST,KeyType key)
//在顺序表ST中查找其关键字等于key的数据元素，若找到，
//则函数值为该元素在表中的位置，否则为0
{
	ST.elem[0].key=key; //"哨兵"
	int i;
	for(i=ST.length;!EQ(ST.elem[i].key,key);--i) //从后往前找
		;
	return i; //找不到时，i为0
}//Search_Seq

//自己实现的
Status CreateSSTable(SSTable &S)
//构造一个静态查找表S
{
	int i,j,n;
	printf("请输入表中元素个数：");
	scanf("%d",&n);
	S.length=n;
	SElemType *p;
	p=(SElemType *)malloc((n+1)*sizeof(SElemType));
	S.elem=p;
	puts("请输入表中元素");
	for(i=1;i<=n;++i)
	{
		S.elem[i].data=i;
		scanf("%d",&j);
		S.elem[i].key=j;
	}
	return OK;
}//CreateSSTable

//自己实现的
Status DestroySSTable(SSTable S)
//销毁静态查找表S
{
	free(S.elem);
	S.length=0;
	return OK;
}//DestroySSTable

//自己实现的
void ShowSSTable(SSTable S)
//在屏幕上输出静态查找表
{
	int i;
	puts("show SSTable ");
	for(i=1;i<=S.length;++i)
	{
		printf("[%d %d] ",S.elem[i].data,S.elem[i].key);
	}
	putchar('\n');
}
int Search_Bin(SSTable ST,KeyType key)
//在有序表ST中插半查找其关键字等于key的数据元素，
//若找到，则函数值为该元素在表中的位置，否则为0
{
	int low=1; //置区间初值
	int high=ST.length;
	int mid;
	while(low<=high)
	{
		mid=(low+high)/2;
		if(EQ(key,ST.elem[mid].key))
			return mid; //找到待查元素
		else if(LT(key,ST.elem[mid].key))
			high=mid-1; //继续在前半区间进行查找
		else
			low=mid+1; //继续在后半区间进行查找
	}
	return 0; //顺序表中不存在待查元素
}//Search_Bin


//main函数做测试用
int main()
{
	SSTable S;
	KeyType i,n;
	CreateSSTable(S);	
	ShowSSTable(S);
	printf("请输入key: ");
	scanf("%d",&n);
	i=Search_Bin(S,n);
	printf("found: %d\n",i);
	DestroySSTable(S);
	return 0;
}
