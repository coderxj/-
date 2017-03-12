/*
* author: acme
*   date: 2017-3-12
*  blogs: http://blog.csdn.net/qq_18297675
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

enum NodeType { ATOM, LIST };

typedef struct _GList
{
	NodeType nodeType;   //节点类型
	union
	{
		char c;          //原子 
		_GList* subList; //子表
	};
	_GList* next;		//指向后继节点
}GList, *PGList;


void CreateGList(PGList* glist,char* s)
{
	//若是()，则广义表为空
	static int i = -1;   //因为这里把i定义为了静态变量，所以整个程序就只能正常创建一个广义表,解决办法是把i当作参数传进去，一层层传递
	++i;
	if (s[i] == '(' && s[i + 1] == ')')
		(*glist) = NULL;
	else if (s[i] == '(') //如果是左括号，则递归构建子表
	{
		(*glist) = (PGList)malloc(sizeof(_GList));
		(*glist)->nodeType = LIST;
		(*glist)->c = 0;
		CreateGList(&(*glist)->subList,s);
	}
	else
	{
		(*glist) = (PGList)malloc(sizeof(_GList));
		(*glist)->nodeType = ATOM;
		(*glist)->c = s[i];
	}

	++i;
	if (*glist == NULL);
	else if (s[i] == ',')
		CreateGList(&(*glist)->next,s);
	else if (s[i] == ')' || s[i] == '\0')
		(*glist)->next = NULL;
}

int GetLength(PGList glist)
{
	if (glist != NULL)
		return 1 + GetLength(glist->next);
	else
		return 0;
}

int GetDepth(PGList glist)
{
	int max = 0;
	while (glist != NULL)
	{
		if (glist->nodeType == LIST)  //如果有子表，就继续深入遍历
		{
			int dep = GetDepth(glist->subList);
			if (dep > max) max = dep;  //取最大的深度
		}
		glist = glist->next;         
	}
	return max + 1;     
}

void Print(PGList glist)
{
	if (!glist)
		return;
	else if (glist->nodeType == LIST)
	{
		printf("(");
		Print(glist->subList);
		printf(")");
	}
	else if (glist->nodeType == ATOM)
	{
		printf("%c", glist->c);
		
	}	
	if (glist->next)
	{
		printf(",");
		Print(glist->next);
	}
		
}

int main()
{
	PGList gl;
	CreateGList(&gl, "(1,2,3,5,6,7,(8,(8,8),8),8,9,9,9,9,0)"); //(1,2)
	printf("%d\n", GetLength(gl->subList));
	printf("%d\n", GetDepth(gl->subList));
	Print(gl->subList);
	return 0;
}
