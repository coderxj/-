#pragma once
/*
* author: acme
*   date: 2017-3-12
*  blogs: http://blog.csdn.net/qq_18297675
*/

#include <iostream>
#include <string>
using namespace std;

template<typename T>
class GList		//广义表类
{
	enum NodeType { ATOM, LIST };   //节点类型
private:
	class Node   //广义表结点类
	{
	public:
		Node(NodeType nodeType, T atom)
			:nodeType(nodeType), atom(atom) {}
	private:
		NodeType nodeType;		//节点类型
		union
		{
			T atom;				//原子
			Node* subList;		//子表
		};
		Node* next;				//指向下一个元素
		friend class GList;
	};
public:
	GList();
	GList(string s);
	~GList();

public:
	int Length();
	int Depth();									//广义表深度
	int AtomNums()const { return m_atomNums; };		//原子个数
	void CreateGList(string s);                     //创建广义表
	void AddFront(T atom);							//添加原子到广义表的前面
	void AddRear(T atom);							//添加原子到广义表的后面  
	void AddFront(GList<T>* g);                     //添加表到广义表的前面
	void AddRear(GList<T>* g);                      //添加表到广义表的后面  
	void Print();                                   //打印广义表
private:
	void Create(Node** glist, string s);            //创建广义表
	int GetLength(Node* glist);						//计算广义表长度
	int GetDepth(Node* glist);                      //计算广义表深度
	void Print(Node* glist);                        //打印广义表
	Node* GetHead();                                //获取头节点
	Node* GetTail();                                //获取尾结点 
private:
	int m_atomNums;            //原子个数
	Node* m_glist;             //指向广义表头节点的指针
	int m_i;                   //这个的用处是在Create函数中的s下标，如果在Create函数中用静态变量的话，那么重复创建对象的时候，i的值没有初始化会出错
};

template<typename T>
GList<T>::GList()
{
	m_i = -1;
	m_atomNums = 0;
}

template<typename T>
GList<T>::GList(string s)
{
	m_i = -1;
	m_atomNums = 0;
	CreateGList(s);
}

template<typename T>
GList<T>::~GList()
{
	if (m_glist)
		delete m_glist;
	m_glist = nullptr;
}


/************************private function start********************************/
//创建广义表
template<typename T>
void GList<T>::Create(Node** glist, string s)
{
	//若是()，则广义表为空
	
	++m_i;
	if (s[m_i] == '(' && s[m_i + 1] == ')')
		(*glist) = nullptr;
	else if (s[m_i] == '(') //如果是左括号，则递归构建子表
	{
		(*glist) = new Node(LIST, 0);
		Create(&(*glist)->subList, s);
	}
	else
	{
		T atom;
		string temp;
		string s1(typeid(T).name());
		if (s1.compare("char") == 0)   //char字符，就一个个的
			atom = s[m_i];
		else
		{
			int c1 = 0;
			int c2 = 0;
			int c = 0;
			c1 = s.find_first_of(',', m_i) - m_i;   //计算要截取多少个字符
			c2 = s.find_first_of(')', m_i) - m_i;
			if (c1 < 0 || c1 > c2)              //取大于0的最小值
				c = c2;							//例如，(1,(1,2),3),这时到2这个原子的时候，离')'最近，截取长度为1，所以选它
			else
				c = c1;
			temp = s.substr(m_i, c);  //将原子截取出来
		}
		if (s1.compare("int") == 0)//需要将字符串转换为整形
		{
			atom = atoi(temp.c_str());
			m_i += temp.size() - 1;   //-1是为了抵消下面的++i
		}
		else if (s1.compare("double") == 0)
		{
			atom = atof(temp.c_str());
			m_i += temp.size() - 1;
		}
		(*glist) = new Node(ATOM, atom);
		++m_atomNums;
	}
	++m_i;
	if (*glist == nullptr);
	else if (s[m_i] == ',')
		Create(&(*glist)->next, s);   //递归构建后继节点
	else if (s[m_i] == ')' || s[m_i] == '\0')   //当子表或者构建完成，把最后的指针置为NULL
		(*glist)->next = nullptr;
}

//计算广义表长度
template<typename T>
int GList<T>::GetLength(Node* glist)
{
	return glist ? 1 + GetLength(glist->next) : 0;
}

//计算广义表深度
template<typename T>
int GList<T>::GetDepth(Node* glist)
{
	int max = 0;
	while (glist != nullptr)
	{
		if (glist->nodeType == LIST)     //如果有子表，就继续深入遍历
		{
			int dep = GetDepth(glist->subList);
			if (dep > max) max = dep;    //取最大的深度
		}
		glist = glist->next;
	}
	return max + 1;
}

//打印广义表
template<typename T>
void GList<T>::Print(Node* glist)
{
	if (!glist)
		return;
	else if (glist->nodeType == LIST)
	{
		cout << "(";
		Print(glist->subList);
		cout << ")";
	}
	else if (glist->nodeType == ATOM)
		cout << glist->atom;
	if (glist->next)
	{
		cout << ",";
		Print(glist->next);
	}
}

//获取头节点
template<typename T>
typename GList<T>::Node* GList<T>::GetHead()
{
	return m_glist;
}

//获取尾结点 
template<typename T>
typename GList<T>::Node* GList<T>::GetTail()
{
	Node* cur = m_glist->subList;		//当前节点
	while (cur->next)
		cur = cur->next;
	return cur;
}

/************************private function end********************************/



//广义表长度
template<typename T>
int GList<T>::Length()    //这里要记住，const对象只能调用const函数，且const函数不能对成员函数做修改，否则会出错,所以这里把const去掉
{
	return GetLength(m_glist->subList);
}

//广义表深度
template<typename T>
int GList<T>::Depth()
{
	return GetDepth(m_glist->subList);
}

//创建广义表
template<typename T>
void GList<T>::CreateGList(string s)
{
	Create(&m_glist, s);
}

//添加原子到广义表的前面
template<typename T>
void GList<T>::AddFront(T atom)			//这里和单链表的添加一模一样
{
	Node* node = new Node(ATOM, atom);
	node->next = m_glist->subList;   //这里的m_glist->subList相当于头节点,而不是m_glist->next
	m_glist->subList = node;         //因为第一个节点肯定是表节点,创建的时候就是这样定义了
	++m_atomNums;
}

//添加原子到广义表的后面
template<typename T>
void GList<T>::AddRear(T atom)          //这里和单链表的添加一模一样 
{
	Node* tail = GetTail();		//最后一个节点
	Node* node = new Node(ATOM, atom);
	tail->next = node;
	node->next = nullptr;
	++m_atomNums;
}

//添加表到广义表的前面
template<typename T>
void GList<T>::AddFront(GList<T>* g)
{
	Node* head = g->GetHead();
	head->next = m_glist->subList;
	m_glist->subList = head;
	m_atomNums += g->AtomNums();
}

//添加表到广义表的后面
template<typename T>
void GList<T>::AddRear(GList<T>* g)
{
	Node* tail = GetTail();				//最后一个节点
	tail->next = g->GetHead();
	m_atomNums += g->AtomNums();
}

//打印广义表
template<typename T>
void GList<T>::Print()
{
	cout << '(';
	Print(m_glist->subList);
	cout << ')' << endl;
}
