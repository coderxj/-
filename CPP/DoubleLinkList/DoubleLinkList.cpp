/*
* author: acme
*   date: 2017-1-21
*  blogs: http://blog.csdn.net/qq_18297675
*/

#pragma once
#include <iostream>
#include <string>
using namespace std;

template<typename T>
class Node    //节点类
{
public:		  //初始化构造一个节点
	Node<T>(T d, Node<T>* p = NULL, Node<T>* n = NULL) : data(d) , pre(p) , next(n) {}
public:
	T data;
	Node<T>* pre;  //前驱节点
	Node<T>* next; //后继节点
};


template<typename T>
class DoubleLinkList   //循环链表类
{
public:
	DoubleLinkList();
	DoubleLinkList(T initNodeValue);
	~DoubleLinkList();
public:
	bool IsEmpty();							//判断表是否为空
	int Size();								//获取元素个数
	void AddFromHead(Node<T>* node);		//添加数据（头添加）
	void AddFromTail(Node<T>* node);		//添加数据（尾添加）
	void Insert(int local, Node<T>* node);	//插入数据（指定位置）
	void DeleteFromLocal(int local);		//删除数据 （指定位置）
	void DeleteFromElement(T e);			//删除数据 （指定元素）
	int SearchFromElmemt(T e);				//根据指定元素查找，返回位置
	T SearchFromLocal(int local);			//根据位置查找指定元素  
	void Reverse();							//逆转表
	void Print(bool bReverse = false);		//遍历元素(可以正遍历，也可以倒着遍历)
	void CopyList(DoubleLinkList<T>& sl);	//复制表
	void Rewrite(int local, T e);			//修改元素
	void ClearLinkList();                   //清空链表
	Node<T>* GetNode(int local);            //获取指定位置的节点
	void SortByAsc();                       //升序排序
	void SortByDesc();                      //降序排序
	Node<T>* GetTailNode();                 //获取最后一个节点
	void MergeList(DoubleLinkList<T>& sl);   //合并链表(无序)，会改变原表
	void MergeListOrder(DoubleLinkList<T>& sl, bool bAsc = true); //合并链表(有序)
	void MergeListNoChange(DoubleLinkList<T>& sl); //合并链表(无序)，不会改变原表
	void MergeListNoChangeOrder(DoubleLinkList<T>& sl, bool bAsc = true); //合并链表(有序),不会改变原表
private:
	int GetLocal(T e);						//返回元素位置
	void SelectSort(bool bAsc = true);      //选择排序法
	void InitList();                        //初始化链表
	void SwapNodeData(Node<T>* node1, Node<T>* node2); //交换两个节点的数据
private:
	Node<T>* m_head;   //头节点
	Node<T>* m_tail;   //尾节点(这个只是指向最后一个节点，并不是最后一个节点指向尾节点)
	int m_iCount;      //链表大小
	T m_initNodeValue; //初始化节点的值,如果没有这个变量，则当初始化string的时候，实例化的时候会出错
};

//默认构造
template<typename T>
DoubleLinkList<T>::DoubleLinkList()
{
	m_initNodeValue = 0;
	InitList();    //初始化链表
}

//有参构造
template<typename T>
DoubleLinkList<T>::DoubleLinkList(T initNodeValue = 0)
{
	m_initNodeValue = initNodeValue;
	InitList();    //初始化链表
}

template<typename T>
DoubleLinkList<T>::~DoubleLinkList()
{
	delete m_head;                   //删除头节点  
	m_head = NULL;
	delete m_tail;                   //删除尾指针
	m_tail = NULL;
}

//初始化链表
template<typename T>
void DoubleLinkList<T>::InitList()
{
	m_iCount = 0;
	m_head = new Node<T>(m_initNodeValue);//创建头节点
	m_tail = new Node<T>(m_initNodeValue);//创建尾节点
}

//判断表是否为空
template<typename T>
bool DoubleLinkList<T>::IsEmpty()
{
	return m_iCount ? false : true;
}

//获取元素个数
template<typename T>
int DoubleLinkList<T>::Size()
{
	return m_iCount;
}

//添加数据（头添加）
template<typename T>
void DoubleLinkList<T>::AddFromHead(Node<T>* node)
{
	if (IsEmpty())				//如果链表为空，第一次添加的时候，就让尾指针指向第一个添加的节点
	{ 
		m_tail->next = node;        //例如 head->NULL,现在添加了个node1,则node1->NULL,head->node1,先把正方向连好
		node->next = m_head->next;  //然后node1->head
		m_head->next = node;
		node->pre = m_head;
	}
	else
	{
		node->next = m_head->next;     //例如 head->node1,现在添加了个node2,则node2->node1,head->node2,先把正方向连好
		m_head->next = node;           //然后node1 -> node2,node2->head
		node->next->pre = node;
		node->pre = m_head;
	}
	++m_iCount;
}

//添加数据（尾添加）
template<typename T>
void DoubleLinkList<T>::AddFromTail(Node<T>* node)
{
	if (IsEmpty())
		AddFromHead(node);   //如果是第一次添加，则调用AddFromHead即可
	else
	{
		m_tail->next->next = node;  //tail.next表示最后一个节点，这句代码的意思是，让最后一个节点指向新添进来的节点
		node->pre = m_tail->next;   //新添进来的节点的前驱指向原来的最后一个节点
		m_tail->next = node;        //修改tail的指向
		++m_iCount;
	}
}

//插入数据（指定位置）
template<typename T>
void DoubleLinkList<T>::Insert(int local, Node<T>* node)
{						
	if (local < m_iCount && local >= 0)
	{
		Node<T>* cur = m_head;   //注意，这里千万不能是m_head->next,因为如果当前链表为空插入的位置
								 //是0，则会直接执行cur->next这个表达式，解引用空指针会出错	
		for (int i = 0;i < local;i++, cur = cur->next); //遍历到local这个位置
		node->next = cur->next;			//在该位置插入
		cur->next = node;
		node->next->pre = node;
		node->pre = cur;
		++m_iCount;
	}
	else if (local == m_iCount)//如果是插入尾部，直接调用AddFromTail函数即可
		AddFromTail(node);

}

//返回元素位置
template<typename T>
int DoubleLinkList<T>::GetLocal(T e)
{
	Node<T>* cur = m_head->next;
	for (int i = 0;i < m_iCount;i++, cur = cur->next)
		if (cur->data == e)
			return i;
	return -1;
}

//删除数据 （指定位置）
template<typename T>
void DoubleLinkList<T>::DeleteFromLocal(int local)
{
	if (local < m_iCount - 1 && local >= 0)   //当要删除的位置合理的情况下才能删除
	{
		Node<T>* cur = m_head;
		for (int i = 0;i < local;i++)
			cur = cur->next;
		Node<T>* temp;
		temp = cur->next;
		cur->next = temp->next;           //删除该位置下的元素
		cur->next->pre = cur;
		--m_iCount;
		delete temp;                       //释放掉该节点
	}
	else if (local == m_iCount - 1)  //删除的是最后一个元素的话
	{
		Node<T>* temp = m_tail->next;   //最后一个节点
		m_tail->next = temp->pre;		//指向最后一个节点的前一个节点
		m_tail->next->next = NULL;      //最后一个节点指向NULL
		--m_iCount;
		delete temp;
	}
}

//删除数据 （指定元素）
template<typename T>
void DoubleLinkList<T>::DeleteFromElement(T e)
{
	int local = GetLocal(e);
	DeleteFromLocal(local);
}

//根据指定元素查找，返回位置
template<typename T>
int DoubleLinkList<T>::SearchFromElmemt(T e)
{
	return GetLocal(e);
}

//根据位置查找指定元素
template<typename T>
T DoubleLinkList<T>::SearchFromLocal(int local)
{
	Node<T>* node = GetNode(local);
	if (node)
		return node->data;
	else
		return NULL;
}

//逆转表,时间复杂度为0(n/2)
template<typename T>
void DoubleLinkList<T>::Reverse()
{
	Node<T>* node1 = m_head->next;
	Node<T>* node2 = m_tail->next;
	while (node1 != node2)
	{
		SwapNodeData(node1, node2);   //交换数据项，千万别交换节点
		node1 = node1->next;   //往后
		node2 = node2->pre;    //往前
		if (node1 == node2->pre) //如果元素个数是偶数，则要多进行一步交换操作
		{
			SwapNodeData(node1, node2);   //交换数据项，千万别交换节点
			break;
		}
	}
}

//遍历元素
template<typename T>
void DoubleLinkList<T>::Print(bool bReverse)
{
	if (bReverse)  //倒序
	{
		Node<T>* cur = m_tail->next;
		if (!cur) return;
		do
		{
			cout << cur->data << endl;
		} while ((cur = cur->pre) != m_head);
	}
	else
	{
		Node<T>* cur = m_head;
		while (cur = cur->next)
			cout << cur->data << endl;
	}
}

//复制表
template<typename T>
void DoubleLinkList<T>::CopyList(DoubleLinkList<T>& sl)
{
	Node<T>* cur = m_head->next;
	for (int i = 0;i < m_iCount;i++, cur = cur->next)
	{
		Node<T>* temp = new Node<T>(m_initNodeValue);
		memcpy(temp, cur, sizeof(Node<T>));          //这里一定要注意，不能只复制头节点，这样只是两个头节点指向同一空间，并没有实现真正的复制
		sl.AddFromTail(temp);   //因为加了个尾指针，现在头添加和尾添加时间复杂度都是0(1)
	}
}

//修改元素
template<typename T>
void DoubleLinkList<T>::Rewrite(int local, T e)
{
	Node<T>* node = GetNode(local);
	if (node)
		node->data = e;
}

//清空链表
template<typename T>
void DoubleLinkList<T>::ClearLinkList()
{
	Node<T>* cur = m_head->next;
	for (int i = 0;i < m_iCount;i++)
	{
		Node<T>* temp;
		temp = cur;         //保存前一个节点的地址 
		cur = cur->next;    //向前查找下一个节点
		delete temp;         //释放前一个节点的空间
	}
	m_head->next = NULL;      //最后让头节点指向NULL
	m_tail->next = NULL;
}

//获取指定位置的节点
template<typename T>
Node<T>* DoubleLinkList<T>::GetNode(int local)
{
	if (local < m_iCount / 2 && local >= 0)   //如果local在前半部分，则从前往后找
	{
		Node<T>* cur = m_head->next;
		for (int i = 0;i < local;i++)  //遍历
			cur = cur->next;
		return cur;
	}
	else if (local >= m_iCount / 2 && local < m_iCount - 1) //如果local在后半部分，则从后往前找
	{
		Node<T>* cur = m_tail->next;
		for (int i = 0;i < m_iCount - local - 1;i++)  //遍历
			cur = cur->pre;
		return cur;
	}
	else if (local == m_iCount - 1)  //如果是查找最后一个节点，直接返回tail指向的节点即可
		return m_tail->next;
	else
		return NULL;
}

//升序排序
template<typename T>
void DoubleLinkList<T>::SortByAsc()
{
	SelectSort();
}

//降序排序
template<typename T>
void DoubleLinkList<T>::SortByDesc()
{
	SelectSort(false);
}

//选择排序法
template<typename T>
void DoubleLinkList<T>::SelectSort(bool bAsc)
{
	for (int i = 0;i < m_iCount;i++)
	{
		Node<T>* node1 = GetNode(i);
		for (int j = i + 1;j < m_iCount;j++)
		{
			Node<T>* node2 = GetNode(j);
			if (bAsc)   //升序
			{
				if (node1->data > node2->data)
					SwapNodeData(node1, node2);
			}
			else        //降序
			{
				if (node1->data < node2->data)
					SwapNodeData(node1, node2);
			}	
		}
	}
}

//交换两个节点的数据
template<typename T>
void DoubleLinkList<T>::SwapNodeData(Node<T>* node1, Node<T>* node2)
{
	T temp;
	temp = node1->data;
	node1->data = node2->data;
	node2->data = temp;
}

//获取最后一个节点
template<typename T>
Node<T>* DoubleLinkList<T>::GetTailNode()
{
	return m_tail->next;
}

//合并链表  ,需要注意的是，合并后，原来的表就会被改变。
template<typename T>
void DoubleLinkList<T>::MergeList(DoubleLinkList<T>& sl)
{
	if (IsEmpty())  //如果目的表为空
		this->m_head->next = sl.m_head->next;  //直接让头节点指向表2的第一个节点
	else
	{
		this->m_tail->next->next = sl.m_head->next;     //表1的最后一个节点指向表2的第一个节点
		sl.m_head->next->pre = this->m_tail->next;      //表2的第一个节点指向表1的最后一个节点
	}
	this->m_tail->next = sl.m_tail->next;           //表1的尾指针指向表二的最后一个元素 
	this->m_iCount += sl.m_iCount;                  //还要把元素个数加起来
}

//合并链表(有序)
template<typename T>
void DoubleLinkList<T>::MergeListOrder(DoubleLinkList<T>& sl, bool bAsc)
{
	MergeList(sl);
	SelectSort(bAsc);
}

//合并链表(无序)，不会改变原表
template<typename T>
void DoubleLinkList<T>::MergeListNoChange(DoubleLinkList<T>& sl)
{
	DoubleLinkList<T> list(m_initNodeValue);
	sl.CopyList(list);            //复制链表,这样就不会改变原表
	MergeList(list);
}

//合并链表(有序),不会改变原表
template<typename T>
void DoubleLinkList<T>::MergeListNoChangeOrder(DoubleLinkList<T>& sl, bool bAsc = true)
{
	DoubleLinkList<T> list(m_initNodeValue);
	sl.CopyList(list);            //复制链表,这样就不会改变原表
	MergeListOrder(list, bAsc);
}
