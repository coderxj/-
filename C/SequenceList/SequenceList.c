/*
* author: acme
*   date: 2017-1-16
   blogs: http://blog.csdn.net/qq_18297675 
*/



#include <stdio.h>
#include <string.h>
#define MAX 100    //顺序表中元素的最大个数


typedef struct _student
{
	int id;
	char name[16];
}STUDENT,*LPSTUDENT;

STUDENT g_stu[MAX];
int g_iCount = 0;   //记录当前表中元素个数

//判断表是否已满
bool IsFull()
{
	return g_iCount >= MAX ? true : false;
}

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
void AddFromHead(STUDENT s)
{
	if (IsFull())
	{
		printf("元素个数大于 %d 个，不再允许添加,请删除元素后重试.\n", MAX);
		return;
	}
	//如果数组中有元素，则往后移，否则直接添加到头部
	if (g_iCount > 0)
	{
		//往后移
		for (int i = g_iCount;i > 0;i--)
			g_stu[i] = g_stu[i - 1];
	}
	g_stu[0] = s;
	++g_iCount;
}

//添加数据（尾添加）
void AddFromTail(STUDENT s)
{
	if (IsFull())
	{
		printf("元素个数大于 %d 个，不再允许添加,请删除元素后重试.\n", MAX);
		return;
	}
	g_stu[g_iCount++] = s;
}

//插入数据（指定位置）
void Insert(int local, STUDENT s)
{
	if (IsFull())
	{
		printf("元素个数大于 %d 个，不再允许插入,请删除元素后重试.\n", MAX);
		return;
	}
	//往后移
	for (int i = g_iCount;i > local ;i--)
		g_stu[i] = g_stu[i - 1];
	g_stu[local] = s;
	++g_iCount;
}

//根据id返回元素位置
int GetLocalFromId(int id)
{
	for (int i = 0;i<g_iCount;i++)
		if (g_stu[i].id == id)
			return i;
	return -1;  //表示不存在
}

//根据name返回元素位置
int GetLocalFromName(char* name)
{
	for (int i = 0;i < g_iCount;i++)
		if (strcmp(g_stu[i].name, name) == 0)
			return i;
	return -1;  //表示不存在
}

//删除数据 （指定位置）
void DeleteFromLocal(int local)
{
	//先判断是否为空
	if (IsEmpty())
	{
		printf("表中无元素，删除操作失败.\n");
		return;
	}
	if (local >= g_iCount)
	{
		printf("指定的位置超过了当前表中的元素个数，删除操作失败.\n");
		return;
	}
	//直接往前移，覆盖掉
	for (int i = local;i < g_iCount;i++)
		g_stu[i] = g_stu[i + 1];
	--g_iCount;
}

//删除数据 （指定id）
void DeleteFromId(int id)
{
	if (IsEmpty())
	{
		printf("表中无元素，删除操作失败.\n");
		return;
	}
	int local = GetLocalFromId(id);
	if (local == -1)
	{
		printf("删除的元素不存在.\n");
		return;
	}
	DeleteFromLocal(local);
}

//删除数据 （指定name）
void DeleteFromName(char* name)
{
	if (IsEmpty())
	{
		printf("表中无元素，删除操作失败.\n");
		return;
	}
	int local = GetLocalFromName(name);
	if (local == -1)
	{
		printf("删除的元素不存在.\n");
		return;
	}
	DeleteFromLocal(local);
}

//查找数据 （指定id，返回name）
char* SearchFromId(int id)
{
	int local = GetLocalFromId(id);
	if (local == -1)
	{
		printf("%d 不存在，请重新查询.\n", id);
		return NULL;
	}
	return g_stu[local].name;
}

//查找数据 （指定name，返回id）
int SearchFromName(char* name)
{
	int local = GetLocalFromName(name);
	if (local == -1)
	{
		printf("%s 不存在，请重新查询.\n", name);
		return -1;
	}
	return g_stu[local].id;
}

//逆转表
void Reverse()
{
	STUDENT temp;
	for (int i = 0;i < g_iCount / 2;i++)   //头尾互换的思想
	{
		temp = g_stu[i];
		g_stu[i] = g_stu[g_iCount - i - 1];
		g_stu[g_iCount - i - 1] = temp;
	}
}

//修改数据
void Rewrite(int local, STUDENT s)
{
	if (local < g_iCount && local >= 0) //数组索引直接修改
		g_stu[local] = s;
}

//遍历数据
void Print()
{
	if (IsEmpty())
	{
		printf("表中无元素.\n");
		return;
	}
	for (int i = 0;i<g_iCount;i++)
		printf("%d -- %s\n", g_stu[i].id, g_stu[i].name);
}

int main()
{
	/*
	do something test
	*/	
	
	return 0;
}
