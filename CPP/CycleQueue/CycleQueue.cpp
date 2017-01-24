/*
* author: acme
*   date: 2017-1-25
*  blogs: http://blog.csdn.net/qq_18297675
*/
#pragma once
#include <iostream>
#include <string>
#include <exception>
using namespace std;

//自定义异常类
class CycleQueueException : public exception  //专门提供给外部使用的，不能做成内部类  
{
public:
	CycleQueueException(string msg) : m_msg(msg) {}
	const char * what() const throw ()    //重载
	{
		return m_msg.c_str();
	}
private:
	string m_msg;
};

template<typename T>
class CycleQueue  //顺序队列类
{
public:
	CycleQueue(int queueSize = 50);     //默认队列大小为50个 ？（数据类型） 大小
	~CycleQueue();
public:
	void EnQueue(T e);				    //入队      
	void DeQueue();						//出队
	int GetSize();					   //获取队列长度
	T GetQueueHead();					//获取队头
	void Print();					   //遍历队列
	void ClearQueue();				   //清空队列
private:
	void InitQueue(int queueSize);		//初始化队列,并且指定队列大小
	bool IsEmpty();						//队列是否为空					
	bool IsFull();						//队列是否满
private:
	T* m_data;							//队列数据区域
	int m_front;						//队头
	int m_rear;							//队尾
	int m_queueSize;					//队列的最大长度
	int m_count; 
};

template<typename T>
CycleQueue<T>::CycleQueue(int queueSize = 50)
{
	InitQueue(queueSize);
}

template<typename T>
CycleQueue<T>::~CycleQueue()
{

}

//初始化队列,并且指定队列大小
template<typename T>
void CycleQueue<T>::InitQueue(int queueSize)
{
	m_data = new T[queueSize];  //分配数据区域大小
	m_front = 0;  //初始队头指向0，表示队中无元素
	m_rear = 0;   //初始队尾指向0，表示队中无元素
	m_count = 0;
	m_queueSize = queueSize;
}

//队列是否为空
template<typename T>
bool CycleQueue<T>::IsEmpty()
{
	return m_count == 0 ? true : false;
}

//队列是否满
template<typename T>
bool CycleQueue<T>::IsFull()
{
	return m_count == m_queueSize ? true : false;
}

//入队  
template<typename T>
void CycleQueue<T>::EnQueue(T e)
{
	if (IsFull())
		throw CycleQueueException("队列已满，入队操作失败.");
	else	
	{//如果队列没有满，则循环到数组的第一个a[0]继续存放,把空间利用完
		m_data[m_rear % m_queueSize] = e;
		m_rear = ++m_rear % m_queueSize;
		++m_count;
	}
}

//出队
template<typename T>
void CycleQueue<T>::DeQueue()
{
	if (IsEmpty())
		throw CycleQueueException("队列为空，出队操作失败.");
	else
	{     //队头指针向后移,移到最后，如果没有满，则循环到a[0]继续		
		m_front = ++m_front%m_queueSize;
		--m_count;
	}
}

//获取队列长度
template<typename T>
int CycleQueue<T>::GetSize()
{
	return m_count;
}

//获取队头
template<typename T>
T CycleQueue<T>::GetQueueHead()
{
	if (IsEmpty())
		throw CycleQueueException("队列为空，获取队头操作失败");
	else
		return m_data[m_front];
}

//遍历队列
template<typename T>
void CycleQueue<T>::Print()
{
	if (IsEmpty())
		throw CycleQueueException("队列为空，遍历操作失败");
	else
	{
		if (m_front < m_rear)  //这是正常的，没有循环的时候
		{
			for (int i = m_front;i < m_rear;i++)
				cout << m_data[i] << endl;
		}
		else
		{
			for (int i = m_front;i < m_queueSize;i++)  //分段遍历
				cout << m_data[i] << endl;
			for (int i = 0;i < m_rear;i++)
				cout << m_data[i] << endl;
		}
	}
}

//清空队列
template<typename T>
void CycleQueue<T>::ClearQueue()
{
	if (IsEmpty())
		throw CycleQueueException("队列为空，清空操作失败.");
	else
	{
		m_front = 0;//不用清空数据，入队的时候直接覆盖就好
		m_rear = 0;
		m_count = 0;
	}
}
