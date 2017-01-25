/*
* author: acme
*   date: 2017-1-16
*  blogs: http://blog.csdn.net/qq_18297675
* update: 2017-1-25
*   info: Add exception handling,can customize the table size
*/

#pragma once
#include <iostream>
#include <string>
#include <exception>
using namespace std;

#define ERROR -1 
 
//自定义异常类
class SequenceListException : public exception  //专门提供给外部使用的，不能做成内部类  
{
public:
	SequenceListException(string msg) : m_msg(msg) {}
	const char * what() const throw () { return m_msg.c_str(); }//重载
private:
	string m_msg;
};

template<typename T>    //采用模板类
class SequenceList		//顺序表类
{

public:
	SequenceList(int maxSize = 50);
	~SequenceList();
public:
	bool IsFull();						//判断表是否已满
	bool IsEmpty();						//判断表是否为空
	int GetSize();				//获取元素个数
	void AddFromHead(T e);				//添加数据（头添加）
	void AddFromTail(T e);				//添加数据（尾添加）
	void Insert(int local,T e);			//插入数据（指定位置）
	int GetLocal(T e);					//返回元素位置
	void DeleteFromLocal(int local);    //删除数据 （指定位置）
	void DeleteFromElement(T e);		//删除数据 （指定元素）
	int SearchFromElmemt(T e);          //根据指定元素查找，返回位置
	T SearchFromLocal(int local);       //根据位置查找指定元素  
	void Reverse();                     //逆转表
	void Print();                       //遍历元素
	void CopyList(SequenceList<T>& sl); //复制表
	void Rewrite(int local, T e);       //修改元素
	int Capacity() { return m_maxSize; };  //表的容量 
private:
	T* m_data;			//元素
	int m_count;		//元素个数
	int m_maxSize;      //顺序表中元素的最大个数
};

template<typename T>
SequenceList<T>::SequenceList(int maxSize)
{
	m_data = new T[maxSize];
	m_maxSize = maxSize;
	m_count = 0;
}

template<typename T>
SequenceList<T>::~SequenceList()
{
	delete[] m_data;
	m_data = nullptr;
}

//判断表是否已满
template<typename T>
bool SequenceList<T>::IsFull()
{
	return m_count == m_maxSize ? true : false;
}

//判断表是否为空
template<typename T>
bool SequenceList<T>::IsEmpty()
{
	return m_count == 0 ? true : false;
}

//获取元素个数
template<typename T>
int SequenceList<T>::GetSize()
{
	return m_count;
}

//添加数据（头添加）
template<typename T>
void SequenceList<T>::AddFromHead(T e)
{
	if (IsFull())
		throw SequenceListException("表已满，添加数据失败.");
	if (!IsEmpty())//如果数组中有元素，则往后移，否则直接添加到头部
	{
		//往后移
		for (int i = m_count;i > 0;i--)
			m_data[i] = m_data[i - 1];
	}
	m_data[0] = e;
	++m_count;
}

//添加数据（尾添加）
template<typename T>
void SequenceList<T>::AddFromTail(T e)
{
	if (IsFull())
		throw SequenceListException("表已满，添加数据失败.");
	m_data[m_count++] = e;
}

//插入数据（指定位置）
template<typename T>
void SequenceList<T>::Insert(int local,T e)
{
	if (IsFull())
		throw SequenceListException("表已满，插入数据失败.");
	//往后移
	for (int i = m_count;i > local;i--)
		m_data[i] = m_data[i - 1];
	m_data[local] = e;
	++m_count;
}

//返回元素位置
template<typename T>
int SequenceList<T>::GetLocal(T e)
{
	for (int i = 0;i < m_count;i++)
		if (m_data[i] == e)
			return i;
	return ERROR;  //表示不存在
}

//删除数据 （指定位置）
template<typename T>
void SequenceList<T>::DeleteFromLocal(int local)
{
	//先判断是否为空
	if (IsEmpty())
		throw SequenceListException("表为空，删除数据失败.");
	if (local >= m_count)
		throw SequenceListException("删除的位置为NULL，删除操作失败.");
	//直接往前移，覆盖掉
	for (int i = local;i < m_count;i++)
		m_data[i] = m_data[i + 1];
	--m_count;
}

//删除数据 （指定元素）
template<typename T>
void SequenceList<T>::DeleteFromElement(T e)
{
	//先判断是否为空
	if (IsEmpty())
		throw SequenceListException("表为空，删除数据失败.");
	int local = GetLocal(e);
	//直接往前移，覆盖掉
	for (int i = local;i < m_count;i++)
		m_data[i] = m_data[i + 1];
	--m_count;
}

//根据指定元素查找，返回位置
template<typename T>
int SequenceList<T>::SearchFromElmemt(T e)
{
	return GetLocal(e);
}

//根据位置查找指定元素  
template<typename T>
T SequenceList<T>::SearchFromLocal(int local)
{
	if (local < m_count)
		return m_data[local];
	else
		throw SequenceListException("查找的位置越界，查找失败.");
}

//逆转表
template<typename T>
void SequenceList<T>::Reverse()
{
	T temp;
	for (int i = 0;i < m_count / 2;i++)
	{
		temp = m_data[i];
		m_data[i] = m_data[m_count - i - 1];
		m_data[m_count - i - 1] = temp;
	}
}

//复制表
template<typename T>
void SequenceList<T>::CopyList(SequenceList<T>& sl)
{
	for (int i = 0;i < m_count;i++)
		sl.AddFromTail(m_data[i]);
}

//修改元素
template<typename T>
void SequenceList<T>::Rewrite(int local, T e)
{
	if (local < m_count && local >= 0)
		m_data[local] = e;
}

//遍历数据
template<typename T>
void SequenceList<T>::Print()
{
	if (IsEmpty())
		throw SequenceListException("表为空，遍历数据失败.");
	for (int i = 0;i < m_count;i++)
		cout << m_data[i] << endl;
}
