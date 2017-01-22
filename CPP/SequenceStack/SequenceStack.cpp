/*
* author: acme
*   date: 2017-1-22
*  blogs: http://blog.csdn.net/qq_18297675
*/

#pragma once
#include <iostream>
#include <string>
#define STACK_SIZE 50   //栈大小(默认大小)
#define ERROR ~(1<<31)  //错误数

using namespace std;


template<typename T>
class SequenceStack   //顺序栈类
{
public:
	SequenceStack(int stackSize = STACK_SIZE);
	~SequenceStack();
public:
	bool IsEmpty();       //栈是否为空
	bool IsFull();        //栈是否满了
	int GetSize();        //获取当前栈的长度
	void Push(T e);       //入栈
	void Pop();           //出栈(不返回栈顶元素)
	T PopE();             //出栈(返回栈顶元素)
	T GetTop();           //获取栈顶元素
	void Print();         //遍历栈
	void ClearStack();    //清空栈
private:
	void InitStack();     //初始化栈
	void DestroyStack();  //销毁栈
private:
	T* m_data;			  //栈数据区
	int m_top;			  //栈顶指示
	int m_stackSize;      //栈大小
};

//默认构造函数
template<typename T>
SequenceStack<T>::SequenceStack(int stackSize = STACK_SIZE)
{
	m_stackSize = stackSize;
	InitStack();   //初始化栈
}

//默认析构函数
template<typename T>
SequenceStack<T>::~SequenceStack()
{
	DestroyStack();
}

//初始化栈
template<typename T>
void SequenceStack<T>::InitStack()
{
	m_data = new T[sizeof(T) * m_stackSize];
	memset(m_data, 0, sizeof(m_data));  //初始化栈空间
	m_top = -1;                         //初始化栈顶指向
}

//栈是否为空
template<typename T>
bool SequenceStack<T>::IsEmpty()
{
	return m_top == -1 ? true : false;
}

//栈是否满了
template<typename T>
bool SequenceStack<T>::IsFull()
{
	return m_top == m_stackSize - 1 ? true : false;
}

//获取当前栈的长度
template<typename T>
int SequenceStack<T>::GetSize()
{
	return m_top + 1;
}

//入栈
template<typename T>
void SequenceStack<T>::Push(T e)
{
	if (IsFull())  //如果栈满了，就什么也不做
	{
		cout << "栈已满，入栈操作失败." << endl;
		return;
	}
	m_data[++(m_top)] = e;  //入栈 
}

//出栈(不返回栈顶元素)
template<typename T>
void SequenceStack<T>::Pop()
{
	if (IsEmpty())   //如果栈为空，就什么也不做
	{
		cout << "栈为空，出栈操作失败." << endl;
		return;
	}
	--(m_top);
}

//出栈(返回栈顶元素)
template<typename T>
T SequenceStack<T>::PopE()
{
	if (IsEmpty())   //如果栈为空，就什么也不做
		cout << "栈为空，出栈操作失败." << endl;
	else
		return m_data[(--(m_top)) + 1];
}

//获取栈顶元素
template<typename T>
T SequenceStack<T>::GetTop()
{
	if (IsEmpty())   //如果栈为空，就什么也不做
		cout << "栈为空，获取栈顶元素操作失败." << endl;
	else
		return m_data[m_top];
}

//遍历栈
template<typename T>
void SequenceStack<T>::Print()
{
	if (IsEmpty())   //如果栈为空，就什么也不做
	{
		cout << "栈为空，遍历操作失败." << endl;
		return;
	}
	do
	{
		cout << m_data[m_top] << endl;
	} while (m_top--);
}

//清空栈
template<typename T>
void SequenceStack<T>::ClearStack()
{
	if (IsEmpty())   //如果栈为空，就什么也不做
	{
		cout << "栈为空，清空操作失败." << endl;;
		return;
	}
	m_top = -1;   //直接把栈顶指向-1
}

//销毁栈
template<typename T>
void SequenceStack<T>::DestroyStack()
{
	delete m_data;
	m_top = -1;
	m_stackSize = STACK_SIZE;
}
