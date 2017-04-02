
#pragma once
#include "BTreeSearch.h"

#include <stdio.h>
#include <stdlib.h>

/*
* function				查找节点
* param   PBTreeSearch  二叉查找树指针
* param    int value    要查找的值
* return  PBTreeSearch  返回该结点的指针
*/
PBTreeSearch SearchNode(PBTreeSearch btree, int value)
{
	// 1.如果该节点为空，则退出
	if (!btree)
		return NULL;
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
* param   PBTreeSearch  二叉查找树指针
* param    int value    要查找的值
* return  PBTreeSearch  返回父节点
*/
PBTreeSearch SearchParentNode(PBTreeSearch btree, int value)
{
	// 1.如果该节点为空，则退出
	if (!btree || (!btree->left && !btree->right))
		return NULL;
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
* function				查找值
* param   PBTreeSearch  二叉查找树指针
* param    int value    要查找的值
* return				成功返回该值，失败返回NO_FIND
*/
int Search(PBTreeSearch btree, int value)
{
	PBTreeSearch node = SearchNode(btree, value);
	return node ? node->value : NO_FIND;
}

/*
* function				创建节点
* param   value			节点值
* return   PBTreeSearch 返回创建的节点
*/
PBTreeSearch CreateNode(int value)
{
	PBTreeSearch node = (PBTreeSearch)malloc(sizeof(_btree_search));
	node->count = 1;
	node->value = value;
	node->left = NULL;
	node->right = NULL;
	return node;
}

/*
* function				添加节点辅助函数
* param   PBTreeSearch  二叉查找树指针
* param   PBTreeSearch  要添加的节点
* return                无
*/
void Add(PBTreeSearch btree, PBTreeSearch node)
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
* function				添加节点
* param   PBTreeSearch  二叉查找树指针
* param    int value    要添加的值
* return                无
*/
void AddValue(PBTreeSearch* btree, int value)
{
	// 1.如果btree为null，说明当前是第一次添加根节点
	if (!(*btree))
		*btree = CreateNode(value);
	else
	{
		// 2.先查找value值，如果存在，则直接count++
		PBTreeSearch node = SearchNode(*btree, value);
		if (node)
			node->count++;
		else
		{
			// 3.如果该值不存在，则创建新结点
			node = CreateNode(value);

			// 4.添加节点
			Add(*btree, node);
		}
	}	
}

/*
* function				删除节点辅助函数
* param   cur			需要删除的节点
* param   par			需要删除节点的父节点
* param   bLeft         cur是左节点还是右节点
* return                无
*/
void Delete(PBTreeSearch* cur, PBTreeSearch* par,bool bLeft)
{
	// 1.若该节点无孩子，则直接删除
	if (!(*cur)->left && !(*cur)->right)
	{
		free(*cur);
		if(bLeft)
			(*par)->left = NULL;
		else
			(*par)->right = NULL;
	}
	// 2.若该节点只有一个孩子，则将该孩子直接顶替到原来的位置上
	else if ((!(*cur)->left && (*cur)->right) || ((*cur)->left && !(*cur)->right))
	{
		PBTreeSearch temp = *cur;
		if (temp->left)  //根据bLeft的值来修改孩子节点
			if(bLeft)
				(*par)->left = temp->left;
			else
				(*par)->right = temp->left;
		else
			if(bLeft)
				(*par)->left = temp->right;
			else
				(*par)->right = temp->right;
		free(temp);
	}
	// 3.若该节点有两个孩子，则将该节点的右子树中最小的那个节点替换上去
	else
	{
		PBTreeSearch minNode = FindMinNode((*cur)->right);  //找到需要删除的节点的右子树中最小的节点
		PBTreeSearch parent = SearchParentNode((*cur), minNode->value); //同样，获取父节点是为了置孩子节点为null
		(*cur)->value = minNode->value; //修改值就好
		if (parent->left->value == minNode->value)  //如果是在左孩子中找到最小值
			parent->left = NULL;
		else if (parent->right->value == minNode->value) //如果是在右孩子中找到，则左孩子肯定为null，这时只需要修改指向即可
			(*cur)->right = minNode->right;
		free(minNode);
	}
}

/*
* function				删除节点
* param   PBTreeSearch  二叉查找树指针
* param    int value    要删除的值
* return                无
*/
void DeleteValue(PBTreeSearch* btree, int value)
{
	// 1.如果btree为空则退出
	if (!(*btree));
	// 2.如果该节点是根节点的话
	else if ((*btree)->value == value)
	{
		PBTreeSearch rootPar = (PBTreeSearch)malloc(sizeof(_btree_search));
		rootPar->left = *btree;		
		Delete(btree, &rootPar, true);   //这里模拟下面的，声明一个root的父节点，然后以同样的方式调用它
		*btree = rootPar->left;			 //最后要将root节点的指向修改	
		free(rootPar);
	}
	else
	{
		// 3.查找需要删除节点的父节点  (需要找到父节点是因为最后要将它的孩子置为null)
		PBTreeSearch par = SearchParentNode(*btree, value);
		if (!par)
			return;
		// 4.删除该节点(因为不懂是左还是右，所以要进一步判断)
		if (par->left && par->left->value == value)
			Delete(&par->left, &par, true);
		else
			Delete(&par->right, &par, false);
	}
}

/*
* function				查找最小节点
* param   PBTreeSearch  二叉查找树指针
* return                无
*/
PBTreeSearch FindMinNode(PBTreeSearch btree)
{
	if (!btree)
		return NULL;
	PBTreeSearch cur = btree;
	while (cur->left)
		cur = cur->left;
	return cur;
}

/*
* function				查找最小值
* param   PBTreeSearch  二叉查找树指针
* return                无
*/
int FindMinValue(PBTreeSearch btree)
{
	PBTreeSearch node = FindMinNode(btree);
	return node ? node->value : NO_FIND;
}

/*
* function				查找最大值
* param   PBTreeSearch  二叉查找树指针
* return                无
*/
int FindMaxValue(PBTreeSearch btree)
{
	if (!btree)
		return NO_FIND;
	PBTreeSearch cur = btree;
	while (cur->right)
		cur = cur->right;
	return cur->value;
}

/*
* function				遍历二叉查找树(从小到大,用中序遍历即可)
* param   PBTreeSearch  二叉查找树指针
* return                无
*/
void PrintMinToMax(PBTreeSearch btree)
{
	if (btree)
	{
		PrintMinToMax(btree->left);
		int i = btree->count;
		while (i--)                     //循环输出相同的值
			printf("%d ", btree->value);
		PrintMinToMax(btree->right);
	}
}

/*
* function				遍历二叉查找树(从大到小,遍历顺序：右 -> 根 -> 左)
* param   PBTreeSearch  二叉查找树指针
* return                无
*/
void PrintMaxToMin(PBTreeSearch btree)
{
	if (btree)
	{
		PrintMaxToMin(btree->right);
		int i = btree->count;
		while (i--)                       //循环输出相同的值
			printf("%d ", btree->value);
		PrintMaxToMin(btree->left);
	}
}
