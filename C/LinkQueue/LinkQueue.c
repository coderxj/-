
/*
* author: acme
*   date: 2017-1-24
*  blogs: http://blog.csdn.net/qq_18297675
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERROR ~(1<<31)

//节点结构
typedef struct _node
{
	int data;             //这个其实和单链表的定义是一样的，只不过限制了头尾操作 
	_node* next;
}NODE,*LPNODE;

//队列结构
typedef struct _link_queue
{
	LPNODE front;   //头节点，指向队首
	LPNODE rear;    //尾节点，指向队尾
	int count;      //队列大小
}LINKQUEUE,*LPLINKQUEUE;

//创建一个空队列
LPLINKQUEUE CreateQueue()
{
	LPLINKQUEUE queue = (LPLINKQUEUE)malloc(sizeof(_link_queue)); //创建一个队列
	LPNODE front = (LPNODE)malloc(sizeof(_node));
	LPNODE rear = (LPNODE)malloc(sizeof(_node));
	front->data = -1;        //要记得，queue只是把front、rear节点包装起来，真正存储数据的还是NODE结构
	front->next = NULL;      //一定要分别创建两个节点，否则front和rear的地址一样，那就没用了
	rear->data = -1;
	rear->next = NULL;
	queue->front = front;   //初始化队列中的front和rear节点
	queue->rear = rear;
	queue->count = 0;
	return queue;
}

//队列是否为空	
bool IsEmpty(LPLINKQUEUE queue)
{
	return queue->count == 0 ? true : false;
}

//入队    
void EnQueue(LPLINKQUEUE queue,int e)
{
	LPNODE node = (LPNODE)malloc(sizeof(_node));  //创建新的节点
	node->data = e;
	if (queue->count == 0)		//如果是第一次添加，则让front和rear同时指向它
		queue->front->next = node;   
	else                            
		queue->rear->next->next = node;  //原来最后一个节点指向新的最后一个节点
	queue->rear->next = node;			 //最后一个节点指向NULL
	node->next = NULL;					 //rear指向最后一个节点
	++queue->count;
}

//出队
void DeQueue(LPLINKQUEUE queue)
{
	if (IsEmpty(queue))
		printf("队列为空，出队操作失败.\n");
	else
	{
		LPNODE temp = queue->front->next;   //将要出队的节点保存起来
		queue->front->next = temp->next;    //front指向后一个节点
		--queue->count;
		free(temp);                         //释放节点
	}
}

 //获取队列长度
int GetSize(LPLINKQUEUE queue)
{
	return queue->count;
}

//获取队头
int GetQueueHead(LPLINKQUEUE queue)
{
	return IsEmpty(queue) ? ERROR : queue->front->next->data;
}

//遍历队列
void Print(LPLINKQUEUE queue)
{
	LPNODE cur = queue->front->next;
	for (int i = 0; i < queue->count; i++,cur = cur->next)
		printf("%d\n", cur->data);
}

//清空队列
void ClearQueue(LPLINKQUEUE queue)
{
	int count = queue->count;
	for (int i = 0; i < count; i++)
		DeQueue(queue);             //挨个出队即可 
	queue->front->next = NULL;      //最后调整头尾指向
	queue->rear->next = NULL;
}
