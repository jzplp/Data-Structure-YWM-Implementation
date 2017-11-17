/***************************************************************************
 *  @file       BTree.cpp
 *  @author     jz
 *  @date       18 Feb. 2016
 *  @remark     数据结构 c语言版 严蔚敏 第九章
 *  @note	B树
 ***************************************************************************/
//实现用
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
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

#define M 3 //B-Tree的阶，暂设为3

typedef ElemType Record;
struct BTNode //结点类型
{
	int keynum; //结点中关键字个数
	BTNode *parent; //指向双亲节点
	KeyType key[M+1]; //关键字向量，0号单元未用
	BTNode *ptr[M+1]; //子树指针向量，0号单元用到
	Record *recptr[M+1]; //记录指针向量，0号单元未用
};
typedef BTNode * BTree; //B树类型
struct Result //B树的查找结果类型
{
	BTNode *pt; //指向找到的结点
	int i; //在结点中的关键字序号 1<=i<=m;
	int tag; //1:查找成功 2:查找失败
};

//自己实现的
int Search(BTNode *p,KeyType K)
{
	int i=1;
	while(i <= p->keynum)
	{
		if(K<=p->key[i])
			break;
		++i;
	}
	if(K==p->key[i])
		return i;
	else
		return i-1;
}//Search

Result SearchBTree(BTree T,KeyType K)
//在M阶B树上查找关键字K，返回结果(pt,i,tag).若查找成功，
//则tag=1，指针pt所指结点中第i个关键字等于K，否则特征值tag=0，
//等于k的关键字应插入在指针pt所指结点中第i个关键字和第i+1个关键字之间
{
	BTNode *p=T,*q=NULL; //p指向待查节点，q指向p的双亲
	int i=0;
	bool found=false;
	Result r;
	while(p&&!found)
	{
		i=Search(p,K);
		if(i>0 && p->key[i]==K)
			found=true;
		else
		{
			q=p;
			p=p->ptr[i];
		}
	}
	if(found) //查找成功
	{
		r.pt=p;
		r.i=i;
		r.tag=1;
	}else //查找不成功
	{
		r.pt=q;
		r.i=i;
		r.tag=0;
	}
	return r;
}//SearchBTree

//自己实现的
void Insert(BTNode *q,int i,int x,BTNode *ap)
//将x和ap分别插入到q->key[i+1]和q->ptr[i+1]
{
	int s;
	for(s=q->keynum;s>=i+1;--s)
	{
		q->key[s+1]=q->key[s];
		q->ptr[s+1]=q->ptr[s];
	}
	q->key[i+1]=x;
	q->ptr[i+1]=ap;		
	q->keynum=q->keynum+1;
}//Insert

//自己实现的
void split(BTNode *q,int s,BTree &ap)
//将q->key[s+1...M],q->ptr[s...M]和q->recptr[s+1...M]移入新结点*ap
{
	int i,c=0;
	ap=(BTree)malloc(sizeof(BTNode));
	for(i=s;i<=M;++i,++c)
	{
		ap->key[c]=q->key[i];
		ap->ptr[c]=q->ptr[i];
		ap->recptr[c]=q->recptr[i];
	}
	q->keynum=s-1;
	ap->keynum=M-s;
	ap->parent=q->parent;
}//split

//自己实现的
void NewRoot(BTree &T,BTNode *q,int x,BTNode *ap)
//T是空树(参数q初值为NULL)或者根节点已分裂为结点*q和*ap
//生成含信息(T,x,ap)的新的根节点*T，原T和ap为子树指针
{
	BTNode *b=(BTree)malloc(sizeof(BTNode));
	b->keynum=1;
	b->parent=NULL;
	b->ptr[0]=T;
	b->ptr[1]=ap;
	b->key[1]=x;
	if(T!=NULL)
		T->parent=ap->parent=b;
	T=b;
}//NewRoot
	
Status InsertBTree(BTree &T,KeyType K,BTree q,int i)
//在m阶B树上结点*q的key[i]与key[i+1]之间插入关键字K
//若引起节点过大，则沿双亲链进行必要的结点分裂调整，使T仍然是M阶B树
{
	int x=K,s;
	BTNode *ap=NULL;
	bool finished=false;
	while(q && !finished)
	{
		//将x和ap分别插入到q->key[i+1]和q->ptr[i+1];
		Insert(q,i,x,ap);
		if(q->keynum<M) //插入完成
			finished=true;
		else //分裂结点*q
		{
			s=int(ceil(double(M)/2));
			//将q->key[s+1...M],q->ptr[s...M]和q->recptr[s+1...M]移入新结点*ap
			split(q,s,ap);
			x=q->key[s];
			q=q->parent;
			if(q) //在双亲节点*q中查找x的插入位置
				i=Search(q,x);
		}
	}
	if(!finished)
		//T是空树或者(参数q初值为NULL)或者根节点已分裂为结点*和*ap
		//生成含信息(T,x,ap)的新的根节点*T，原T和ap为子树指针
		NewRoot(T,q,x,ap);
}//InsertBTree

//main函数做测试用
int main()
{
	BTree T=NULL;
	int i=1;
	Result r;
	while(i!=0)
	{
		scanf("%d",&i);
		r=SearchBTree(T,i);
		if(r.tag)
			printf("find! %p %d\n",r.pt,r.i);
		else
		{
			printf("insert! %p %d\n",r.pt,r.i);
			InsertBTree(T,i,r.pt,r.i);
		}
	}
	return 0;
}
