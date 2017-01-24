
/*
* author: acme
*   date: 2017-1-24
*  blogs: http://blog.csdn.net/qq_18297675
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ERROR ~(1<<31)  //错误数

//栈结构
typedef struct _sequence_queue
{
	int* data;			//队列数据区域
	int front;          //队头
	int rear;           //队尾
	int QUEUE_SIZE;     //队列的最大长度
}SEQQUEUE, *LPSEQQUEUE;

//初始化队列,并且指定队列大小
void InitQueue(LPSEQQUEUE queue,int queueSize)
{
	queue->data = (int*)malloc(sizeof(int)*queueSize);  //分配数据区域大小
	queue->front = 0;  //初始队头指向0，表示队中无元素
	queue->rear = 0;   //初始队尾指向0，表示队中无元素
	queue->QUEUE_SIZE = queueSize;
}

//队列是否为空
bool IsEmpty(LPSEQQUEUE queue)
{
	return queue->rear - queue->front == 0 ? true : false;
}

//队列是否满
bool IsFull(LPSEQQUEUE queue)
{
	return queue->rear == queue->QUEUE_SIZE ? true : false;
}

//入队
void EnQueue(LPSEQQUEUE queue, int e)
{
	if (IsFull(queue))
		printf("队列已满，入队操作失败.\n");
	else
		queue->data[queue->rear++] = e;	
}

//出队
void DeQueue(LPSEQQUEUE queue)
{
	if (IsEmpty(queue))
		printf("队列为空，出队操作失败.\n");
	else
		++queue->front;  //队头指针向后移		
}

//获取队列长度
int GetSize(LPSEQQUEUE queue)
{
	return queue->rear - queue->front;
}

//获取队头
int GetQueueHead(LPSEQQUEUE queue)
{
	return IsEmpty(queue) ? ERROR : queue->data[queue->front];
}

//遍历队列
void Print(LPSEQQUEUE queue)
{
	if (IsEmpty(queue))
		printf("队列为空，遍历操作失败.\n");
	else
	{
		for (int i = queue->front;i<queue->rear;i++)
			printf("%d\n", queue->data[i]);
	}
}

//清空队列
void ClearQueue(LPSEQQUEUE queue)
{
	if (IsEmpty(queue))
		printf("队列为空，清空操作失败.\n");
	else
	{
		queue->front = 0;//不用清空数据，入队的时候直接覆盖就好
		queue->rear = 0;
	}
}
