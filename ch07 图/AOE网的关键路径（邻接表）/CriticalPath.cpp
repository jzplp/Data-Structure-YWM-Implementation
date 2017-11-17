/***************************************************************************
 *  @file       CriticalPath.cpp
 *  @author     jz
 *  @date       28 Jan. 2016
 *  @remark     数据结构 c语言版 严蔚敏 第七章
 *  @note	AOE网的关键路径（邻接表）
 ***************************************************************************/
//实现用
#include<stdlib.h>
#include<stdio.h>
//#include<limits.h>
//#include<string.h>
//测试用

#include "DataStructure.h" //本书需要的一些定义

typedef int VertexType; //顶点数据类型
typedef int InfoType; //弧相关信息类型
#define MAX_VERTEX_NUM 20 //最大顶点个数
enum GraphKind {DG,DN,UDG,UDN}; //｛有向图，有向网，无向图，无向网｝
struct ArcNode
{
	int adjvex; //该弧所指向的顶点的位置
	ArcNode * nextarc; //指向下一条弧的指针
	InfoType info; //该弧相关信息
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

//自己实现的
Status CreateDG(ALGraph &G)
//采用邻接表存储表示，构造有向图G
{
	int i,j,k,c;
	puts("请输入顶点数，弧数");
	scanf("%d %d",&G.vexnum,&G.arcnum);
	puts("请输入每个顶点的值");
	for(i=0;i<G.vexnum;++i) //构造顶点向量
	{
		scanf("%d",&G.vertices[i].data);
		G.vertices[i].firstarc=NULL; //初始化指针
	}
	puts("请输入每条弧的始点v1，终点v2,权");
	for(k=0;k<G.arcnum;++k)
	{
		scanf("%d %d %d",&i,&j,&c);
		i=i-1; //确定v1和v2在G中的位置
		j=j-1;
		ArcNode *p=(ArcNode *)malloc(sizeof(ArcNode)); //假定有足够空间
		p->adjvex=j; //对弧头结点赋值
		p->nextarc=G.vertices[i].firstarc;
		p->info=c;
		G.vertices[i].firstarc=p; //在出弧和入弧链头的插入
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
			printf("(%d %d) ",(p->adjvex)+1,p->info);
			p=p->nextarc;
		}
		putchar('\n');
	}
	return OK;
}//ShowGraph

//自己实现的
Status FindInDegree(ALGraph G,int *indegree)
//采用邻接表，对每个顶点求入度，并放入数组indegree中
{
	int i;
	ArcNode *p;
	for(i=0;i<G.vexnum;++i)
		indegree[i]=0; //初始化数组
	for(i=0;i<G.vexnum;++i)
	{
		p=G.vertices[i].firstarc;
		while(p)
		{
			++indegree[p->adjvex];
			p=p->nextarc;
		}
	}
	return OK;
}

//=====以下为栈的部分=====
//__BEGIN -----复制自SqStack.cpp-----
typedef int ElemType; //数据元素的类型，测试用，可更改

#define STACK_INIT_SIZE 100 //存储空间初始分配量
#define STACK_INCREMENT 10 //存储空间分配增量

struct SqStack
{
	ElemType * base; //在构造之前和销毁之后，base的值为null
	ElemType * top; //栈顶指针
	int StackSize; //当前已分配的存储空间，以元素为单位
};

Status InitStack (SqStack &S)
//构造一个空栈
{
	S.base=(ElemType *)malloc(STACK_INIT_SIZE*sizeof(ElemType));
	if(!S.base) //存储分配失败
		exit(OVERFLOW);
	S.top=S.base;
	S.StackSize=STACK_INIT_SIZE;
	return OK;
}//InitStack

Status GetTop(SqStack S,ElemType &e)
//若栈不空 则返回e的栈顶元素
{
	if(S.top==S.base) //栈为空
		return ERROR;
	e=*(S.top-1);
	return OK;
}//GetTop

Status Push(SqStack &S,ElemType e)
//插入元素e为新的栈顶元素
{
	if(S.top-S.base>=S.StackSize)//栈满，追加存储空间
	{
		S.base=(ElemType *)realloc(S.base,(S.StackSize+STACK_INCREMENT)*sizeof(ElemType));
		if(!S.base)  //存储分配失败
			exit(OVERFLOW);
		S.top=S.base+S.StackSize;
		S.StackSize+=STACK_INCREMENT;
	}
	*S.top++=e;
	return OK;
}//Push

Status Pop(SqStack &S,ElemType &e)
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


//__END -----复制自SqStack.cpp-----

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

Status TopologicalOrder(ALGraph G,SqStack &T,int *ve)
//有向图G采用邻接表存储结构，求各顶点事件的最早发生时间ve
//若G无回路，则输出G的顶点的一个拓扑序列到栈T中，并返回OK，否则返回ERROR
{
	int indegree[MAX_VERTEX_NUM]; //存放每个顶点入度的数组
	SqStack S; //建立零入度顶点栈S
	int i,j,k,count;
	ArcNode *p;
	FindInDegree(G,indegree); //对每个顶点求入度
	InitStack(S);
	InitStack(T);
	for(i=0;i<G.vexnum;++i)
	{
		if(!indegree[i])
			Push(S,i);
		ve[i]=0; //初始化ve
	}
	count=0; //对输出顶点计数
	printf("拓扑序列为：");
	while(!StackEmpty(S))
	{
		Pop(S,i);
		Push(T,i);
		printf("%d ",G.vertices[i].data);
		++count; //输出i号顶点并计数
		p=G.vertices[i].firstarc;
		while(p)
		{
			k=p->adjvex;
			if(!(--indegree[k]))
				Push(S,k); //若入度减为0，则入栈
			if(ve[i]+(p->info) >ve[k])
				ve[k]=ve[i]+(p->info);
			p=p->nextarc;	
		}//while
	}//while
	putchar('\n');
	DestroyStack(S);
	if(count<G.vexnum)
		return ERROR;
	return OK;
}//TopologicalOrder

Status CriticalPath(ALGraph G)
//G为有向网，输出G的各项关键活动
{
	int ve[MAX_VERTEX_NUM]; //事件的最早发生时间
	SqStack T;
	if(!TopologicalOrder(G,T,ve))
		return ERROR;
	int vl[MAX_VERTEX_NUM]; //时间的最迟发生时间
	int i,j,k,dut,ee,el;
	char tag;
	ArcNode *p;
	for(i=0;i<G.vexnum-1;++i)
		vl[i]=1000; //初始化最迟发生时间
	vl[G.vexnum-1]=ve[G.vexnum-1];
	puts("活动表：");
	while(!StackEmpty(T))
	{
		Pop(T,j);
		p=G.vertices[j].firstarc;
		while(p)
		{
			k=p->adjvex;
			dut=p->info;
			if(vl[k]-dut<vl[j])
				vl[j]=vl[k]-dut;
			p=p->nextarc;
		}//while
	}
	printf("ve ");
	for(i=0;i<G.vexnum;++i)
		printf("%d ",ve[i]);
	putchar('\n');
	printf("vl ");
	for(i=0;i<G.vexnum;++i)
		printf("%d ",vl[i]);
	putchar('\n');
	for(j=0;j<G.vexnum;++j)
	{
		p=G.vertices[j].firstarc;
		while(p)
		{
			k=p->adjvex;
			dut=p->info;
			ee=ve[j];
			el=vl[k]-dut;
			tag=(ee==el)?'*':' ';
			printf("%d %d %d %d %d %c\n",j+1,k+1,dut,ee,el,tag);
			p=p->nextarc;
		}//while
	}
	DestroyStack(T);
}//CriticalPath


		
//main函数做测试用
int main()
{
	ALGraph g;
	CreateDG(g);
	ShowGraph(g);
	SqStack s;
	int a[MAX_VERTEX_NUM];
	CriticalPath(g);
	return 0;
}
