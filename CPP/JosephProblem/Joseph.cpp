/*
* author: acme
*   date: 2017-1-26
*  blogs: http://blog.csdn.net/qq_18297675
*/
#include <iostream>
using namespace std;
//约瑟夫问题
class Joseph
{
private:
	class Node  //节点类
	{
	public: 
		Node(int d = 0, Node* n = nullptr) : data(d), next(n) {}
	private:
		int data;
		Node* next;
		friend class Joseph;
	};
public:
	Joseph() {}
public:
	void Print(int n, int k);      //打印出死亡顺序
	int GetLastOne(int n, int k);  //获取最后一个dead位置
	int GetRule(int n, int local); //获取最后一个dead的规则
private:
	Node* CreateCycleList(int n);  //创建一个循环链表
	Node* Delete(Node* node);      //删除一个节点，返回删除后当前节点
};

//创建一个循环链表
Joseph::Node* Joseph::CreateCycleList(int n)
{
	Node* head = new Node(); //头节点只是中转作用
	Node* tail = new Node(); //尾指针，最后用来连接头尾
	head->next = NULL;
	for (int i = n;i > 0;i--)
	{
		Node* node = new Node();
		node->data = i;
		if (i == n)
			tail->next = node;   //尾指针指向最后一个节点
		node->next = head->next;//利用头添加法  ,所以序号i要倒着添加
		head->next = node;
	}
	tail->next->next = head->next;//尾指针指向第一个节点 
	delete tail;
	return head->next;    //去掉头节点返回
}

//删除一个节点，返回删除后当前节点
Joseph::Node* Joseph::Delete(Node* node)
{
	Node* temp = node->next;					//暂存需要删除的节点 
	node->next = temp->next;					//删除掉该节点，就是前一个节点指向后后一个节点
	delete temp;						 //释放节点
	return node = node->next;
}

//打印出死亡顺序
void Joseph::Print(int n, int k)
{
	if (k <= 0) return;
	Node* cur = CreateCycleList(n);
	if (k == 1)  //如果自杀规则是 1 的话，那肯定是最后一个不死了
	{
		for (int i = 0;i < n;i++, cur = cur->next)
			cout << cur->data << "->";
		cout << endl;
	}
	else
	{
		while (cur != cur->next)//当只剩下最后一个元素后，cur就不等于cur->next
		{
			for (int i = 0;i < k - 2;i++)  //这个循环只能循环到要删掉的节点的前一个 
				cur = cur->next;        //（因为后面删除节点的时候，需要前一个指向后后一个节点）
			cout << cur->next->data <<"->"; //打印出后一个节点的值
			cur = Delete(cur);
		}
		cout << cur->data << endl;
	}
}

/*
* function		获取最后一个dead位置
*	 param		n为元素个数
*    param		k为规则数（数到几kill一个）
*	return		无
*/
int Joseph::GetLastOne(int n, int k)
{
	if (k < 1) return -1;
	Node* cur = CreateCycleList(n);
	if (k == 1)  //如果自杀规则是 1 的话，那肯定是最后一个不死了
		for (int i = 0;i < n;i++, cur = cur->next);
	else
	{
		while (cur != cur->next)//当只剩下最后一个元素后，cur就不等于cur->next
		{
			for (int i = 0;i < k - 2;i++)  //这个循环只能循环到要删掉的节点的前一个 
				cur = cur->next;        //（因为后面删除节点的时候，需要前一个指向后后一个节点）
			cur = Delete(cur);
		}
	}
	return cur->data;
}

/*
* function		获取最后一个dead的规则
*	 param		n为元素个数
*    param      想站的位置（序号）
*	return		规则数（数到几kill一个）
*/
int Joseph::GetRule(int n, int local)
{
	int k = 0;
	while (true)
	{
		if (GetLastOne(n, k++) == local)
			return k - 1;
	}
}

int main()
{
	Joseph joseph;
	joseph.Print(41, 3);
	cout << joseph.GetLastOne(41, 3) << endl;
	cout << joseph.GetRule(41, 31) << endl;
	return 0;
}
