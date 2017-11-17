/***************************************************************************
 *  @file       LinearList.cpp
 *  @author     jz
 *  @date       11 Oct. 2015
 *  @remark     数据结构 c语言版 严蔚敏 第二章
 *  @note	数据结构线性表顺序存储结构的实现 数组形式
 ***************************************************************************/
//实现用
#include<stdlib.h>
//测试用
#include<stdio.h>

#include "DataStructure.h"//本书需要的一些定义

typedef int ElemType; //数据元素的类型，测试用，可更改

//线性表的动态分配顺序存储结构
#define LIST_INIT_SIZE 100 //线性表存储空间的初始分配量
#define LIST_INCREMENT 100 //线性表存储空间的分配增量

typedef struct
{
	ElemType *elem; //存储空间基址
	int length; //当前长度
	int ListSize; //当前分配的存储容量（以sizeof(ElemType)为单位）
}SqList;
Status InitList_Sq(SqList &L)
{
//构造一个空的线性表L
	L.elem=(ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if(!L.elem)
		exit(OVERFLOW); //存储分配失败
	L.length=0; //空表 长度为0
	L.ListSize=LIST_INIT_SIZE; //初始存储容量
	return OK;
}//InitList_Sq

Status ListInsert_Sq(SqList &L,int i,ElemType e)
{
//在顺序存储表中第i个位置之前插入新的元素e
//i的合法值为1<=i<=L.length+1
	if(i<1||i>L.length+1)
		return ERROR; //i值不合法
	if(L.length>=L.ListSize)
	{//当前存储空间已满 增加分配
		ElemType * newbase=(ElemType *)realloc(L.elem,(L.ListSize+LIST_INCREMENT)*sizeof(ElemType));
		if(!newbase)
			exit(OVERFLOW); //存储分配失败
		L.elem=newbase; //新基址
		L.ListSize+=LIST_INCREMENT; //增加存储容量
	}
	ElemType * InPosition=&(L.elem[i-1]); //InPosition为插入位置
	for(ElemType * p=&(L.elem[L.length-1]);p>=InPosition;--p)
		*(p+1)=*p; //插入位置之后的元素右移
	*InPosition=e; //插入e
	++L.length; //表长增1
	return OK;
}//ListInsert_Sq

Status ListDelete_Sq(SqList &L,int i,ElemType &e)
{
//在顺序线性表中删除第i个元素，并用e返回其值
//i的合法值为1<=i<=L.length
	if((i<1)||(i>L.length))
		return ERROR; //i值不合法
	ElemType *InPosition=&L.elem[i-1]; //InPosition为被删除元素的位置
	e=*InPosition; //被删除元素值赋给e
	ElemType *EndPosition=L.elem+L.length-1; //表尾元素的位置
	for(++InPosition;InPosition<=EndPosition;++InPosition)
		*(InPosition-1)=*InPosition; //被删除元素之后的元素左移；
	--L.length;
	return OK;
}//ListDelete_Sq

//自己实现的
Status GetElem_Sq(SqList &L,int i,ElemType &e)
{
//用e返回L中第i个数据元素的值
//i的合法值为1<=i<=L.length
	if((i<1)||(i>L.length))
		return ERROR; //i值不合法
	e=L.elem[i-1];
	return OK;
}//GetElem_Sq

//自己实现的
Status DestroyList_Sq(SqList &L)
{
//销毁线性表L
	free(L.elem); //释放数组内存；
	L.length=0; //长度为0
	L.ListSize=0; //分配的存储容量为0
	return OK;
}//DestroyList_Sq

int LocateELem_Sq(SqList L,ElemType e,Status (* compare)(ElemType,ElemType))
{
//在顺序线性表L中查找第一个值与e满足compare()的元素(compare返回1)的位序
//若找到，则返回其在L中的位序，否则返回0
	int i=1; //i的初值为第一个元素的存储位置
	ElemType *p=L.elem; //p的初值为第一个元素的存储位置
	while(i<=L.length && !compare(*p++,e))
		++i; //查找具体位置
	if(i<=L.length)
		return i; //如果有就返回位置i
	else
		return 0; //否则返回0
}//LocateELem_Sq

//自己实现的
//测试LocateELem_Sq函数用
Status equal(ElemType p1,ElemType p2)
{
//比较两个元素的值 若相等就返回1，否则返回0
	if(p1==p2)
		return 1;
	return 0;
}//equal

//自己实现的
void UnionList_Sq(SqList &La,SqList Lb)
{
//将所有在线性表Lb但不在线性表La中的数据元素插入到La中
	int La_len=La.length,Lb_len=Lb.length; //求线性表的长度
	ElemType e; //暂时存放数据用
	for(int i=1;i<=Lb_len;++i)
	{
		GetElem_Sq(Lb,i,e); //取Lb中第i个数据元素赋给e
		if(!LocateELem_Sq(La,e,equal))
			ListInsert_Sq(La,++La_len,e); //如果La中不存在和e相同的数据元素，则插入之
	}
}//UnionList_Sq

void MergeList_Sq(SqList La,SqList Lb,SqList &Lc)
{
//已知顺序线性表La和Lb的元素按值非递减排列
//归并La和Lb得到新的顺序线性表Lc，Lc的元素也按值非递减排列
//Lc为未初始化的顺序线性表
	ElemType *pa=La.elem,*pb=Lb.elem;
	//初始化Lc大小为La和Lb元素的和
	Lc.ListSize=Lc.length=La.length+Lb.length;
	ElemType *pc=Lc.elem=(ElemType *)malloc(Lc.ListSize*sizeof(ElemType));
	if(!Lc.elem)
		exit(OVERFLOW); //存储分配失败
	//pa_last与pb_last 为对应线性表的最后一个元素的位置
	ElemType *pa_last=La.elem+La.length-1;
	ElemType *pb_last=Lb.elem+Lb.length-1;
	while(pa<=pa_last&&pb<=pb_last)//归并过程
	{
		if(*pa<=*pb)
			*pc++=*pa++;
		else
			*pc++=*pb++;
	}
	//若La或Lb有剩余未归并 则插到Lc末尾
	while(pa<=pa_last)
		*pc++=*pa++;
	while(pb<=pb_last)
		*pc++=*pb++;
}//MergeList_Sq

//main函数做测试用
int main()
{
	SqList l1,l2,l3;
	InitList_Sq(l1);
	InitList_Sq(l2);
	for(int i=1;i<=10;i++)
	{
		ListInsert_Sq(l1,i,i*2);
		ListInsert_Sq(l2,i,i*3);
	}
	ElemType e;
	for(int i=10;i>0;--i)
	{
		//GetElem_Sq(l1,i,e);
		//ListDelete_Sq(l1,i,e);
		//printf("%d ",e);
	}

	//UnionList_Sq(l1,l2);
	MergeList_Sq(l1,l2,l3);
	for(int i=1;i<l3.length;i++)
	{	
		GetElem_Sq(l3,i,e);
		printf("%d ",e);
	}
	//printf("\n %d \n",LocateELem_Sq(l1,10,equal));
	DestroyList_Sq(l1);
	DestroyList_Sq(l2);
	
	return 0;
}

	
	
