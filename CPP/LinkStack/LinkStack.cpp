/*
* author: acme
*   date: 2017-1-22
*  blogs: http://blog.csdn.net/qq_18297675
* update: 2017-1-25
*   info: add exception handling ,change node class become inner private class
*/

#pragma once
#include <iostream>
#include <string>
#include <exception>
using namespace std;

//自定义异常类
class LinkStackException : public exception  //专门提供给外部使用的，不能做成内部类  
{
public:
	LinkStackException(string msg) : m_msg(msg) {}
	const char * what() const throw () { return m_msg.c_str(); }//重载
private:
	string m_msg;
};

template<typename T>
class LinkStack    //链栈
{
private://把Node作为内部类，不让外部访问
	class Node    //节点类
	{
	public://初始化构造一个节点
		Node(T d, Node* n = nullptr) : data(d), next(n) {}
	private:
		T data;
		Node* next;
		friend class LinkStack;
	};
public:
	LinkStack(T initValue = 0);
	~LinkStack();
	
	bool IsEmpty();		//栈是否为空   
	int GetSize();		//获取当前栈的长度	
	void Push(T e);		//入栈			
	void Pop();			//出栈(不返回栈顶元素)				
	T PopE();			//出栈(返回栈顶元素)	
	T GetTop();		//获取栈顶元素					
	void Print();		//遍历栈	
	void ClearStack();  //清空栈
private:
	void InitStack();  //初始化栈
private:
	Node* m_top;	   //栈顶指针   
	int m_count;       //记录栈的大小
	T m_initValue;     //节点的初始值，防止string用int来初始化所带来的错误
};

//有参构造
template<typename T>
LinkStack<T>::LinkStack(T initValue)
{
	m_initValue = initValue;
	InitStack();  //初始化栈
}

//默认析构函数
template<typename T>
LinkStack<T>::~LinkStack()
{
	delete m_top;
}

//初始化栈
template<typename T>
void LinkStack<T>::InitStack()
{
	m_top = new Node(m_initValue);   //创建栈顶指针
	m_count = 0;
}

//栈是否为空 
template<typename T>
bool LinkStack<T>::IsEmpty()
{
	return m_count == 0 ? true : false;
}

//获取当前栈的长度
template<typename T>
int LinkStack<T>::GetSize()
{
	return m_count;
}

//入栈
template<typename T>
void LinkStack<T>::Push(T e)
{
	Node* node = new Node(e);  //创建一个新的节点
	node->next = m_top->next;  
	m_top->next = node;          //让栈顶指针指向新的栈顶节点
	++m_count;
}

//出栈(不返回栈顶元素)
template<typename T>
void LinkStack<T>::Pop()
{
	if (IsEmpty())        
		throw LinkStackException("栈为空，出栈操作失败.");
	else
	{
		Node* temp = m_top->next;//保存将要出栈的元素（其实就是链表中删除元素的步骤）
		m_top->next = temp->next;
		--m_count;
		delete temp;    //释放节点
	}
}

//出栈(返回栈顶元素)	
template<typename T>
T LinkStack<T>::PopE()
{
	if (IsEmpty())
		throw LinkStackException("栈为空，出栈操作失败.");
	else
	{
		Node* temp = m_top->next;//保存将要出栈的元素（其实就是链表中删除元素的步骤）
		T data = temp->data;       //保存要返回的值
		m_top->next = temp->next;
		--m_count;
		delete temp;    //释放节点
		return data;
	}
}

//获取栈顶元素	
template<typename T>
T LinkStack<T>::GetTop()
{
	if(IsEmpty())
		throw LinkStackException("栈为空，获取栈顶元素操作失败.");
	else
		return m_top->next->data;
}

//遍历栈	
template<typename T>
void LinkStack<T>::Print()
{
	if (IsEmpty())
		return;
	else
	{
		Node* cur = m_top;    //和链表遍历一样
		while (cur = cur->next)  
			cout << cur->data << endl;
	}
}

//清空栈
template<typename T>
void LinkStack<T>::ClearStack()
{
	if (IsEmpty())
		throw LinkStackException("栈为空，清空栈操作失败.");
	else
	{
		while (m_count)
			Pop();
		m_top->next = NULL;
	}
}
