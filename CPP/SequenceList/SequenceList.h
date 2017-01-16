/*
* author: acme
*   date: 2017-1-16
*  blogs: http://blog.csdn.net/qq_18297675
*/

#pragma once
#include <iostream>
#include <string>
using namespace std;

#define MAX 100			    //顺序表中元素的最大个数
#define ERROR -1
 
template<typename T>    //采用模板类
class SequenceList		  //顺序表类
{

public:
	SequenceList();
	~SequenceList();
public:
	bool IsFull();						          //判断表是否已满
	bool IsEmpty();						          //判断表是否为空
	int GetElementCount();				      //获取元素个数
	void AddFromHead(T e);				      //添加数据（头添加）
	void AddFromTail(T e);				      //添加数据（尾添加）
	void Insert(int local,T e);			    //插入数据（指定位置）
	int GetLocal(T e);					        //返回元素位置
	void DeleteFromLocal(int local);    //删除数据 （指定位置）
	void DeleteFromElement(T e);		    //删除数据 （指定元素）
	int SearchFromElmemt(T e);          //根据指定元素查找，返回位置
	T SearchFromLocal(int local);       //根据位置查找指定元素  
	void Reverse();                     //逆转表
	void Print();                       //遍历元素
	void CopyList(SequenceList<T>& sl); //复制表
	void Rewrite(int local, T e);       //修改元素
private:
	T m_e[MAX];			//元素
	int m_count;		//元素个数
};

template<typename T>
SequenceList<T>::SequenceList()
{
	m_count = 0;
}

template<typename T>
SequenceList<T>::~SequenceList()
{
}

//判断表是否已满
template<typename T>
bool SequenceList<T>::IsFull()
{
	return m_count == MAX ? true : false;
}

//判断表是否为空
template<typename T>
bool SequenceList<T>::IsEmpty()
{
	return m_count == 0 ? true : false;
}

//获取元素个数
template<typename T>
int SequenceList<T>::GetElementCount()
{
	return m_count;
}

//添加数据（头添加）
template<typename T>
void SequenceList<T>::AddFromHead(T e)
{
	if (IsFull())
	{
		cout << "元素个数大于 " << MAX <<" 个，不再允许添加,请删除元素后重试."<<endl;
		return;
	}
	//如果数组中有元素，则往后移，否则直接添加到头部
	if (!IsEmpty())
	{
		//往后移
		for (int i = m_count;i > 0;i--)
			m_e[i] = m_e[i - 1];
	}
	m_e[0] = e;
	++m_count;
}

//添加数据（尾添加）
template<typename T>
void SequenceList<T>::AddFromTail(T e)
{
	if (IsFull())
	{
		cout << "元素个数大于 " << MAX << " 个，不再允许添加,请删除元素后重试." << endl;
		return;
	}
	m_e[m_count++] = e;
}

//插入数据（指定位置）
template<typename T>
void SequenceList<T>::Insert(int local,T e)
{
	if (IsFull())
	{
		cout << "元素个数大于 " << MAX << " 个，不再允许添加,请删除元素后重试." << endl;
		return;
	}
	//往后移
	for (int i = m_count;i > local;i--)
		m_e[i] = m_e[i - 1];
	m_e[local] = e;
	++m_count;
}

//返回元素位置
template<typename T>
int SequenceList<T>::GetLocal(T e)
{
	for (int i = 0;i < m_count;i++)
		if (m_e[i] == e)
			return i;
	return ERROR;  //表示不存在
}

//删除数据 （指定位置）
template<typename T>
void SequenceList<T>::DeleteFromLocal(int local)
{
	//先判断是否为空
	if (IsEmpty())
	{
		cout << "表中无元素，删除操作失败." << endl;
		return;
	}
	if (local >= m_count)
	{
		cout << "指定的位置超过了当前表中的元素个数，删除操作失败." << endl;
		return;
	}
	//直接往前移，覆盖掉
	for (int i = local;i < m_count;i++)
		m_e[i] = m_e[i + 1];
	--m_count;
}

//删除数据 （指定元素）
template<typename T>
void SequenceList<T>::DeleteFromElement(T e)
{
	//先判断是否为空
	if (IsEmpty())
	{
		cout << "表中无元素，删除操作失败." << endl;
		return;
	}
	int local = GetLocal(e);
	//直接往前移，覆盖掉
	for (int i = local;i < m_count;i++)
		m_e[i] = m_e[i + 1];
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
	return local < m_count ? m_e[local] : (T)ERROR;
}

//逆转表
template<typename T>
void SequenceList<T>::Reverse()
{
	T temp;
	for (int i = 0;i < m_count / 2;i++)
	{
		temp = m_e[i];
		m_e[i] = m_e[m_count - i - 1];
		m_e[m_count - i - 1] = temp;
	}
}

//复制表
template<typename T>
void SequenceList<T>::CopyList(SequenceList<T>& sl)
{
	for (int i = 0;i < m_count;i++)
		sl.AddFromTail(m_e[i]);
}

//修改元素
template<typename T>
void SequenceList<T>::Rewrite(int local, T e)
{
	if (local < m_count && local >= 0)
		m_e[local] = e;
}

//遍历数据
template<typename T>
void SequenceList<T>::Print()
{
	if (IsEmpty())
	{
		cout << "表中无元素." << endl;
		return;
	}
	for (int i = 0;i < m_count;i++)
		cout << m_e[i] << endl;
}
