/*
* author: acme
*   date: 2017-1-21
*  blogs: http://blog.csdn.net/qq_18297675
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//学生信息结构
typedef struct _student
{
	int id;
	char name[16];
}STUDENT, *LPSTUDENT;

//链表结构
typedef struct _link_list
{
	STUDENT s;           //链表中的节点的数据项，这里用一个结构体表示
	_link_list* pre;     //指向上一个节点(前驱)
	_link_list* next;    //指向下一个节点(后继)
}DOUBLE_LINK_LIST, *LPDOUBLE_LINK_LIST;

DOUBLE_LINK_LIST head = { 0 };  //创建一个全局的链表头节点(可以用一个函数创建，返回一个局部头节点)
DOUBLE_LINK_LIST tail = { 0 };  //如果头节点是全局的，那么只能有一个链表，如果想要N个，则需要创建一个局部头节点
								//还可以加一个尾指针，这样合并表的时候只需要把尾指针指向另一个表的头就可以了

int g_iCount = 0;        //记录当前链表中元素的个数

//初始化链表
void InitLinkList()
{
	head.next = NULL;
	head.pre = NULL;
	tail.next = NULL;
	tail.pre = NULL;
}

//判断表是否为空						 
bool IsEmpty()
{
	return g_iCount ? false : true;
}

//获取元素个数
int Size()
{
	return g_iCount;
}

//添加数据（头添加）
void AddFromHead(LPDOUBLE_LINK_LIST node)
{
	if (IsEmpty())				//如果链表为空，第一次添加的时候，就让尾指针指向第一个添加的节点
	{
		tail.next = node;
		node->next = head.next;
		head.next = node;
		node->pre = &head;
	}
	else
	{
		node->next = head.next;     //例如 head->node1,现在添加了个node2,则node2->node1,head->node2,先把正方向连好
		head.next = node;           //然后node1 -> node2,node2->head
		node->next->pre = node;
		node->pre = &head;
	}
    ++g_iCount;
}

//添加数据（尾添加）
void AddFromTail(LPDOUBLE_LINK_LIST node)
{
	if (IsEmpty())
		AddFromHead(node);   //如果是第一次添加，则调用AddFromHead即可
	else
	{
		tail.next->next = node;  //tail.next表示最后一个节点，这句代码的意思是，让最后一个节点指向新添进来的节点
		node->next = NULL;       //新添进来的节点，就是最后一个节点，指向NULL
		node->pre = tail.next;   //新添进来的节点的前驱指向原来的最后一个节点
		tail.next = node;        //修改tail的指向
		++g_iCount;
	}
}

//插入数据（指定位置）
void Insert(int local, LPDOUBLE_LINK_LIST node)
{
	if (local < g_iCount && local >= 0)   //当要插入的位置合理的情况下才能插入
	{
		LPDOUBLE_LINK_LIST cur = &head;
		for (int i = 0;i < local;i++)    //遍历到指定位置
			cur = cur->next;        
		node->next = cur->next;			//在该位置插入
		cur->next = node;
		node->next->pre = node;
		node->pre = cur;
		++g_iCount;
	}
	else if (local == g_iCount)
		AddFromTail(node);
}

//根据id返回元素位置
int GetLocalFromId(int id)
{
	LPDOUBLE_LINK_LIST cur = head.next;
	for (int i = 0;i < g_iCount;i++)  //遍历，一一比较
	{
		if (cur->s.id == id)
			return i;
		cur = cur->next;
	}
	return -1;   //不存在，返回-1
}

//根据name返回元素位置
int GetLocalFromName(char* name)
{
	LPDOUBLE_LINK_LIST cur = head.next;
	for (int i = 0;i < g_iCount;i++)  //遍历，一一比较
	{
		if (strcmp(cur->s.name, name) == 0)
			return i;
		cur = cur->next;
	}
	return -1;   //不存在，返回-1
}

//删除数据 （指定位置）
void DeleteFromLocal(int local)
{
	if (local < g_iCount - 1 && local >= 0)   //当要删除的位置合理的情况下才能删除
	{
		LPDOUBLE_LINK_LIST cur = &head;
		for (int i = 0;i < local;i++)    //遍历到指定位置
			cur = cur->next;
		LPDOUBLE_LINK_LIST temp;
		temp = cur->next;
		cur->next = temp->next;           //删除该位置下的元素
		cur->next->pre = cur;
		--g_iCount;
		free(temp);                       //释放掉该节点
	}
	else if(local == g_iCount - 1)  //删除的是最后一个元素的话
	{
		LPDOUBLE_LINK_LIST temp = tail.next;   //最后一个节点
		tail.next = temp->pre;	//指向最后一个节点的前一个节点
		tail.next->next = NULL;
		--g_iCount;
		free(temp);
	}
}

//删除数据 （指定id）
void DeleteFromId(int id)
{
	int local = GetLocalFromId(id);
	DeleteFromLocal(local);
}

//删除数据 （指定name）
void DeleteFromName(char* name)
{
	int local = GetLocalFromName(name);
	DeleteFromLocal(local);
}

//查找数据 （指定id，返回name）
char* SearchFromId(int id)
{
	LPDOUBLE_LINK_LIST cur = head.next;
	for (int i = 0;i < g_iCount;i++)  //遍历，一一比较
	{
		if (cur->s.id == id)          //找到该节点
			return cur->s.name;
		cur = cur->next;
	}
	return NULL;
}

//查找数据 （指定name，返回id）
int SearchFromName(char* name)
{
	LPDOUBLE_LINK_LIST cur = head.next;
	for (int i = 0;i < g_iCount;i++)  //遍历，一一比较
	{
		if (strcmp(cur->s.name, name) == 0)          //找到该节点
			return cur->s.id;
		cur = cur->next;
	}
	return -1;
}

//根据local查找指定节点，返回该节点
LPDOUBLE_LINK_LIST GetNode(int local)
{
	if (local < g_iCount / 2 && local >= 0)   //如果local在前半部分，则从前往后找
	{
		LPDOUBLE_LINK_LIST cur = head.next;
		for (int i = 0;i < local;i++)  //遍历
			cur = cur->next;
		return cur;
	}
	else if (local >= g_iCount / 2 && local < g_iCount - 1) //如果local在后半部分，则从后往前找
	{
		LPDOUBLE_LINK_LIST cur = tail.next;
		for (int i = 0;i < g_iCount - local - 1;i++)  //遍历
			cur = cur->pre;
		return cur;
	}
	else if (local == g_iCount - 1)  //如果是查找最后一个节点，直接返回tail指向的节点即可
		return tail.next;
	else
		return NULL;

}

//逆转表,时间复杂度为0(n/2)
void Reverse()
{
	STUDENT temp;
	LPDOUBLE_LINK_LIST node1 = head.next;
	LPDOUBLE_LINK_LIST node2 = tail.next;

	while (node1 != node2) 
	{
		temp = node1->s;       //交换数据项，千万别交换节点
		node1->s = node2->s;
		node2->s = temp;
		node1 = node1->next;   //往后
		node2 = node2->pre;    //往前
		if (node1 == node2->pre) //如果元素个数是偶数，则要多进行一步交换操作
		{
			temp = node1->s;       //交换数据项，千万别交换节点
			node1->s = node2->s;
			node2->s = temp;
			break;
		}
	}
}

//修改数据
void Rewrite(int local, STUDENT s)
{
	LPDOUBLE_LINK_LIST node = GetNode(local);
	if (node)
		node->s = s;
}

//清空链表
void ClearLinkList()
{
	LPDOUBLE_LINK_LIST cur = head.next;
	for (int i = 0;i < g_iCount;i++)
	{
		LPDOUBLE_LINK_LIST temp;
		temp = cur;         //保存前一个节点的地址 
		cur = cur->next;    //向前查找下一个节点
		free(temp);         //释放前一个节点的空间
	}
	head.next = NULL;      //最后让头节点指向NULL
	tail.next = NULL;
}

//遍历数据
void Print(bool bReverse)   //可以顺序打印，也可以倒序打印
{
	if (bReverse)  //倒序
	{
		LPDOUBLE_LINK_LIST cur = tail.next;
		if (!cur) return;
		do
		{
			printf("%d - %s\n", cur->s.id, cur->s.name);
		} while ((cur = cur->pre) != &head);
	}
	else
	{
		LPDOUBLE_LINK_LIST cur = &head;
		while (cur = cur->next)
			printf("%d - %s\n", cur->s.id, cur->s.name);
	}
	
}
