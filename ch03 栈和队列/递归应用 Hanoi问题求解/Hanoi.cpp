/***************************************************************************
 *  @file       Hanoi.cpp
 *  @author     jz
 *  @date       09 Nov. 2015
 *  @remark     数据结构 c语言版 严蔚敏 第三章
 *  @note	递归应用 Hanoi问题求解
 ***************************************************************************/
//实现用
#include<stdio.h>
//测试用

//全局变量 搬动次数c
int c=0;

void move(char x,int n,char z)
//把编号为n的圆盘从x移到z
{
	printf("第%d次移动 从 %c 塔把 %d 盘 移动到 %c 塔\n",++c,x,n,z);
}

void Hanoi(int n,char x,char y,char z)
//将塔座x上按直径由小到大且自上而下编号为1至n的n个圆盘按规则搬到塔座z上，y可用作辅助塔座。
{
	if(n==1)
		move(x,1,z);
	else
	{
		Hanoi(n-1,x,z,y); //将x上编号为1至n-1的圆盘移到y，z做辅助塔
		move(x,n,z); //将编号为n的圆盘从x移到z
		Hanoi(n-1,y,x,z); //将y上编号为1至n-1的圆盘移到z，x做辅助塔
	}
}//Hanoi

//main函数做测试用
int main()
{
	char x='x',y='y',z='z';
	int n=100;
	Hanoi(n,x,y,z);
	return 0;
}

