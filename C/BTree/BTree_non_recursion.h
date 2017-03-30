#pragma once
/*
* author: acme
*   date: 2017-3-30
*  blogs: http://blog.csdn.net/qq_18297675
*/

enum NodeType
{
	LEFT_NODE,
	RIGHT_NODE
};

//二叉树结构
typedef struct _binary_tree
{
	char data;				//值域
	bool bLCExits;			//左孩子是否存在
	bool bRCExits;			//左孩子是否存在
	_binary_tree* left;		//左节点
	_binary_tree* right;	//右节点
}BTree, *PBTree;

//栈节点
typedef struct _node
{
	PBTree node;
	_node* next;
}Node, *PNode;

//栈结构 (先进后出)
typedef struct _stack
{
	PNode top;		//栈顶指针
	int count;		//栈中元素
}Stack, *PStack;

//队列结构 （先进先出）
typedef struct _queue 
{
	PNode front;	//队头指针
	PNode rear;		//队尾指针
	int count;		//队中元素
}Queue, *PQueue;

/*****************************栈实现*****************************/

/*
* function				创建栈
* return                返回栈结构
*/
Stack CreateStack()
{
	PStack stack = (PStack)malloc(sizeof(_stack));
	stack->top = (PNode)malloc(sizeof(_node));
	stack->count = 0;
	return *stack;
}

/*
* function				栈是否为空
* param		PStack		栈结构指针
* return                空返回true，否则返回false
*/
bool StackIsEmpty(PStack stack)
{
	return stack->count == 0;
}

/*
* function				入栈
* param		PStack		栈结构指针
* param     PBTree      二叉树节点
* return                无
*/
void Push(PStack stack,PBTree node)
{
	PNode newNode = (PNode)malloc(sizeof(_node));  //相当于单链表的头添加
	newNode->node = node;
	newNode->next = stack->top->next;
	stack->top->next = newNode;
	stack->count++;
}

/*
* function				出栈
* param		PStack		栈结构指针
* return                返回栈顶元素
*/
void Pop(PStack stack)
{ 
	if (stack->count == 0)
		return;
	PNode temp = stack->top->next;   //和单链表的头删除一样
	stack->top->next = temp->next;
	free(temp);
	stack->count--;
}

/*
* function				获取栈顶元素
* param		PStack		栈结构指针
* return                返回栈顶元素
*/
PBTree Top(PStack stack)
{
	return stack->count == 0 ? NULL : stack->top->next->node;
}

/*
* function				销毁栈
* param		PStack		栈结构指针
* return                无
*/
void DestroyStack(PStack stack)
{
	while (stack->count > 0)
	{
		PNode temp = stack->top->next;   //和单链表的头删除一样
		stack->top->next = temp->next;
		free(temp);
		stack->count--;
	}
	stack = NULL;
}

/*****************************栈实现*****************************/

/*****************************队列实现*****************************/

/*
* function				创建队列
* return                返回队列结构
*/
Queue CreateQueue()
{
	PQueue queue = (PQueue)malloc(sizeof(_queue));
	queue->front = (PNode)malloc(sizeof(_node));
	queue->rear = (PNode)malloc(sizeof(_node));
	queue->count = 0;
	queue->front->next = NULL;
	queue->rear->next = NULL;
	return *queue;
}

/*
* function				队列是否为空
* param		PStack		栈结构指针
* return                空返回true，否则返回false
*/
bool QueueIsEmpty(PQueue queue)
{
	return queue->count == 0;
}

/*
* function				入队
* param		PQueue		队列结构指针
* param     PBTree      二叉树节点
* return                无
*/
void QPush(PQueue queue, PBTree node)
{
	PNode newNode = (PNode)malloc(sizeof(_node));  //相当于单链表的尾添加
	newNode->node = node;
	if (queue->count == 0)  //第一次添加的时候，修改一下头指针
		queue->front->next = newNode;
	else
		queue->rear->next->next = newNode;  //直接让最后一个元素指向新的元素
	queue->rear->next = newNode;//修改尾指针
	newNode->next = NULL;
	queue->count++;
}

/*
* function				出队
* param		PQueue		队列结构指针
* return                
*/
void QPop(PQueue queue)
{
	if (queue->count == 0)
		return;
	PNode temp = queue->front->next;   //和单链表的头删除一样
	queue->front->next = temp->next;
	free(temp);
	queue->count--;
}

/*
* function				获取队头元素
* param		PQueue		队列结构指针
* return
*/
PBTree Front(PQueue queue)
{
	return queue->count == 0? NULL : queue->front->next->node;
}

/*****************************队列实现*****************************/

/*****************************二叉树非递归实现*****************************/

/*
* function				计算字符串长度
* param		char* s     字符串s
* return                返回长度
*/
int _csize(char* s)
{
	if (!s)
		return 0;
	int len = 0;
	while (*s++) ++len;
	return len;
}

/*
* function				计算字符串长度
* param		NodeType    创建的节点类型
* return                返回长度
*/
PBTree CreateNode(char ch)
{
	PBTree btree = (PBTree)malloc(sizeof(_binary_tree));
	btree->data = ch;
	btree->bLCExits = false;
	btree->bRCExits = false;
	btree->left = NULL;
	btree->right = NULL;
	return btree;
}

/*
* function				创建二叉树(前序创建)
* param		char* s     根据给定字符串创建	
* return                返回二叉树的根节点
*/
PBTree CreateBTree(char* s)
{
	if (!s || s[0] == '\0')  //如果s为空 则树也为空
		return NULL;
	Stack stack = CreateStack();  //创建一个栈
	int i = 0;
	// 1.先创建根节点
	PBTree root = CreateNode(s[i++]);
	PBTree btree = root;		//用一个临时的指针代替root，因为最后要返回root指针，所以它不能改变
	Push(&stack,root);			//将根节点压入栈中
	int len = _csize(s);
	while (i < len)  
	{
		// 2.如果当前读到的字符不为空，并且当前节点的左孩子不存在，则创建它
		if (s[i] != ' ' && btree->bLCExits == false)
		{
			btree->left = CreateNode(s[i]);	//创建左孩子
			btree->bLCExits = true;			//左孩子存在
			btree = btree->left;
			Push(&stack, btree);  //入栈
			++i;
		}
		// 3.如果当前读到的字符不为空，并且当前节点的右孩子不存在，则创建它
		else if (s[i] != ' ' && btree->bRCExits == false)
		{
			btree->right = CreateNode(s[i]);//创建右孩子
			btree->bRCExits = true;			//右孩子存在
			btree = btree->right;
			Push(&stack, btree);  //入栈
			++i;
		}
		// 4.如果当前读到的字符为空，并且当前节点的左孩子不存在，则将当前节点的左孩子置为存在（空也算孩子）
		else if (s[i] == ' ' && btree->bLCExits == false) //空节点
			btree->bLCExits = true, ++i;  //左孩子存在
		// 5.如果当前读到的字符为空，并且当前节点的右孩子不存在，则将当前节点的右孩子置为存在（空也算孩子）
		else if (s[i] == ' ' && btree->bRCExits == false)
			btree->bRCExits = true, ++i;  //右孩子存在		

		// 6.回溯回去,当该节点的度为2的时候(就是左右孩子都存在的情况)
		if (btree->bLCExits && btree->bRCExits)
			Pop(&stack),btree = Top(&stack);
	}
	DestroyStack(&stack);  //最后销毁栈
	return root;
}

/*
* function				判断二叉树是否为空遍历
* param		PBTree      root
* return                无
*/
bool BTreeIsEmpty(PBTree t)
{
	return t == NULL;
}

/*
* function				计算二叉树深度
* param		PBTree      root
* return                无
*/
int BTreeDepth(PBTree root)
{
	if (!root) return 0;
	Queue queue = CreateQueue();		//创建一个队列
	PBTree cur = root;					//当前节点
	int iDepth = 0;
	QPush(&queue, root);					//先将根节点加入队列中
	while (!QueueIsEmpty(&queue))			//当队列中没有元素时，遍历完成 
	{
		++iDepth;							//外层循环控制层数
		int curLevelNodes = queue.count;	//当前层数的节点数
		int temp = 0;						//临时记录已经遍历的节点数

		while (temp++ < curLevelNodes)		//当遍历完当前层数后，退出内层循环，继续遍历下一层
		{
			cur = Front(&queue);			//获取当前队头元素
			QPop(&queue);                   //遍历过后就出队
			if (cur->left)					//如果左孩子不为空，则入队等待遍历
				QPush(&queue, cur->left);

			if (cur->right)				    //如果右孩子不为空，则入队等待遍历
				QPush(&queue, cur->right);
		}
	}
	return iDepth;
}

/*
* function				计算二叉树双分支节点数
* param		PBTree      root
* return                无
*/
int GetN2(PBTree root)
{
	Stack stack = CreateStack();   //创建一个栈
	PBTree btree = root;           //创建临时指针指向root
	int count = 0;
	//利用前序遍历来访问所有的节点
	while (btree || !StackIsEmpty(&stack))
	{	
		while (btree)
		{
			Push(&stack, btree);
			btree = btree->left;
		}
		if (!StackIsEmpty(&stack))
		{
			btree = Top(&stack);
			if (btree)                            //再这里能保证所有的节点都能被遍历到
				if (btree->left && btree->right)  //当该节点有两个分支的时候+1
					++count;
			Pop(&stack);
			btree = btree->right;
		}
	}
	return count;
}

/*
* function				计算二叉树单分支节点数
* param		PBTree      root
* return                无
*/
int GetN1(PBTree root)
{
	Stack stack = CreateStack();   //创建一个栈
	PBTree btree = root;           //创建临时指针指向root
	int count = 0;
	//利用前序遍历来访问所有的节点
	while (btree || !StackIsEmpty(&stack))
	{
		while (btree)
		{
			Push(&stack, btree);
			btree = btree->left;
		}
		if (!StackIsEmpty(&stack))
		{
			btree = Top(&stack);
			if (btree)                            //再这里能保证所有的节点都能被遍历到
				if ((btree->left && !btree->right) || (!btree->left && btree->right))  //当该节点仅且只有一个分支的时候+1
					++count;
			Pop(&stack);
			btree = btree->right;
		}
	}
	return count;
}

/*
* function				计算二叉树终端节点数
* param		PBTree      root
* return                无
*/
int GetN0(PBTree root)
{
	return GetN2(root) + 1; //计算公式n0 = n2 + 1;
}

/*
* function				前序遍历
* param		PBTree      root
* return                无
*/
void PreOrder(PBTree root)
{
	Stack stack = CreateStack();   //创建一个栈
	PBTree btree = root;           //创建临时指针指向root
	// 1. 若当前节点不为空，或者栈中元素不为空（相当于还没有遍历完所有节点）
	while (btree || !StackIsEmpty(&stack))
	{
		// 2. 先遍历左子树，一直到左子树为空为止。
		while (btree)
		{
			printf("%c", btree->data);
			Push(&stack,btree);
			btree = btree->left;
		}

		// 3.若栈中还有元素，则将当前btree赋值为它的右子树，然后再重复 1~2步骤
		if (!StackIsEmpty(&stack))
		{
			btree = Top(&stack);
			Pop(&stack);         
			btree = btree->right;
		}
	}
	printf("\n");
}

/*
* function				中序遍历
* param		PBTree      root
* return                无
*/
void InOrder(PBTree root)
{
	Stack stack = CreateStack();   //创建一个栈
	PBTree btree = root;           //创建临时指针指向root
	// 1. 若当前节点不为空，或者栈中元素不为空（相当于还没有遍历完所有节点）
	while (btree || !StackIsEmpty(&stack))
	{
		// 2. 先遍历左子树，一直到左子树为空为止。
		while (btree)
		{	
			Push(&stack, btree);
			btree = btree->left;
		}

		// 3.若栈中还有元素，则将当前btree赋值为它的右子树，然后再重复 1~2步骤
		if (!StackIsEmpty(&stack))
		{
			btree = Top(&stack);
			printf("%c", btree->data);   //遍历完左子树后输出它们的根节点
			Pop(&stack);
			btree = btree->right;
		}
	}
	printf("\n");
}

/*
* function				后序遍历
* param		PBTree      root
* return                无
*/
void PostOrder(PBTree root)
{
	Stack stack = CreateStack();	//创建一个栈
	PBTree cur;						//当前结点 
	PBTree pre = NULL;				//前一次访问的结点 
	Push(&stack,root);              //先将根节点入栈
	while (!StackIsEmpty(&stack))
	{
		cur = Top(&stack);          //这里的cur就像是每颗子树的根节点，然后重复这些步骤
		if ((!cur->left && !cur->right) ||
			(pre && (pre == cur->left || pre == cur->right)))
		{
			printf("%c", cur->data);  //如果当前结点没有孩子结点或者孩子节点都已被访问过 
			Pop(&stack);
			pre = cur;
		}
		else
		{
			if (cur->right != NULL)      //这里先将右孩子入栈，这样出栈的时候，左孩子就先出栈
				Push(&stack,cur->right);
			if (cur->left != NULL)
				Push(&stack,cur->left);
		}
	}
	printf("\n");
}

/*
* function				层次遍历
* param		PBTree      root
* return                无
*/
void translevel(PBTree root)
{
	if (!root) return;
	Queue queue = CreateQueue();		//创建一个队列
	PBTree cur = root;					//当前节点
	QPush(&queue, root);				//先将根节点加入队列中
	while (!QueueIsEmpty(&queue))		//当队列中没有元素时，遍历完成 
	{
		cur = Front(&queue);			//获取当前队头元素
		QPop(&queue);                   //遍历过后就出队
		printf("%c", cur->data);		//先输出该子树的根节点
		if (cur->left)					//如果左孩子不为空，则入队等待遍历
			QPush(&queue, cur->left);   
		if (cur->right)				    //如果右孩子不为空，则入队等待遍历
			QPush(&queue, cur->right);
	}
	printf("\n");
}

/*
* function				添加节点值(添加的位置是不确定的)
* param		PBTree      root
* param		char	    ch
* return                无
*/
void AddValue(PBTree root, char ch)
{
	//采用层次遍历的办法，一层层扫描，若有空的地方，则添加到该地方
	if (!root)
	{
		root = CreateNode(ch);
		return;
	}	
	Queue queue = CreateQueue();		//创建一个队列
	PBTree cur = root;					//当前节点
	QPush(&queue, root);				//先将根节点加入队列中
	while (!QueueIsEmpty(&queue))		//当队列中没有元素时，遍历完成 
	{
		cur = Front(&queue);			//获取当前队头元素
		QPop(&queue);                   //遍历过后就出队
		if (cur->left)					//如果左孩子不为空，则入队等待遍历
			QPush(&queue, cur->left);
		else                            //否则就添加值，然后退出
		{
			cur->left = CreateNode(ch);
			break;
		}
		if (cur->right)				    //如果右孩子不为空，则入队等待遍历
			QPush(&queue, cur->right);
		else                            //否则就添加值，然后退出
		{
			cur->right = CreateNode(ch);//否则就添加值，然后退出
			break;
		}
	}
}

/*
* function				查找值
* param		PBTree      root
* param		char	    ch
* return                成功返回true，否则返回false
*/
bool Search(PBTree root, char ch)
{
	//利用层次遍历来查找
	if (!root) return false;
	Queue queue = CreateQueue();		//创建一个队列
	PBTree cur = root;					//当前节点
	QPush(&queue, root);				//先将根节点加入队列中
	while (!QueueIsEmpty(&queue))		//当队列中没有元素时，遍历完成 
	{
		cur = Front(&queue);			//获取当前队头元素
		if (cur->data == ch)
			return true;
		QPop(&queue);                   //遍历过后就出队
		if (cur->left)					//如果左孩子不为空，则入队等待遍历
			QPush(&queue, cur->left);
		if (cur->right)				    //如果右孩子不为空，则入队等待遍历
			QPush(&queue, cur->right);
	}
	return false;
}

/*****************************二叉树非递归实现*****************************/
