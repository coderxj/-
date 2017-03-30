#pragma once
/*
* author: acme
*   date: 2017-3-30
*  blogs: http://blog.csdn.net/qq_18297675
*/
#include <iostream>
#include <string>
using namespace std;

template<typename T>
class BTree
{
private:
	class Node  //节点类
	{
	public:
		Node(T data, Node* left = nullptr, Node* right = nullptr)
			:data(data), left(left), right(right) {}
	private:
		T data;
		Node* left;
		Node* right;
		friend class BTree;
	};

public:
	BTree();
	BTree(string s);
	~BTree();

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
	void CreateBtree(Node** root, string s);		//创建二叉树
	int Depth(Node* root);
	void GetN2(Node* root,int* count);
	void GetN1(Node* root, int* count);
	int GetN0(Node* root);
	void PreOrder(Node* root);
	void InOrder(Node* root);
	void PostOrder(Node* root);
	void Translevel(Node* root);
	void PrintNodeAtLevel(Node* root, int level);				//层次变量辅助函数
	void LevelAdd(Node* root, int level, T data, bool* bAdd);	//添加节点的辅助函数
	bool Search(Node* root,T data, bool* bFind);					//查找该值
private:
	Node* m_root;		//根节点
	int m_i;			//数组下标
};

/*
	默认构造函数
*/
template<typename T>
BTree<T>::BTree()
{
	m_root = nullptr;
}

/*
	带参构造函数
*/
template<typename T>
BTree<T>::BTree(string s)
{
	m_root = nullptr;
	Create(s);
}

/*
	默认析构函数
*/
template<typename T>
BTree<T>::~BTree()
{
	if (m_root)
		delete m_root;
	m_root = nullptr;
}

/***************private function*******************/

/*
* function				创建二叉树
* param		Node**		二级指针
* param		string		s
* return                无
*/
template<typename T>
void BTree<T>::CreateBtree(Node** root, string s)
{
	++m_i;
	//如果s为空，即二叉树为空,若s=""或者到达末尾s[i]都等于'\0'，这里空节点用空格表示
	if (s.empty() || s[m_i] == ' ')
		(*root) = nullptr;
	else
	{
		*root = new Node(s[m_i]);			//创建节点
		CreateBtree(&(*root)->left, s);		//递归创建左子树	
		CreateBtree(&(*root)->right, s);	//递归创建右子树
	}
}

/*
* function				计算二叉树深度
* param		Node*		root
* return                返回二叉树深度
*/
template<typename T>
int BTree<T>::Depth(Node* root)
{
	if (!root)
		return 0;
	else
	{
		int lDepth = Depth(root->left);   //递归计算左子树的深度
		int rDepth = Depth(root->right);  //递归计算右子树的深度
											   //返回较深的那个+1
		if (lDepth >= rDepth)
			return lDepth + 1;
		else
			return rDepth + 1;
	}
}

/*
* function				计算二叉树双分支节点数
* param		Node*		root
* return                返回二叉树双分支节点数
*/
template<typename T>
void BTree<T>::GetN2(Node* root, int* count)
{
	if (root == nullptr)   //如果二叉树为空，则返回0
		return;
	else
	{
		if (root->left && root->right)  //当该节点有两个分支的时候+1
			++(*count);
		GetN2(root->left, count);    //遍历左子树
		GetN2(root->right, count);   //遍历右子树
	}
}

/*
* function				计算二叉树单分支节点数
* param		Node*		root
* return                二叉树单分支节点数
*/
template<typename T>
void BTree<T>::GetN1(Node* root, int* count)
{
	if (root == nullptr)   //如果二叉树为空，则返回0
		return;
	else
	{
		if ((root->left && !root->right) || (!root->left && root->right))  //当该节点仅且只有一个分支的时候+1
			++(*count);
		GetN1(root->left, count);    //遍历左子树
		GetN1(root->right, count);   //遍历右子树
	}
}

/*
* function				计算二叉树终端节点数
* param		Node*		root
* return                二叉树终端节点数
*/
template<typename T>
int BTree<T>::GetN0(Node* root)
{
	int count = 0;
	GetN2(root, &count);
	return count + 1;		//计算公式n0 = n2 + 1;
}

/*
* function				前序遍历
* param		Node*		root
* return                无
*/
template<typename T>
void BTree<T>::PreOrder(Node* root)
{
	if (root)
	{
		cout << root->data << " ";
		PreOrder(root->left);
		PreOrder(root->right);
	}
}

/*
* function				中序遍历
* param		Node*		root
* return                无
*/
template<typename T>
void BTree<T>::InOrder(Node* root)
{
	if (root)
	{
		InOrder(root->left);
		cout << root->data << " ";
		InOrder(root->right);
	}
}

/*
* function				后序遍历
* param		Node*		root
* return                无
*/
template<typename T>
void BTree<T>::PostOrder(Node* root)
{
	if (root)
	{
		PostOrder(root->left);
		PostOrder(root->right);
		cout << root->data << " ";
	}
}

/*
* function				层次遍历
* param		Node*		root
* return                无
*/
template<typename T>
void BTree<T>::Translevel(Node* root)
{
	if (NULL == root)
		return;
	int depth = Depth(root);
	for (int i = 1; i <= depth; i++)
		PrintNodeAtLevel(root, i);
	cout << endl;
}

/*
* function				层次变量辅助函数
* param		int			level,层数
* return                无
*/
template<typename T>
void BTree<T>::PrintNodeAtLevel(Node* root,int level)
{
	// 空树或层级不合理
	if (nullptr == root || level < 1)
		return;

	if (1 == level)
	{
		cout << root->data << " ";
		return;
	}

	// 左子树的 level - 1 级
	PrintNodeAtLevel(root->left, level - 1);

	// 右子树的 level - 1 级
	PrintNodeAtLevel(root->right, level - 1);
}

/*
* function				添加节点的辅助函数
* param		int			level
* param		T			data
* param		bool*		标记是否添加成功
* return                无
*/
template<typename T>
void BTree<T>::LevelAdd(Node* root, int level, T data, bool* bAdd)
{
	//用来标记新的节点是否已经添加，如果添加了就退出了，避免重复添加
	if (*bAdd)return;
	//如果该节点为空，则可以将data赋值给该节点
	if (!root->left || !root->right)
	{
		Node* node = new Node(data);	//创建节点
		if (!root->left)
			root->left = node;
		else
			root->right = node;
		*bAdd = true;
		return;
	}
	//层级不合理
	if (level < 1)
		return;
	//递归结束条件
	if (1 == level)
		return;

	// 左子树的 level - 1 级
	LevelAdd(root->left, level - 1, data, bAdd);

	// 右子树的 level - 1 级
	LevelAdd(root->right, level - 1, data, bAdd);
}

/*
* function				查找该值
* param		Node*		root
* param		T			data
* param		bool	    标志是否找到了
* return                若存在则返回true，否则返回false
*/
template<typename T>
bool BTree<T>::Search(Node* root, T data, bool* bFind)
{
	if (*bFind)return true;    //如果已经找到了就不需要继续查找了
	//利用前序遍历来查找						 
	if (root)
	{
		if (root->data == data)
			*bFind = true;
		Search(root->left, data, bFind);
		Search(root->right, data, bFind);
	}
}

/******************private function*****************/

/******************public function*******************/

/*
* function				创建二叉树(前序创建)
* param		char* s     根据给定串创建
* return                无
*/
template<typename T>
void BTree<T>::Create(string s)
{
	m_i = -1;
	CreateBtree(&m_root, s);
}

/*
* function				是否为空
* return                空返回true，否则返回false
*/
template<typename T>
bool BTree<T>::IsEmpty()
{
	return m_root == nullptr;
}

/*
* function				二叉树深度
* return                返回二叉树深度
*/
template<typename T>
int BTree<T>::Depth()
{
	return Depth(m_root);
}

/*
* function				二叉树双分支节点数
* return                返回二叉树双分支节点数
*/
template<typename T>
int BTree<T>::GetN2()
{
	int count = 0;
	GetN2(m_root, &count);
	return count;
}

/*
* function				二叉树单分支节点数
* return                返回二叉树单分支节点数
*/
template<typename T>
int BTree<T>::GetN1()
{
	int count = 0;
	GetN1(m_root, &count);
	return count;
}

/*
* function				二叉树叶子节点数
* return                返回二叉树叶子节点数
*/
template<typename T>
int BTree<T>::GetN0()
{
	return GetN0(m_root);
}

/*
* function				前序遍历
* return                无
*/
template<typename T>
void BTree<T>::PreOrder()
{
	PreOrder(m_root);
	cout << endl;
}

/*
* function				中序遍历
* return                无
*/
template<typename T>
void BTree<T>::InOrder()
{
	InOrder(m_root);
	cout << endl;
}

/*
* function				后序遍历
* return                无
*/
template<typename T>
void BTree<T>::PostOrder()
{
	PostOrder(m_root);
	cout << endl;
}

/*
* function				层次遍历
* return                无
*/
template<typename T>
void BTree<T>::Translevel()
{
	Translevel(m_root);
	cout << endl;
}

/*
* function				添加节点值(添加的位置是不确定的)
* param		T			data	
* return                无
*/
template<typename T>
void BTree<T>::AddValue(T data)
{
	//采用层次遍历的办法，一层层扫描，若有空的地方，则添加到该地方
	if (nullptr == m_root) //如果此时二叉树为空，则创建根节点
	{
		m_root = new Node(data);	//创建根节点
		return;
	}
	int depth = Depth(m_root);

	bool bAdd = false;   //标记是否添加成功，避免重复添加
	for (int i = 1; i <= depth; i++)
	{
		if (bAdd)   //如果已经添加成功，则退出
			break;
		LevelAdd(m_root, i, data, &bAdd);
	}
}

/*
* function				查找该值
* param		char	    data
* return                若存在则返回true，否则返回false
*/
template<typename T>
bool BTree<T>::Search(T data)
{
	bool bFind = false;
	return Search(m_root, data, &bFind);
}


/******************public function*******************/
