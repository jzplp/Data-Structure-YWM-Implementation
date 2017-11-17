/***************************************************************************
 *  @file       OLGraph.cpp
 *  @author     jz
 *  @date       22 Jan. 2016
 *  @remark     数据结构 c语言版 严蔚敏 第七章
 *  @note	有向图的十字链表
 ***************************************************************************/
//实现用
#include<stdlib.h>
#include<stdio.h>
#include<limits.h>
//#include<string.h>
//测试用

#include "DataStructure.h" //本书需要的一些定义

typedef int VertexType; //顶点数据类型
typedef char InfoType; //弧相关信息类型
#define MAX_VERTEX_NUM 20 //最大顶点个数
struct ArcBox
{
	int tailvex,headvex; //该弧的头和尾顶点的位置
	ArcBox * hlink,* tlink; //分别为弧头相同和弧尾相同的弧的链域
	InfoType *info; //该弧相关信息的指针
};
struct VexNode
{
	VertexType data;
	ArcBox * firstin,* firstout; //分别指向该顶点的第一条入弧和出弧
};
struct OLGraph
{
	VexNode xlist[MAX_VERTEX_NUM]; //表头向量
	int vexnum,arcnum; //有向图的当前顶点数和弧数
};

Status CreateDG(OLGraph &G)
//采用十字链表存储表示，构造有向图G
{
	int i,j,k,IncInfo;
	puts("请输入顶点数，弧数和是否有弧信息(1是有,0是没有) 空格分隔");
	scanf("%d %d %d",&G.vexnum,&G.arcnum,&IncInfo);
	puts("请输入每个顶点的值");
	for(i=0;i<G.vexnum;++i) //构造顶点向量
	{
		scanf("%d",&G.xlist[i].data);
		G.xlist[i].firstin=NULL; //初始化指针
		G.xlist[i].firstout=NULL;
	}
	puts("请输入每条弧的始点v1，终点v2");
	for(k=0;k<G.arcnum;++k)
	{
		scanf("%d %d",&i,&j);
		i=i-1; //确定v1和v2在G中的位置
		j=j-1;
		ArcBox *p=(ArcBox *)malloc(sizeof(ArcBox)); //假定有足够空间
		p->tailvex=i; //对弧头结点赋值
		p->headvex=j;
		p->hlink=G.xlist[j].firstin;
		p->tlink=G.xlist[i].firstout;
		p->info=NULL;
		G.xlist[j].firstin=G.xlist[i].firstout=p; //在出弧和入弧链头的插入
		if(IncInfo)
			;//输入边的信息
	}
}//CreateDG

//自己实现的
Status ShowGraph(OLGraph G)
//在屏幕上输出图g的内容
{
	int i;
	ArcBox *p;
	for(i=0;i<G.vexnum;i++)
	{
		printf("vex:%d ",G.xlist[i].data);
		p=G.xlist[i].firstin;
		printf("firstin:(show tailvex): ");
		while(p)
		{
			printf("%d ",(p->tailvex)+1);
			p=p->hlink;
		}
		putchar('\n');
		p=G.xlist[i].firstout;
		printf("firstin:(show headvex): ");
		while(p)
		{
			printf("%d ",(p->headvex)+1);
			p=p->tlink;
		}
		putchar('\n');
	}
}//ShowGraph
		
//main函数做测试用
int main()
{
	OLGraph g;
	CreateDG(g);
	ShowGraph(g);
	return 0;
}
