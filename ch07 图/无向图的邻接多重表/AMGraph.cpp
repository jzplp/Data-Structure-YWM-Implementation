/***************************************************************************
 *  @file       AMGraph.cpp
 *  @author     jz
 *  @date       22 Jan. 2016
 *  @remark     数据结构 c语言版 严蔚敏 第七章
 *  @note	无向图的邻接多重表
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
enum VisitIf {unvisited,visited}; 
struct EBox
{
	VisitIf mark; //访问标记
	int ivex,jvex; //该遍依附的两个顶点的位置
	EBox *ilink,*jlink; //分别依附于这两个顶点的下一条边
	InfoType *info; //该边信息指针
};
struct VexBox
{
	VertexType data;
	EBox *firstedge; //第一条依附于该顶点的边
};
struct AMGraph
{
	VexBox adjmulist[MAX_VERTEX_NUM];
	int vexnum,edgenum; //无向图当前的顶点数和边数
};

//main函数做测试用
int main()
{
}
	

