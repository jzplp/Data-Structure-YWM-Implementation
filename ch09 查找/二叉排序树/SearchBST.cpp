/***************************************************************************
 *  @file       SearchBST.cpp
 *  @author     jz
 *  @date       16 Feb. 2016
 *  @remark     数据结构 c语言版 严蔚敏 第九章
 *  @note	二叉排序树
 ***************************************************************************/
//实现用
#include<stdlib.h>
#include<stdio.h>
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

//=====以下为二叉树的二叉链表存储结构的部分=====
//__BEGIN -----复制自BiTree.cpp-----
struct BiTNode
{
	ElemType data;
	BiTNode *lchild,*rchild; //左右孩子指针
};
typedef BiTNode * BiTree;


//自己实现的
Status InOrderTraverse(BiTree T,Status(* Visit)(ElemType e))
//采用二叉链表存储结构，Visit是对数据元素操作的应用函数，
//中序遍历二叉树T的递归算法，对每个数据元素调用函数Visit
{
	if(T)
	{
		if(InOrderTraverse(T->lchild,Visit))
			if(Visit(T->data))
				if(InOrderTraverse(T->rchild,Visit))
					return OK;
		return ERROR;
	}else
		return OK;
}//InOrderTraverse


Status print(ElemType e)
{
	printf("%d ",e.key);
	return OK;
}//print

//__END -----复制自BiTree.cpp-----

BiTree SearchBST(BiTree T,KeyType key)
//在根指针T所指的二叉排序树中递归地查找某关键字等于key的数据元素
//若查找成功，则返回指向该数据元素结点的指针，否则返回空指针
{
	if( !T || EQ(key,T->data.key) )
		return T; //查找结束
	else if(LT(key,T->data.key)) //在左子树中继续查找
		return SearchBST(T->lchild,key);
	else //在右子树中继续查找
		return SearchBST(T->rchild,key);
}//SearchBST

Status SearchBST_F(BiTree T,KeyType key,BiTree f,BiTree &p)
//在根指针T所指的二叉排序树中递归地查找某关键字等于key的数据元素
//若查找成功，则指针p指向该数据元素结点,并返回true，否则指针p指向查找路径
//上访问的最后一个结点并返回false，指针f指向T的双亲，其初始调用值为NULL
{
	if(!T) //查找不成功
	{
		p=f;
		return false;
	}else if(EQ(key,T->data.key)) //查找结束
	{
		p=T;
		return true; 
	}else if(LT(key,T->data.key)) //在左子树中继续查找
		return SearchBST_F(T->lchild,key,T,p);
	else //在右子树中继续查找
		return SearchBST_F(T->rchild,key,T,p);
}//SearchBST_F

Status InsertBST(BiTree &T,ElemType e)
//当二叉树T中不存在关键字等于e.key的数据元素时，
//插入e并返回true，否则返回false
{
	BiTNode *p,*s;
	if(!SearchBST_F(T,e.key,NULL,p)) //查找不成功
	{
		s=(BiTree)malloc(sizeof(BiTNode));
		s->data=e;
		s->lchild=s->rchild=NULL;
		if(!p) //*s为新的根结点
			T=s;
		else if(LT(e.key,p->data.key)) //*s为左孩子
			p->lchild=s;
		else //*s为右孩子
			p->rchild=s;
		return true;
	}else
		return false;
}//InsertBST

Status Delete(BiTree &p)
//从二叉排序树中删除结点p，并重接它的左和右子树
{
	BiTNode *q,*s;
	if(!p->rchild) //右子树空则只需重接它的左子树
	{
		q=p;
		p=p->lchild;
		free(q);
	}
	else if(!p->lchild) //左子树空则只需重接它的右子树
	{
		q=p;
		p=p->rchild;
		free(q);
	}
	else //左右子树均不空
	{
		q=p;
		s=p->lchild; //转左
		while(s->rchild) //然后向右到尽头
		{
			q=s;
			s=s->rchild;
		}
		p->data=s->data;
		if(q!=p)
			q->rchild=s->lchild; //重接*q的右子树
		else
			q->lchild=s->lchild; //重接*q的左子树
		free(s);
	}
	return true;
}//Delete

Status DeleteBST(BiTree &T,KeyType key)
//若二叉排序树T中存在关键字等于key的数据元素时，删除该数据元素结点，
//并返回true，否则返回false
{
	if(!T) //不存在关键字等于k的数据元素
		return false;
	else
	{
		if(EQ(key,T->data.key)) //找到了
			return Delete(T);
		else if(LT(key,T->data.key))
			return DeleteBST(T->lchild,key);
		else
			return DeleteBST(T->rchild,key);
	}
}//DeleteBST


//main函数做测试用
int main()
{
	BiTree b=NULL;
	ElemType e;
	bool bi;
	int k=1;
	while(k)
	{
		printf("search ?");
		scanf("%d",&k);
		e.key=k;
		bi=InsertBST(b,e);
		if(bi)
			puts("Insert");
		else
			puts("Found!");
	}
	putchar('\n');
	puts("OrderTraverse:");
	InOrderTraverse(b,print);
	putchar('\n');
	while(k!=12345)
	{
		printf("delete ?");
		scanf("%d",&k);
		bi=DeleteBST(b,k);
		if(bi)
			puts("Delete!");
		else
			puts("NOT Found!");
		puts("OrderTraverse:");
		InOrderTraverse(b,print);
		putchar('\n');
		putchar('\n');
	}

	return 0;
}
