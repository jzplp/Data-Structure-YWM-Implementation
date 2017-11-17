/***************************************************************************
 *  @file       SString.cpp
 *  @author     jz
 *  @date       05 Jan. 2016
 *  @remark     数据结构 c语言版 严蔚敏 第四章
 *  @note	串的定长顺序存储表示
 ***************************************************************************/
//实现用
#include<stdlib.h>
#include<stdio.h>
//测试用

#include "DataStructure.h" //本书需要的一些定义

//串的定长顺序存储表示
#define MAXSTRLEN 20 //用户可在255以内定义最大串长
typedef unsigned char SString[MAXSTRLEN+1]; //0号单元存放串的长度

Status Concat(SString &T,SString S1,SString S2)
//由T返回S1与S2连接而成的新串，若未截断，则返回true，否则返回false。
//T可以是未构造的串
{
	bool uncnt;
	if(S1[0]+S2[0]<=MAXSTRLEN) //未截断
	{
		for(int i=1;i<=S1[0];i++)
			T[i]=S1[i];
		for(int i=1;i<=S2[0];i++)
			T[S1[0]+i]=S2[i];
		T[0]=S1[0]+S2[0];
		uncnt=true;
	}else if(S1[0]<MAXSTRLEN) //截断
	{
		for(int i=1;i<=S1[0];i++)
			T[i]=S1[i];
		for(int i=1;i<=MAXSTRLEN-S1[0];i++)
			T[S1[0]+i]=S2[i];
		T[0]=MAXSTRLEN;
		uncnt=false;
	}else
	{
		for(int i=0;i<=MAXSTRLEN;i++)
			T[i]=S1[i]; //T[0]==S1[0]==MAXSTRLEN
		uncnt=false;
	}
	return uncnt;
}//Concat

//自己实现的
void InitString(SString &S)
//S为一个未初始化的串，构造S为一个空串
{
	S[0]=0;
}//InitString

//自己实现的
void InitScanfString(SString &S)
//构造未初始化的串S，并输入数据
{
	int i=0;
	unsigned char c=0;
	//输入字符串内容 以回车结尾（回车不计入字符串内）
	while(c!='\n'&&i<255)
	{
		S[i]=c;
		scanf("%c",&c);
		i++;
	}
	S[0]=i-1;
}//InitScanfString	

//自己实现的
void StrShow(SString S)
//S为一个非空字符串，在屏幕上显示S的内容
{
	for(int i=1;i<=S[0];i++)
		printf("%c",S[i]);
}//StrShow

Status SubString(SString &Sub,SString S,int pos,int len)
//用Sub返回串S的第pos个字符起长度为len的子串。
//S可以是未构造的串
{
	if(pos<1||pos>S[0]||len<0||len>S[0]-pos+1)
		return ERROR;
	for(int i=1;i<=len;i++)
	{
		Sub[i]=S[pos+i-1];
	}
	Sub[0]=len;
	return OK;
}//SubString

int Index(SString S,SString T,int pos)
//返回子串T在主串S中第pos个字符的位置，若不存在，则函数值为0
//其中T非空，1<=pos<=S[0]
{
	int i=pos,j=1;
	while(i<=S[0]&&j<=T[0])
	{
		if(S[i]==T[j]) //继续比较后继字符
		{
			++i;
			++j;
		}else
		{
			i=i-j+2;
			j=1;
		}
	}//while
	if(j>T[0])
		return i-T[0];
	else
		return 0;
}//Index

int Index_KMP(SString S,SString T,int pos,int next[])
//利用模式串T的next函数求T在主串S中第pos个字符之后的位置的KMP算法
//其中T非空，1<=pos<=S[0]
{
	int i=pos,j=1;
	while(i<=S[0]&&j<=T[0])
	{
		if(j==0||S[i]==T[j]) //继续向后比较字符
		{
			++i;
			++j;
		}else
			j=next[j];
	}//while
	if(j>T[0])
		return i-T[0]; //匹配成功
	else
		return 0;
}//Index_KMP

void get_next(SString T,int next[])
//求模式串T的next函数值并存入数组next （修正前）
{
	int i=1,j=0;
	next[1]=0;
	while(i<T[0])
	{
		if(j==0||T[i]==T[j])
		{
			++i;
			++j;
			next[i]=j;
		}else
			j=next[j];
	}
}//get_next

void get_nextval(SString T,int nextval[])
//求模式串T的next函数值并存入数组nextval （修正后）
{
	int i=1,j=0;
	nextval[1]=0;
	while(i<T[0])
	{
		if(j==0||T[i]==T[j])
		{
			++i;
			++j;
			if(T[i]!=T[j])
				nextval[i]=j;
			else
				nextval[i]=nextval[j];
		}else
			j=nextval[j];
	}
}//get_nextval

//main函数做测试用
int main()
{
	SString s1,s2,s;
	InitString(s);
	puts("InitScanfString(s1);");
	InitScanfString(s1);
	puts("InitScanfString(s2);");
	InitScanfString(s2);
	//bool uncnt=Concat(s,s1,s2);
	//printf("%d   ",uncnt);
	//SubString(s,s1,3,4);
	int next[s2[0]];
	get_nextval(s2,next);
	printf("  %d",Index_KMP(s1,s2,1,next));
	//StrShow(s1);
	return 0;
}
