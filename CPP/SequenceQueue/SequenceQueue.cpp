
/*
* author: acme
*   date: 2017-1-24
*  blogs: http://blog.csdn.net/qq_18297675
*/
#pragma once
#include <iostream>
#include <string>
using namespace std;

template<typename T>
class SequenceQueue  //顺序队列类
{
public:
	SequenceQueue(int queueSize = 50);   //默认队列大小为50个 ？（数据类型） 大小
	~SequenceQueue();
public:
	void EnQueue(T e);				   //入队      
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
};

template<typename T>
SequenceQueue<T>::SequenceQueue(int queueSize = 50)
{
	InitQueue(queueSize);
}

template<typename T>
SequenceQueue<T>::~SequenceQueue()
{

}

//初始化队列,并且指定队列大小
template<typename T>
void SequenceQueue<T>::InitQueue(int queueSize)
{
	m_data = new T[queueSize];  //分配数据区域大小
	m_front = 0;  //初始队头指向0，表示队中无元素
	m_rear = 0;   //初始队尾指向0，表示队中无元素
	m_queueSize = queueSize;
}

//队列是否为空
template<typename T>
bool SequenceQueue<T>::IsEmpty()
{
	return m_rear - m_front == 0 ? true : false;
}

//队列是否满
template<typename T>
bool SequenceQueue<T>::IsFull()
{
	return m_rear == m_queueSize ? true : false;
}

 //入队  
template<typename T>
void SequenceQueue<T>::EnQueue(T e)
{
	if (IsFull())
		cout << "队列已满，入队操作失败." << endl;
	else
		m_data[m_rear++] = e;
}

//出队
template<typename T>
void SequenceQueue<T>::DeQueue()
{
	if (IsEmpty())
		cout << "队列为空，出队操作失败." << endl;
	else
		++m_front;  //队头指针向后移		
}

//获取队列长度
template<typename T>
int SequenceQueue<T>::GetSize()
{
	return m_rear - m_front;
}

  //获取队头
template<typename T>
T SequenceQueue<T>::GetQueueHead()
{
	if (IsEmpty())
		cout << "队列为空，获取队头操作失败" << endl;
	else
		return m_data[m_front];
}

//遍历队列
template<typename T>
void SequenceQueue<T>::Print()
{
	if (IsEmpty())
		cout << "队列为空，遍历操作失败" << endl;
	else
	{
		for (int i = m_front;i < m_rear;i++)
			cout << m_data[i] << endl;
	}
}

 //清空队列
template<typename T>
void SequenceQueue<T>::ClearQueue()
{
	if (IsEmpty())
		printf("队列为空，清空操作失败.\n");
	else
	{
		m_front = 0;//不用清空数据，入队的时候直接覆盖就好
		m_rear = 0;
	}
}
