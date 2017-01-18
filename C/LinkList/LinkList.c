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
}LINKLIST,*LPLINKLIST;

LINKLIST head = { 0 };   //创建一个全局的链表头节点(可以用一个函数创建，返回一个局部头节点)
int g_iCount = 0;        //记录当前链表中元素的个数

					
//判断表是否为空
bool IsEmpty()
{
	return g_iCount ? false : true;
}

//获取元素个数
int GetElementCount()
{
	return g_iCount;
}

//添加数据（头添加）
void AddFromHead(LPLINKLIST l)
{
	l->next = head.next;    //例如 head->l1,现在添加了个l,则l->l1,head->l,就是改变指向
	head.next = l;
	++g_iCount;
}

//添加数据（尾添加）
void AddFromTail(LPLINKLIST l)
{
	LPLINKLIST cur = &head;   
	while (cur->next)         //千万不能写成while(cur=cur->next);，因为当遍历完之后再cur->next(空指针)会出错
		cur = cur->next;      //遍历到链表末尾
	cur->next = l;            //把l挂在链表的末尾
	l->next = NULL;           //最后让l指向NULL
	++g_iCount;
}

//插入数据（指定位置）
void Insert(int local, LPLINKLIST l)
{
	if (local < g_iCount && local >= 0)   //当要插入的位置合理的情况下才能插入
	{
		LPLINKLIST cur = &head;
		for (int i = 0;i < local;i++)    //遍历到指定位置
			cur = cur->next;
		l->next = cur->next;              //在该位置插入
		cur->next = l;
		++g_iCount;
	}
}

//根据id返回元素位置
int GetLocalFromId(int id)
{
	LPLINKLIST cur = head.next;
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
	LPLINKLIST cur = head.next;
	for (int i = 0;i < g_iCount;i++)  //遍历，一一比较
	{
		if (strcmp(cur->s.name,name) == 0)
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
		LPLINKLIST cur = &head;
		for (int i = 0;i < local;i++)    //遍历到指定位置
			cur = cur->next;
		LPLINKLIST temp;
		temp = cur->next;
		cur->next = temp->next;           //删除该位置下的元素
		--g_iCount;
		free(temp);                       //释放掉该节点
	}
}

//删除数据 （指定id）
void DeleteFromId(int id)
{
	LPLINKLIST cur = head.next;
	LPLINKLIST pre = &head;
	for (int i = 0;i < g_iCount;i++)  //遍历，一一比较
	{
		if (cur->s.id == id)          //找到该节点
		{
			LPLINKLIST temp;
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
	LPLINKLIST cur = head.next;
	LPLINKLIST pre = &head;
	for (int i = 0;i < g_iCount;i++)  //遍历，一一比较
	{
		if (strcmp(cur->s.name, name) == 0)          //找到该节点
		{
			LPLINKLIST temp;
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
	LPLINKLIST cur = head.next;
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
	LPLINKLIST cur = head.next;
	for (int i = 0;i < g_iCount;i++)  //遍历，一一比较
	{
		if (strcmp(cur->s.name,name) == 0)          //找到该节点
			return cur->s.id;
		cur = cur->next;
	}
	return -1;
}

//根据local查找指定节点，返回该节点
LPLINKLIST GetNode(int local)
{
	if (local < g_iCount && local >= 0)
	{
		LPLINKLIST cur = head.next;
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
	for (int i =0;i<g_iCount/2;i++)
	{
		LPLINKLIST node1 = GetNode(i);                //获取节点
		LPLINKLIST node2 = GetNode(g_iCount - i - 1);
		temp = node1->s;                              //交换数据项，千万别交换节点
		node1->s = node2->s;
		node2->s = temp;
	}
}

//逆转表(方法2，牺牲空间换取时间，速度很快，时间复杂度为0(n))
void Reverse2()
{
	LINKLIST tHead = { 0 };     //临时头节点
	LPLINKLIST cur = head.next;
	for (int i = 0;i < g_iCount;i++)
	{
		LPLINKLIST l = (LPLINKLIST)malloc(sizeof(_link_list));
		memcpy(l, cur, sizeof(_link_list));   //这里一定要复制，而不是赋值=，如果是=，则两指针指向的是同一个节点
		l->next = tHead.next;        //这里采用头添加，结束后，就会自动逆转过来了         
		tHead.next = l;
		cur = cur->next;
	}
	cur = head.next;
	LPLINKLIST temp = tHead.next;
	for (int i = 0;i < g_iCount;i++) 
	{
		memcpy(cur, temp, sizeof(_link_list));   //因为头添加已经是逆转了，所以直接复制到原来的链表中即可
		temp = temp->next;
		cur = cur->next;
	}
}

//修改数据
void Rewrite(int local, STUDENT s)
{
	if (local < g_iCount && local >= 0)   //当要删除的位置合理的情况下才能删除
	{
		LPLINKLIST cur = head.next;
		for (int i = 0;i < local;i++)    //遍历到指定位置
			cur = cur->next;
		cur->s = s;                       //修改
	}
}

//清空链表
void ClearLinkList()
{
	LPLINKLIST cur = head.next;
	for (int i = 0;i<g_iCount;i++)
	{
		LPLINKLIST temp;
		temp = cur;         //保存前一个节点的地址 
		cur = cur->next;    //向前查找下一个节点
		free(temp);         //释放前一个节点的空间
	} 
	head.next = NULL;       //最后让头节点指向NULL
}

//遍历数据
void Print()
{
	LPLINKLIST cur = &head;
	while (cur = cur->next)
		printf("%d - %s\n", cur->s.id, cur->s.name);
}
