/***************************************************************************
 *  @file       ALGraph.cpp
 *  @author     jz
 *  @date       21 Jan. 2016
 *  @remark     数据结构 c语言版 严蔚敏 第七章
 *  @note	图的邻接表
 ***************************************************************************/
//实现用
#include<stdlib.h>
#include<stdio.h>
//#include<limits.h>
//#include<string.h>
//测试用

#include "DataStructure.h" //本书需要的一些定义

typedef int VertexType; //顶点数据类型
typedef char InfoType; //弧相关信息类型
#define MAX_VERTEX_NUM 20 //最大顶点个数
enum GraphKind {DG,DN,UDG,UDN}; //｛有向图，有向网，无向图，无向网｝
struct ArcNode
{
	int adjvex; //该弧所指向的顶点的位置
	ArcNode * nextarc; //指向下一条弧的指针
	InfoType *info; //该弧相关信息的指针
};
struct VNode
{
	VertexType data; //顶点信息
	ArcNode * firstarc; //指向第一条依附于该顶点的弧的指针
};
typedef VNode AdjList[MAX_VERTEX_NUM];
struct ALGraph
{
	AdjList vertices;
	int vexnum,arcnum; //图的当前顶点数和弧数
	GraphKind kind; //图的种类标志
};
//__BEGIN -----复制自TopologicalSort.cpp-----

//自己实现的
Status CreateDG(ALGraph &G)
//采用邻接表存储表示，构造有向图G
{
	int i,j,k,IncInfo;
	puts("请输入顶点数，弧数和是否有弧信息(1是有,0是没有) 空格分隔");
	scanf("%d %d %d",&G.vexnum,&G.arcnum,&IncInfo);
	puts("请输入每个顶点的值");
	for(i=0;i<G.vexnum;++i) //构造顶点向量
	{
		scanf("%d",&G.vertices[i].data);
		G.vertices[i].firstarc=NULL; //初始化指针
	}
	puts("请输入每条弧的始点v1，终点v2");
	for(k=0;k<G.arcnum;++k)
	{
		scanf("%d %d",&i,&j);
		i=i-1; //确定v1和v2在G中的位置
		j=j-1;
		ArcNode *p=(ArcNode *)malloc(sizeof(ArcNode)); //假定有足够空间
		p->adjvex=j; //对弧头结点赋值
		p->nextarc=G.vertices[i].firstarc;
		p->info=NULL;
		G.vertices[i].firstarc=p; //在出弧和入弧链头的插入
		if(IncInfo)
			;//输入边的信息
	}
}//CreateDG

//自己实现的
Status ShowGraph(ALGraph G)
//采用邻接表,在屏幕上输出图g的内容
{
	int i;
	ArcNode *p;
	puts("show 邻接表");
	for(i=0;i<G.vexnum;i++)
	{
		printf("vex:%d ",G.vertices[i].data);
		p=G.vertices[i].firstarc;
		printf("firstarc:(show adjvex): ");
		while(p)
		{
			printf("%d ",(p->adjvex)+1);
			p=p->nextarc;
		}
		putchar('\n');
	}
	return OK;
}//ShowGraph

//__END -----复制自TopologicalSort.cpp-----
int main()
{
}

