/***************************************************************************
 *  @file       HString.cpp
 *  @author     jz
 *  @date       03 Jan. 2016
 *  @remark     数据结构 c语言版 严蔚敏 第四章
 *  @note	串的堆分配存储表示
 ***************************************************************************/
//实现用
#include<stdlib.h>
#include<stdio.h>
//测试用

#include "DataStructure.h" //本书需要的一些定义

//串的堆分配存储表示
struct HString
{
	char *ch; //若是非空串，则按串长分配存储区，否则ch为NULL
	int length; //串长度
};

Status StrInsert(HString &S,int pos,HString T)
//1<=pos<=S.length(S)+1 在串S的第pos个字符之前插入串T。
{
	if(pos<1||pos>S.length+1)
		return ERROR; //pos不合法
	if(T.length) //T非空，则重新分配存储空间，插入T
	{
		if(!(S.ch=(char *)realloc(S.ch,(S.length+T.length)*sizeof(char))))
			exit(OVERFLOW);
		for(int i=S.length-1;i>=pos-1;--i)
			S.ch[i+T.length]=S.ch[i]; //为插入T而腾出位置
		for(int i=0;i<T.length;++i)
			S.ch[pos-1+i]=T.ch[i]; //插入T
		S.length+=T.length;
	}
	return OK;
}//StrInsert

//自己实现的
void InitString(HString &S)
//S为一个未初始化的串，构造S为一个空串
{
	S.ch=NULL;
	S.length=0;
}//InitString

//自己实现的
Status InitScanfString(HString &S)
//构造未初始化的串S，并输入数据
{
	int i=0,count;
	unsigned char c;
	printf("您要输入的字符个数(以空格结尾) 再输入字符");
	scanf("%d ",&count);
	if(count<0)
		return ERROR;
	S.length=count;
	if(!(S.ch=(char *)malloc(S.length*sizeof(char))))
		exit(OVERFLOW);

	//输入字符串内容 输入最后一个后用回车结尾
	while(i<count)
	{
		scanf("%c",&c);
		S.ch[i]=c;
		i++;
	}
	while(getchar()!='\n') //清楚缓冲区内剩余字符
		;
}//InitScanfString

//自己实现的
void StrShow(HString S)
//S为一个非空字符串，在屏幕上显示S的内容
{
	printf("字符串内容为：");
	for(int i=0;i<S.length;++i)
		printf("%c",S.ch[i]);
}//StrShow

//自己实现的
void DestroyString(HString &S)
//销毁一个串
{
	if(S.ch!=NULL)
		free(S.ch);
	S.ch=NULL;
	S.length=0;
}//DestroyString

Status StrAssign(HString &T,char *chars)
//生成一个其值等于串常量chars的串T
{
	if(T.ch)
		free(T.ch); //释放T原有空间
	int i;
	char *c;
	for(i=0,c=chars;*c;++i,++c)
		; //求chars的长度i
	if(!i)
	{
		T.ch=NULL;
		T.length=0;
	}else
	{
		if(!(T.ch=(char*)malloc(i*sizeof(char))))
			exit(OVERFLOW);
		for(int a=0;a<i;a++)
			T.ch[a]=chars[a];
		T.length=i;
	}
	return OK;
}//StrAssign

int Strlength(HString S)
//返回S的元素个数，称为串的长度
{
	return S.length;
}//Strlength

int StrCompare(HString S,HString T)
//若S>T，则返回值>0,若S=T,则返回值=0,若S<T,则返回值<0
{
	for(int i=0;i<S.length&&i<T.length;++i)
		if(S.ch[i]!=T.ch[i])
			return S.ch[i]-T.ch[i];
	return S.length-T.length;
}//StrCompare

Status Concat(HString &T,HString S1,HString S2)
//用T返回由S1和S2连接而成的新串
{
	if(T.ch)
		free(T.ch); //释放旧空间
	if(!(T.ch=(char *)malloc((S1.length+S2.length)*sizeof(char))))
		exit(OVERFLOW);
	int i;
	for(i=0;i<S1.length;++i)
		T.ch[i]=S1.ch[i];
	for(i=0;i<S2.length;i++)
		T.ch[i+S1.length]=S2.ch[i];
	T.length=S1.length+S2.length;
	return OK;
}//Concat

Status SubString(HString &Sub,HString S,int pos,int len)
//用Sub返回串S的第pos个字符起长度为len的子串
//其中，1<=pos<=S.length,0<=len<=S.length-pos+1
{
	if(pos<1||pos>S.length||len<0||len>S.length-pos+1)
		return ERROR;
	if(Sub.ch)
		free(Sub.ch); //释放旧空间
	if(!len) //空子串
	{
		Sub.ch=NULL;
		Sub.length=0;
	}else
	{
		if(!(Sub.ch=(char *)malloc(len*sizeof(char))))
			exit(OVERFLOW);
		for(int i=0;i<len;++i)
			Sub.ch[i]=S.ch[pos+i-1];
		Sub.length=len;
	}
	return OK;
}//SubString

//main函数做测试用
int main()
{
	HString s,s1,s2;
	InitString(s);
	InitScanfString(s1);
	//InitScanfString(s2);
	//Concat(s,s1,s2);
	//StrInsert(s,7,s1);
	//char a[7]="qwerty";
	//StrAssign(s,a);
	SubString(s,s1,2,4);
	StrShow(s);
	//printf("   %d",StrCompare(s,s1));
	DestroyString(s);
	DestroyString(s1);
	//DestroyString(s2);
	return 0;
}


