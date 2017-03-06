#include "String.h"

/*
* function			默认长度，空字符串,类似C++的构造函数
* return   PString  字符串结构体指针
*/
String String1()
{
	PString pstr = (PString)malloc(sizeof(_string));   //String结构指针
	pstr->count = 0;                                   //初始化字符数为0
	PNode headNode = CreateNode(0);						   //创建一个头节点
	pstr->headNode = headNode;
	PNode endNode = CreateNode(0);						   //创建一个尾节点
	pstr->endNode = endNode;
	return *pstr;
}

/*
* function			可以用字符串初始化结构体,类似C++的构造函数
* param    str		字符串
* return   PString  字符串结构体指针
*/
String String2(char* s)
{
	PString pstr = (PString)malloc(sizeof(_string));   //String结构指针
	pstr->count = 0;
	setlocale(LC_ALL, "chs");
	PNode headNode = CreateNode(0);						   //创建一个头节点
	pstr->headNode = headNode;
	PNode endNode = CreateNode(0);						   //创建一个尾节点
	pstr->endNode = endNode;
	int len = _cbytes(s);							//计算字符串字节数
	for (int i = 0; i < len;i++)					//将字符串存储进链表中
	{												
		if ((int)s[i] < 0)				//如果是中文字符，处理一下
		{				
			PushRear(pstr, CToW(s[i],s[i + 1]));//窄字符转为宽字符
			i++;
		}
		else
			PushRear(pstr, s[i]);
	}

	return *pstr;
}

/*
* function			可以用数组初始化结构体,类似C++的构造函数
* param    array	int数组
* param    arraySize数组大小
* param    separator分隔符
* return   PString  字符串结构体指针
*/
String String3(int a[], int arraySize, int separator)
{
	PString pstr = (PString)malloc(sizeof(_string));   //String结构指针
	pstr->count = 0;
	PNode headNode = CreateNode(0);						   //创建一个头节点
	pstr->headNode = headNode;
	PNode endNode = CreateNode(0);						   //创建一个尾节点
	pstr->endNode = endNode;
	for (int i = 0;i < arraySize;i++)
	{
		char buf[64] = "";
		sprintf(buf, "%d", a[i]);
		int len = _csize(buf);
		for (int j = 0;j < len;j++)
			PushRear(pstr, buf[j]);
		if (i != arraySize - 1)
			PushRear(pstr, separator);   //插入分隔符
	}

	return *pstr;
}

/*
* function			可以用数组初始化结构体,类似C++的构造函数
* param    array	double数组
* param    arraySize数组大小
* param    separator分隔符
* return   PString  字符串结构体指针
*/
String String4(double a[], int arraySize, char separator)
{
	PString pstr = (PString)malloc(sizeof(_string));   //String结构指针
	pstr->count = 0;
	PNode headNode = CreateNode(0);						   //创建一个头节点
	pstr->headNode = headNode;
	PNode endNode = CreateNode(0);						   //创建一个尾节点
	pstr->endNode = endNode;
	for (int i = 0;i < arraySize;i++)
	{
		char buf[64] = "";
		sprintf(buf, "%lf", a[i]);
		int len = _csize(buf);
		for (int j = 0;j < len;j++)
			PushRear(pstr, buf[j]);
		if (i != arraySize - 1)
			PushRear(pstr, separator);   //插入分隔符
	}

	return *pstr;
}

/*
* function			创建结点
* param    PString  字符串结构体指针
* return   PNode    返回一个结点
*/
PNode CreateNode(int ch)
{
	PNode node = (PNode)malloc(sizeof(_node));         //创建一个节点
	node->c = 0;
	node->w = 0;
	if (ch > 255)				//中文字符
		node->w = ch;
	else
		node->c = (char)ch;     //英文字符
	node->next = NULL;
	return node;
}

/*
* function			获取字符串大小
* param    PString  字符串结构体指针
* return   int      返回字符串大小
*/
int Size(PString pstr)
{
	return pstr ? pstr->count : 0;
}

/*
* function			添加一个字符到最后
* param    PString  字符串结构体指针
* param    char		字符
* return		    无
*/
void PushRear(PString pstr, int ch)
{
	if (pstr->count == 0)
		PushFront(pstr, ch);
	else
	{
		PNode node = CreateNode(ch);         //创建一个节点
		PNode cur = pstr->endNode->next;	 //最后一个节点
		cur->next = node;
		pstr->endNode->next = node;          //修改尾节点的指向
		pstr->count++;
	}
}

/*
* function			添加一个字符到前面
* param    PString  字符串结构体指针
* param    char		字符
* return		    无
*/
void PushFront(PString pstr, int ch)
{
	PNode node = CreateNode(ch);          //创建一个节点
 	node->next = pstr->headNode->next;    //头添加方式
	pstr->headNode->next = node;
	if (pstr->count == 0)                 //如果是第一次添加，则让尾节点指向第一个节点
		pstr->endNode->next = node;
	pstr->count++;
}

/*
* function			删除最后一个字符
* param    PString  字符串结构体指针
* return		    无
*/
void PopRear(PString pstr)
{
	PNode cur = pstr->headNode->next;
	PNode pre = pstr->headNode;
	//遍历到pre为倒数第二个的时候
	for (int i = 0;i < pstr->count - 1;i++, cur = cur->next, pre = pre->next);
	free(cur);        //释放最后一个节点
	pre->next = NULL; //让倒数第二个变为最后一个节点
	pstr->endNode->next = pre;  //修改尾节点指向
	pstr->count--;
}

/*
* function			删除第一个字符
* param    PString  字符串结构体指针
* return		    无
*/
void PopFront(PString pstr)
{
	PNode cur = pstr->headNode->next;
	PNode pre = pstr->headNode;
	pre->next = cur->next;  //让倒数第二个变为最后一个节点
	free(cur);				//释放第一个节点
	pstr->count--;
}

/*
* function			删除子串
* param    PString  字符串结构体指针
* param    start	删除的起始位置
* param    end		删除的终点位置
* return		    删除失败返回-1
*/
int DeleteSub1(PString pstr, int start, int end)
{
	if (!pstr->headNode)  //防止引用空指针
		return -1;
	if (start < 0 || start > pstr->count - 1 || end < 0 ||
		end >  pstr->count - 1 || end < start)
		return -1;
	int len = end - start + 1;
	FreeNode(pstr, start, len);  //只要释放要删除的节点即可，连接工作已经封装再内
	return len;
}

/*
* function			删除子串
* param    PString  字符串结构体指针
* param    start	删除的起始位置
* param    len		要删除的长度
* return		    删除失败返回-1
*/
int DeleteSub2(PString pstr, int start, int len)
{
	if (!pstr->headNode)  //防止引用空指针
		return -1;
	if (start < 0 || start > pstr->count - 1 || start + len > pstr->count)
		return -1;
	FreeNode(pstr, start, len);
	return len;
}

/*
* function			截取子串
* param    PString  字符串结构体指针
* param    start	截取的起始位置
* param    end		截取的终点位置
* return		    截取失败返回NULL
*/
char* SubString1(PString pstr, int start, int end)
{
	if (!pstr->headNode)  //防止引用空指针
		return NULL;
	if (start < 0 || start > pstr->count - 1 || end < 0 ||
		end >  pstr->count - 1 || end < start)
		return NULL;
	int len = end - start + 1;
	PNode nodes = GetNodes(pstr, start, len);    //获取要截取的节点
	return GetStringFromNodes(nodes,len);
}

/*
* function			截取子串
* param    PString  字符串结构体指针
* param    start	截取的起始位置
* param    len		截取的长度
* return		    截取失败返回NULL
*/
char* SubString2(PString pstr, int start, int len)
{
	if (!pstr->headNode)  //防止引用空指针
		return NULL;
	if (start < 0 || start > pstr->count - 1 || start + len > pstr->count)
		return NULL;
	PNode nodes = GetNodes(pstr, start, len);    //获取要截取的节点
	return GetStringFromNodes(nodes, len);
}

/*
* function			替换字符  (窄字符替换窄字符)
* param    PString  字符串结构体指针
* param    s		替换的源字符
* param    d		替换后的字符
* return		    替换失败返回-1
*/
int ReplaceChar1(PString pstr, char s, char d)
{
	if (!pstr->headNode) return -1;
	PNode cur = pstr->headNode->next;
	int count = 0;
	for (int i = 0;i < pstr->count;i++, cur = cur->next)
	{
		if (cur->c == s)
			cur->c = d,++count;
	}
	return count;
}

/*
* function			替换字符  (窄字符替换宽字符)
* param    PString  字符串结构体指针
* param    s		替换的源字符
* param    d		替换后的字符
* return		    替换失败返回-1
*/
int ReplaceChar2(PString pstr, char s, wchar_t d)
{
	if (!pstr->headNode) return -1;
	PNode cur = pstr->headNode->next;
	int count = 0;
	for (int i = 0;i < pstr->count;i++, cur = cur->next)
	{
		if (cur->c == s)
			cur->c = 0,cur->w = d, ++count;
	}
	return count;
}

/*
* function			替换字符  (宽字符替换窄字符)
* param    PString  字符串结构体指针
* param    s		替换的源字符
* param    d		替换后的字符
* return		    替换失败返回-1
*/
int ReplaceChar3(PString pstr, wchar_t s, char d)
{
	if (!pstr->headNode) return -1;
	PNode cur = pstr->headNode->next;
	int count = 0;
	for (int i = 0;i < pstr->count;i++, cur = cur->next)
	{
		if (cur->w == s)
			cur->w = 0, cur->c = d, ++count;
	}
	return count;
}

/*
* function			替换字符  (宽字符替换宽字符)
* param    PString  字符串结构体指针
* param    s		替换的源字符
* param    d		替换后的字符
* return		    替换失败返回-1
*/
int ReplaceChar4(PString pstr, wchar_t s, wchar_t d)
{
	if (!pstr->headNode) return -1;
	PNode cur = pstr->headNode->next;
	int count = 0;
	for (int i = 0;i < pstr->count;i++, cur = cur->next)
	{
		if (cur->w == s)
			cur->w = d, ++count;
	}
	return count;
}

/*
* function			替换字符(窄字符)
* param    PString  字符串结构体指针
* param    local	替换的位置
* param    d		替换后的字符
* return		    替换失败返回-1
*/
int ReplaceChar5(PString pstr, int local, char d)
{
	if (!pstr->headNode) return -1;
	if (local <0 || local > pstr->count - 1)return -1;
	PNode cur = pstr->headNode->next;
	for (int i = 0;i < local;i++, cur = cur->next);
	cur->c = d;
	return 1;
}

/*
* function			替换字符
* param    PString  字符串结构体指针
* param    local	替换的位置
* param    d		替换后的字符
* return		    替换失败返回-1
*/
int ReplaceChar6(PString pstr, int local, wchar_t d)
{
	if (!pstr->headNode) return -1;
	if (local <0 || local > pstr->count - 1)return -1;
	PNode cur = pstr->headNode->next;
	for (int i = 0;i < local;i++, cur = cur->next);
	cur->w = d;
	return 1;
}

/*
* function			替换子串
* param    PString  字符串结构体指针
* param    s		替换的源串
* param    d		替换的目标串
* return		    替换失败返回-1
*/
int ReplaceSubStr1(PString pstr, char* s, char* d)
{
	PNode cur = pstr->headNode->next;
	int lens = _csize(s);
	int lend = _csize(d);
	int lensBytes = _cbytes(s);
	int j = 0;
	int count = 0;
	for (int i = 0; i < pstr->count; i++, cur = cur->next)
	{
		PNode temp = cur;
		for (j = 0; j < lensBytes; j++,temp = temp->next)
		{
			if (i + lens > pstr->count)
				break;
			if ((int)s[j] < 0)  //处理中文字符
			{
				if(temp->w != CToW(s[j],s[j + 1]))
					break;
				j++;
			}
			else
			{
				if(temp->c != s[j])
					break;
			}
		}
		if (j == lensBytes)  //如果找到了就替换
		{
			//  这里也分三种情况
			//1.lens  == lend 直接覆盖即可
			if (lens == lend)
			{
				cur = ReplaceSubStr2(pstr, i, d);
				i += lens - 1;  // - 1是抵消i++
			}

			//2.lens < lend 先覆盖lens个长度，之后剩下的插入进去 
			if (lens < lend)
			{
				int lendBytes = _cbytes(d);
				int cb = 0;
				char* buf = (char*)malloc(sizeof(char)*lendBytes);
				InitBuf(buf, 0, lendBytes);
				int j = 0;
				for (int k = 0;k < lens;k++,j++)  //将lend的前lens个字符截取出来
				{
					if ((int)d[j] < 0)
						sprintf(buf,"%s%c%c",buf,d[j],d[j + 1]), j++;
					else
						buf[j] = d[j];
				}
				cur = ReplaceSubStr2(pstr, i, buf);
				InitBuf(buf, 0, lendBytes);
				for (int k = j;k < lendBytes;k++)  //将lend的剩下的字符截取出来
				{
					if ((int)d[k] < 0)
						sprintf(buf, "%s%c%c", buf, d[k], d[k + 1]), k++;
					else
						sprintf(buf, "%s%c", buf, d[k]);
				}
				InsertSub(pstr, i + lens, buf);  //将剩下的字符插入
				for (int k = 0;k < lend - lens;k++, cur = cur->next);  //记得往后移动
				i += lend - 1;
			}

			//3.lens > lend 先覆盖lend个长度，之后删除剩下的长度
			if (lens > lend)
			{
				cur = ReplaceSubStr2(pstr, i, d);        //先覆盖，后删除
				DeleteSub2(pstr, i + lend, lens - lend);
				i += lend - 1;
			}
			count++;
		}
	}
	return count;
}

/*
* function			替换子串
* param    PString  字符串结构体指针
* param    local	替换的起始位置
* param    d		替换的目标串
* return		    替换失败返回NULL
*/
PNode ReplaceSubStr2(PString pstr, int local, char* d)
{
	if (!pstr->headNode)
		return NULL;
	PNode cur = pstr->headNode->next;
	PNode pre = NULL;
	int len = _cbytes(d);
	for (int i = 0;i < local;i++, cur = cur->next);  //遍历到指定位置
	for (int i = 0;i < len;i++, cur = cur->next)
	{
		if ((int)d[i] < 0)  //处理中文字符
		{
			if (!cur)                   //如果替换的字符串超出了当前的范围，则直接插入到后面
			{
				PushRear(pstr, CToW(d[i], d[i + 1]));
				cur = pstr->endNode->next;   //这里要将cur的指向修改为最后一个节点，否则再次循环后cur为NULL，会出错
			}	
			else
			{
				cur->w = CToW(d[i], d[i + 1]);
				cur->c = 0;
			}
			i++;
		}
		else
		{
			if (!cur)                   //如果替换的字符串超出了当前的范围，则直接插入到后面
			{
				PushRear(pstr, d[i]);
				cur = pstr->endNode->next;
			}
			else
				cur->c = d[i], cur->w = 0;
		}
		if (i == len - 1)
			pre = cur;    //记录倒数第二个节点
	}
	return pre;
}

/*
* function			查找字符第一次出现的位置
* param    PString  字符串结构体指针
* param    ch		要查找的字符
* return		    查找失败返回-1
*/
int FindFirst(PString pstr, int ch)
{
	PNode cur = pstr->headNode->next;
	for (int i = 0;i < pstr->count;i++,cur = cur->next)
	{
		if (ch > 255)
		{
			if (cur->w == (wchar_t)ch)
				return i;
		}	
		else
		{
			if (cur->c == (char)ch)
				return i;
		}	
	}
	return -1;
}

/*
* function			查找字符最后一次出现的位置
* param    PString  字符串结构体指针
* param    ch		要查找的字符
* return		    查找失败返回-1
*/
int FindLast(PString pstr, int ch)
{
	PNode cur = pstr->headNode->next;
	int max = -1;
	for (int i = 0;i < pstr->count;i++, cur = cur->next)
	{
		if (ch > 255)
		{
			if (cur->w == (wchar_t)ch)
				max = i;
		}
		else
		{
			if (cur->c == (char)ch)
				max = i;
		}	
	}
	return max;
}

/*
* function			给定起始位置查找字符出现的位置
* param    PString  字符串结构体指针
* param    ch		要查找的字符
* param    start	起始位置
* return		    查找失败返回-1
*/
int Find(PString pstr, int ch, int start)
{
	if (start < 0 || start > pstr->count - 1)
		return -1;
	PNode cur = pstr->headNode->next;
	for (int i = 0;i < start;i++, cur = cur->next);  //先遍历到指定
	for (int i = start;i < pstr->count;i++, cur = cur->next)
	{
		if (ch > 255)
		{
			if (cur->w == (wchar_t)ch)
				return i;
		}
		else
		{
			if (cur->c == (char)ch)
				return i;
		}			
	}
	return -1;
}

/*
* function			查找子串第一次出现的位置
* param    PString  字符串结构体指针
* param    sub		要查找的子串
* return		    查找失败返回-1
*/
int FindSubFirst(PString pstr, char* sub)
{
	PNode cur = pstr->headNode->next;
	int j = 0;
	int len = _cbytes(sub);
	for (int i = 0;i < pstr->count;i++, cur = cur->next)
	{
		PNode temp = cur;
		for (j = 0; j < len; j++, temp = temp->next)
		{
			if ((int)sub[j] < 0)  //处理中文字符
			{
				if (temp->w != CToW(sub[j], sub[j + 1]))
					break;
				j++;
			}
			else
			{
				if (temp->c != sub[j])
					break;
			}
		}
		if (j == len)
			return i;
	}
	return -1;
}

/*
* function			查找子串最后一次出现的位置
* param    PString  字符串结构体指针
* param    sub		要查找的子串
* return		    查找失败返回-1
*/
int FindSubLast(PString pstr, char* sub)
{
	PNode cur = pstr->headNode->next;
	int j = 0;
	int max = -1;
	int len = _cbytes(sub);
	for (int i = 0;i < pstr->count;i++, cur = cur->next)
	{
		PNode temp = cur;
		for (j = 0; j < len; j++, temp = temp->next)
		{
			if ((int)sub[j] < 0)  //处理中文字符
			{
				if (temp->w != CToW(sub[j], sub[j + 1]))
					break;
				j++;
			}
			else
			{
				if (temp->c != sub[j])
					break;
			}
		}
		if (j == len)
			max = i;
	}
	return max;
}

/*
* function			查找子串出现的位置
* param    PString  字符串结构体指针
* param    sub		要查找的子串
* param    start	起始位置
* return		    查找失败返回-1
*/
int FindSub(PString pstr, char* sub, int start)
{
	if (start < 0 || start > pstr->count - 1)
		return -1;
	PNode cur = pstr->headNode->next;
	for (int i = 0;i < start;i++, cur = cur->next);  //先遍历到指定
	int j = 0;
	int len = _cbytes(sub);
	int lens = _csize(sub);   //这里减去字符串的长度，是防止下面第二个循环引用空指针出错
	for (int i = 0;i < pstr->count - lens + 1;i++, cur = cur->next)
	{
		PNode temp = cur;
		for (j = 0; j < len; j++, temp = temp->next)
		{
			if ((int)sub[j] < 0)  //处理中文字符
			{
				if (temp->w != CToW(sub[j], sub[j + 1]))
					break;
				j++;
			}
			else
			{
				if (temp->c != sub[j])
					break;
			}
		}
		if (j == len)
			return i + start;
	}
	return -1;
}

/*
* function			插入字符
* param    PString  字符串结构体指针
* param    local    要插入的位置
* param    ch		要插入的字符
* return		    无
*/
void InsertChar(PString pstr, int local,int ch )
{
	if (pstr->count == 0)
		PushFront(pstr, ch);
	local = local < 0 ? 0 : local > pstr->count ? pstr->count : local;
	PNode cur = pstr->headNode;
	for (int i = 0;i < local;i++, cur = cur->next);  //遍历到指定位置插入
	PNode node = CreateNode(ch);
	node->next = cur->next;
	cur->next = node;
	pstr->count++;
}

/*
* function			插入字符串
* param    PString  字符串结构体指针
* param    local    要插入的位置
* param    sub		要插入的字符串
* return		    无
*/
void InsertSub(PString pstr, int local,char* sub)
{
	local = local < 0 ? 0 : local > pstr->count ? pstr->count:local;
	PNode cur = pstr->headNode;
	for (int i = 0;i < local;i++, cur = cur->next);  //遍历到指定位置插入
	int len = _cbytes(sub);
	for (int i = 0;i < len; i++)   //循环插入
	{
		PNode node = NULL;
		if ((int)sub[i] < 0)  //处理中文字符
			node = CreateNode(CToW(sub[i], sub[i + 1])),i++;
		else
			node = CreateNode(sub[i]);
		node->next = cur->next;
		cur->next = node;
		cur = node;
	}
	pstr->count += _csize(sub);
}

/*
* function			统计字符出现过的次数
* param    PString  字符串结构体指针
* param    ch		要查找的字符
* return		    返回字符出现的次数
*/
int AppearTimes(PString pstr, int ch)
{
	PNode cur = pstr->headNode->next;
	int count = 0;
	while (cur)
	{
		if (ch > 255)
		{
			if (cur->w == (wchar_t)ch)
				++count;
		}	
		else
		{
			if (cur->c == (char)ch)
				++count;
		}		
		cur = cur->next;
	}
	return count;
}

/*
* function			统计子串出现过的次数
* param    PString  字符串结构体指针
* param    sub		要查找的子串
* return		    返回字符出现的次数
*/
int CountSubTimes(PString pstr, char* sub)
{
	PNode cur = pstr->headNode;
	int count = 0;
	int len = _cbytes(sub);
	int i = 0;
	while (cur->next)
	{
		PNode temp = cur;
		for (i = 0;i < len;i++, temp = temp->next)
		{
			if ((int)sub[i] < 0)   //处理中文字符
			{
				if (temp->w != CToW(sub[i], sub[i + 1]))
					break;
				i++;   //这里的i++是因为中文字符占两个字节，所以再跳过一个字节
			}
			else
			{
				if (temp->c != sub[i])
					break;
			}
		}
		if (i == len)
			count++;
		cur = cur->next;
	}
	return count;
}

/*
* function			比较两个String是否相等
* param    PString  字符串结构体指针
* param   pstr1		字符串1
* param   pstr2		字符串2
* return		    相等返回true
*/
bool Equal(PString pstr1, PString pstr2)
{
	if(pstr1->count != pstr2->count)
		return false;
	PNode cur1 = pstr1->headNode->next;
	PNode cur2 = pstr2->headNode->next;
	int i = 0;
	for (;i < pstr1->count;i++, cur1 = cur1->next, cur2 = cur2->next)
	{
		if(cur1->c != cur2->c  && cur1->c != 0)
			break;
		else if(cur1->w != cur2->w  && cur1->w != 0)
			break;
	}
	if (i == pstr1->count)
		return true;
	else
		return false;
}

/*
* function			计算字符串字节数(窄字符)
* param    str		字符串
* return		    返回长度
*/
int _cbytes(char* str)
{
	if (!str) return 0;
	int len = 0;
	while (*str++)
		++len;
	return len;
}

/*
* function			计算字符串长度(窄字符)
* param    str		字符串
* return		    返回长度
*/
int _csize(char* str)
{
	if (!str) return 0;
	int len = 0;
	while (*str)
	{
		if ((int)*str < 0)  //中文第一个字节为负数
			str += 2;
		else
			++str;
		++len;
	}
	return len;
}

/*
* function			获取字符串
* param    PString  字符串结构体指针
* return		    返回data
*/
char* GetString(PString pstr)
{
	return GetStringFromNodes(GetNodes(pstr,0,pstr->count),pstr->count);
}

/*
* function			打印字符串
* param    str		字符串
* param    start    起始位置
* param    end      终点位置
* return		    无
*/
void Print(PString pstr, int start, int end)
{
	if (!pstr->headNode)  //防止引用空指针
		return;
	start = start<0 || start > pstr->count - 1 ? 0 : start;		//防止越界
	end = end<0 || end > pstr->count - 1 ? pstr->count : end;	//防止越界
	if (end < start)											//防止倒置
	{
		int temp = 0;
		temp = start;
		start = end;
		end = start;
	}
	for (int i = 0;i < start;i++)
		pstr->headNode = pstr->headNode->next;
	setlocale(LC_ALL, "chs");			//设置一下显示中文
	PNode cur = pstr->headNode->next;
	for (int i = start; i < end; i++, cur = cur->next)
	{
		if (cur->c != 0)
			printf("%c", cur->c);
		else
			wprintf(L"%c", cur->w);
	}
	printf("\n");
}

/*
* function			清除字符串
* param    PString  字符串结构体指针
* return		    无
*/
void Clear(PString pstr)
{
	FreeNode(pstr, 0, pstr->count);
}

/*
* function			释放节点
* param    PString  字符串结构体指针
* param    start    释放的节点的起始位置
* param    num      释放节点的个数
* return		    无
*/
void FreeNode(PString pstr, int start, int num)
{
	start = start < 0 ? 0 : start > pstr->count - 1 ? (start = pstr->count - 1) : start;  //防止越界
	num = start + num > pstr->count ? pstr->count - start : num;
	PNode cur = pstr->headNode->next;
	PNode pre = pstr->headNode;
	for (int i = 0;i < start;i++, cur = cur->next, pre = pre->next);   //先遍历到start这个位置的前一个位置
	//开始释放num个节点
	for (int i = 0;i < num;i++)
	{
		PNode temp = cur->next;
		free(cur);
		pre->next = temp;
		cur = temp;
	}
	if (start + num == pstr->count)  //如果最后一个节点被释放了，则需要修改尾节点
		pstr->endNode->next = pre;
	pstr->count -= num;
}

/*
* function			获取节点
* param    PString  字符串结构体指针
* param    start    获取节点的起始位置
* param    num      获取节点的个数
* return		    返回获取到的节点
*/
PNode GetNodes(PString pstr, int start, int num)
{
	PNode cur = pstr->headNode->next;
	PNode nodes = CreateNode(0);
	PNode node = nodes;
	for (int i = 0;i < start;i++, cur = cur->next);  //遍历到start这个位置
	for (int i = 0;i < num;i++)
	{
		node->next = CreateNode(cur->c?cur->c:cur->w);
		cur = cur->next;
		node = node->next;
	}
	node->next = NULL;
	return nodes->next;
}

/*
* function			初始化缓冲区
* param    buf		字符串缓冲区
* param    value    初始化的值
* param    len      缓冲区大小
* return		    无
*/
void InitBuf(char* buf, int value, int len)
{
	if (!buf) return;
	for (int i = 0;i < len;i++)
		buf[i] = value;
}

/*
* function			从节点中获取到字符串
* param    nodes	字符节点
* param    num		节点个数
* return		    无
*/
char* GetStringFromNodes(PNode nodes, int num)
{
	if (!nodes)return NULL;
	char* buf = (char*)malloc(sizeof(num * 2));  //这里分配两倍的num空间，防止最坏的情况是全中文
	InitBuf(buf, 0, num * 2);
	char ch[3] = "";                             //存放从宽字节转来的中文字符
	int j = 0;                                   //buf数组的下标
	for (int i = 0;i < num;i++, j++, nodes = nodes->next)
	{
		if (nodes->c != 0)
			buf[j] = nodes->c;
		else
		{
			wcstombs(ch, &nodes->w, 2);   //宽字节转换为窄字节
			buf[j] = ch[0];
			buf[++j] = ch[1];
		}
	}
	buf[j] = '\0';  //最后要记得加上结束标记
	return buf;
}

/*
* function			窄字符转化为宽字符
* param    ch1		第一个字节
* param    ch2		第二个字节
* return		    返回一个宽字符
*/
wchar_t CToW(char ch1, char ch2)
{
	char buf[3] = "";
	sprintf(buf, "%c%c", ch1, ch2);
	wchar_t wh[1] = L"";
	mbstowcs(wh, buf, 1);
	return wh[0];
}
