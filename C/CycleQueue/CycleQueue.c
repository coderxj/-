/*
* author: acme
*   date: 2017-1-25
*  blogs: http://blog.csdn.net/qq_18297675
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ERROR ~(1<<31)  //错误数

//队列结构
typedef struct _cycle_queue
{
	int* data;			//队列数据区域
	int front;          //队头
	int rear;           //队尾
	int count;          //加这个字段主要是更清晰的表示元素的个数，不用老是纠结rear-front得什么
	int QUEUE_SIZE;     //队列的最大长度
}CYCLEQUEUE, *LPCYCLEQUEUE;

//初始化队列,并且指定队列大小
void InitQueue(LPCYCLEQUEUE queue, int queueSize)
{
	queue->data = (int*)malloc(sizeof(int)*queueSize);  //分配数据区域大小
	queue->front = 0;  //初始队头指向0，表示队中无元素
	queue->rear = 0;   //初始队尾指向0，表示队中无元素
	queue->count = 0;
	queue->QUEUE_SIZE = queueSize;
}

//队列是否为空
bool IsEmpty(LPCYCLEQUEUE queue)
{
	return queue->count == 0 ? true : false;
}

//队列是否满
bool IsFull(LPCYCLEQUEUE queue)
{
	return queue->count == queue->QUEUE_SIZE ? true : false;
}

//入队
void EnQueue(LPCYCLEQUEUE queue, int e)
{
	if (IsFull(queue))
		printf("队列已满，入队操作失败.\n");
	else   //如果队列没有满，则循环到数组的第一个a[0]继续存放,把空间利用完
	{
		queue->data[queue->rear % queue->QUEUE_SIZE] = e;
		queue->rear = ++queue->rear % queue->QUEUE_SIZE;
		++queue->count;
	}
		
}

//出队
void DeQueue(LPCYCLEQUEUE queue)
{
	if (IsEmpty(queue))
		printf("队列为空，出队操作失败.\n");
	else
	{     //队头指针向后移,移到最后，如果没有满，则循环到a[0]继续		
		queue->front = ++queue->front%queue->QUEUE_SIZE;  
		--queue->count;
	}
}

//获取队列长度
int GetSize(LPCYCLEQUEUE queue)
{
	return queue->count;
}

//获取队头
int GetQueueHead(LPCYCLEQUEUE queue)
{
	return IsEmpty(queue) ? ERROR : queue->data[queue->front];
}

//遍历队列
void Print(LPCYCLEQUEUE queue)
{
	if (IsEmpty(queue))
		printf("队列为空，遍历操作失败.\n");
	else
	{
		if (queue->front < queue->rear)  //这是正常的，没有循环的时候
		{
			for (int i = queue->front;i < queue->rear;i++)
				printf("%d\n", queue->data[i]);
		}	
		else
		{
			for (int i = queue->front;i < queue->QUEUE_SIZE;i++)  //分段遍历
				printf("%d\n", queue->data[i]);
			for (int i = 0;i < queue->rear;i++)
				printf("%d\n", queue->data[i]);
		}

	}
}

//清空队列
void ClearQueue(LPCYCLEQUEUE queue)
{
	if (IsEmpty(queue))
		printf("队列为空，清空操作失败.\n");
	else
	{
		queue->front = 0;//不用清空数据，入队的时候直接覆盖就好
		queue->rear = 0;
		queue->count = 0;
	}
}
