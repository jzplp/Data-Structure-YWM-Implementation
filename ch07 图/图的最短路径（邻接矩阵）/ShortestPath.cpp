/***************************************************************************
 *  @file       ShortestPath.cpp
 *  @author     jz
 *  @date       29 Jan. 2016
 *  @remark     数据结构 c语言版 严蔚敏 第七章
 *  @note	图的最短路径（邻接矩阵）
 ***************************************************************************/
//实现用
#include<stdlib.h>
#include<stdio.h>
#include<limits.h>
//#include<string.h>
//测试用

#include "DataStructure.h" //本书需要的一些定义

//=====以下为图的邻接矩阵部分，有改动=====
//__BEGIN -----复制自MGraph.cpp----
//顶点关系类型 对无权图用1或0表示相邻否；对带权图，则为权值类型
typedef int VRType; 
typedef int VertexType; //顶点数据类型
typedef char InfoType; //弧相关信息类型

#define INFINITY INT_MAX/2 //不可能取到的最大值
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

//__END -----复制自MGraph.cpp----

//仿照CreateUDN,自己实现的
Status CreateDN(MGraph &G)
//采用数组（邻接矩阵）表示法，构造有向网G
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
	puts("请输入每条边的顶点v1，v2和权值");
	for(k=0;k<G.arcnum;++k) //构造邻接矩阵
	{
		scanf("%d %d %d",&i,&j,&w);
		i=i-1;
		j=j-1;
		G.arcs[i][j].adj=w;
		if(IncInfo)
			;//输入边的信息
	}
	return OK;
}//CreateDN

//__BEGIN -----复制自MGraph.cpp----

Status CreateGraph(MGraph &G)
//采用数组（邻接矩阵）表示法，构造图G
{
	puts("请输入图的类型：1表示有向图DG，2表示有向网DN，3表示无向图UDG，4表示无向图UDN");
	int i;
	scanf("%d",&i);
	G.kind=GraphKind(i-1);
	switch(G.kind)
	{
		case DG:
			//return CreateDG(G); //构造有向图G
		case DN:
			return CreateDN(G); //构造有向网G
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

//=====以上为图的邻接矩阵部分，有改动=====
void ShortestPath_DIJ(MGraph G,int v0)
//用Dijkstra算法求有向网G的v0顶点到其余顶点v的最短路径P[v]及其带权长度D[v]
{
	v0=v0-1;
	//finally[v]为true，则当且仅当v属于S，即已经求得从v0到v的最短路径
	bool finally[MAX_VERTEX_NUM];
	//若P[v][w]为真，则w是从v0到v当前求得的（不一定是最正确的）最短路径上的顶点
	bool P[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	//D[v]存放v0到v的最短路径的带权长度
	int D[MAX_VERTEX_NUM];
	int v,i,j,w,min;
	for(v=0;v<G.vexnum;++v)
	{
		finally[v]=false;
		D[v]=G.arcs[v0][v].adj;
		for(w=0;w<G.vexnum;++w)
			P[v][w]=false; //设空路径
		if(D[v]<INFINITY)
		{
			P[v][v0]=true; //??有什么用？
			P[v][v]=true;
		}//for
	}
	D[v0]=0;
	finally[v0]=true; //初始化，顶点v0属于S集
	//开始主循环，每次求得v0到某个v顶点的最短路径，并加入到S集
	for(i=1;i<G.vexnum;++i) //其余G.vexnum-1个顶点
	{
		min=INFINITY;
		for(w=0;w<G.vexnum;++w)
		{
			if(!finally[w]) //w顶点在V-S中
				if(D[w]<min) //w顶点离v0顶点更近
				{
					v=w;
					min=D[w];
				}
		}
		finally[v]=true; //离v0顶点最近的v加入S集
		for(w=0;w<G.vexnum;++w) //更新当前最短路径及距离
		{
			if(!finally[w]&&(min+G.arcs[v][w].adj<D[w]))
			{ //修改D[w]和P[w],w属于V-S
				D[w]=min+G.arcs[v][w].adj;
				for(j=0;j<G.vexnum;++j)
					P[w][j]=P[v][j];
				P[w][w]=true; //P[w]=P[v]+[w]
			}//if
		}//for
	}//for
	printf("D[v]: ");
	for(i=0;i<G.vexnum;++i)
		printf("%d ",D[i]);
	putchar('\n');
	puts("P[v][w]: ");
	for(i=0;i<G.vexnum;++i)
	{
		for(j=0;j<G.vexnum;++j)
			printf("%d ",P[i][j]);
		putchar('\n');
	}
}//ShortestPath_DIJ

void ShortestPath_FLOYD(MGraph G)
//用Floyd算法求有向网G中各对顶点v和w之间最短路径P[v][w]及其带权长度D[v][w]
{
	int v,w,u,i;
	//若P[v][w][u]为true，则u是从v到w当前求得的最短路径上的顶点
	bool P[MAX_VERTEX_NUM][MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	int D[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

	for(v=0;v<G.vexnum;++v) //各对结点之间初始已知路径及距离
		for(w=0;w<G.vexnum;++w)
		{
			D[v][w]=G.arcs[v][w].adj;
			if(v==w) // 此处和书上不同
				D[v][w]=0;
			for(u=0;u<G.vexnum;++u)
				P[v][w][u]=false;
			if(D[v][w]<INFINITY) //从v到w有直接路径
			{
				P[v][w][v]=true;
				P[v][w][w]=true;
			}//if
		}//for
	for(u=0;u<G.vexnum;++u)
	for(v=0;v<G.vexnum;++v)
		for(w=0;w<G.vexnum;++w)
			
				if(D[v][u]+D[u][w]<D[v][w])
				{ //从v经u到w的一条路径更短
					D[v][w]=D[v][u]+D[u][w];
					for(v=0;v<G.vexnum;++v)	
						P[v][w][i]=P[v][u][i]||P[u][w][i];
				}//if
	puts("D[v][w]: ");
	for(v=0;v<G.vexnum;++v)
	{
		for(w=0;w<G.vexnum;++w)
			printf("%d ",D[v][w]);
		putchar('\n');
	}
	puts("P[v][w][u]: ");
	for(v=0;v<G.vexnum;++v)
	{
		for(w=0;w<G.vexnum;++w)
		{
			for(u=0;u<G.vexnum;++u)
				printf("%d ",P[v][w][u]);
			putchar('\n');
		}
		putchar('\n');
	}
}//ShortestPath_FLOYD






//main函数做测试用
int main()
{
	MGraph g;
	CreateGraph(g);
	ShowGraph(g);
	ShortestPath_FLOYD(g);
	return 0;
}
