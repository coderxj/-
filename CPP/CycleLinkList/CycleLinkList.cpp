#pragma once
#include <iostream>
#include <string>
using namespace std;

template<typename T>
class Node    //节点类
{
public:		  //初始化构造一个节点
	Node<T>(T d, Node<T>* n = NULL) : data(d), next(n) {}
public:
	T data;
	Node<T>* next;
};


template<typename T>
class CycleLinkList   //循环链表类
{
public:
	CycleLinkList(T initNodeValue);
	~CycleLinkList();
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
	void Reverse1();						//逆转表方法1
	void Reverse2();						//逆转表方法2
	void Print();							//遍历元素
	void CopyList(CycleLinkList<T>& sl);	//复制表
	void Rewrite(int local, T e);			//修改元素
	void ClearLinkList();                   //清空链表
	Node<T>* GetNode(int local);            //获取指定位置的节点
	void SortByAsc();                       //升序排序
	void SortByDesc();                      //降序排序
	Node<T>* GetTailNode();                 //获取最后一个节点
	void MergeList(CycleLinkList<T>& sl);   //合并链表(无序)，会改变原表
	void MergeListOrder(CycleLinkList<T>& sl,bool bAsc = true); //合并链表(有序)
	void MergeListNoChange(CycleLinkList<T>& sl); //合并链表(无序)，不会改变原表
	void MergeListNoChangeOrder(CycleLinkList<T>& sl, bool bAsc = true); //合并链表(有序),不会改变原表
private:
	int GetLocal(T e);						//返回元素位置
	void SelectSort(bool bAsc = true);      //选择排序法
	void InitList();                        //初始化链表
private:
	Node<T>* m_head;   //头节点
	Node<T>* m_tail;   //尾节点(这个只是指向最后一个节点，并不是最后一个节点指向尾节点)
	int m_iCount;      //链表大小
	T m_initNodeValue; //初始化节点的值,如果没有这个变量，则当初始化string的时候，实例化的时候会出错
};

template<typename T>
CycleLinkList<T>::CycleLinkList(T initNodeValue)
{
	m_initNodeValue = initNodeValue;
	InitList();    //初始化链表
}

template<typename T>
CycleLinkList<T>::~CycleLinkList()
{
	delete m_head;                   //删除头节点  
	m_head = NULL;
	delete m_tail;                   //删除尾指针
	m_tail = NULL;
}

//初始化链表
template<typename T>
void CycleLinkList<T>::InitList()
{
	m_iCount = 0;
	m_head = new Node<T>(m_initNodeValue);//创建头节点
	m_tail = new Node<T>(m_initNodeValue);//创建尾节点
 	m_head->next = m_head;                //初始化的时候自己指向自己
}

//判断表是否为空
template<typename T>
bool CycleLinkList<T>::IsEmpty()
{
	return m_iCount ? false : true;
}

//获取元素个数
template<typename T>
int CycleLinkList<T>::Size()
{
	return m_iCount;
}

//添加数据（头添加）
template<typename T>
void CycleLinkList<T>::AddFromHead(Node<T>* node)
{
	if (IsEmpty()) //如果链表为空，则尾指针指向第一次添加进来的节点
		m_tail->next = node;
	node->next = m_head->next;
	m_head->next = node;
	++m_iCount;
}

//添加数据（尾添加）
template<typename T>
void CycleLinkList<T>::AddFromTail(Node<T>* node)
{
	Node<T>* cur = m_head;
	while (cur->next != m_head)
		cur = cur->next;     //遍历到链表末尾
	cur->next = node;               //直接把新的节点挂在链表末尾
	node->next = m_head;            //最后一个节点指向head
	m_tail->next = node;            //tail指向最后一个节点
	++m_iCount;
}

//插入数据（指定位置）
template<typename T>
void CycleLinkList<T>::Insert(int local, Node<T>* node)
{
	Node<T>* cur = m_head;   //注意，这里千万不能是m_head->next,因为如果当前链表为空插入的位置
							 //是0，则会直接执行cur->next这个表达式，解引用空指针会出错							
	if (local < m_iCount && local >= 0)
	{
		for (int i = 0;i < local;i++, cur = cur->next); //遍历到local这个位置
		node->next = cur->next;
		cur->next = node;       //这里的操作就和头添加一样,就是改变指向
		++m_iCount;
	}
	else if(local == m_iCount)//如果是插入尾部，直接调用AddFromTail函数即可
		AddFromTail(node);

}

//返回元素位置
template<typename T>
int CycleLinkList<T>::GetLocal(T e)
{
	Node<T>* cur = m_head->next;
	for (int i = 0;i < m_iCount;i++, cur = cur->next)
		if (cur->data == e)
			return i;
	return -1;
}

//删除数据 （指定位置）
template<typename T>
void CycleLinkList<T>::DeleteFromLocal(int local)
{
	if (local < m_iCount && local >= 0) //当删除的位置合法的时候才进行删除操作
	{
		Node<T>* pre = m_head;
		Node<T>* cur = m_head->next;
		for (int i = 0;i < local;i++, cur = cur->next, pre = pre->next);  //遍历到指定位置
		Node<T>* temp = cur;
		pre->next = temp->next;  //例如:pre->cur->next,现在直接让pre->next，然后释放掉cur
		delete cur;
		--m_iCount;
	}
}

//删除数据 （指定元素）
template<typename T>
void CycleLinkList<T>::DeleteFromElement(T e)
{
	Node<T>* pre = m_head;
	Node<T>* cur = m_head->next;
	for (int i = 0;i < m_iCount;i++, cur = cur->next, pre = pre->next)  //遍历到指定位置
		if (cur->data == e)
		{
			Node<T>* temp = cur;
			pre->next = temp->next;  //例如:pre->cur->next,现在直接让pre->next，然后释放掉cur
			delete cur;
			--m_iCount;
			break;
		}
}

//根据指定元素查找，返回位置
template<typename T>
int CycleLinkList<T>::SearchFromElmemt(T e)
{
	return GetLocal(e);
}

//根据位置查找指定元素
template<typename T>
T CycleLinkList<T>::SearchFromLocal(int local)
{
	if (local < m_iCount && local >= 0)//当搜索的位置合法的时候才进行搜索操作
	{
		Node<T>* cur = m_head->next;
		for (int i = 0; i < local; i++, cur = cur->next);
		return cur->data;
	}
	else
		return NULL;
}

//逆转表(方法1，牺牲时间换取空间，速度很慢，时间复杂度为0(n^2))
template<typename T>
void CycleLinkList<T>::Reverse1()
{
	T temp;
	for (int i = 0;i < m_iCount / 2;i++)
	{
		Node<T>* node1 = GetNode(i);                //获取节点
		Node<T>* node2 = GetNode(m_iCount - i - 1);
		temp = node1->data;                         //交换数据项，千万别交换节点
		node1->data = node2->data;
		node2->data = temp;
	}
}

//逆转表(方法2，牺牲空间换取时间，速度很快，时间复杂度为0(n))
template<typename T>
void CycleLinkList<T>::Reverse2()
{
	Node<T>* tHead = new Node<T>(m_initNodeValue);     //临时头节点
	Node<T>* tTail = new Node<T>(m_initNodeValue);     //临时尾节点
	tHead->next = tHead;
	Node<T>* cur = m_head->next;
	for (int i = 0;i < m_iCount;i++)
	{
		Node<T>* node = new Node<T>(m_initNodeValue);
		memcpy(node, cur, sizeof(Node<T>));   //这里一定要复制，而不是赋值=，如果是=，则两指针指向的是同一个节点
		if (i == 0)
		{
			tTail->next = node;               //一开始就让tTail指向最后一个节点
			node->next = tHead;               //最后一个节点指向头节点
		}
		node->next = tHead->next;			  //这里采用头添加，结束后，就会自动逆转过来了         
		tHead->next = node;
		cur = cur->next;
	}
	m_head = tHead;   //因为头添加已经是逆转了，所以直接把头节点和尾节点的地址赋值给成员变量即可
	m_tail = tTail;   //注意，一定要头尾同时赋值，不然它们的指向就乱了。
}

//遍历元素
template<typename T>
void CycleLinkList<T>::Print()
{
	Node<T>* cur = m_head;
	int i = 0;
	while ((i++ != m_iCount) && (cur = cur->next) != m_head) //防止合并后，其中被合并的表变成单链表，陷入死循环
		cout << cur->data << endl;
}

//复制表
template<typename T>
void CycleLinkList<T>::CopyList(CycleLinkList<T>& sl)
{
	Node<T>* cur = m_head->next;
	for (int i = 0;i < m_iCount;i++, cur = cur->next)
	{
		Node<T>* temp = new Node<T>(m_initNodeValue);
		memcpy(temp, cur, sizeof(Node<T>));          //这里一定要注意，不能只复制头节点，这样只是两个头节点指向同一空间，并没有实现真正的复制
		sl.AddFromHead(temp);
	}
	sl.Reverse2();   //最后逆转一次
}

//修改元素
template<typename T>
void CycleLinkList<T>::Rewrite(int local, T e)
{
	if (local < m_iCount && local >= 0)
	{
		Node<T>* cur = m_head->next;
		for (int i = 0;i < local;i++, cur = cur->next);
		cur->data = e;
	}
}

//清空链表
template<typename T>
void CycleLinkList<T>::ClearLinkList()
{
	Node<T>* cur = m_head->next;
	for (int i = 0;i < m_iCount;i++)
	{
		Node<T>* temp;
		temp = cur;         //保存前一个节点的地址 
		cur = cur->next;    //向前查找下一个节点
		delete temp;        //释放前一个节点的空间
	}
	m_iCount = 0;
	m_head->next = m_head;
	m_tail->next = NULL;
}

//获取指定位置的节点
template<typename T>
Node<T>* CycleLinkList<T>::GetNode(int local)
{
	if (local < m_iCount && local >= 0)//当获取的位置合法的时候才进行获取操作
	{
		Node<T>* cur = m_head->next;
		for (int i = 0;i < local;i++, cur = cur->next);
		return cur;
	}
	else
		return NULL;
}

//升序排序
template<typename T>
void CycleLinkList<T>::SortByAsc()
{
	SelectSort();
}

//降序排序
template<typename T>
void CycleLinkList<T>::SortByDesc()
{
	SelectSort(false);
}

//选择排序法
template<typename T>
void CycleLinkList<T>::SelectSort(bool bAsc)
{
	for (int i = 0;i < m_iCount;i++)
	{
		Node<T>* node1 = GetNode(i);
		for (int j = i + 1;j < m_iCount;j++)
		{
			Node<T>* node2 = GetNode(j);
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

//获取最后一个节点
template<typename T>
Node<T>* CycleLinkList<T>::GetTailNode()
{
	return m_tail->next;
}

//合并链表  ,需要注意的是，合并后，原来的表就会被改变。
template<typename T>
void CycleLinkList<T>::MergeList(CycleLinkList<T>& sl)
{
	this->m_tail->next->next = sl.m_head->next;     //表1的最后一个节点指向表2的第一个节点
	this->m_tail->next = sl.m_tail->next;           //表1的尾指针指向表二的最后一个元素 
	sl.m_tail->next->next = this->m_head;			//表2的最后一个节点指向表1的head节点
	this->m_iCount += sl.m_iCount;                  //还要把元素个数加起来
}

//合并链表(有序)
template<typename T>
void CycleLinkList<T>::MergeListOrder(CycleLinkList<T>& sl,bool bAsc)
{
	MergeList(sl);
	SelectSort(bAsc);
}

//合并链表(无序)，不会改变原表
template<typename T>
void CycleLinkList<T>::MergeListNoChange(CycleLinkList<T>& sl)
{
	CycleLinkList<T> list(m_initNodeValue);
	sl.CopyList(list);            //复制链表,这样就不会改变原表
	MergeList(list);          
}

//合并链表(有序),不会改变原表
template<typename T>
void CycleLinkList<T>::MergeListNoChangeOrder(CycleLinkList<T>& sl, bool bAsc = true)
{
	CycleLinkList<T> list(m_initNodeValue);
	sl.CopyList(list);            //复制链表,这样就不会改变原表
	MergeListOrder(list, bAsc);
}
