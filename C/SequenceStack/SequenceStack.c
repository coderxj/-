/*
* author: acme
*   date: 2017-1-22
*  blogs: http://blog.csdn.net/qq_18297675
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define STACK_SIZE 50   //栈大小
#define ERROR ~(1<<31)  //错误数

//栈结构
typedef struct _sequence_stack
{
	int data[STACK_SIZE];  //栈数据大小
	int top;               //栈顶标记
}SEQSTACK,*LPSEQSTACK;

//初始化栈
void InitStack(LPSEQSTACK stack)
{
	memset(stack->data, 0, sizeof(stack->data));  //初始化栈空间
	stack->top = -1;                              //初始化栈顶指向
}

//栈是否为空
bool IsEmpty(LPSEQSTACK stack)
{
	return stack->top == -1 ? true : false;
}

//栈是否满了
bool IsFull(LPSEQSTACK stack)
{
	return stack->top == STACK_SIZE - 1 ? true : false;
}

//获取当前栈的长度
int GetSize(LPSEQSTACK stack) 
{
	return stack->top + 1;
}

//入栈
void Push(LPSEQSTACK stack,int e)
{
	if (IsFull(stack))  //如果栈满了，就什么也不做
	{
		printf("栈已满，入栈操作失败.\n");
		return;
	}
	stack->data[++(stack->top)] = e;  //入栈 
}

//出栈(不返回栈顶元素)
void Pop(LPSEQSTACK stack)
{
	if (IsEmpty(stack))   //如果栈为空，就什么也不做
	{
		printf("栈为空，出栈操作失败.\n");
		return;
	}
	--(stack->top);
}

//出栈(返回栈顶元素)
int PopE(LPSEQSTACK stack)
{
	if (IsEmpty(stack))   //如果栈为空，就什么也不做
	{
		printf("栈为空，出栈操作失败.\n");
		return ERROR;
	}
	return stack->data[--(stack->top)];  
}

//获取栈顶元素
int GetTop(LPSEQSTACK stack)
{
	if (IsEmpty(stack))   //如果栈为空，就什么也不做
	{
		printf("栈为空，获取栈顶元素操作失败.\n");
		return ERROR;
	}
	return stack->data[stack->top];
}

//遍历栈
void Print(LPSEQSTACK stack)
{
	if (IsEmpty(stack))   //如果栈为空，就什么也不做
	{
		printf("栈为空，遍历操作失败.\n");
		return;
	}
	do 
	{
		printf("%d\n", stack->data[stack->top]);
	} while (stack->top--);
}

//清空栈
void ClearStack(LPSEQSTACK stack)
{
	if (IsEmpty(stack))   //如果栈为空，就什么也不做
	{
		printf("栈为空，清空操作失败.\n");
		return;
	}
	stack->top = -1;   //直接把栈顶指向-1
}
