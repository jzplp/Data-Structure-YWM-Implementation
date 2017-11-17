/***************************************************************************
 *  @file       BiTree.cpp
 *  @author     jz
 *  @date       14 Jan. 2016
 *  @remark     数据结构 c语言版 严蔚敏 第六章
 *  @note	二叉树的二叉链表存储结构 各种遍历算法
 ***************************************************************************/
//实现用
#include<stdlib.h>
#include<stdio.h>
//测试用

#include "DataStructure.h" //本书需要的一些定义

typedef char ElemType; //数据元素的类型
struct BiTNode
{
	ElemType data;
	BiTNode *lchild,*rchild; //左右孩子指针
};
typedef BiTNode * BiTree;

//=====以下为栈的部分=====
//__BEGIN -----复制自SqStack.cpp-----

typedef BiTNode * SElemType; //数据元素的类型，测试用，可更改

#define STACK_INIT_SIZE 100 //存储空间初始分配量
#define STACK_INCREMENT 10 //存储空间分配增量

struct SqStack
{
	SElemType * base; //在构造之前和销毁之后，base的值为null
	SElemType * top; //栈顶指针
	int StackSize; //当前已分配的存储空间，以元素为单位
};

Status InitStack (SqStack &S)
//构造一个空栈
{
	S.base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if(!S.base) //存储分配失败
		exit(OVERFLOW);
	S.top=S.base;
	S.StackSize=STACK_INIT_SIZE;
	return OK;
}//InitStack

Status GetTop(SqStack S,SElemType &e)
//若栈不空 则返回S的栈顶元素e
{
	if(S.top==S.base) //栈为空
		return ERROR;
	e=*(S.top-1);
	return OK;
}//GetTop

Status Push(SqStack &S,SElemType e)
//插入元素e为新的栈顶元素
{
	if(S.top-S.base>=S.StackSize)//栈满，追加存储空间
	{
		S.base=(SElemType *)realloc(S.base,(S.StackSize+STACK_INCREMENT)*sizeof(SElemType));
		if(!S.base)  //存储分配失败
			exit(OVERFLOW);
		S.top=S.base+S.StackSize;
		S.StackSize+=STACK_INCREMENT;
	}
	*S.top++=e;
	return OK;
}//Push

Status Pop(SqStack &S,SElemType &e)
//若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK，否则返回ERROR
{
	if(S.top==S.base) //空栈
		return ERROR;
	e=*--S.top;
	return OK;
}//Pop

//自己实现的
Status DestroyStack(SqStack &S)
//销毁栈S，S不再存在
{
	free(S.base);
	S.base=S.top=NULL;
	S.StackSize=0;
	return OK;
}//DestroyStack

//__BEGIN -----复制自Conversion.cpp-----

//自己实现的
Status StackEmpty(SqStack S)
//若栈S为空栈，则返回ture，否则返回false
{
	if(S.top==S.base) //空栈
		return true;
	return false;
}//StackEmpty

//__END -----复制自Conversion.cpp-----

//__BEGIN -----复制自LineEdit.cpp-----

//自己实现的
void ClearStack(SqStack &S)
//把S置为空栈
{
	S.top=S.base;
}//ClearStack

//__END -----复制自LineEdit.cpp-----
//=====以上为栈的部分=====


Status PreOrderTraverse(BiTree T,Status(* Visit)(ElemType e))
//采用二叉链表存储结构，Visit是对数据元素操作的应用函数，
//先序遍历二叉树T的递归算法，对每个数据元素调用函数Visit
{
	if(T)
	{
		if(Visit(T->data))
			if(PreOrderTraverse(T->lchild,Visit))
				if(PreOrderTraverse(T->rchild,Visit))
					return OK;
		return ERROR;
	}else
		return OK;
}//PreOrderTraverse

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

//自己实现的
Status PostOrderTraverse(BiTree T,Status(* Visit)(ElemType e))
//采用二叉链表存储结构，Visit是对数据元素操作的应用函数，
//后序遍历二叉树T的递归算法，对每个数据元素调用函数Visit
{
	if(T)
	{
		if(PostOrderTraverse(T->lchild,Visit))
			if(PostOrderTraverse(T->rchild,Visit))
				if(Visit(T->data))
					return OK;
		return ERROR;
	}else
		return OK;
}//PostOrderTraverse

Status PreOrderTraverse1(BiTree T,Status(* Visit)(ElemType e))
//采用二叉链表存储结构，Visit是对数据元素操作的应用函数，
//先序遍历二叉树T的非递归算法1，对每个数据元素调用函数Visit
{
	SqStack S;
	InitStack(S);
	Push(S,T); //根指针进栈
	BiTNode *p;
	while(!StackEmpty(S))
	{
		while(GetTop(S,p)&&p) //走到最左边尽头
		{
			if(!Visit(p->data))
			{
				DestroyStack(S);
				return ERROR;
			}
			Push(S,p->lchild);
		}
		Pop(S,p); //空指针退栈
		if(!StackEmpty(S)) //访问节点，向右一步
		{
			Pop(S,p);
			Push(S,p->rchild);
		}//if
	}//while
	DestroyStack(S);
	return OK;
}//PreOrderTraverse1

Status InOrderTraverse1(BiTree T,Status(* Visit)(ElemType e))
//采用二叉链表存储结构，Visit是对数据元素操作的应用函数，
//中遍历二叉树T的非递归算法1，对每个数据元素调用函数Visit
{
	SqStack S;
	InitStack(S);
	Push(S,T); //根指针进栈
	BiTNode *p;
	while(!StackEmpty(S))
	{
		while(GetTop(S,p)&&p) //走到最左边尽头
			Push(S,p->lchild); 
		Pop(S,p); //空指针退栈
		if(!StackEmpty(S)) //访问节点，向右一步
		{
			Pop(S,p);
			if(!Visit(p->data))
			{
				DestroyStack(S);
				return ERROR;
			}
			Push(S,p->rchild);
		}//if
	}//while
	DestroyStack(S);
	return OK;
}//InOrderTraverse1

Status InOrderTraverse2(BiTree T,Status(* Visit)(ElemType e))
//采用二叉链表存储结构，Visit是对数据元素操作的应用函数，
//中遍历二叉树T的非递归算法2，对每个数据元素调用函数Visit
{
	SqStack S;
	InitStack(S);
	BiTNode *p=T;
	while(p||!StackEmpty(S))
	{
		if(p) //根指针进栈，遍历左子树
		{
			Push(S,p);
			p=p->lchild;
		}else //根指针退栈，访问根节点，遍历右子树
		{
			Pop(S,p);
			if(!Visit(p->data))
			{
				DestroyStack(S);
				return ERROR;
			}
			p=p->rchild;
		}//else
	}//while
	DestroyStack(S);
	return OK;
}//InOrderTraverse2

//网上的算法
Status PostOrderTraverse1(BiTree T,Status(* Visit)(ElemType e))
//采用二叉链表存储结构，Visit是对数据元素操作的应用函数，
//后序遍历二叉树T的非递归算法1，对每个数据元素调用函数Visit
{
	SqStack S;
	InitStack(S);
	Push(S,T); //根指针进栈
	BiTNode *p,*pre=NULL; //pre指向已访问过的最后一个结点。
	while(!StackEmpty(S))
	{
		//获取栈顶指针，如果当前结点有左子树，并且左子树结点不是刚被访问的节点；
		//如果当前结点有右子树，并且右子树结点不是刚被访问的结点,
		//表明栈顶指针指向的树结点未被访问，且左子树和右子树均未被访问。
		//此时，将结点的左子树进栈。
		if(GetTop(S,p) && p->lchild && pre!=p->lchild && !(p->rchild && pre == p->rchild))
			Push(S, p->lchild);
		//如果栈顶指针的右子树存在，且未被访问。则将右子树进栈
		else if (p->rchild && pre!=p->rchild)
			Push(S,p->rchild);
		//如果左子树和右子树均被访问过，则结点退栈，并进行访问。更新pre。
		else
		{
			Pop(S,p);
			if (!Visit(p->data))
			{
				DestroyStack(S);
				return ERROR;
			}
			pre = p;
		}
	}
	DestroyStack(S);
	return OK;
}//PostOrderTraverse1

Status CreateBiTree_PreOrder(BiTree &T)
//按先序次序输入二叉树中结点的值（一个字符），空格字符表示空树，
//构造二叉链表表示的二叉树T (必须把所有连接数据节点的空树输满)
{
	char ch=getchar();
	if(ch==' ')
		T=NULL;
	else
	{
		if(!(T=(BiTNode*)malloc(sizeof(BiTNode))))
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
//main函数做测试用
int main()
{
	BiTree b;
	CreateBiTree_PreOrder(b);
	puts("PreOrderTraverse:");
	PreOrderTraverse(b,print);
	putchar('\n');
	puts("PreOrderTraverse1:");
	PreOrderTraverse1(b,print);
	putchar('\n');
	puts("InOrderTraverse:");
	InOrderTraverse(b,print);
	putchar('\n');
	puts("InOrderTraverse1:");
	InOrderTraverse1(b,print);
	putchar('\n');
	puts("InOrderTraverse2:");
	InOrderTraverse1(b,print);
	putchar('\n');
	puts("PostOrderTraverse:");
	PostOrderTraverse(b,print);
	putchar('\n');
	puts("PostOrderTraverse1:");
	PostOrderTraverse1(b,print);
	putchar('\n');
	return 0;
}
