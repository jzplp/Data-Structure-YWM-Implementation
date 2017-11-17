/***************************************************************************
 *  @file       TraverseMGraph.cpp
 *  @author     jz
 *  @date       21 Jan. 2016
 *  @remark     数据结构 c语言版 严蔚敏 第七章
 *  @note	图的遍历算法 以邻接矩阵为存储结构
 ***************************************************************************/
//实现用
#include<stdlib.h>
#include<stdio.h>
#include<limits.h>
//#include<string.h>
//测试用

#include "DataStructure.h" //本书需要的一些定义

//=====以下为图的邻接矩阵部分=====
//__BEGIN -----复制自MGraph.cpp----

//顶点关系类型 对无权图用1或0表示相邻否；对带权图，则为权值类型
typedef int VRType; 
typedef int VertexType; //顶点数据类型
typedef char InfoType; //弧相关信息类型

#define INFINITY INT_MAX //不可能取到的最大值
#define MAX_VERTEX_NUM 20 //最大顶点个数
enum GraphKind {DG,DN,UDG,UDN}; //｛有向图，有向网，无向图，无向网｝
struct ArcCell
{
	VRType adj; //顶点关系
	InfoType *info; //该弧相关信息的指针
};
typedef ArcCell AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
struct MGraph
{
	VertexType vexs[MAX_VERTEX_NUM]; //顶点向量
	AdjMatrix arcs; //邻接矩阵
	int vexnum,arcnum; //图的当前顶点数和弧数
	GraphKind kind; //图的种类标志
};

Status CreateUDN(MGraph &G)
//采用数组（邻接矩阵）表示法，构造无向网G
{
	int i,j,k,w,IncInfo;
	puts("请输入顶点数，弧数和是否有弧信息（1是有，0是没有） 空格分隔");
	scanf("%d %d %d",&G.vexnum,&G.arcnum,&IncInfo);
	puts("请输入每个顶点的值");
	for(i=0;i<G.vexnum;++i) //构造顶点向量
		scanf("%d",&G.vexs[i]);
	for(i=0;i<G.vexnum;++i) //初始化邻接矩阵
		for(j=0;j<=G.vexnum;++j)
		{
			G.arcs[i][j].adj=INFINITY;
			G.arcs[i][j].info=NULL;
		}
	puts("请输入每条边的两个顶点和权值");
	for(k=0;k<G.arcnum;++k) //构造邻接矩阵
	{
		scanf("%d %d %d",&i,&j,&w);
		i=i-1;
		j=j-1;
		G.arcs[i][j].adj=w;
		if(IncInfo)
			;//输入边的信息
		G.arcs[j][i].adj=G.arcs[i][j].adj; //置<v1,v2>的对称弧<v2,v1>
		G.arcs[j][i].info=G.arcs[i][j].info;
	}
	return OK;
}//CreateUDN

Status CreateGraph(MGraph &G)
//采用数组（邻接矩阵）表示法，构造图G
{
	puts("请输入图的类型：0表示有向图DG,1表示有向网DN,2表示无向图UDG,3表示无向图UDN");
	scanf("%d",&G.kind);
	switch(G.kind)
	{
		case DG:
			//return CreateDG(G); //构造有向图G
		case DN:
			//return CreateDN(G); //构造有向网G
		case UDG:
			//return CreateUDG(G); //构造无向图G
		case UDN:
			return CreateUDN(G); //构造无向网G
		default:
			return ERROR;
	}
}//CreateGraph

//自己实现的
Status ShowGraph(MGraph G)
//在屏幕上输出图g的内容
{
	int i,j;
	puts("vexs:");
	for(i=0;i<G.vexnum;++i)
		printf("%d ",G.vexs[i]);
	putchar('\n');
	puts("arcs:");
	for(i=0;i<G.vexnum;++i)
	{
		for(j=0;j<G.vexnum;++j)
		{
			if(G.arcs[i][j].adj==INFINITY)
				printf("0 ");
			else
				printf("%d ",G.arcs[i][j].adj);
		}
		putchar('\n');
	}
}//ShowGraph

//__END -----复制自MGraph.cpp----

//自己实现的
int FirstAdjVex(MGraph G,int v)
//采用数组（邻接矩阵）表示法，返回结点v的第一个(以v为弧尾的弧的)邻接顶点,若没有则返回-1
{
	int i=0;
	while(i<G.vexnum && G.arcs[v][i].adj==INFINITY)
		++i;
	if(i==G.vexnum)
		return -1;
	else
		return i;
}//FirstAdjVex

//自己实现的
int NextAdjVex(MGraph G,int v,int w)
//采用数组（邻接矩阵）表示法，返回结点v的(以v为弧尾的弧的)下一个（相对于w的）邻接顶点,若没有则返回-1
{
	int i=w+1;
	while(i<G.vexnum && G.arcs[v][i].adj==INFINITY)
		++i;
	if(i>=G.vexnum)
		return -1;
	else
		return i;
}//NextAdjVex

//=====以上为图的邻接矩阵部分=====

bool visited[MAX_VERTEX_NUM]; //访问标志数组

void DFS(MGraph G,int v,Status (*Visit)(MGraph G,int v))
//从第v个顶点出发递归地深度优先遍历图G
{
	int w;
	visited[v]=true;
	Visit(G,v); //访问第v个顶点
	for(w=FirstAdjVex(G,v);w>=0;w=NextAdjVex(G,v,w))
		if(!visited[w]) //对v的尚未访问的邻接顶点w递归调用DFS
			DFS(G,w,Visit);
}//DFS

void DFSTraverse(MGraph G,Status (*Visit)(MGraph G,int v))
//对图G做深度优先遍历
{
	int v;
	for(v=0;v<G.vexnum;++v) //访问标志数组初始化
		visited[v]=false;
	for(v=0;v<G.vexnum;++v)
		if(!visited[v]) //对尚未访问的顶点调用DFS
			DFS(G,v,Visit); 
}//DFSTraverse

//自己实现的
Status PrintVex(MGraph G,int v)
{
	printf("%d ",G.vexs[v]);
	return OK;
}
//=====以下为栈的部分=====
//__BEGIN -----复制自LinkQueue.cpp-----

typedef int ElemType; //数据元素的类型，测试用，可更改

struct QNode
{
	ElemType data;
	struct QNode * next;
};

typedef QNode * QueuePtr;

struct LinkQueue
{
	QueuePtr front; //队头指针
	QueuePtr rear; //队尾指针
};

Status InitQueue(LinkQueue &Q)
//构造一个空队列Q
{
	Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode));
	if(!Q.front) //存储分配失败
		exit(OVERFLOW);
	Q.front->next=NULL;
	return OK;
}//InitQueue

Status DestroyQueue(LinkQueue &Q)
//销毁队列Q
{
	while(Q.front)
	{
		Q.rear=Q.front->next;
		free(Q.front);
		Q.front=Q.rear;
	}
	return OK;
}//DestroyQueue

Status EnQueue(LinkQueue &Q,ElemType e)
//插入元素e为队列Q的新的队尾元素
{
	QueuePtr p=(QueuePtr)malloc(sizeof(QNode));
	if(!p)
		exit(OVERFLOW); //存储分配失败
	p->data=e;
	p->next=NULL;
	Q.rear->next=p;
	Q.rear=p;
	return OK;
}//EnQueue

Status DeQueue(LinkQueue &Q,ElemType &e)
//若队列不空，则删除Q的队头元素，用e返回其值，并返回OK
//否则返回ERROR
{
	if(Q.front==Q.rear) //队列为空
		return ERROR;
	QueuePtr p=Q.front->next;
	e=p->data;
	Q.front->next=p->next;
	if(Q.rear==p) //队列中仅有一个元素
		Q.rear=Q.front;
	free(p);
	return OK;
}//DeQueue
//__END -----复制自LinkQueue.cpp-----

//__BEGIN -----复制自Bank_Simulation.cpp-----

//自己实现的
int QueueLength(LinkQueue &Q)
//返回链式队列Q的元素个数，即队列的长度
{
	int i=1;
	QueuePtr lq=Q.front->next;
	if(lq==NULL)
		return 0;
	while(lq!=Q.rear)
	{
		i++;
		lq=lq->next;
	}
	return i;
}//QueueLength

//自己实现的
Status QueueEmpty(LinkQueue Q)
//若队列Q为空队列，则返回true，否则返回false
{
	return (Q.front==Q.rear);
}//QueueEmpty

//自己实现的
Status Gethead(LinkQueue Q,ElemType &e)
//若队列不空，则用e返回Q的队头元素，并返回OK，否则返回error
{
	if(Q.front==Q.rear)
		return ERROR;
	e=Q.front->next->data;
	return OK;
}//Gethead

//__END -----复制自Bank_Simulation.cpp----

//=====以上为栈的部分=====
void BFSTraverse(MGraph G,Status (*Visit)(MGraph G,int v))
//按广度优先非递归遍历图G。使用辅助队列Q和访问标志数组visited
{
	int v,w,u;
	LinkQueue Q;
	for(v=0;v<G.vexnum;++v)
		visited[v]=false;
	for(v=0;v<G.vexnum;++v)
	{
		if(!visited[v])
		{
			InitQueue(Q);
			visited[v]=true;
			Visit(G,v);
			EnQueue(Q,v);
			while(!QueueEmpty(Q))
			{
				DeQueue(Q,u);
				for(w=FirstAdjVex(G,u);w>=0;w=NextAdjVex(G,u,w))
					if(!visited[w])
					{
						visited[w]=true;
						Visit(G,w);
						EnQueue(Q,w);
					}//if
			}//while
			DestroyQueue(Q);
		}//if
	}//for
}//BFSTraverse


//main函数做测试用
int main()
{
	MGraph g;
	CreateGraph(g);
	ShowGraph(g);
	printf("BFSTraverse: ");
	BFSTraverse(g,PrintVex);
	return 0;
}
