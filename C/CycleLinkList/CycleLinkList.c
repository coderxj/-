/*
* author: acme
*   date: 2017-1-19
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
	_link_list* next;    //指向下一个节点
}CYCLE_LINK_LIST, *LPCYCLE_LINK_LIST;

CYCLE_LINK_LIST head = { 0 };   //创建一个全局的链表头节点(可以用一个函数创建，返回一个局部头节点)
                         //如果头节点是全局的，那么只能有一个链表，如果想要N个，则需要创建一个局部头节点
						 //还可以加一个尾指针，这样合并表的时候只需要把尾指针指向另一个表的头就可以了

int g_iCount = 0;        //记录当前链表中元素的个数

//初始化链表
void InitLinkList()
{
	head.next = &head;	 //其实也就是把头指向头 head->head(刚开始的时候)
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
void AddFromHead(LPCYCLE_LINK_LIST l)
{
	l->next = head.next;     //例如 head->l1,现在添加了个l,则l->l1,head->l,就是改变指向
	head.next = l;
	++g_iCount;
}

//添加数据（尾添加）
void AddFromTail(LPCYCLE_LINK_LIST l)
{
	LPCYCLE_LINK_LIST cur = &head;
	while (cur->next != &head)//循环链表，遍历到末尾不再是指针域为空了，而是等于头节点
		cur = cur->next;      //遍历到链表末尾
	cur->next = l;            //把l挂在链表的末尾
	l->next = &head;           //最后让l指向头节点
	++g_iCount;
}

//插入数据（指定位置）
void Insert(int local, LPCYCLE_LINK_LIST l)
{
	if (local < g_iCount && local >= 0)   //当要插入的位置合理的情况下才能插入
	{
		LPCYCLE_LINK_LIST cur = &head;
		for (int i = 0;i < local;i++)    //遍历到指定位置
			cur = cur->next;
		l->next = cur->next;              //在该位置插入
		cur->next = l;
		++g_iCount;
	}
	else if (local == g_iCount)
		AddFromTail(l);
}

//根据id返回元素位置
int GetLocalFromId(int id)
{
	LPCYCLE_LINK_LIST cur = head.next;
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
	LPCYCLE_LINK_LIST cur = head.next;
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
	if (local < g_iCount && local >= 0)   //当要删除的位置合理的情况下才能删除
	{
		LPCYCLE_LINK_LIST cur = &head;
		for (int i = 0;i < local;i++)    //遍历到指定位置
			cur = cur->next;
		LPCYCLE_LINK_LIST temp;
		temp = cur->next;
		cur->next = temp->next;           //删除该位置下的元素
		--g_iCount;
		free(temp);                       //释放掉该节点
	}
}

//删除数据 （指定id）
void DeleteFromId(int id)
{
	LPCYCLE_LINK_LIST cur = head.next;
	LPCYCLE_LINK_LIST pre = &head;
	for (int i = 0;i < g_iCount;i++)  //遍历，一一比较
	{
		if (cur->s.id == id)          //找到该节点
		{
			LPCYCLE_LINK_LIST temp;
			temp = cur;
			pre->next = temp->next;   //修改指向，就是删除了   
			free(temp);               //最后要释放节点
			--g_iCount;
			break;                    //记得退出，否则访问空指针会出错
		}
		cur = cur->next;
		pre = pre->next;
	}
}

//删除数据 （指定name）
void DeleteFromName(char* name)
{
	LPCYCLE_LINK_LIST cur = head.next;
	LPCYCLE_LINK_LIST pre = &head;
	for (int i = 0;i < g_iCount;i++)  //遍历，一一比较
	{
		if (strcmp(cur->s.name, name) == 0)          //找到该节点
		{
			LPCYCLE_LINK_LIST temp;
			temp = cur;
			pre->next = temp->next;   //修改指向，就是删除了   
			free(temp);               //最后要释放节点
			--g_iCount;
			break;
		}
		cur = cur->next;
		pre = pre->next;
	}
}

//查找数据 （指定id，返回name）
char* SearchFromId(int id)
{
	LPCYCLE_LINK_LIST cur = head.next;
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
	LPCYCLE_LINK_LIST cur = head.next;
	for (int i = 0;i < g_iCount;i++)  //遍历，一一比较
	{
		if (strcmp(cur->s.name, name) == 0)          //找到该节点
			return cur->s.id;
		cur = cur->next;
	}
	return -1;
}

//根据local查找指定节点，返回该节点
LPCYCLE_LINK_LIST GetNode(int local)
{
	if (local < g_iCount && local >= 0)
	{
		LPCYCLE_LINK_LIST cur = head.next;
		for (int i = 0;i < local;i++)  //遍历
			cur = cur->next;
		return cur;
	}
	else
		return NULL;
}

//逆转表(方法1，牺牲时间换取空间，速度很慢，时间复杂度为0(n^2))
void Reverse1()
{
	STUDENT temp;
	for (int i = 0;i < g_iCount / 2;i++)
	{
		LPCYCLE_LINK_LIST node1 = GetNode(i);                //获取节点
		LPCYCLE_LINK_LIST node2 = GetNode(g_iCount - i - 1);
		temp = node1->s;                              //交换数据项，千万别交换节点
		node1->s = node2->s;
		node2->s = temp;
	}
}

//逆转表(方法2，牺牲空间换取时间，速度很快，时间复杂度为0(n))
void Reverse2()
{
	CYCLE_LINK_LIST tHead = { 0 };     //临时头节点
	tHead.next = &tHead;
	LPCYCLE_LINK_LIST cur = head.next;
	for (int i = 0;i < g_iCount;i++)
	{
		LPCYCLE_LINK_LIST l = (LPCYCLE_LINK_LIST)malloc(sizeof(_link_list));
		memcpy(l, cur, sizeof(_link_list));   //这里一定要复制，而不是赋值=，如果是=，则两指针指向的是同一个节点
		l->next = tHead.next;        //这里采用头添加，结束后，就会自动逆转过来了         
		tHead.next = l;
		cur = cur->next;
	}
	cur = head.next;
	LPCYCLE_LINK_LIST temp = tHead.next;
	while ((cur->next) != &tHead)
	{
		memcpy(cur, temp, sizeof(_link_list));   //因为头添加已经是逆转了，所以直接复制到原来的链表中即可
		temp = temp->next;
		cur = cur->next;
	}    
	cur->next = &head;//最后让尾节点指向头节点,若没有这一句，则cur->next指向的是tHead
}

//修改数据
void Rewrite(int local, STUDENT s)
{
	if (local < g_iCount && local >= 0)   //当要删除的位置合理的情况下才能删除
	{
		LPCYCLE_LINK_LIST cur = head.next;
		for (int i = 0;i < local;i++)    //遍历到指定位置
			cur = cur->next;
		cur->s = s;                       //修改
	}
}

//清空链表
void ClearLinkList()
{
	LPCYCLE_LINK_LIST cur = head.next;
	for (int i = 0;i < g_iCount;i++)
	{
		LPCYCLE_LINK_LIST temp;
		temp = cur;         //保存前一个节点的地址 
		cur = cur->next;    //向前查找下一个节点
		free(temp);         //释放前一个节点的空间
	}
	head.next = &head;      //最后让头节点指向头节点
}

//遍历数据
void Print()
{
	LPCYCLE_LINK_LIST cur = &head;
	while ((cur = cur->next) != &head)
		printf("%d - %s\n", cur->s.id, cur->s.name);
}
