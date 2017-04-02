#include "BTreeSearch.h"


//默认构造函数
BTreeSearch::BTreeSearch()
{
	m_nodeCount = 0;
}

//默认析构函数
BTreeSearch::~BTreeSearch()
{
}

/**********************private function***********************/

/*
* function				查找节点
* param	   Node*		节点指针
* param    int value    要查找的值
* return   Node*		成功返回该结点的指针，否则返回null
*/
BTreeSearch::Node* BTreeSearch::SearchNode(Node* btree,int value)
{
	// 1.如果该节点为空，则退出
	if (!btree)
		return nullptr;
	// 2.如果该节点的值等于value，则返回该节点
	else if (btree->value == value)
		return btree;
	// 3.如果该节点的值大于value，则递归遍历左子树
	else if (btree->value > value)
		SearchNode(btree->left, value);
	// 4.如果该节点的值小于value，则递归遍历右子树
	else if (btree->value < value)
		SearchNode(btree->right, value);
}

/*
* function				查找父节点
* param	   Node*		节点指针
* param    int value    要查找的值
* return   Node*		成功返回父节点，否则返回null
*/
BTreeSearch::Node* BTreeSearch::SearchParentNode(Node* btree,int value)
{
	// 1.如果该节点为空，则退出
	if (!btree || (!btree->left && !btree->right))
		return nullptr;
	// 2.如果该节点的值等于value，则返回该节点
	else if (btree->left && btree->left->value == value)
		return btree;
	else if (btree->right && btree->right->value == value)
		return btree;
	// 3.如果该节点的值大于value，则递归遍历左子树
	else if (btree->value > value)
		SearchParentNode(btree->left, value);
	// 4.如果该节点的值小于value，则递归遍历右子树
	else if (btree->value < value)
		SearchParentNode(btree->right, value);
}

/*
* function				创建节点
* param   value			节点值
* return  Node*			返回创建的节点
*/
BTreeSearch::Node* BTreeSearch::CreateNode(int value)
{
	return new Node(value);
}

/*
* function				添加节点辅助函数
* param		Node*		节点指针
* param		Node*		要添加的节点
* return                无
*/
void BTreeSearch::Add(Node* btree,Node* node)
{
	if (!btree)
		btree = node;
	// 1.如果该节点的值大于value，且其左节点为null，则将node作为该节点的左孩子
	else if (btree->value > node->value && !btree->left)
		btree->left = node;
	// 2.如果该节点的值小于value，且其右节点为null，则将node作为该节点的右孩子
	else if (btree->value < node->value && !btree->right)
		btree->right = node;
	// 3.如果该节点的值大于value，且其左节点不为null，则递归左子树
	else if (btree->value > node->value && btree->left)
		Add(btree->left, node);
	// 4.如果该节点的值小于value，且其右节点不为null，则递归右子树
	else if (btree->value < node->value && btree->right)
		Add(btree->right, node);
}

/*
* function				删除节点辅助函数
* param   cur			需要删除的节点
* param   par			需要删除节点的父节点
* param   bLeft         cur是左节点还是右节点
* return                无
*/
void BTreeSearch::Delete(Node** cur, Node** par, bool bLeft)
{
	// 1.若该节点无孩子，则直接删除
	if (!(*cur)->left && !(*cur)->right)
	{
		delete *cur;
		if (bLeft)
			(*par)->left = nullptr;
		else
			(*par)->right = nullptr;
	}
	// 2.若该节点只有一个孩子，则将该孩子直接顶替到原来的位置上
	else if ((!(*cur)->left && (*cur)->right) || ((*cur)->left && !(*cur)->right))
	{
		Node* temp = *cur;
		if (temp->left)  //根据bLeft的值来修改孩子节点
			if (bLeft)
				(*par)->left = temp->left;
			else
				(*par)->right = temp->left;
		else
			if (bLeft)
				(*par)->left = temp->right;
			else
				(*par)->right = temp->right;
		delete temp;
	}
	// 3.若该节点有两个孩子，则将该节点的右子树中最小的那个节点替换上去
	else
	{
		Node* minNode = FindMinNode((*cur)->right);  //找到需要删除的节点的右子树中最小的节点
		Node* parent = SearchParentNode((*cur), minNode->value); //同样，获取父节点是为了置孩子节点为null
		(*cur)->value = minNode->value; //修改值就好
		if (parent->left->value == minNode->value)  //如果是在左孩子中找到最小值
			parent->left = nullptr;
		else if (parent->right->value == minNode->value) //如果是在右孩子中找到，则左孩子肯定为null，这时只需要修改指向即可
			(*cur)->right = minNode->right;
		delete minNode;
	}
}

/*
* function				查找最小节点
* param   Node*			指定从哪个根节点开始查找
* return                无
*/
BTreeSearch::Node* BTreeSearch::FindMinNode(Node* btree)
{
	if (!btree)
		return nullptr;
	Node* cur = btree;
	while (cur->left)
		cur = cur->left;
	return cur;
}

/*
* function				打印二叉树辅助函数
* param	  Node*			节点指针
* param   bool			true(从小到大输出)，false（从大到小输出）
* return                无
*/
void BTreeSearch::Print(Node* btree, bool bMinToMax)
{
	if (bMinToMax)
	{
		if (btree)
		{
			Print(btree->left,bMinToMax);
			int i = btree->count;
			while (i--)                     //循环输出相同的值
				cout << btree->value << " ";
			Print(btree->right, bMinToMax);
		}
	}
	else
	{
		if (btree)
		{
			Print(btree->right, bMinToMax);
			int i = btree->count;
			while (i--)                       //循环输出相同的值
				cout << btree->value << " ";
			Print(btree->left, bMinToMax);
		}
	}
}

/**********************private function***********************/



/**********************public function***********************/

/*
* function				查找值
* param    int value    要查找的值
* return				成功返回该值，失败返回NO_FIND
*/
int BTreeSearch::Search(int value)
{
	Node* node = SearchNode(m_root, value);
	return node ? node->value : NO_FIND;
}

/*
* function				添加值
* param   int			要添加的值
* return                无
*/
void BTreeSearch::Add(int value)
{
	// 1.如果btree为null，说明当前是第一次添加根节点
	if (!m_root)
		m_root = CreateNode(value);
	else
	{
		// 2.先查找value值，如果存在，则直接count++
		Node* node = SearchNode(m_root, value);
		if (node)
			node->count++;
		else
		{
			// 3.如果该值不存在，则创建新结点
			node = CreateNode(value);

			// 4.添加节点
			Add(m_root, node);
		}
	}
	m_nodeCount++;
}

/*
* function				删除值
* param    int value    要删除的值
* return                删除失败返回false，否则返回true
*/
bool BTreeSearch::Delete(int value)
{
	// 1.如果btree为空则退出
	if (!m_root) return false;
	// 2.如果该节点是根节点的话
	else if (m_root->value == value)
	{
		Node* rootPar = new Node(0);
		rootPar->left = m_root;
		Delete(&m_root, &rootPar, true);   //这里模拟下面的，声明一个root的父节点，然后以同样的方式调用它
		m_root = rootPar->left;			   //最后要将root节点的指向修改	
		delete rootPar;
		--m_nodeCount;		
	}
	else
	{
		// 3.查找需要删除节点的父节点  (需要找到父节点是因为最后要将它的孩子置为null)
		Node* par = SearchParentNode(m_root, value);
		if (!par)
			return false;
		// 4.删除该节点(因为不懂是左还是右，所以要进一步判断)
		if (par->left && par->left->value == value)
			Delete(&par->left, &par, true);
		else
			Delete(&par->right, &par, false);
		--m_nodeCount;
	}
	return true;
}

/*
* function				获取二叉树节点个数(包括重复的)
* return                返回节点个数
*/
int BTreeSearch::Size()
{
	return m_nodeCount;
}

/*
* function				获取最小值
* return                返回二叉树的最小值
*/
int BTreeSearch::GetMinValue()
{
	Node* node = FindMinNode(m_root);
	return node ? node->value : NO_FIND;
}

/*
* function				获取最大值
* return                返回二叉树的最大值
*/
int BTreeSearch::GetMaxValue()
{
	if (!m_root)
		return NO_FIND;
	Node* cur = m_root;
	while (cur->right)
		cur = cur->right;
	return cur->value;
}

/*
* function				遍历二叉查找树
* param   bool			true(从小到大输出)，false（从大到小输出）
* return                无
*/
void BTreeSearch::Print(bool bMinToMax)
{
	Print(m_root, bMinToMax);
	cout << endl;
}

/**********************public function***********************/
