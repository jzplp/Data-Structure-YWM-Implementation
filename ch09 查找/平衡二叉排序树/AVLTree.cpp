/***************************************************************************
 *  @file       AVLTree.cpp
 *  @author     jz
 *  @date       18 Feb. 2016
 *  @remark     数据结构 c语言版 严蔚敏 第九章
 *  @note	平衡二叉排序树
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

#define LH +1 //左高
#define EH 0  //等高
#define RH -1 //右高

struct AVLNode
{
	ElemType data;
	int bf; //平衡因子
	AVLNode *lchild,*rchild; //左右孩子指针
};
typedef AVLNode * AVLTree;

void R_Rotate(AVLTree &p)
//对以p为根的二叉排序树做右旋处理，处理之后p指向新的树根结点，
//即旋转处理之前的左子树的根结点
{
	AVLNode *lc=p->lchild; //lc指向的*p的左子树的根结点
	p->lchild=lc->rchild; //lc的右子树挂接为*p的左子树
	lc->rchild=p;
	p=lc; //p指向新的根结点
}//R_Rotate

void L_Rotate(AVLTree &p)
//对以p为根的二叉排序树做左旋处理，处理之后p指向新的树根结点，
//即旋转处理之前的右子树的根结点
{
	AVLNode *rc=p->rchild; //lc指向的*p的右子树的根结点
	p->rchild=rc->lchild; //lc的左子树挂接为*p的右子树
	rc->lchild=p;
	p=rc; //p指向新的根结点
}//L_Rotate

void LeftBalance(AVLTree &T)
//对以指针T所指结点为根的二叉树作左平衡旋转处理，
//本算法结束时，指针T指向新的根结点
{
	AVLTree lc,rd;
	lc=T->lchild; //lc指向T的左子树根结点
	switch(lc->bf) //检查*T的左子树的平衡度，并作相应平衡处理
	{
		case LH: //新结点插入在左孩子的左子树上，要做单右旋处理
			T->bf=lc->bf=EH;
			R_Rotate(T);
			break;
		case RH: //新结点插入在*T的左孩子的右子树上，要做双旋处理
			rd=lc->rchild; //rd指向*T的左孩子的右子树根
			switch(rd->bf)
			{
				case LH:
					T->bf=RH;
					lc->bf=EH;
					break;
				case EH:
					T->bf=lc->bf=EH;
					break;
				case RH:
					T->bf=EH;
					lc->bf=LH;
					break;
			}//switch
			rd->bf=EH;
			L_Rotate(T->lchild);
			R_Rotate(T);
	}//switch
}//LeftBalance

void RightBalance(AVLTree &T)
//对以指针T所指结点为根的二叉树作右平衡旋转处理，
//本算法结束时，指针T指向新的根结点
{
	AVLTree lc,rd;
	lc=T->rchild; //lc指向T的右子树根结点
	switch(lc->bf) //检查*T的右子树的平衡度，并作相应平衡处理
	{
		case LH: //新结点插入在右孩子的左子树上，要做双旋处理
			rd=lc->lchild; //rd指向*T的右孩子的左子树根
			switch(rd->bf)
			{
				case LH:
					T->bf=EH;
					lc->bf=RH;
					break;
				case EH:
					T->bf=lc->bf=EH;
					break;
				case RH:
					T->bf=LH;
					lc->bf=EH;
					break;
			}//switch
			rd->bf=EH;
			R_Rotate(T->rchild);
			L_Rotate(T);
		case RH: //新结点插入在*T的右孩子的右子树上，要做单左旋处理
			T->bf=lc->bf=EH;
			L_Rotate(T);
			break;	
	}//switch
}//RightBalance
Status InsertAVL(AVLTree &T,ElemType e,bool &taller)
//若在平衡的二叉树T中不存在和e有相同关键字的结点，
//则插入一个数据元素为e的新结点，并返回1，否则返回0
//若因插入使得二叉排序树失去平衡，则作平衡旋转处理，
//taller反应T长高与否，初始调用时值任意
{
	if(!T) //插入新结点，树“长高”，置taller为true
	{
		T=(AVLNode *)malloc(sizeof(AVLNode));
		T->data=e;
		T->lchild=T->rchild=NULL;
		T->bf=EH;
		taller=true;
	}else
	{
		if(EQ(e.key,T->data.key)) //树中已存在和e有相同关键字的结点，则不再插入
		{
			taller=false;
			return 0;
		}
		if(LT(e.key,T->data.key)) //应继续在*T的左子树中进行搜索
		{
			if(!InsertAVL(T->lchild,e,taller)) //未插入
				return 0;
			if(taller) //已插入到*T的左子树中且左子树“长高”
				switch(T->bf) //检查*T的平衡度
				{
					case LH: //原本左子树比右子树高，需要作左平衡处理
						LeftBalance(T);
						taller=false;
						break;
					case EH: //原本左右子树等高，现因左子树增高而使树增高
						T->bf=LH;
						taller=true;
						break;
					case RH: //原本右子树比左子树高，现左右子树等高
						T->bf=EH;
						taller=false;
						break;
				}//switch
		}else //应继续在*T的右子树中进行搜索
		{
			if(!InsertAVL(T->rchild,e,taller)) //未插入
				return 0;
			if(taller) //已插入到*T的右子树中且右子树“长高”
				switch(T->bf) //检查*T的平衡度
				{
					case LH: //原本左子树比右子树高，现左右子树等高
						T->bf=EH;
						taller=false;
						break;
					case EH: //原本左右子树等高，现因右子树增高而使树增高
						T->bf=RH;
						taller=true;
						break;
					case RH: //原本右子树比左子树高,需要作左平衡处理
						RightBalance(T);
						taller=false;
						break;
				}//switch
		}//else
	}//else
	return 1;
}//InsertAVL

//__BEGIN -----复制自BiTree.cpp-----

//自己实现的
Status InOrderTraverse(AVLTree T,Status(* Visit)(ElemType e))
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

//main函数做测试用
int main()
{
	AVLTree t=NULL;
	ElemType e;
	bool bi,taller;
	int k=1;
	while(k)
	{
		printf("search ?");
		scanf("%d",&k);
		e.key=k;
		bi=InsertAVL(t,e,taller);
		if(bi)
			puts("Insert");
		else
			puts("Found!");
	}
	putchar('\n');
	puts("OrderTraverse:");
	InOrderTraverse(t,print);
	putchar('\n');
	return 0;
}
