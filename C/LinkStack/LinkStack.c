/*
* author: acme
*   date: 2017-1-22
*  blogs: http://blog.csdn.net/qq_18297675
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ERROR ~(1<<31)

//链栈结构
typedef struct _link_stack
{
	int data;              //定义的时候和正常的链表一样，只是限制了添加插入删除等功能而已
	_link_stack* next;
}LINKSTACK,*LPLINKSTACK;

/*
这里不创建全局变量，全部用局部变量，所以就需要一个创建栈的函数，记录栈大小就用栈顶指针中的data。
*/

//创建一个空栈
LPLINKSTACK CreateStack()
{
	LPLINKSTACK top = (LPLINKSTACK)malloc(sizeof(_link_stack));
	top->data = 0;		//栈顶指针中数据域存放的是栈的大小
	top->next = NULL;  
	return top;
}

//栈是否为空
bool IsEmpty(LPLINKSTACK top)
{
	return top ? (top->data == 0 ? true : false) : true;//先判断top是否为空，防止空指针错误
}

//获取当前栈的长度
int GetSize(LPLINKSTACK top)
{
	return top ? top->data : ERROR;  //先判断top是否为空，防止空指针错误
}

//入栈
void Push(LPLINKSTACK top,int e)
{
	LPLINKSTACK node = (LPLINKSTACK)malloc(sizeof(_link_stack)); //创建一个新节点
	node->data = e;            //给节点赋值
	node->next = top->next;   //这里就和链表的头添加一样
	top->next = node;
	top->data++;              //记录栈大小
}

//出栈(不返回栈顶元素)
void Pop(LPLINKSTACK top)
{
	if (IsEmpty(top))  //如果栈为空，则什么也不做
		return;
	LPLINKSTACK temp = top->next;   //保存将要出栈的元素（其实就是链表中删除元素的步骤）
	top->next = temp->next;
	top->data--;                    
	free(temp);                      //释放节点
}

//出栈(返回栈顶元素)
int PopE(LPLINKSTACK top)
{
	if (IsEmpty(top))  //如果栈为空，则什么也不做
		return ERROR;
	LPLINKSTACK temp = top->next;   //保存将要出栈的元素（其实就是链表中删除元素的步骤）
	int data = temp->data;
	top->next = temp->next;
	free(temp);                      //释放节点
	return data;
}

//获取栈顶元素
int GetTop(LPLINKSTACK top)
{
	return IsEmpty(top) ? ERROR : top->next->data; //要先判断栈是否为空
}

//遍历栈
void Print(LPLINKSTACK top)
{
	if (IsEmpty(top))
		return;
	LPLINKSTACK cur = top;   //和遍历链表一样
	while (cur = cur->next)
		printf("%d\n", cur->data);
}

//清空栈
void ClearStack(LPLINKSTACK top)
{
	if (IsEmpty(top))
		return;
	while (top->data)		//挨个出栈即可
		Pop(top);
	top->next = NULL;
}
