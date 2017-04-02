/*
* author: acme
*   date: 2017-4-2
*  blogs: http://blog.csdn.net/qq_18297675
*/
#pragma once
#include <iostream>
using namespace std;
#define NO_FIND ~(1<<31)  

class BTreeSearch
{
public:
	class Node  //节点类
	{
	public: Node(int value) :value(value), count(1), left(nullptr), right(nullptr) {}
	private:
		int value;		//节点值
		int count;		//节点值相同的个数
		Node* left;		//左孩子
		Node* right;	//右孩子
		friend class BTreeSearch;
	};
public:
	BTreeSearch();
	~BTreeSearch();

public:
	int Search(int value);								//查找值
	void Add(int value);								//添加值
	bool Delete(int value);								//删除值
	int Size();                                         //获取二叉树节点个数(包括重复的)
	int GetMinValue();									//获取最小值
	int GetMaxValue();									//获取最大值
	void Print(bool bMinToMax);							//打印二叉树				
private:
	Node* SearchNode(Node* btree, int value);			//查找节点
	Node* SearchParentNode(Node* btree,int value);		//查找父节点
	Node* CreateNode(int value);						//创建节点
	void Add(Node* btree, Node* node);					//添加节点辅助函数
	void Delete(Node** cur, Node** par, bool bLeft);	//删除节点辅助函数
	Node* FindMinNode(Node* btree);						//查找最小节点
	void Print(Node* btree,bool bMinToMax);				//打印二叉树辅助函数
private:
	Node* m_root;										//根节点
	int m_nodeCount;                                    //节点个数
};

