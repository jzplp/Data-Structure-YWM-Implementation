/***************************************************************************
 *  @file       HuffmanTree.cpp
 *  @author     jz
 *  @date       18 Jan. 2016
 *  @remark     数据结构 c语言版 严蔚敏 第六章
 *  @note	Huffman树和Huffman编码
 ***************************************************************************/
//实现用
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
//测试用

#include "DataStructure.h" //本书需要的一些定义

typedef char ElemType; //数据元素的类型

struct HTNode
{
	unsigned int weight;
	unsigned int parent,lchild,rchild;
};
typedef HTNode * HuffmanTree; //动态分配数组存储Huffman树
typedef char * * HuffmanCode; //动态分配数组存储Huffman编码表

//自己实现的
Status Select_HT(HuffmanTree HT,int i,int &s1,int &s2)
//在Huffman树HT的前i个结点中选择parent为0且weight最小的两个节点s1和s2
{
	int c;
	int sw1,sw2;
	s1,s2=0;
	sw1=sw2=0x1000; //设为weight不可能达到的最大值
	for(c=1;c<=i;c++)
	{
		if(HT[c].parent==0)
		{
			if(HT[c].weight<sw1)
			{
				s1=c;
				sw1=HT[c].weight;
			}
		}
	}
	for(c=1;c<=i;c++)
	{
		if(HT[c].parent==0)
		{
			if(HT[c].weight<sw2&&c!=s1)
			{
				s2=c;
				sw2=HT[c].weight;
			}
		}
	}
	if(s1==0||s2==0)
		return ERROR;
}

Status HuffmanCoding(HuffmanTree &HT,HuffmanCode &HC,int *w,int n)
//w存放n个字符的权值（均>0）,构造Huffman树HT，并求出n个字符的Huffman编码
{
	if(n<=1)
		return ERROR;
	int m=2*n-1,i;
	HTNode * p;
	HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode)); //0号单元未用
	for(p=HT+1,i=1;i<=n;++i,++p,++w) //0号单元 未用 所以是HT+1
	{
		p->weight=*w;
		p->parent=0;
		p->lchild=0;
		p->rchild=0;
	}
	for(;i<=m;++i,++p)
	{
		p->weight=0;
		p->parent=0;
		p->lchild=0;
		p->rchild=0;
	}
	for(i=n+1;i<=m;++i) //建Huffman树
	{
		int s1,s2;
		//在HT中选择parent为0且weight最小的两个结点，其序号分别为s1和s2
		Select_HT(HT,i-1,s1,s2);
		HT[s1].parent=i;
		HT[s2].parent=i;
		HT[i].lchild=s1;
		HT[i].rchild=s2;
		HT[i].weight=HT[s1].weight+HT[s2].weight;
	}
	//---从叶子到根逆向求每个字符的Huffman编码---
	//分配n个字符编码的头指针向量
	HC=(HuffmanCode)(malloc((n+1)*sizeof(char *)));
	char * cd=(char *)malloc(n*sizeof(char)); //分配求编码的工作空间
	cd[n-1]='\0'; //编码结束符
	for(i=1;i<=n;++i) //逐个字符求Huffman编码
	{
		int start=n-1; //编码结束符位置
		int c,f;
		for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent)
			if(HT[f].lchild==c)
				cd[--start]='0';
			else
				cd[--start]='1';
		//为第i个字符编码分配空间
		HC[i]=(char *)malloc((n-start)*sizeof(char));
		strcpy(HC[i],&cd[start]);
	}
	free(cd);
	return OK;
}//HuffmanCoding

Status HuffmanCoding1(HuffmanTree &HT,HuffmanCode &HC,int *w,int n)
//w存放n个字符的权值（均>0）,构造Huffman树HT，并求出n个字符的Huffman编码
{
	if(n<=1)
		return ERROR;
	int m=2*n-1,i;
	HTNode * p;
	HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode)); //0号单元未用
	for(p=HT+1,i=1;i<=n;++i,++p,++w) //0号单元 未用 所以是HT+1
	{
		p->weight=*w;
		p->parent=0;
		p->lchild=0;
		p->rchild=0;
	}
	for(;i<=m;++i,++p)
	{
		p->weight=0;
		p->parent=0;
		p->lchild=0;
		p->rchild=0;
	}
	for(i=n+1;i<=m;++i) //建Huffman树
	{
		int s1,s2;
		//在HT中选择parent为0且weight最小的两个结点，其序号分别为s1和s2
		Select_HT(HT,i-1,s1,s2);
		HT[s1].parent=i;
		HT[s2].parent=i;
		HT[i].lchild=s1;
		HT[i].rchild=s2;
		HT[i].weight=HT[s1].weight+HT[s2].weight;
	}
	//---从叶子到根逆向求每个字符的Huffman编码---
	//分配n个字符编码的头指针向量
	HC=(HuffmanCode)(malloc((n+1)*sizeof(char *)));
	char * cd=(char *)malloc(n*sizeof(char)); //分配求编码的工作空间
	int pp=m,cdlen=0;
	for(i=1;i<=m;i++)
		HT[i].weight=0; //遍历Huffman时用作结点结束状态标志
	while(pp)
	{
		if(HT[pp].weight==0) //向左
		{
			HT[pp].weight=1;
			if(HT[pp].lchild!=0)
			{
				pp=HT[pp].lchild;
				cd[cdlen++]='0';
			}
			else if(HT[pp].rchild==0) //登记叶子节点的字符的编码	
			{
				HC[pp]=(char *)malloc((cdlen+1)*sizeof(char));
				cd[cdlen]='\0';
				strcpy(HC[pp],cd); //复制编码
			}
		}else if(HT[pp].weight==1) //向右
		{
			HT[pp].weight=2;
			if(HT[pp].rchild!=0)
			{
				pp=HT[pp].rchild;
				cd[cdlen++]='1';
			}
		}else //HT[pp].weight==2 返回
		{
			HT[pp].weight=0;
			pp=HT[pp].parent;
			--cdlen;
		}//else
	}//while
	free(cd);
	return OK;
}//HuffmanCoding1


//自己实现的
void ShowHCode(HuffmanTree HT,HuffmanCode HC,int *w,int n)
//输出Huffman编码和对应的Huffman树，w为n个字符的权值，n为字符个数
{
	int i;
	for(i=1;i<=n;i++)
		printf("%d  %s\n",*w++,HC[i]);
	putchar('\n');
	for(i=1;i<=2*n-1;i++)
		printf("%d  %d %d %d %d\n",i,HT[i].weight,HT[i].parent,HT[i].lchild,HT[i].rchild);
}//ShowHCode

//main函数做测试用
int main()
{
	HuffmanTree t;
	HuffmanCode hc;
	int w[8]={5,29,7,8,14,23,3,11};
	//int w[4]={7,5,2,4};
	HuffmanCoding1(t,hc,w,8);
	ShowHCode(t,hc,w,8);
	return 0;
}

