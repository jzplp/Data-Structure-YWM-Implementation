/***************************************************************************
 *  @file       BiThrTree.cpp
 *  @author     jz
 *  @date       16 Jan. 2016
 *  @remark     数据结构 c语言版 严蔚敏 第六章
 *  @note	线索二叉树
 ***************************************************************************/
//实现用
#include<stdlib.h>
#include<stdio.h>
//测试用

#include "DataStructure.h" //本书需要的一些定义

typedef char ElemType; //数据元素的类型

enum PointerTag{Link,Thread}; //Link==0:指针，Thread==1:线索

struct BiThrNode
{
	ElemType data;
	BiThrNode *lchild,*rchild; //左右孩子指针
	PointerTag LTag,RTag;//左右标志
};
typedef BiThrNode *BiThrTree;

Status InorderTraverse_Thr(BiThrTree T,Status (*Visit)(ElemType e))
//T指向头结点，头结点的左链lchild指向根结点
//中序遍历二叉线索树T的非递归算法，对每个数据元素调用函数Visit
{
	BiThrNode *p=T->lchild; //p指向根结点
	while(p!=T) //空树或遍历结束时 p==T
	{
		while(p->LTag==Link)
			p=p->lchild;
		if(!Visit(p->data)) //访问其左子树为空的结点
			return ERROR;
		while(p->RTag==Thread && p->rchild!=T)
		{
			p=p->rchild;
			Visit(p->data); //访问后继节点
		}
		p=p->rchild;
	}
	return OK;
}//InorderTraverse_Thr

void InThreading(BiThrTree p,BiThrNode* &pre)
{
	if(p)
	{
		InThreading(p->lchild,pre); //左子树线索化
		if(!p->lchild) //前驱线索
		{
			p->LTag=Thread;
			p->lchild=pre;
		}
		if(!pre->rchild) //后继线索
		{
			pre->RTag=Thread;
			pre->rchild=p;
		}
		pre=p; //保持pre指向p的前驱
		InThreading(p->rchild,pre);//右子树线索化
	}
}//InThreading

Status InorderThreading(BiThrTree &Thrt,BiThrTree T)
//中序遍历二叉树T，并将其中序线索化，Thrt指向头结点
{
	BiThrNode *pre,p;
	if(!(Thrt=(BiThrTree)malloc(sizeof(BiThrNode))))
		exit(OVERFLOW);
	Thrt->LTag=Link; //建立头结点
	Thrt->RTag=Thread;
	Thrt->rchild=Thrt; //右指针回指
	if(!T) //若二叉树空，则左指针回指
		Thrt->lchild=Thrt;
	else
	{
		Thrt->lchild=T;
		pre=Thrt;
		InThreading(T,pre); //中序遍历进行中序线索化
		pre->rchild=Thrt; //最后一个结点线索化
		pre->RTag=Thread;
		Thrt->rchild=pre;
	}
	return OK;
}//InorderThreading

//__BEGIN -----复制自BiTree.cpp----有改动

Status CreateBiTree_PreOrder(BiThrTree &T)
//按先序次序输入二叉树中结点的值（一个字符），空格字符表示空树，
//构造二叉链表表示的二叉树T (必须把所有连接数据节点的空树输满)
{
	char ch=getchar();
	if(ch==' ')
		T=NULL;
	else
	{
		if(!(T=(BiThrNode *)malloc(sizeof(BiThrNode))))
			exit(OVERFLOW);
		T->data=ch; //生成根节点
		CreateBiTree_PreOrder(T->lchild); //构造左子树
		CreateBiTree_PreOrder(T->rchild); //构造右子树
	}
	return OK;
}//CreateBiTree_PreOrder

Status print(ElemType e)
{
	putchar(e);
	return OK;
}
//__BEGIN -----复制自BiTree.cpp----

void PreThreading(BiThrTree p,BiThrNode* &pre)
{
	if(p)
	{
		if(!p->lchild) //前驱线索
		{
			p->LTag=Thread;
			p->lchild=pre;
		}
		if(!pre->rchild) //后继线索
		{
			pre->RTag=Thread;
			pre->rchild=p;
		}
		pre=p; //保持pre指向p的前驱
		if(p->LTag==Link)
			PreThreading(p->lchild,pre); //左子树线索化
		PreThreading(p->rchild,pre);//右子树线索化
	}
}//PreThreading

Status PreorderThreading(BiThrTree &Thrt,BiThrTree T)
//先序遍历二叉树T，并将其先序线索化，Thrt指向头结点
{
	BiThrNode *pre;
	if(!(Thrt=(BiThrTree)malloc(sizeof(BiThrNode))))
		exit(OVERFLOW);
	Thrt->LTag=Link; //建立头结点
	Thrt->RTag=Thread;
	Thrt->rchild=Thrt; //右指针回指
	if(!T) //若二叉树空，则左指针回指
		Thrt->lchild=Thrt;
	else
	{
		Thrt->lchild=T;
		pre=Thrt;
		PreThreading(T,pre); //先序遍历进行先序线索化
		pre->rchild=Thrt; //最后一个结点线索化
		pre->RTag=Thread;
		Thrt->rchild=pre;
	}
	return OK;
}//PreorderThreading

Status PreorderTraverse_Thr(BiThrTree T,Status (*Visit)(ElemType e))
//T指向头结点，头结点的左链lchild指向根结点
//先序遍历二叉线索树T的非递归算法，对每个数据元素调用函数Visit
{
	puts("aaaaaaaaaaaaaaaaaaaaa");
	BiThrNode *p=T->lchild; //p指向根结点
	while(p!=T) //空树或遍历结束时 p==T
	{
		while(p->LTag==Link)
		{
			if(!Visit(p->data))
				return ERROR;
			p=p->lchild;
		}
		if(!Visit(p->data)) 
			return ERROR;
		p=p->rchild;
	}
	return OK;
}//PreorderTraverse_Thr

//main函数做测试用
int main()
{
	BiThrTree t1,t2;
	CreateBiTree_PreOrder(t1);
	PreorderThreading(t2,t1);
	PreorderTraverse_Thr(t2,print);
}


