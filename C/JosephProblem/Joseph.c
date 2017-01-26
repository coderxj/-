
/*
* author: acme
*   date: 2017-1-26
*  blogs: http://blog.csdn.net/qq_18297675
*/
#include <stdio.h>
#include <stdlib.h>

//节点结构
typedef struct _node
{
	int data;
	_node* next;
}NODE, *LPNODE;

/*
* function		创建一个循环链表
*	 param		n为元素个数
*	return		指向第一个节点的指针
*/
LPNODE CreateCycleList(int n)
{
	LPNODE head = (LPNODE)malloc(sizeof(_node)); //头节点只是中转作用
	LPNODE tail = (LPNODE)malloc(sizeof(_node)); //尾指针，最后用来连接头尾
	head->next = NULL;
	for (int i = n;i > 0;i--)
	{
		LPNODE node = (LPNODE)malloc(sizeof(_node));
		node->data = i;
		if (i == n)
			tail->next = node;   //尾指针指向最后一个节点
		node->next = head->next;//利用头添加法  ,所以序号i要倒着添加
		head->next = node;
	}
	tail->next->next = head->next;//尾指针指向第一个节点 
	free(tail);
	return head->next;    //去掉头节点返回
}

/*
* function		打印出死亡顺序
*	 param		n为元素个数
*    param		k为规则数（数到几kill一个）
*	return		无
*/
void Print(int n, int k)
{
	if (k <= 0) return;
	LPNODE cur = CreateCycleList(n);
	if (k == 1)  //如果自杀规则是 1 的话，那肯定是最后一个不死了
	{
		for (int i = 0;i < n;i++, cur = cur->next)
			printf("%d->", cur->data);
		printf("\n");
		return;
	}
	while (cur != cur->next)//当只剩下最后一个元素后，cur就不等于cur->next
	{
		for (int i = 0;i < k - 2;i++)  //这个循环只能循环到要删掉的节点的前一个 
			cur = cur->next;        //（因为后面删除节点的时候，需要前一个指向后后一个节点）
		printf("%d->", cur->next->data); //打印出后一个节点的值
		LPNODE temp = cur->next;              //暂存需要删除的节点 
		cur->next = temp->next;         //删除掉该节点，就是前一个节点指向后后一个节点
		free(temp);						  //释放节点
		cur = cur->next;
	}
	printf("%d\n", cur->data);
}

/*
* function		获取最后一个dead位置
*	 param		n为元素个数
*    param		k为规则数（数到几kill一个）
*	return		无
*/
int GetLastOne(int n, int k)
{
	if (k < 1) return -1;
	LPNODE cur = CreateCycleList(n);
	if (k == 1)  //如果自杀规则是 1 的话，那肯定是最后一个不死了
		for (int i = 0;i < n;i++, cur = cur->next);
	else
	{
		while (cur != cur->next)//当只剩下最后一个元素后，cur就不等于cur->next
		{
			for (int i = 0;i < k - 2;i++)  //这个循环只能循环到要删掉的节点的前一个 
				cur = cur->next;        //（因为后面删除节点的时候，需要前一个指向后后一个节点）
			LPNODE temp = cur->next;       //暂存需要删除的节点 
			cur->next = temp->next;         //删除掉该节点，就是前一个节点指向后后一个节点
			free(temp);						  //释放节点
			cur = cur->next;
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
int GetRule(int n, int local)
{
	int k = 0;
	while (true)
	{
		if (GetLastOne(n, k++) == local)
			return k - 1;
	}
}

int main(void)
{

	int n = 41;
	Print(n, 3);
	printf("\n%d\n", GetLastOne(n, 3));
	printf("\n%d\n", GetRule(n, 31));
	return 0;
}
