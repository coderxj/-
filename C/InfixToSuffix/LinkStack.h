#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ERROR ~(1<<31)

//链栈结构
typedef struct _link_stack
{
	double dData;         
	char cData;   
	_link_stack* next;
}LINKSTACK, *LPLINKSTACK;

/*
这里不创建全局变量，全部用局部变量，所以就需要一个创建栈的函数，记录栈大小就用栈顶指针中的data。
*/

//创建一个空栈
LPLINKSTACK CreateStack()
{
	LPLINKSTACK top = (LPLINKSTACK)malloc(sizeof(_link_stack));
	top->dData = 0;		//栈顶指针中数据域存放的是栈的大小
	top->cData = 0;
	top->next = NULL;
	return top;
}

//栈是否为空
bool IsEmpty(LPLINKSTACK top)
{
	return top ? ((int)top->dData == 0 ? true : false) : true;//先判断top是否为空，防止空指针错误
}

//入栈
void PushD(LPLINKSTACK top, double e)
{
	LPLINKSTACK node = (LPLINKSTACK)malloc(sizeof(_link_stack)); //创建一个新节点
	node->dData = e;            //给节点赋值
	node->next = top->next;   //这里就和链表的头添加一样
	top->next = node;
	top->dData++;             //记录栈大小
}

//入栈
void PushC(LPLINKSTACK top, char e)
{
	LPLINKSTACK node = (LPLINKSTACK)malloc(sizeof(_link_stack)); //创建一个新节点
	node->cData = e;            //给节点赋值
	node->next = top->next;   //这里就和链表的头添加一样
	top->next = node;
	top->dData++;             //记录栈大小
}

//出栈(不返回栈顶元素)
void Pop(LPLINKSTACK top)
{
	if (IsEmpty(top))  //如果栈为空，则什么也不做
		return;
	LPLINKSTACK temp = top->next;   //保存将要出栈的元素（其实就是链表中删除元素的步骤）
	top->next = temp->next;
	top->dData--;
	free(temp);                      //释放节点
}

//出栈(返回栈顶元素)
char PopC(LPLINKSTACK top)
{
	if (IsEmpty(top))  //如果栈为空，则什么也不做
		return ERROR;
	LPLINKSTACK temp = top->next;   //保存将要出栈的元素（其实就是链表中删除元素的步骤）
	char data = temp->cData;
	top->next = temp->next;
	top->dData--;
	free(temp);                      //释放节点
	return data;
}

//出栈(返回栈顶元素)
double PopD(LPLINKSTACK top)
{
	if (IsEmpty(top))  //如果栈为空，则什么也不做
		return ERROR;
	LPLINKSTACK temp = top->next;   //保存将要出栈的元素（其实就是链表中删除元素的步骤）
	double data = temp->dData;
	top->next = temp->next;
	top->dData--;
	free(temp);                      //释放节点
	return data;
}

//获取栈顶元素
double GetTopD(LPLINKSTACK top)
{
	return IsEmpty(top) ? ERROR : top->next->dData; //要先判断栈是否为空
}

//获取栈顶元素
char GetTopC(LPLINKSTACK top)
{
	return IsEmpty(top) ? ERROR : top->next->cData; //要先判断栈是否为空
}
