/***************************************************************************
 *  @file       HashTable.cpp
 *  @author     jz
 *  @date       23 Feb. 2016
 *  @remark     数据结构 c语言版 严蔚敏 第九章
 *  @note	哈希表
 ***************************************************************************/
//实现用
#include<stdlib.h>
#include<stdio.h>
//#include<math.h>
//#include<limits.h>
//#include<string.h>
//测试用

#include "DataStructure.h" //本书需要的一些定义

typedef int KeyType; //关键字类型说明
struct ElemType //数据元素类型定义
{
	KeyType key; //关键字域
	int data; //自定义的域
};
//对两个关键字的比较约定 数值型关键字
#define EQ(a,b) ((a)==(b))
#define LT(a,b) ((a)<(b))
#define LQ(a,b) ((a)<=(b))

//哈希表容量递增表，一个合适的素数序列
int hashsize[8]={499,997,1453,1999,2503,3011,3499,4001};

struct HashTable
{
	ElemType *elem; //数据元素存储基址，动态分配数组
	int count; //当前数据元素个数
	int sizeindex; //hashsize[sizeindex]为当前容量
};
#define SUCCESS 1
#define UNSUCCESS 0
#define DUPLICATE -1

#define NULLKEY 0 //表示无记录

//自己实现的
int Hash(KeyType K)
{
	return K;
}//Hash

//自己实现的
int collision(int p,int c)
{
	return p+1;
}//collision

Status SearchHash(HashTable H,KeyType K,int &p,int &c)
//在开放定址Hash表中查找关键码为K的元素，若查找成功，
//以p指示待查数据元素在表中位置，并返回SUCCESS，
//否则，以p指示插入位置，并返回UNSUCCESS
//c用以计冲突次数，其初值置0，供建表插入时参考
{
	p=Hash(K); //求得哈希地址
	//该位置填有记录且关键字不相等
	while(H.elem[p].key!=NULLKEY && !EQ(K,H.elem[p].key) && p<hashsize[H.sizeindex])
		collision(p,++c); //求得下一探查地址p
	if(EQ(K,H.elem[p].key) && p<hashsize[H.sizeindex]) //查找成功
		return SUCCESS;
	else
		return UNSUCCESS;
}//SearchHash

//自己实现的
void CreateHashTable(HashTable &H)
//构造一个新的哈希表H
{
	H.elem=(ElemType *)malloc(hashsize[0]*sizeof(ElemType));
	H.count=0;
	H.sizeindex=0;
	int i;
	ElemType e;
	e.key=NULLKEY;
	for(i=0;i<hashsize[0];++i)
		H.elem[i]=e;
}//CreateHashTable

//自己实现的
void RecreateHashTable(HashTable &H)
//重建哈希表
{
	int i;
	ElemType e;
	e.key=NULLKEY;
	H.elem=(ElemType *)realloc(H.elem,hashsize[++H.sizeindex]);
	for(i=hashsize[H.sizeindex-1];i<hashsize[H.sizeindex];++i)
		H.elem[i]=e;
}//RecreateHashTable

Status InsertHash(HashTable &H,ElemType e)
//查找不成功时插入数据元素e到开放定址哈希表H中，并返回OK
//若冲突次数过大，则重建哈希表
{
	int c=0,p;
	if(SearchHash(H,e.key,p,c))
		return DUPLICATE; //表中已有和e相同关键字的元素
	else if(c<hashsize[H.sizeindex]/2 && p<hashsize[H.sizeindex]) 
	//若冲突次数未达上限（c的阈值可调）
	{ //插入e
		H.elem[p]=e;
		++H.count;
		return OK;
	}else
	{
		RecreateHashTable(H); //重建哈希表
		return UNSUCCESS;
	}
}//InsertHash

//main函数做测试用
int main()
{
	HashTable h;
	CreateHashTable(h);
	int i=1,tag;
	ElemType e;
	while(i!=0)
	{
		e.key=i;
		tag=InsertHash(h,e);
		if(tag==DUPLICATE)
			puts("Find!");
		else if(tag==OK)
			puts("Insert!");
		else
			puts("Fail! RecreateHashTable!");
		scanf("%d",&i);
	}
	return 0;
}

