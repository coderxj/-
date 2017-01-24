
/*
* author: acme
*   date: 2017-1-24
*  blogs: http://blog.csdn.net/qq_18297675
*/

#pragma once
#include <iostream>
#include <string>
#include <exception>
using namespace std;

//自定义异常类
class LinkQueueException : public exception  //专门提供给外部使用的，不能做成内部类  
{
public:
	LinkQueueException(string msg) : m_msg(msg) {}
	const char * what() const throw ()    //重载
	{
		return m_msg.c_str();
	}
private:
	string m_msg;
};

//链队列
template<typename T>
class LinkQueue		
{
private:  //把Node作为内部类，不让外部访问
	class Node        //节点类
	{
	public:
		Node(T d, Node* n = nullptr) : data(d), next(n) {}
	private:
		T data;
		Node* next;
		friend class LinkQueue;   //如果成员变量声明为私有，那么只有声明友元类才能访问
	};
public:
	LinkQueue();            //无参构造
	LinkQueue(T initValue); //有惨构造
	~LinkQueue();
	void EnQueue(T e);		//入队  
	void DeQueue();			//出队
	int GetSize();			//获取队列长度
	T GetQueueHead();		//获取队头
	void Print();           //遍历队列
	void ClearQueue();      //清空队列
private:
	void InitQueue();		//初始化队列
	bool IsEmpty();			//队列是否为空

private:
	Node* m_front; //头节点，指向队首
	Node* m_rear;  //尾节点，指向队尾
	int m_count;		  //队列大小
	T m_initVlaue;    //初始化节点的值
};

//无参构造
template<typename T>
LinkQueue<T>::LinkQueue()
{
	m_initVlaue = 0;
	InitQueue();
}

//有惨构造
template<typename T>
LinkQueue<T>::LinkQueue(T initVlaue)
{
	m_initVlaue = initVlaue;
	InitQueue();
}

template<typename T>
LinkQueue<T>::~LinkQueue()
{
	delete m_front;
	m_front = nullptr;
	delete m_rear;
	m_rear = nullptr;
}

//初始化队列
template<typename T>
void LinkQueue<T>::InitQueue()
{
	m_front = new Node(m_initVlaue);  //创建首尾两个节点
	m_rear = new Node(m_initVlaue);
	m_count = 0;
}

//队列是否为空
template<typename T>
bool LinkQueue<T>::IsEmpty()
{
	return m_count == 0 ? true : false;
}

//入队
template<typename T>
void LinkQueue<T>::EnQueue(T e)
{
	Node* node = new Node(m_initVlaue);  //创建新的节点
	node->data = e;
	if (m_count == 0)			//如果是第一次添加，则让front和rear同时指向它
		m_front->next = node;
	else
		m_rear->next->next = node;  //原来最后一个节点指向新的最后一个节点
	m_rear->next = node;			 //最后一个节点指向NULL
	node->next = nullptr;					 //rear指向最后一个节点
	++m_count;
}

//出队
template<typename T>
void LinkQueue<T>::DeQueue()
{
	if (IsEmpty())
		throw LinkQueueException("队列为空，出队操作失败");  //抛出异常
	else
	{
		Node* temp = m_front->next;   //将要出队的节点保存起来
		m_front->next = temp->next;    //front指向后一个节点
		--m_count;
		delete temp;                         //释放节点
	}
}

//获取队列长度
template<typename T>
int LinkQueue<T>::GetSize()
{
	return m_count;
}

//获取队头
template<typename T>
T LinkQueue<T>::GetQueueHead()
{
	return IsEmpty() ? throw LinkQueueException("队列为空，获取队头操作失败") : m_front->next->data;
}

//遍历队列
template<typename T>
void LinkQueue<T>::Print()
{
	Node* cur = m_front->next;
	for (int i = 0; i < m_count; i++, cur = cur->next)
		cout << cur->data << endl;
}

 //清空队列
template<typename T>
void LinkQueue<T>::ClearQueue()
{
	for (int i = 0; i < m_count; i++)
		DeQueue();					//挨个出队即可 
	m_front->next = nullptr;        //最后调整头尾指向
	m_rear->next = nullptr;
}
