/***************************************************************************
 *  @file       TSMatrix.cpp
 *  @author     jz
 *  @date       10 Jan. 2016
 *  @remark     数据结构 c语言版 严蔚敏 第五章
 *  @note	稀疏矩阵的三元组顺序存储结构 （行和列从1开始）
 ***************************************************************************/
//实现用
#include<stdlib.h>
#include<stdio.h>
//测试用

#include "DataStructure.h" //本书需要的一些定义

typedef char ElemType; //数据元素的类型

#define MAXSIZE 200 //假设非零元个数的最大值为200 可更改
struct Triple
{
	int i,j; //该非零元的行下标和列下标
	ElemType e;
};
struct TSMatrix
{
	Triple data[MAXSIZE+1]; //非零元三元组表 data[0]未用
	int mu,nu,tu; //矩阵的行数，列数和非零元个数
};

Status TransposeSMatrix(TSMatrix M,TSMatrix &T)
//采用三元组表存储表示，求稀疏矩阵M的转置矩阵T
{
	T.mu=M.nu;
	T.nu=M.mu;
	T.tu=M.tu;
	if(T.tu)
	{
		int q=1;
		for(int col=1;col<=M.nu;++col)
			for(int p=1;p<=M.tu;++p)
				if(M.data[p].j==col)
				{
					T.data[q].i=M.data[p].j;
					T.data[q].j=M.data[p].i;
					T.data[q].e=M.data[p].e;
					++q;
				}
	}
	return OK;
}//TransposeSMatrix

Status FastTransposeSMatrix(TSMatrix M,TSMatrix &T)
//采用三元组表存储表示，求稀疏矩阵M的转置矩阵T
{
	T.mu=M.nu;
	T.nu=M.mu;
	T.tu=M.tu;
	//num[0]和cpot[0]未用
	int num[M.tu+1];
	int cpot[M.tu+1];
	if(T.tu)
	{
		int col;
		for(col=1;col<=M.nu;++col)
			num[col]=0;
		for(col=1;col<=M.nu;++col) //求M中每一列含非零元个数
			++num[M.data[col].j];
		cpot[1]=1;
		for(col=2;col<=M.tu;++col) //求第col列中第一个非零元在b.data中的序号
			cpot[col]=cpot[col-1]+num[col-1];
		int p,q;
		for(p=1;p<=M.tu;++p)
		{
			col=M.data[p].j;
			q=cpot[col];
			T.data[q].i=M.data[p].j;
			T.data[q].j=M.data[p].i;
			T.data[q].e=M.data[p].e;
			++cpot[col];
		}//for
	}//if
	return OK;
}//FastTransposeSMatrix

//自己实现的
Status CreateTSMatrix(TSMatrix &M)
//构造未初始化的用三元组表，并输入数据
{
	printf("您要输入的三元组行数，列数，个数(以回车结尾)\n");
	scanf("%d %d %d",&M.mu,&M.nu,&M.tu);
	if(M.tu<0)
		return ERROR;
	int c;
	for(c=1;c<=M.tu;++c)
	{
		printf("输入第%d个三元组，一共%d个(回车结尾)\n",c,M.tu);
		scanf("%d %d %d",&M.data[c].i,&M.data[c].j,&M.data[c].e);
	}
	return OK;
}//CreateTSMatrix

//自己实现的
Status ShowTSMatrix(TSMatrix M)
//输出稀疏矩阵M中的元素
{
	int c;
	puts("稀疏矩阵中的元素如下：");
	for(c=1;c<=M.tu;++c)
		printf("%d  %d  %d\n",M.data[c].i,M.data[c].j,M.data[c].e);
	putchar('\n');
}//ShowTSMatrix


//main函数做测试用
int main()
{
	TSMatrix m,t;
	CreateTSMatrix(m);
	//TransposeSMatrix(m,t);
	FastTransposeSMatrix(m,t);
	ShowTSMatrix(t);
	return 0;
}
