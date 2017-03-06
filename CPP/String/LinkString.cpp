#include "String.h"


/*
* function			默认长度，空字符串
* return   String	String类
*/
String::String()
{
	m_head = new Node();   
	m_tail = new Node();
	m_count = 0;
}

/*
* function			可以用字符串初始化String
* param    s		字符串
* return   String   String类
*/
String::String(char* s)
{
	cout << setlocale(LC_ALL, "chs") << endl;
	m_head = new Node();
	m_tail = new Node();
	m_count = 0;
	int len = _cbytes(s);							//计算字符串字节数
	for (int i = 0; i < len;i++)					//将字符串存储进链表中
	{
		if ((int)s[i] < 0)				//如果是中文字符，处理一下
		{
			PushRear(CToW(s[i], s[i + 1]));//窄字符转为宽字符
			i++;
		}
		else
			PushRear(s[i]);
	}
}

String::~String()
{
	if(m_head)
		delete m_head;
	if(m_tail)
		delete m_tail;
	m_head = nullptr;
	m_tail = nullptr;
}

/***************private function start*****************/

/*
* function			创建结点
* param    ch		字符
* return   Node*	返回一个结点
*/
String::Node* String::CreateNode(int ch)
{
	Node* node = new Node(ch);         //创建一个节点
	return node;
}

/*
* function			计算字符串字节数(窄字符)
* param    s		字符串
* return		    返回长度
*/
int String::_cbytes(char* s)
{
	if (!s) return 0;
	int len = 0;
	while (*s++)
		++len;
	return len;
}

/*
* function			计算字符串长度(窄字符)
* param    s		字符串
* return		    返回长度
*/
int String::_csize(char* s)
{
	if (!s) return 0;
	int len = 0;
	while (*s)
	{
		if ((int)*s < 0)  //中文第一个字节为负数
			s += 2;
		else
			++s;
		++len;
	}
	return len;
}

/*
* function			释放节点
* param    start    释放的节点的起始位置
* param    num      释放节点的个数
* return		    无
*/
void String::FreeNode(int start, int num)
{
	start = start < 0 ? 0 : start >m_count - 1 ? (start = m_count - 1) : start;  //防止越界
	num = start + num > m_count ? m_count - start : num;
	
	Node* cur = GetNode(start);   //遍历到起始位置的前一个位置
	Node* pre = cur->pre;
			
	//开始释放num个节点
	for (int i = 0;i < num;i++)
	{
		Node* temp = cur->next;
		delete cur;
		pre->next = temp;   //前指向后
		if(temp)
			temp->pre = pre;    //后指向前
		cur = temp;         //往前移动
	}
	if (start + num == m_count)  //如果最后一个节点被释放了，则需要修改尾节点
	{
		m_tail->next = pre;
		m_tail->pre = pre->pre;
	}
		
	m_count -= num;
}

/*
* function			获取节点
* param    start    获取节点的起始位置
* param    num      获取节点的个数
* return		    返回获取到的节点
*/
String::Node* String::GetNodes(int start, int num)
{
	Node* cur = nullptr;
	Node* nodes = CreateNode();
	Node* node = nodes;

	//如果start偏后面，则从后面遍历
	cur = GetNode(start);
	
	for (int i = 0;i < num;i++)
	{
		node->next = new Node(cur->c ? cur->c : cur->w,cur->next,cur->pre);
		node = node->next;
		cur = cur->next;
	}
	node->next = nullptr;
	return nodes->next;
}

/*
* function			初始化缓冲区
* param    buf		字符串缓冲区
* param    value    初始化的值
* param    len      缓冲区大小
* return		    无
*/
void String::InitBuf(char* buf, int value, int len)
{
	if (!buf) return;
	for (int i = 0;i < len;i++)
		buf[i] = value;
}

/*
* function			从节点中获取到字符串
* param    nodes	字符节点
* param    num		节点个数
* return		    返回char* 字符串
*/
char* String::GetStringFromNodes(Node* nodes, int num) 
{
	if (!nodes)return nullptr;
	char* buf = new char[num * 2];  //这里分配两倍的num空间，防止最坏的情况是全中文
	InitBuf(buf, 0, num * 2);
	char* ch = nullptr;                             //存放从宽字节转来的中文字符
	int j = 0;                                   //buf数组的下标
	for (int i = 0;i < num;i++, j++, nodes = nodes->next)
	{
		if (nodes->c != 0)
			buf[j] = nodes->c;
		else
		{
			ch = WToC(nodes->w);
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
wchar_t String::CToW(char ch1, char ch2)
{
	char buf[3] = "";
	sprintf_s(buf, "%c%c", ch1, ch2);
	wchar_t wh[1] = L"";
	mbstowcs(wh, buf, 1);
	return wh[0];
}

/*
* function			宽字符转化为窄字符
* param    ch		宽字符
* return		    返回一个char ch[3]的数组，一个宽字符占两个字节
*/
char* String::WToC(wchar_t ch)
{
	char buf[3] = "";
	wcstombs(buf, &ch, 2);   //宽字节转换为窄字节
	return buf;
}

/*
* function			获取起始位置的那个节点
* param    start	起始位置
* return		    返回起始节点
*/
String::Node* String::GetNode(int start)
{
	//如果start偏后面，则从后面遍历
	Node* cur = nullptr;
	if (start > m_count / 2)
	{
		cur = m_tail->next;
		for (int i = m_count - 1;i > start;i--, cur = cur->pre);  //遍历到start这个位置
	}
	else
	{
		cur = m_head->next;
		for (int i = 0;i < start;i++, cur = cur->next);  //遍历到start这个位置
	}
	return cur;
}

/***************private function end*****************/

/*
* function			获取字符串大小
* return   int      返回字符串大小
*/
int String::Size()
{
	return m_count;
}

/*
* function			获取字符串字节数
* return   int      返回字符串字节数
*/
int String::Bytes()
{
	return _cbytes(GetStringFromNodes(GetNodes(0,m_count),m_count));
}

/*
* function			是否为空
* return   bool     空返回true
*/
bool String::IsEmpty()
{
	return m_count ? false : true;
}

/*
* function			添加一个字符到前面
* param    ch		字符
* return		    无
*/
void String::PushFront(int ch)
{
	Node* node = CreateNode(ch);			//创建一个节点
	if (IsEmpty())					//如果链表为空，第一次添加的时候，就让尾指针指向第一个添加的节点
	{
		m_tail->next = node;        //例如 head->NULL,现在添加了个node1,则node1->NULL,head->node1,先把正方向连好
		node->next = m_head->next;  //然后node1->head
		m_head->next = node;
		node->pre = m_head;
	}
	else
	{
		node->next = m_head->next;     //例如 head->node1,现在添加了个node2,则node2->node1,head->node2,先把正方向连好
		m_head->next = node;           //然后node1 -> node2,node2->head
		node->next->pre = node;
		node->pre = m_head;
	}
	m_count++;
}

/*
* function			添加一个字符到最后
* param    ch		字符
* return		    无
*/
void String::PushRear(int ch)
{
	Node* node = CreateNode(ch);
	if (IsEmpty())
		PushFront(ch);
	else
	{
		m_tail->next->next = node;  //tail.next表示最后一个节点，这句代码的意思是，让最后一个节点指向新添进来的节点
		node->pre = m_tail->next;   //新添进来的节点的前驱指向原来的最后一个节点
		m_tail->next = node;        //修改tail的指向
		m_count++;
	}
}

/*
* function			添加字符串到前面
* param    s		字符串
* return		    无
*/
void String::PushFront(char* s)
{
	if(s)
		Insert(0, s);
}

/*
* function			添加字符串到最后
* param    s		字符串
* return		    无
*/
void String::PushRear(char* s)
{
	if (s)
		Insert(m_count, s);
}

/*
* function			删除最后n个字符
* param    n		删除字符的个数
* return		    无
*/
void String::PopRear(int n)
{
	DeleteSub(m_count - n, m_count - 1);
}

/*
* function			删除前面n个字符
* param    n		删除字符的个数
* return		    无
*/
void String::PopFront(int n)
{
	DeleteSub(0, n - 1);
}

/*
* function			删除指定位置字符
* param    local	删除的位置
* return		    删除失败返回-1
*/
int String::Delete(int local)
{
	if (IsEmpty())
		return -1;
	if (local < 0 || local > m_count - 1)
		return -1;
	FreeNode(local, 1);  //只要释放要删除的节点即可，连接工作已经封装再内
	return 1;
}

/*
* function			删除子串
* param    start	删除的起始位置
* param    end		删除的终点位置
* return		    删除失败返回-1
*/
int String::DeleteSub(int start, int end)
{
	if (IsEmpty())  
		return -1;
	if (start < 0 || start > m_count - 1 || end < 0 ||
		end >  m_count - 1 || end < start)
		return -1;
	int len = end - start + 1;
	FreeNode(start, len);  //只要释放要删除的节点即可，连接工作已经封装再内
	return len;
}

/*
* function			删除子串
* param    start	删除的起始位置
* param    len		要删除的长度
* return		    删除失败返回-1
*/
int String::DeleteSubLen(int start, int len)
{
	if (IsEmpty())  
		return -1;
	if (start < 0 || start > m_count - 1 || start + len > m_count)
		return -1;
	FreeNode(start, len);
	return len;
}

/*
* function			截取子串
* param    start	截取的起始位置
* param    end		截取的终点位置
* return		    截取失败返回nullptr
*/
char* String::SubString(int start, int end)
{
	if (IsEmpty())  
		return NULL;
	if (start < 0 || start > m_count - 1 || end < 0 ||
		end >  m_count - 1 || end < start)
		return NULL;
	int len = end - start + 1;
	Node* nodes = GetNodes(start, len);		//获取要截取的节点
	return GetStringFromNodes(nodes, len);
}

/*
* function			截取子串
* param    start	截取的起始位置
* param    len		截取的长度
* return		    截取失败返回nullptr
*/
char* String::SubStringLen(int start, int len)
{
	if (IsEmpty())  
		return NULL;
	if (start < 0 || start > m_count - 1 || start + len > m_count)
		return NULL;
	Node* nodes = GetNodes(start, len);    //获取要截取的节点
	return GetStringFromNodes(nodes, len);
}

/*
* function			替换字符  (窄字符替换窄字符)
* param    s		替换的源字符
* param    d		替换后的字符
* return		    替换失败返回-1
*/
int String::Replace(int s, int d)
{
	if (IsEmpty()) return -1;
	Node* cur = m_head->next;
	int count = 0;
	for (int i = 0;i <m_count;i++, cur = cur->next)
	{
		if (s > 255)  //中文字符
		{
			if (cur->w == s)
			{
				if (d > 255)  //要替换的也是中文字符
					cur->w = d, ++count;
				else
					cur->c = d, cur->w = 0, ++count;
			}
		}
		else
		{
			if (cur->c == s)
			{
				if (d > 255)  //要替换的是中文字符
					cur->w = d,cur->c = 0 , ++count;
				else
					cur->c = d , ++count;
			}
		}	
	}
	return count;
}

/*
* function			替换字符(窄字符)
* param    local	替换的位置
* param    d		替换后的字符
* return		    替换失败返回-1
*/
int String::ReplaceLocal(int local, int d)
{
	if (IsEmpty()) return -1;
	if (local <0 || local > m_count - 1)return -1;
	Node* cur = GetNode(local);
	if (d > 255)
		cur->w = d;
	else
		cur->c = d;
	return 1;
}

/*
* function			替换子串
* param    s		替换的源串
* param    d		替换的目标串
* return		    替换失败返回-1
*/
int String::Replace(char* s, char* d)
{
	Node* cur = m_head->next;
	int lens = _csize(s);
	int lend = _csize(d);
	int lensBytes = _cbytes(s);
	int j = 0;
	int count = 0;
	for (int i = 0; i < m_count; i++, cur = cur->next)
	{
		Node* temp = cur;
		for (j = 0; j < lensBytes; j++, temp = temp->next)
		{
			if (i + lens > m_count)
				break;
			if ((int)s[j] < 0)  //处理中文字符
			{
				if (temp->w != CToW(s[j], s[j + 1]))
					break;
				j++;
			}
			else
			{
				if (temp->c != s[j])
					break;
			}
		}
		if (j == lensBytes)  //如果找到了就替换
		{
			//  这里也分三种情况
			//1.lens  == lend 直接覆盖即可
			if (lens == lend)
			{
				cur = Replace(i, d);
				i += lens - 1;  // - 1是抵消i++
			}

			//2.lens < lend 先覆盖lens个长度，之后剩下的插入进去 
			if (lens < lend)
			{
				int lendBytes = _cbytes(d);
				int cb = 0;
				char* buf = new char[lendBytes];
				InitBuf(buf, 0, lendBytes);
				int j = 0;
				for (int k = 0;k < lens;k++, j++)  //将lend的前lens个字符截取出来
				{
					if ((int)d[j] < 0)
						sprintf(buf, "%s%c%c", buf, d[j], d[j + 1]), j++;
					else
						buf[j] = d[j];
				}
				cur = Replace(i, buf);
				InitBuf(buf, 0, lendBytes);
				for (int k = j;k < lendBytes;k++)  //将lend的剩下的字符截取出来
				{
					if ((int)d[k] < 0)
						sprintf(buf, "%s%c%c", buf, d[k], d[k + 1]), k++;
					else
						sprintf(buf, "%s%c", buf, d[k]);
				}
				Insert(i + lens, buf);  //将剩下的字符插入
				for (int k = 0;k < lend - lens;k++, cur = cur->next);  //记得往后移动
				i += lend - 1;
			}

			//3.lens > lend 先覆盖lend个长度，之后删除剩下的长度
			if (lens > lend)
			{
				cur = Replace(i, d);        //先覆盖，后删除
				DeleteSubLen(i + lend, lens - lend);
				i += lend - 1;
			}
			count++;
		}
	}
	return count;
}

/*
* function			替换子串
* param    local	替换的起始位置
* param    d		替换的目标串
* return		    替换失败返回nullptr
*/
String::Node* String::Replace(int local, char* d)
{
	if (IsEmpty())
		return NULL;
	Node* cur = GetNode(local);
	int len = _cbytes(d);
	for (int i = 0;i < len;i++, cur = cur->next)
	{
		if ((int)d[i] < 0)  //处理中文字符
		{
			if (!cur)                   //如果替换的字符串超出了当前的范围，则直接插入到后面
			{
				PushRear(CToW(d[i], d[i + 1]));
				cur = m_tail->next;   //这里要将cur的指向修改为最后一个节点，否则再次循环后cur为NULL，会出错
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
				PushRear(d[i]);
				cur = m_tail->next;
			}
			else
				cur->c = d[i], cur->w = 0;
		}
	}
	return cur->pre;
}

/*
* function			查找字符第一次出现的位置
* param    ch		要查找的字符
* return		    查找失败返回-1
*/
int String::FindFirst(int ch)
{
	Node* cur = m_head->next;
	for (int i = 0;i < m_count;i++, cur = cur->next)
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
* param    ch		要查找的字符
* return		    查找失败返回-1
*/
int String::FindLast(int ch)
{
	Node* cur = m_tail->next;
	for (int i = m_count - 1;i >= 0;i--, cur = cur->pre)
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
* function			给定起始位置查找字符出现的位置
* param    ch		要查找的字符
* param    start	起始位置
* return		    查找失败返回-1
*/
int String::Find(int ch, int start)
{
	if (start < 0 || start > m_count - 1)
		return -1;
	Node* cur = GetNode(start);
	for (int i = start;i < m_count;i++, cur = cur->next)
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
* param    s		要查找的子串
* return		    查找失败返回-1
*/
int String::FindFirst(char* s)
{
	Node* cur = m_head->next;
	int j = 0;
	int len = _cbytes(s);
	for (int i = 0;i < m_count;i++, cur = cur->next)
	{
		Node* temp = cur;
		for (j = 0; j < len; j++, temp = temp->next)
		{
			if ((int)s[j] < 0)  //处理中文字符
			{
				if (temp->w != CToW(s[j], s[j + 1]))
					break;
				j++;
			}
			else
			{
				if (temp->c != s[j])
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
* param    s		要查找的子串
* return		    查找失败返回-1
*/
int String::FindLast(char* s)
{
	int j = 0;
	int len = _cbytes(s);
	Node* cur = GetNode(m_count - _csize(s));   //遍历到m_count - 字符串长度的位置，这样可以少比几次
	for (int i = 0;i < m_count;i++, cur = cur->pre)
	{
		Node* temp = cur;
		for (j = 0; j < len; j++, temp = temp->next)
		{
			if ((int)s[j] < 0)  //处理中文字符
			{
				if (temp->w != CToW(s[j], s[j + 1]))
					break;
				j++;
			}
			else
			{
				if (temp->c != s[j])
					break;
			}
		}
		if (j == len)
			return i;
	}
	return -1;
}

/*
* function			查找子串出现的位置
* param    s		要查找的子串
* param    start	起始位置
* return		    查找失败返回-1
*/
int String::Find(char* s, int start)
{
	Node* cur = GetNode(start);
	int j = 0;
	int len = _cbytes(s);
	int lens = _csize(s);
	for (int i = start;i < m_count - lens + 1;i++, cur = cur->next)
	{
		Node* temp = cur;
		for (j = 0; j < len; j++, temp = temp->next)
		{
			if ((int)s[j] < 0)  //处理中文字符
			{
				if (temp->w != CToW(s[j], s[j + 1]))
					break;
				j++;
			}
			else
			{
				if (temp->c != s[j])
					break;
			}
		}
		if (j == len)
			return i;
	}
	return -1;
}

/*
* function			插入字符
* param    local    要插入的位置
* param    ch		要插入的字符
* param    n		要插入的个数
* return		    无
*/
void String::Insert(int local, int ch, int n)
{
	local = local < 0 ? 0 : local > m_count ? m_count : local;
	if (IsEmpty() || local == m_count)    //如果是空的，则直接全部尾添加即可,或者插入的位置是最后一个
	{
		for (int i = 0;i < n;i++)
			PushRear(ch);
	} 
	else 
	{
		Node* cur = GetNode(local)->pre;
		for (int i = 0;i < n;i++)
		{
			Node* node = CreateNode(ch);  //假设原来 A->C
			node->next = cur->next;     //正方向连接 A->B->C
			cur->next = node;
			node->next->pre = node;     //反方向连接A<-B<-C
			node->pre = cur;
		}
		m_count += n;
	}
}

/*
* function			插入字符串
* param    local    要插入的位置
* param    s		要插入的字符串
* param    n		要插入的个数
* return		    无
*/
void String::Insert(int local, char* s, int n)
{
	local = local < 0 ? 0 : local > m_count ? m_count : local;
	if (IsEmpty() || local == m_count)    //如果是空的，则直接全部尾添加即可,或者插入的位置是最后一个
	{
		int len = _cbytes(s);
		for (int i = 0;i < n;i++)
		{
			for (int j = 0;j < len;j++)
			{
				if ((int)s[j] < 0)  //处理中文字符
					PushRear(CToW(s[j], s[j + 1])), j++;
				else
					PushRear(s[j]);
			}
		}		
	}
	else
	{
		Node* cur = GetNode(local);
		for (int i = 0;i < n;i++)
		{	
			int len = _cbytes(s);
			for (int j = 0;j < len; j++)   //循环插入
			{
				Node* node = NULL;
				if ((int)s[j] < 0)  //处理中文字符
					node = CreateNode(CToW(s[j], s[j + 1])), j++;
				else
					node = CreateNode(s[j]);
				node->next = cur->next;
				cur->next = node;
				node->next->pre = node;
				node->pre = cur;
				cur = node;
			}
		}
		m_count += _csize(s) * n;
	}
}

/*
* function			统计字符出现过的次数
* param    ch		要查找的字符
* return		    返回字符出现的次数
*/
int String::AppearTimes(int ch)
{
	Node* cur = m_head->next;
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
* param    s		要查找的子串
* return		    返回字符出现的次数
*/
int String::AppearTimes(char* s)
{
	Node* cur = m_head;
	int count = 0;
	int len = _cbytes(s);
	int i = 0;
	while (cur->next)
	{
		Node* temp = cur;
		for (i = 0;i < len;i++, temp = temp->next)
		{
			if ((int)s[i] < 0)   //处理中文字符
			{
				if (temp->w != CToW(s[i], s[i + 1]))
					break;
				i++;   //这里的i++是因为中文字符占两个字节，所以再跳过一个字节
			}
			else
			{
				if (temp->c != s[i])
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
* param   s1		字符串1
* param   s2		字符串2
* return		    相等返回true
*/
bool String::Equal(String& s)
{
	if (Size() != s.Size())
		return false;
	Node* cur1 = m_head->next;
	Node* cur2 = s.m_head->next;
	int i = 0;
	for (;i < m_count;i++, cur1 = cur1->next, cur2 = cur2->next)
	{
		if (cur1->c != cur2->c  && cur1->c != 0)
			break;
		else if (cur1->w != cur2->w  && cur1->w != 0)
			break;
	}
	if (i == m_count)
		return true;
	else
		return false;
}

/*
* function			比较两个char*是否相等
* param   s1		字符串1
* param   s2		字符串2
* return		    相等返回true
*/
bool String::Equal(const char* s)
{
	char* s1 = GetString();
	int len1 = _cbytes(s1);
	int len2 = _cbytes((char*)s);
	if (len1 != len2)
		return false;
	else
	{
		for (int i = 0;i < len1;i++)
		{
			if (s1[i] != s[i])
				return false;
		}
	}
	return true;
}

/*
* function			获取字符串
* return		    返回data
*/
char* String::GetString()
{
	return  GetStringFromNodes(GetNodes(0, m_count), m_count);
}

/*
* function			打印字符串
* param    start    起始位置
* param    end      终点位置
* return		    无
*/
void String::Print(int start, int end)
{
	if (IsEmpty())  //防止引用空指针
		return;
	start = start<0 || start > m_count - 1 ? 0 : start;		//防止越界
	end = end<0 || end > m_count - 1 ? m_count : end;	//防止越界
	if (end < start)											//防止倒置
	{
		int temp = 0;
		temp = start;
		start = end;
		end = start;
	}
	setlocale(LC_ALL, "chs");			//设置一下显示中文
	Node* cur = GetNode(start);
	for (int i = start; i < end; i++, cur = cur->next)
	{
		if (cur->c != 0)
			cout<< cur->c;
		else
			wcout<<cur->w;
	}
	cout << endl;
}

/*
* function			清空字符串
* return		    无
*/
void String::Clear()
{
	FreeNode(0, m_count);
}

/*
* function			逆转字符串
* return		    无
*/
void String::Reverse()
{
	Node* head = m_head->next;
	Node* tail = m_tail->next;
	int temp1;
	int temp2;  //对折交换值
	for (int i = 0;i < m_count / 2;i++, head = head->next, tail = tail->pre)
	{
		temp1 = head->c, temp2 = head->w;
		head->c = tail->c, head->w = tail->w;
		tail->c = temp1, tail->w = temp2;
	}
}

/*
* function			连接字符串
* return		    无
*/
void String::ConCat(char* s)
{
	PushRear(s);
}

/*
* function			连接字符串
* return		    无
*/
void String::ConCat(String& s)
{
	PushRear(s.GetString());
}

/*
* function			赋值
* param    s        char*
* return		    无
*/
void String::Assign(char* s)
{
	Clear();     //赋值操作就是覆盖原来的值，所以这里要先清空字符串
	PushRear(s);
}

/*
* function			赋值
* param    s        String
* return		    无
*/
void String::Assign(String& s)
{
	if (this != &s)   //防止自己给自己赋值会Clear掉自己
	{
		Clear();     //赋值操作就是覆盖原来的值，所以这里要先清空字符串
		PushRear(s.GetString());
	}
}

/*
* function			获取指定位置的值 
* param    s        String
* return		    返回该位置的字符
*/
int String::GetAt(int iPos)
{
	Node* node = GetNode(iPos);
	return node->c ? node->c : node->w;
}

/*
* function			重载+号运算符 
* param    s        String
* return		    String类
*/
String& String::operator +(String& s)
{
	ConCat(s);
	return *this;
}

/*
* function			重载+号运算符
* param    s        char*
* return		    无
*/
String& String::operator +(char* s)
{
	ConCat(s);
	return *this;
}

/*
* function			重载=号运算符 
* param    s        String
* return		    String类
*/
String& String::operator =(String& s)
{
	Assign(s);
	return *this;
}

/*
* function			重载=号运算符
* param    s        char*
* return		    无
*/
String& String::operator =(char* s)
{
	Assign(s);
	return *this;
}

/*
* function			重载+=号运算符
* param    s        String
* return		    String类
*/
String& String::operator +=(String& s)
{
	ConCat(s);
	Assign(*this);
	return *this;
}

/*
* function			重载+=号运算符
* param    s        char*
* return		    无
*/
String& String::operator +=(char* s)
{
	ConCat(s);
	Assign(*this);
	return *this;
}

/*
* function			重载[]运算符   
* param    iPos     元素位置
* return		    返回该字符
*/
int String::operator [](int iPos)
{
	return GetAt(iPos);
}
