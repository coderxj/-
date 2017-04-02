/*
* author: acme
*   date: 2017-4-2
*  blogs: http://blog.csdn.net/qq_18297675
*/
#pragma once
#include <stdio.h>
#include <stdlib.h>

#define NO_FIND ~(1<<31)  

//树节点
typedef struct _btree_search
{
	int value;					//节点值
	int count;					//重复节点的个数
	_btree_search* left;		//左孩子
	_btree_search* right;		//右孩子
}BTreeSearch,*PBTreeSearch;

/*
* function				查找节点
* param   PBTreeSearch  二叉查找树指针
* param    int value    要查找的值
* return  PBTreeSearch  返回该结点的指针
*/
PBTreeSearch SearchNode(PBTreeSearch btree, int value);

/*
* function				查找父节点
* param   PBTreeSearch  二叉查找树指针
* param    int value    要查找的值
* return  PBTreeSearch  返回父节点
*/
PBTreeSearch SearchParentNode(PBTreeSearch btree, int value);

/*
* function				查找值
* param   PBTreeSearch  二叉查找树指针
* param    int value    要查找的值
* return				成功返回该值，失败返回NO_FIND
*/
int Search(PBTreeSearch btree, int value);

/*
* function				创建节点
* param   value			节点值
* return   PBTreeSearch 返回创建的节点
*/
PBTreeSearch CreateNode(int value);

/*
* function				添加节点辅助函数
* param   PBTreeSearch  二叉查找树指针
* param   PBTreeSearch  要添加的节点
* return                无
*/
void Add(PBTreeSearch btree, PBTreeSearch node);

/*
* function				添加节点
* param   PBTreeSearch  二叉查找树指针
* param    int value    要添加的值
* return                无
*/
void AddValue(PBTreeSearch* btree, int value);

/*
* function				删除节点辅助函数
* param   cur			需要删除的节点
* param   par			需要删除节点的父节点
* param   bLeft         cur是左节点还是右节点
* return                无
*/
void Delete(PBTreeSearch* cur, PBTreeSearch* par, bool bLeft);

/*
* function				删除节点
* param   PBTreeSearch  二叉查找树指针
* param    int value    要删除的值
* return                无
*/
void DeleteValue(PBTreeSearch* btree, int value);

/*
* function				查找最小节点
* param   PBTreeSearch  二叉查找树指针
* return                无
*/
PBTreeSearch FindMinNode(PBTreeSearch btree);

/*
* function				查找最小值
* param   PBTreeSearch  二叉查找树指针
* return                无
*/
int FindMinValue(PBTreeSearch btree);

/*
* function				查找最大值
* param   PBTreeSearch  二叉查找树指针
* return                无
*/
int FindMaxValue(PBTreeSearch btree);

/*
* function				遍历二叉查找树(从小到大,用中序遍历即可)
* param   PBTreeSearch  二叉查找树指针
* return                无
*/
void PrintMinToMax(PBTreeSearch btree);

/*
* function				遍历二叉查找树(从大到小,遍历顺序：右 -> 根 -> 左)
* param   PBTreeSearch  二叉查找树指针
* return                无
*/
void PrintMaxToMin(PBTreeSearch btree);
