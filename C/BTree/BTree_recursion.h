#pragma once
/*
* author: acme
*   date: 2017-3-30
*  blogs: http://blog.csdn.net/qq_18297675
*/

/*
*/

//二叉树结构
typedef struct _binary_tree
{
	char data;				//值域
	_binary_tree* left;		//左节点
	_binary_tree* right;	//右节点
}BTree, *PBTree;


/*****************************递归*****************************/

/*
* function				创建二叉树(前序创建)
* param     PBTree*		root（二级指针）
* param		char* s     根据给定字符串创建
* param     bool        标记是否新创建一颗树
* return                无
*/
void CreateBTree(PBTree* root, char* s, bool newTree)
{
	static int i = -1;		//s下标
	if (newTree) i = -1;	//因为i是静态变量，所以只能手动修改它值，如果是新的二叉树则重置它的值
	++i;
	//如果s为空，即二叉树为空,若s=""或者到达末尾s[i]都等于'\0'，这里空节点用空格表示
	if (!s || s[i] == '\0' || s[i] == ' ')
		(*root) = NULL;
	else
	{
		*root = (PBTree)malloc(sizeof(_binary_tree));	//创建节点
		(*root)->data = s[i];
		CreateBTree(&(*root)->left, s, false);			//递归创建左子树	
		CreateBTree(&(*root)->right, s, false);			//递归创建右子树
	}
}

/*
* function				判断二叉树是否为空
* param		PBTree      root
* return                空返回true，否则返回false
*/
bool BTreeIsEmpty(PBTree root)
{
	return root == NULL;
}

/*
* function				计算二叉树深度
* param		PBTree      root
* return                返回二叉树深度
*/
int BTreeDepth(PBTree root)
{
	if (!root)
		return 0;
	else
	{
		int lDepth = BTreeDepth(root->left);   //递归计算左子树的深度
		int rDepth = BTreeDepth(root->right);  //递归计算右子树的深度
											//返回较深的那个+1
		if (lDepth >= rDepth)
			return lDepth + 1;
		else
			return rDepth + 1;
	}
}

/*
* function				计算二叉树双分支节点数
* param		PBTree      root
* return                返回二叉树双分支节点数
*/
int GetN2(PBTree root, bool newTree)
{
	static int count = 0;
	if (newTree) count = 0;
	if (root == NULL)   //如果二叉树为空，则返回0
		return 0;
	else
	{
		if (root->left && root->right)  //当该节点有两个分支的时候+1
			++count;
		GetN2(root->left, false);    //遍历左子树
		GetN2(root->right, false);   //遍历右子树
	}
	return count;
}

/*
* function				计算二叉树单分支节点数
* param		PBTree      root
* return                二叉树单分支节点数
*/
int GetN1(PBTree root, bool newTree)
{
	static int count = 0;
	if (newTree) count = 0;
	if (root == NULL)   //如果二叉树为空，则返回0
		return 0;
	else
	{
		if ((root->left && !root->right) || (!root->left && root->right))  //当该节点仅且只有一个分支的时候+1
			++count;
		GetN1(root->left, false);    //遍历左子树
		GetN1(root->right, false);   //遍历右子树
	}
	return count;
}

/*
* function				计算二叉树终端节点数
* param		PBTree      root
* return                二叉树终端节点数
*/
int GetN0(PBTree root)
{
	return GetN2(root, true) + 1; //计算公式n0 = n2 + 1;
}

/*
* function				前序遍历
* param		PBTree      root
* return                无
*/
void PreOrder(PBTree root)
{
	if (root)
	{
		printf("%c", root->data);
		PreOrder(root->left);
		PreOrder(root->right);
	}
}

/*
* function				中序遍历
* param		PBTree      root
* return                无
*/
void InOrder(PBTree root)
{
	if (root)
	{
		InOrder(root->left);
		printf("%c", root->data);
		InOrder(root->right);
	}
}

/*
* function				后序遍历
* param		PBTree      root
* return                无
*/
void PostOrder(PBTree root)
{
	if (root)
	{
		PostOrder(root->left);
		PostOrder(root->right);
		printf("%c", root->data);
	}
}

/*
* function				层次遍历辅助函数
* param		PBTree      root
* param		int			level
* return                无
*/
void PrintNodeAtLevel(PBTree root, int level)
{
	// 空树或层级不合理
	if (NULL == root || level < 1)
		return;

	if (1 == level)//相当于输出根节点，因为每一个节点都可以左为子树的根节点 
	{
		printf("%c", root->data);
		return;
	}

	// 左子树的 level - 1 级
	PrintNodeAtLevel(root->left, level - 1);

	// 右子树的 level - 1 级
	PrintNodeAtLevel(root->right, level - 1);
}

/*
* function				层次遍历
* param		PBTree      root
* return                无
*/
void translevel(PBTree root)
{
	if (NULL == root)
		return;
	int depth = BTreeDepth(root);

	for (int i = 1; i <= depth; i++)
		PrintNodeAtLevel(root, i);
	printf("\n");
}

/*
* function				添加节点的辅助函数
* param		PBTree      root
* param		int			level
* param		char		ch
* param		bool*		标记是否添加成功
* return                无
*/
void LevelAdd(PBTree root, int level,char ch,bool* bAdd)
{
	//用来标记新的节点是否已经添加，如果添加了就退出了，避免重复添加
	if (*bAdd)return;
	//如果该节点为空，则可以将ch赋值给该节点
	if (!root->left || !root->right)
	{
		PBTree node = (PBTree)malloc(sizeof(_binary_tree));	//创建节点
		node->data = ch;
		node->left = NULL;
		node->right = NULL;
		if(!root->left)
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
	LevelAdd(root->left, level - 1, ch, bAdd);

	// 右子树的 level - 1 级
	LevelAdd(root->right, level - 1, ch, bAdd);
}

/*
* function				添加节点值(添加的位置是不确定的)
* param		PBTree      root
* param		char	    ch
* return                无
*/
void AddValue(PBTree root,char ch)
{
	//采用层次遍历的办法，一层层扫描，若有空的地方，则添加到该地方
	if (NULL == root) //如果此时二叉树为空，则创建根节点
	{
		root = (PBTree)malloc(sizeof(_binary_tree));	//创建节点
		root->data = ch;
		root->left = NULL;
		root->right = NULL;
		return;
	}	
	int depth = BTreeDepth(root);

	bool bAdd = false;   //标记是否添加成功，避免重复添加
	for (int i = 1; i <= depth; i++)
	{
		if (bAdd)   //如果已经添加成功，则退出
			break;
		LevelAdd(root, i, ch, &bAdd);
	}		
}

/*
* function				查找该值
* param		PBTree      root
* param		char	    ch
* param		bool	    标志是否是第一次查找,如果是第一次要将标志重置，因为静态变量要手动重置它的值
* return                若存在则返回true，否则返回false
*/
bool Search(PBTree root, char ch,bool first)
{
	static bool bFind = false;
	if (first) bFind = false;
	if (bFind)return true;    //如果已经找到了就不需要继续查找了
	//利用前序遍历来查找
	if (root)
	{
		if (root->data == ch)
			bFind = true;
		Search(root->left, ch, false);
		Search(root->right, ch, false);
	}
}

/*****************************递归*****************************/
