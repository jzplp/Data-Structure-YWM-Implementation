/***************************************************************************
 *  @file       MiniSpanTree.cpp
 *  @author     jz
 *  @date       25 Jan. 2016
 *  @remark     数据结构 c语言版 严蔚敏 第七章
 *  @note	图的最小生成树算法（邻接矩阵）
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
	puts("请输入图的类型：1表示有向图DG，2表示有向网DN，3表示无向图UDG，4表示无向图UDN");
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
//__BEGIN -----复制自TraverseMGraph.cpp----

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

//__END -----复制自TraverseMGraph.cpp----
//=====以上为图的邻接矩阵部分=====

struct CloseEdge //记录从顶点集U到V-U的代价最小的边的辅助数组的项目
{
	VertexType adjvex;
	VRType lowcost;
};

//自己实现的
int minimum(MGraph G,CloseEdge *cc)
//在辅助数组cc中求出代价最小的边（不为0）
{
	int i,sign;
	VRType mini=INFINITY;
	for(i=0;i<G.vexnum;++i)
		if(cc[i].lowcost!=0 && cc[i].lowcost<mini)
		{
			sign=i;
			mini=cc[i].lowcost;
		}
	return sign;
}//minimum

void MiniSpanTree_PRIM(MGraph G,VertexType u)
//用PRIM算法从第u个顶点出发构造网G的最小生成树，输出T的各条边。
{
	CloseEdge cc[MAX_VERTEX_NUM]; //辅助数组
	int i,j,k;
	k=u-1; //u在图中的位置
	for(j=0;j<G.vexnum;++j) //辅助数组初始化
		if(j!=k)
		{
			cc[j].adjvex=u;
			cc[j].lowcost=G.arcs[k][j].adj;
		}
	cc[k].lowcost=0; //初始U={u};
	for(i=1;i<G.vexnum;++i) //选择其余G.vexnum-1个结点
	{
		k=minimum(G,cc); //求出T的下一结点：第k结点
		printf("边：%d %d\n",cc[k].adjvex,G.vexs[k]); //输出生成树的边
		cc[k].lowcost=0; //第k结点并入U集
		for(j=0;j<G.vexnum;++j)
			if(G.arcs[k][j].adj<cc[j].lowcost)
			{
				cc[j].adjvex=G.vexs[k];
				cc[j].lowcost=G.arcs[k][j].adj;
			}
	}
}//MiniSpanTree_PRIM

//main函数做测试用
int main()
{
	MGraph g;
	CreateGraph(g);
	ShowGraph(g);
	MiniSpanTree_PRIM(g,1);
	return 0;
}
