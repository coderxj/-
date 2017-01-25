/*
* author: acme
*   date: 2017-1-18
*  blogs: http://blog.csdn.net/qq_18297675
* update: 2017-1-25
*   info: add exception handling, add tail ptr,improve the efficiency of adding data,change node class become inner private class
*/

#pragma once
#include <iostream>
#include <string>
#include <exception>
using namespace std;

//自定义异常类
class LinkListException : public exception  //专门提供给外部使用的，不能做成内部类  
{
public:
	LinkListException(string msg) : m_msg(msg) {}
	const char * what() const throw () { return m_msg.c_str(); }//重载
private:
	string m_msg;
};

template<typename T>
class LinkList    //链表类
{
private://把Node作为内部类，不让外部访问
	class Node    //节点类
	{
	public://初始化构造一个节点
		Node(T d, Node* n = nullptr) : data(d), next(n) {}
	private:
		T data;
		Node* next;
		friend class LinkList;
	};
public:
	LinkList(T initNode = 0);
	~LinkList();
public:
	bool IsEmpty();							//判断表是否为空
	int Size();								//获取元素个数
	void AddFromHead(T e);		//添加数据（头添加）
	void AddFromTail(T e);		//添加数据（尾添加）
	void Insert(int local, T e);	//插入数据（指定位置）
	void DeleteFromLocal(int local);		//删除数据 （指定位置）
	void DeleteFromElement(T e);			//删除数据 （指定元素）
	int SearchFromElmemt(T e);				//根据指定元素查找，返回位置
	T SearchFromLocal(int local);			//根据位置查找指定元素  
	void Reverse1();						//逆转表方法1
	void Reverse2();						//逆转表方法2
	void Print();							//遍历元素
	void CopyList(LinkList<T>& sl);			//复制表
	void Rewrite(int local, T e);			//修改元素
	void ClearLinkList();                   //清空链表
	Node* GetNode(int local);            //获取指定位置的节点
	void SortByAsc();                       //升序排序
	void SortByDesc();                      //降序排序
private:
	int GetLocal(T e);						//返回元素位置
	void InitList(T initNodeValue);                        //初始化链表
	void SelectSort(bool bAsc = true);             //选择排序法
private:
	Node* m_head;	   //头节点
	Node* m_tail;      //尾指针
	int m_iCount;      //链表大小
	T m_initNodeValue; //初始化节点的值,如果没有这个变量，则当初始化string的时候，实例化的时候会出错
};

template<typename T>
LinkList<T>::LinkList(T initNodeValue)
{
	InitList(initNodeValue);
}

template<typename T>
LinkList<T>::~LinkList()
{
	delete m_head;                   //删除头节点  
	delete m_tail;
}

//初始化链表
template<typename T>
void LinkList<T>::InitList(T initNodeValue)
{
	m_iCount = 0;
	m_initNodeValue = initNodeValue;
	m_head = new Node(m_initNodeValue);//创建头节点
	m_tail = new Node(m_initNodeValue);
}

//判断表是否为空
template<typename T>
bool LinkList<T>::IsEmpty()
{
	return m_iCount ? false : true;
}

//获取元素个数
template<typename T>
int LinkList<T>::Size()
{
	return m_iCount;
}

//添加数据（头添加）
template<typename T>
void LinkList<T>::AddFromHead(T e)
{
	Node* node = new Node(e);
	if (IsEmpty())//如果链表为空，第一次添加的时候，就让尾指针指向第一个添加的节点
		m_tail->next = node;
	node->next = m_head->next;
	m_head->next = node;
	++m_iCount;
}

//添加数据（尾添加）
template<typename T>
void LinkList<T>::AddFromTail(T e)
{
	if (IsEmpty())
		AddFromHead(e);
	else
	{
		Node* node = new Node(e);
		m_tail->next->next = node;//让最后一个节点指向新添进来的节点
		m_tail->next = node;	  //修改tail的指向
		++m_iCount;
	}
}

//插入数据（指定位置）
template<typename T>
void LinkList<T>::Insert(int local, T e)
{						
	if (local < m_iCount && local >= 0)
	{
		Node* cur = m_head;   //注意，这里千万不能是m_head->next,因为如果当前链表为空插入的位置
							  //是0，则会直接执行cur->next这个表达式，解引用空指针会出错
		Node* node = new Node(e);
		for (int i = 0;i < local;i++, cur = cur->next); //遍历到local这个位置
		node->next = cur->next;
		cur->next = node;       //这里的操作就和头添加一样,就是改变指向
		++m_iCount;
	}
	else if (local == m_iCount)//如果是插入尾部，直接调用AddFromTail函数即可
		AddFromTail(e);
}

//返回元素位置
template<typename T>
int LinkList<T>::GetLocal(T e)
{
	Node* cur = m_head->next;
	for (int i = 0;i < m_iCount;i++, cur = cur->next)
		if (cur->data == e)
			return i;
	return -1;
}

//删除数据 （指定位置）
template<typename T>
void LinkList<T>::DeleteFromLocal(int local)
{
	if (local < m_iCount && local >= 0) //当删除的位置合法的时候才进行删除操作
	{
		Node* pre = m_head;
		Node* cur = m_head->next;
		for (int i = 0;i < local;i++, cur = cur->next, pre = pre->next);  //遍历到指定位置
		Node* temp = cur;
		pre->next = temp->next;  //例如:pre->cur->next,现在直接让pre->next，然后释放掉cur
		if (pre->next == NULL)  //如果是删除最后一个元素，则需要修改尾指针
			m_tail->next = pre;
		delete cur;
		--m_iCount;
	}
}

//删除数据 （指定元素）
template<typename T>
void LinkList<T>::DeleteFromElement(T e)
{
	int local = GetLocal(e);
	DeleteFromLocal(local);
}

//根据指定元素查找，返回位置
template<typename T>
int LinkList<T>::SearchFromElmemt(T e)
{
	return GetLocal(e);
}

//根据位置查找指定元素
template<typename T>
T LinkList<T>::SearchFromLocal(int local)
{
	Node* node = GetNode(local);
	if (node)
		return node->data;
	else
		throw LinkListException("查找的位置不存在，查找失败.");
}

//逆转表(方法1，牺牲时间换取空间，速度很慢，时间复杂度为0(n^2))
template<typename T>
void LinkList<T>::Reverse1()
{
	T temp;
	for (int i = 0;i < m_iCount / 2;i++)
	{
		Node* node1 = GetNode(i);                //获取节点
		Node* node2 = GetNode(m_iCount - i - 1);
		temp = node1->data;                         //交换数据项，千万别交换节点
		node1->data = node2->data;
		node2->data = temp; 
	}
}

//逆转表(方法2，牺牲空间换取时间，速度很快，时间复杂度为0(n))
template<typename T>
void LinkList<T>::Reverse2()
{
	Node* tHead = new Node(m_initNodeValue);     //临时头节点
	Node* cur = m_head->next;
	for (int i = 0;i < m_iCount;i++)
	{
		Node* node = new Node(cur->data);     //创建新的节点
		node->next = tHead->next;			  //这里采用头添加，结束后，就会自动逆转过来了         
		tHead->next = node;
		cur = cur->next;
	}
	memcpy(m_head, tHead, sizeof(Node));   //因为头添加已经是逆转了，所以直接复制到原来的链表中即可
	delete tHead;
}

//遍历元素
template<typename T>
void LinkList<T>::Print()
{
	Node* cur = m_head;
	while (cur = cur->next)
		cout << cur->data << endl;
}

//复制表
template<typename T>
void LinkList<T>::CopyList(LinkList<T>& sl)
{
	Node* cur = m_head->next;
	for (int i = 0;i < m_iCount;i++, cur = cur->next)
		sl.AddFromTail(cur->data);
}

//修改元素
template<typename T>
void LinkList<T>::Rewrite(int local, T e)
{
	Node* node = GetNode(local);
	if (node)
		node->data = e;
}

//清空链表
template<typename T>
void LinkList<T>::ClearLinkList()
{
	Node* cur = m_head->next;
	for (int i = 0;i < m_iCount;i++)
	{
		Node* temp;
		temp = cur;         //保存前一个节点的地址 
		cur = cur->next;    //向前查找下一个节点
		delete temp;        //释放前一个节点的空间
	}
	m_head->next = NULL;       //最后让头节点指向NULL
	m_tail->next = NULL;
}


/*
*    GetNode这个函数的返回值要注意，一定要按照这种格式写
*    C++模板的一个特性：依赖受限名称不能作为类型使用，除非在前面加上 typename关键字
*    依赖名称：含有模板类型参数<T>
*    受限名称：含有“::”符号
*    所以Node前面一定要有::，<T>前面一定要有typename关键字
*/
//获取指定位置的节点
template<typename T>
typename LinkList<T>::Node* LinkList<T>::GetNode(int local)
{
	if (local < m_iCount && local >= 0)//当获取的位置合法的时候才进行获取操作
	{
		Node* cur = m_head->next;
		for (int i = 0;i < local;i++, cur = cur->next);
		return cur;
	}
	else
		return NULL;
}

//升序排序
template<typename T>
void LinkList<T>::SortByAsc()
{
	SelectSort();
}

//降序排序
template<typename T>
void LinkList<T>::SortByDesc()
{
	SelectSort(false);
}

// 选择排序法
template<typename T>
void LinkList<T>::SelectSort(bool bAsc)
{
	for (int i = 0;i < m_iCount;i++)
	{
		Node* node1 = GetNode(i);
		for (int j = i + 1;j<m_iCount;j++)
		{
			Node* node2 = GetNode(j);
			T temp;
			if (bAsc)   //升序
			{
				if (node1->data > node2->data)
				{
					temp = node1->data;
					node1->data = node2->data;
					node2->data = temp;
				}
			}
			else        //降序
			{
				if (node1->data < node2->data)
				{
					temp = node1->data;
					node1->data = node2->data;
					node2->data = temp;
				}
			}
		}
	}
}
