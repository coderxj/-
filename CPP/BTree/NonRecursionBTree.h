#pragma once
/*
* author: acme
*   date: 2017-3-30
*  blogs: http://blog.csdn.net/qq_18297675
*/
#include <iostream>
#include <string>
#include <stack>
#include <queue>
using namespace std;

template<typename T>
class NonRecursionBTree
{
private:
	class Node  //节点类
	{
	public:
		Node(T data, Node* left = nullptr, Node* right = nullptr)
			:data(data), left(left), right(right),bLCExits(false),bRCExits(false) {}
	private:
		T data;
		bool bLCExits;			//左孩子是否存在
		bool bRCExits;			//左孩子是否存在
		Node* left;				//左节点
		Node* right;			//右节点
		friend class NonRecursionBTree;
	};

public:
	NonRecursionBTree();
	NonRecursionBTree(string s);
	~NonRecursionBTree();

public:
	void Create(string s);							//创建二叉树
	bool IsEmpty();									//是否为空
	int Depth();									//深度
	int GetN2();									//二叉树双分支节点数
	int GetN1();									//二叉树单分支节点数
	int GetN0();									//二叉树叶子节点数
	void PreOrder();								//前序遍历
	void InOrder();									//中序遍历
	void PostOrder();								//后序遍历
	void Translevel();								//层次遍历
	void AddValue(T data);                          //添加节点值(添加的位置是不确定的)
	bool Search(T data);                            //查找该值

private:
	Node* m_root;		//根节点
};

template<typename T>
NonRecursionBTree<T>::NonRecursionBTree()
{
	m_root = nullptr;
}

template<typename T>
NonRecursionBTree<T>::NonRecursionBTree(string s)
{
	m_root = nullptr;
	Create(s);
}

template<typename T>
NonRecursionBTree<T>::~NonRecursionBTree()
{
	if (m_root)
		delete m_root;
	m_root = nullptr;
}

/*
* function				创建二叉树(前序创建)
* param		char* s     根据给定串创建
* return                无
*/
template<typename T>
void NonRecursionBTree<T>::Create(string s)
{
	if (s.empty())  //如果s为空 则树也为空
		return ;
	stack<Node*> st;	//创建一个栈
	int i = 0;
	// 1.先创建根节点
	m_root = new Node(s[i++]);
	Node* btree = m_root;		//用一个临时的指针代替root，因为最后要返回root指针，所以它不能改变
	st.push(btree);				//将根节点压入栈中
	int len = s.size();
	while (i < len)
	{
		// 2.如果当前读到的字符不为空，并且当前节点的左孩子不存在，则创建它
		if (s[i] != ' ' && btree->bLCExits == false)
		{
			btree->left = new Node(s[i]);	//创建左孩子
			btree->bLCExits = true;			//左孩子存在
			btree = btree->left;
			st.push(btree);  //入栈
			++i;
		}
		// 3.如果当前读到的字符不为空，并且当前节点的右孩子不存在，则创建它
		else if (s[i] != ' ' && btree->bRCExits == false)
		{
			btree->right = new Node(s[i]);	//创建右孩子
			btree->bRCExits = true;			//右孩子存在
			btree = btree->right;
			st.push(btree);  //入栈
			++i;
		}
		// 4.如果当前读到的字符为空，并且当前节点的左孩子不存在，则将当前节点的左孩子置为存在（空也算孩子）
		else if (s[i] == ' ' && btree->bLCExits == false) //空节点
			btree->bLCExits = true, ++i;  //左孩子存在
		// 5.如果当前读到的字符为空，并且当前节点的右孩子不存在，则将当前节点的右孩子置为存在（空也算孩子）
		else if (s[i] == ' ' && btree->bRCExits == false)
			btree->bRCExits = true, ++i;  //右孩子存在		

		// 6.回溯回去,当该节点的度为2的时候(就是左右孩子都存在的情况)
		if (btree->bLCExits && btree->bRCExits)
			st.pop(), btree = st.top();
	}
	while (!st.empty())  //最后销毁栈
		st.pop();
}

/*
* function				是否为空
* return                空返回true，否则返回false
*/
template<typename T>
bool NonRecursionBTree<T>::IsEmpty()
{
	return m_root == nullptr;
}

/*
* function				二叉树深度
* return                无
*/
template<typename T>
int NonRecursionBTree<T>::Depth()
{
	if (!m_root) return 0;
	queue<Node*> q;						//创建一个队列
	Node* cur = m_root;					//当前节点
	int iDepth = 0;
	q.push(cur);						//先将根节点加入队列中
	while (!q.empty())					//当队列中没有元素时，遍历完成 
	{
		++iDepth;							//外层循环控制层数
		int curLevelNodes = q.size();		//当前层数的节点数
		int temp = 0;						//临时记录已经遍历的节点数
		while (temp++ < curLevelNodes)		//当遍历完当前层数后，退出内层循环，继续遍历下一层
		{
			cur = q.front();				//获取当前队头元素
			q.pop();						//遍历过后就出队
			if (cur->left)					//如果左孩子不为空，则入队等待遍历
				q.push(cur->left);
			if (cur->right)				    //如果右孩子不为空，则入队等待遍历
				q.push(cur->right);
		}
	}
	return iDepth;
}

/*
* function				二叉树双分支节点数
* return                无
*/
template<typename T>
int NonRecursionBTree<T>::GetN2()
{
	stack<Node*> st;				//创建一个栈
	Node* btree = m_root;			//创建临时指针指向root
	int count = 0;
	//利用前序遍历来访问所有的节点
	while (btree || !st.empty())
	{
		while (btree)
		{
			st.push(btree);
			btree = btree->left;
		}
		if (!st.empty())
		{
			btree = st.top();
			if (btree)                            //再这里能保证所有的节点都能被判断到
				if (btree->left && btree->right)  //当该节点有两个分支的时候+1
					++count;
			st.pop();
			btree = btree->right;
		}
	}
	return count;
}

/*
* function				二叉树单分支节点数
* return                无
*/
template<typename T>
int NonRecursionBTree<T>::GetN1()
{
	stack<Node*> st;				//创建一个栈
	Node* btree = m_root;			//创建临时指针指向root
	int count = 0;
	//利用前序遍历来访问所有的节点
	while (btree || !st.empty())
	{
		while (btree)
		{
			st.push(btree);
			btree = btree->left;
		}
		if (!st.empty())
		{
			btree = st.top();
			if (btree)                            //再这里能保证所有的节点都能被判断到
				if ((btree->left && !btree->right) || (!btree->left && btree->right))  //当该节点仅且只有一个分支的时候+1
					++count;
			st.pop();
			btree = btree->right;
		}
	}
	return count;
}

/*
* function				二叉树叶子节点数
* return                无
*/
template<typename T>
int NonRecursionBTree<T>::GetN0()
{
	return GetN2() + 1; //计算公式n0 = n2 + 1;
}

/*
* function				前序遍历
* return                无
*/
template<typename T>
void NonRecursionBTree<T>::PreOrder()
{
	stack<Node*> st;				//创建一个栈
	Node* btree = m_root;			//创建临时指针指向root
	// 1. 若当前节点不为空，或者栈中元素不为空（相当于还没有遍历完所有节点）
	while (btree || !st.empty())
	{
		// 2. 先遍历左子树，一直到左子树为空为止。
		while (btree)
		{
			cout << btree->data << " ";
			st.push(btree);
			btree = btree->left;
		}

		// 3.若栈中还有元素，则将当前btree赋值为它的右子树，然后再重复 1~2步骤
		if (!st.empty())
		{
			btree = st.top();
			st.pop();
			btree = btree->right;
		}
	}
	cout << endl;
}

/*
* function				中序遍历
* return                无
*/
template<typename T>
void NonRecursionBTree<T>::InOrder()
{
	stack<Node*> st;				//创建一个栈
	Node* btree = m_root;			//创建临时指针指向root
									// 1. 若当前节点不为空，或者栈中元素不为空（相当于还没有遍历完所有节点）
	while (btree || !st.empty())
	{
		// 2. 先遍历左子树，一直到左子树为空为止。
		while (btree)
		{
			st.push(btree);
			btree = btree->left;
		}

		// 3.若栈中还有元素，则将当前btree赋值为它的右子树，然后再重复 1~2步骤
		if (!st.empty())
		{
			btree = st.top();
			cout << btree->data << " ";//遍历完左子树后输出它们的根节点
			st.pop();
			btree = btree->right;
		}
	}
	cout << endl;
}

/*
* function				后序遍历
* return                无
*/
template<typename T>
void NonRecursionBTree<T>::PostOrder()
{
	if (!m_root)return;
	stack<Node*> st;				//创建一个栈
	Node* cur;						//当前结点 
	Node* pre = nullptr;			//前一次访问的结点 
	st.push(m_root);				//先将根节点入栈
	while (!st.empty())
	{
		cur = st.top();          //这里的cur就像是每颗子树的根节点，然后重复这些步骤
		if ((!cur->left && !cur->right) ||
			(pre && (pre == cur->left || pre == cur->right)))
		{
			cout << cur->data << " ";  //如果当前结点没有孩子结点或者孩子节点都已被访问过 
			st.pop();
			pre = cur;
		}
		else
		{
			if (cur->right != nullptr)      //这里先将右孩子入栈，这样出栈的时候，左孩子就先出栈
				st.push(cur->right);
			if (cur->left != nullptr)
				st.push(cur->left);
		}
	}
	cout << endl;
}

/*
* function				层次遍历
* return                无
*/
template<typename T>
void NonRecursionBTree<T>::Translevel()
{
	if (!m_root) return;
	queue<Node*> q;						//创建一个队列
	Node* cur = m_root;					//当前节点
	q.push(cur);					//先将根节点加入队列中
	while (!q.empty())				//当队列中没有元素时，遍历完成 
	{
		cur = q.front();			//获取当前队头元素
		q.pop();					//遍历过后就出队
		cout << cur->data << " ";				//先输出该子树的根节点
		if (cur->left)					//如果左孩子不为空，则入队等待遍历
			q.push(cur->left);
		if (cur->right)				    //如果右孩子不为空，则入队等待遍历
			q.push(cur->right);
	}
	cout << endl;
}

/*
* function				添加节点值(添加的位置是不确定的)
* param		T			data
* return                无
*/
template<typename T>
void NonRecursionBTree<T>::AddValue(T data)
{
	//采用层次遍历的办法，一层层扫描，若有空的地方，则添加到该地方
	if (!m_root)
	{
		m_root = new Node(data);
		return;
	}
	queue<Node*> q;						//创建一个队列
	Node* cur = m_root;					//当前节点
	q.push(cur);						//先将根节点加入队列中
	while (!q.empty())					//当队列中没有元素时，遍历完成 
	{
		cur = q.front();				//获取当前队头元素
		q.pop();						//遍历过后就出队
		if (cur->left)					//如果左孩子不为空，则入队等待遍历
			q.push(cur->left);
		else                            //否则就添加值，然后退出
		{
			cur->left = new Node(data);
			break;
		}
		if (cur->right)				    //如果右孩子不为空，则入队等待遍历
			q.push(cur->right);
		else                            //否则就添加值，然后退出
		{
			cur->right = new Node(data);//否则就添加值，然后退出
			break;
		}
	}
}

/*
* function				查找该值
* param		char	    data
* return                若存在则返回true，否则返回false
*/
template<typename T>
bool NonRecursionBTree<T>::Search(T data)
{
	//利用层次遍历来查找
	if (!m_root) return false;
	queue<Node*>q;						//创建一个队列
	Node* cur = m_root;					//当前节点
	q.push(cur);						//先将根节点加入队列中
	while (!q.empty())					//当队列中没有元素时，遍历完成 
	{
		cur = q.front();			//获取当前队头元素
		if (cur->data == data)
			return true;
		q.pop();						//遍历过后就出队
		if (cur->left)					//如果左孩子不为空，则入队等待遍历
			q.push(cur->left);
		if (cur->right)				    //如果右孩子不为空，则入队等待遍历
			q.push(cur->right);
	}
	return false;
}
