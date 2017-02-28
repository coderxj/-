#include "String.h"


/*
* function			默认长度，空字符串
*/
String::String()
{													
	m_string = new char[MAX_LEN];			//为数据区分配空间
	InitStr(m_string, 0, MAX_LEN);			//初始化字符串	
	m_curLen = 0;							//当前串长度为0
	m_maxLen = MAX_LEN;						//串的最大长度默认为MAX_LEN
}

/*
* function			可以指定字符串最大长度
* param    len		长度
*/
String::String(int maxLen)
{											
	m_string = new char[maxLen];			//为数据区分配空间
	InitStr(m_string, 0, maxLen);			//初始化字符串	
	m_curLen = 0;                           //当前串长度为0
	m_maxLen = maxLen;						//串的最大长度为用户指定的maxLen
}

/*
* function			可以指定字符串初始化
* param    s		字符串
*/
String::String(char* s)
{
	m_string = new char[MAX_LEN];			//为数据区分配空间
	InitStr(m_string, 0, MAX_LEN);			//初始化字符串
	m_curLen = _csize(s);					//当前串长度为str的长度
	m_maxLen = MAX_LEN;						//串的最大长度默认为MAX_LEN
	for (int i = 0;i < m_curLen;i++)
		m_string[i] = s[i];
}

String::~String()
{
	if (m_string)
		delete[] m_string;
	m_string = NULL;
}

/*
* function			获取字符串大小
* return   int      返回字符串大小
*/
int String::Size()
{
	return m_curLen;
}

/*
* function			重新分配空间
* return   int      返回分配空间的大小，失败返回-1
*/
int String::ReAlloc()
{
	if (!m_string)  //防止引用空指针
		return -1;
	int len =m_maxLen;
	char* temp = new char[len];
	for (int i = 0;i < len;i++)						//将数据暂存起来
		temp[i] = m_string[i];
	m_maxLen *= 2;									//扩大为原来的两倍
	m_string = new char[m_maxLen];
	InitStr(m_string, 0, m_maxLen);					//初始化
	for (int i = 0;i < len;i++)						//将数据暂存起来
		m_string[i] = temp[i];						//恢复数据 
	delete[] temp;
	return m_maxLen;
}

/*
* function			初始化字符串
* param    str		字符串
* parma    value    初始值
* param    len      长度
* return		    无
*/
void String::InitStr(char* str, int value, int len)
{
	for (int i = 0;i < len;i++)
		str[i] = value;
}

/*
* function			计算字符串长度(窄字符)
* param    str		字符串
* return		    返回长度
*/
int String::_csize(const char* str)
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
* function			计算字符串长度(宽字符)
* param    str		字符串
* return		    返回长度
*/
int String::_wsize(const wchar_t* str)
{
	if (!str) return 0;
	int len = 0;
	while (*str++)
		++len;
	return len;
}

/*
* function			添加一个字符到最后
* param    char		字符
* return		    无
*/
void String::PushRear(char ch)
{
	if (!m_string)				//防止引用空指针
		return;
	if (m_curLen == m_maxLen)  //如果空间满了 需要重新分配
		ReAlloc();
	m_string[m_curLen++] = ch;
}

/*
* function			添加字符串到最后
* param    sub		字符川
* return		    无
*/
void String::PushRear(char* sub)
{
	if (!m_string)  //防止引用空指针
		return;
	int len = _csize(sub);
	while (m_curLen + len >= m_maxLen)  //如果空间满了 需要重新分配
		ReAlloc();
	for (int i = 0;i < len;i++)
		m_string[m_curLen + i] = sub[i];
}

/*
* function			添加一个字符到前面
* param    char		字符
* return		    无
*/

void String::PushFront(char ch)
{
	if (!m_string)  //防止引用空指针
		return;
	if (m_curLen == m_maxLen)  //如果空间满了 需要重新分配
		ReAlloc();
	for (int i = m_curLen;i > 0;i--)
		m_string[i] = m_string[i - 1];
	m_string[0] = ch;
	m_curLen++;
}

/*
* function			添加字符串到前面
* param    sub		字符串
* return		    无
*/

void String::PushFront(char* sub)
{
	if (!m_string)  //防止引用空指针
		return;
	int len = _csize(sub);
	while (m_curLen + len >= m_maxLen)  //如果空间满了 需要重新分配
		ReAlloc();
	for (int i = m_curLen + len - 1;i >= 0;i--)
		m_string[i] = m_string[i - len];
	for (int i = 0;i < len;i++)
		m_string[i] = sub[i];
	m_curLen += len;
}

/*
* function			删除最后n个字符
* return		    无
*/
void String::PopRear(int n)
{
	m_curLen = m_curLen - n > 0 ? (m_curLen -= n) : 0;
}

/*
* function			删除前n个字符
* return		    无
*/
void String::PopFront(int n)
{
	if (!m_string)  //防止引用空指针
		return;
	if (m_curLen - n > 0)
	{
		for (int i = 0;i < m_curLen - n;i++)
			m_string[i] = m_string[i + n];
		m_curLen -= n;
	}
	else
		m_curLen = 0;
	
}

/*
* function			删除子串
* param    start	删除的起始位置
* param    end		删除的终点位置
* return		    删除失败返回-1
*/
int String::DeleteSub(int start, int end)
{
	if (!m_string)  //防止引用空指针
		return -1;
	if (start < 0 || start > m_curLen - 1 || end < 0 ||
		end >  m_curLen - 1 || end < start)
		return -1;
	int len = end - start;
	m_curLen -= len;
	for (int i = start;i <= m_curLen;i++)
		m_string[i] = m_string[i + len + 1];
	return len + 1;
}

/*
* function			删除子串
* param    start	删除的起始位置
* param    len		要删除的长度
* return		    删除失败返回-1
*/
int String::DeleteSubLen(int start, int len)
{
	if (!m_string)  //防止引用空指针
		return -1;
	if (start < 0 || start > m_curLen - 1)
		return -1;
	if (start + len > m_curLen)
		len = m_curLen - start;
	m_curLen -= len;
	for (int i = start;i <= m_curLen;i++)
		m_string[i] = m_string[i + len];
	return len;
}

/*
* function			截取子串
* param    start	截取的起始位置
* param    end		截取的终点位置
* return		    截取失败返回NULL
*/
char* String::SubString(int start, int end)
{
	if (!m_string)  //防止引用空指针
		return NULL;
	if (start < 0 || start > m_curLen - 1 || end < 0 ||
		end >  m_curLen - 1 || end < start)
		return NULL;
	char* sub = new char[end - start];
	for (int i = start; i <= end;i++)
		sub[i] = m_string[i];
	sub[end - start + 1] = '\0';   //最后要记得加上‘\0’结束符，不然输出的时候会有乱码出来
	return sub;
}

/*
* function			截取子串
* param    start	截取的起始位置
* param    len		截取的长度
* return		    截取失败返回NULL
*/
char* String::SubStringLen(int start, int len)
{
	if (!m_string)  //防止引用空指针
		return NULL;
	if (start < 0 || start > m_curLen - 1)
		return NULL;
	if (start + len > m_curLen)
		len = m_curLen;
	char* sub = new char[len];
	for (int i = start; i <= start + len;i++)
		sub[i] = m_string[i];
	sub[len] = '\0';   //最后要记得加上‘\0’结束符，不然输出的时候会有乱码出来
	return sub;
}

/*
* function			替换字符
* param    s		替换的源字符
* param    d		替换后的字符
* return		    替换失败返回-1
*/
int String::Replace(char s, char d)
{
	if (!m_string)  //防止引用空指针
		return -1;
	int pos = 0;
	int count = 0;
	if ((pos = FindFirst(s)) == -1)      //如果该字符不存在，则替换失败
		return -1;
	do
	{
		m_string[pos] = d;
		++count;
	} while ((pos = Find(s, pos + 1)) != -1);
	return count;                              //返回成功替换的字符数
}

/*
* function			替换字符
* param    local	替换的位置
* param    d		替换后的字符
* return		    替换失败返回-1
*/
int String::Replace(int local, char d)
{
	if (!m_string)  //防止引用空指针
		return -1;
	if (local < 0 || local > m_curLen - 1)
		return -1;
	m_string[local] = d;
	return local;
}

/*
* function			替换子串
* param    s		替换的源串
* param    d		替换的目标串
* return		    替换失败返回-1
*/
int String::Replace(char* s, char* d)
{
	if (!m_string)  //防止引用空指针
		return -1;
	int pos = 0;
	int count = 0;
	int lens = _csize(s);
	int lend = _csize(d);
	if ((pos = FindFirst(s)) == -1)      //如果该字符不存在，则替换失败
		return -1;
	do
	{
		//如果s串和d串长度相等，则直接覆盖即可
		if (lens == lend)
		{
			for (int i = 0;i < lens;i++)
				m_string[i + pos] = d[i];
		}
		else if (lens > lend)  //如果s串大于d串，则需要覆盖后往前移（填充位置）
		{
			for (int i = 0;i < lend;i++)    //覆盖
				m_string[i + pos] = d[i];
			int p = lens - lend;            //往前移动的距离
			for (int i = pos + lend;i < m_curLen;i++)    //往前移
				m_string[i] = m_string[i + p];
			m_curLen -= p;
		}
		else   //如果s串小于d串，则需要覆盖前往后移（空出位置）
		{
			int p = lend - lens;            //往后移动的距离
			for (int i = m_curLen + p;i >= pos + lens;i--)    //往后移
				m_string[i] = m_string[i - p];
			for (int i = 0;i < lend;i++)    //覆盖
				m_string[i + pos] = d[i];
			m_curLen += p;
		}
		++count;
	} while ((pos = Find(s, pos + lend)) != -1);
	return count;                              //返回成功替换的字符数
}

/*
* function			替换子串
* param    local	替换的起始位置
* param    d		替换的目标串
* return		    替换失败返回-1
*/
int String::Replace(int local, char* d)
{
	if (!m_string)  //防止引用空指针
		return -1;
	if (local < 0 || local > m_curLen - 1)
		return -1;
	int len = _csize(d);
	if (local + len >= m_maxLen)   //空间不够 重新分配
		ReAlloc();
	for (int i = 0;i < len;i++)
		m_string[i + local] = d[i];
	m_curLen += len;
	return local;
}

/*
* function			查找字符第一次出现的位置
* param    ch		要查找的字符
* return		    查找失败返回-1
*/
int String::FindFirst(char ch)
{
	if (!m_string)  //防止引用空指针
		return -1;
	for (int i = 0;i < m_curLen;i++)
		if (m_string[i] == ch)
			return i;
	return -1;
}

/*
* function			查找子串第一次出现的位置
* param    sub		要查找的子串
* return		    查找失败返回-1
*/
int String::FindFirst(char* sub)
{
	if (!m_string)  //防止引用空指针
		return -1;
	int i = 0, j = 0;
	int len = _csize(sub);
	for (;i < m_curLen;i++)
	{
		for (j = 0;j < len;j++)
			if (m_string[i + j] != sub[j])
				break;
		if (j == len)
			return i;
	}
	return -1;
}

/*
* function			查找字符最后一次出现的位置
* param    ch		要查找的字符
* return		    查找失败返回-1
*/
int String::FindLast(char ch)
{
	if (!m_string)  //防止引用空指针
		return -1;
	for (int i = m_curLen - 1;i >= 0;i--)
		if (m_string[i] == ch)
			return i;
	return -1;
}

/*
* function			查找子串最后一次出现的位置
* param    ch		要查找的子串
* return		    查找失败返回-1
*/
int String::FindLast(char* sub)
{
	if (!m_string)  //防止引用空指针
		return -1;
	int i = m_curLen - 1, j = 0;
	int len = _csize(sub);
	for (;i >= 0;i--)
	{
		for (j = 0;j < len;j++)
			if (m_string[i - j] != sub[len - 1 - j])  //从后往前比
				break;
		if (j == len)
			return i - len + 1;
	}
	return -1;
}

/*
* function			给定起始位置查找字符出现的位置
* param    ch		要查找的字符
* param    start	起始位置
* return		    查找失败返回-1
*/
int String::Find(char ch, int start)
{
	if (!m_string)  //防止引用空指针
		return -1;
	for (int i = start;i < m_curLen;i++)
		if (m_string[i] == ch)
			return i;
	return -1;
}

/*
* function			查找子串最后一次出现的位置
* param    sub		要查找的子串
* param    start	起始位置
* return		    查找失败返回-1
*/
int String::Find(char* sub, int start)
{
	if (!m_string)  //防止引用空指针
		return -1;
	int i = start, j = 0;
	int len = _csize(sub);
	for (;i < m_curLen;i++)
	{
		for (j = 0;j < len;j++)
			if (m_string[i + j] != sub[j])
				break;
		if (j == len)
			return i;
	}
	return -1;
}

/*
* function			插入字符
* param    ch		要插入的字符
* param    local    要插入的位置
* return		    无
*/
void String::Insert(char ch, int local)
{
	if (!m_string)  //防止引用空指针
		return;
	local = local < 0 ? 0 : local >= m_curLen ? m_curLen : local;
	if (m_curLen + 1 >= m_maxLen)  //如果空间不够 重新分配
		ReAlloc();
	for (int i = m_curLen;i > local;i--)
		m_string[i] = m_string[i - 1];
	m_string[local] = ch;
	m_curLen++;
}

/*
* function			插入字符串
* param    sub		要插入的字符串
* param    local    要插入的位置
* return		    无
*/
void String::Insert(char* sub, int local)
{
	if (!m_string)  //防止引用空指针
		return;
	local = local < 0 ? 0 : local >= m_curLen ? m_curLen : local;
	int len = _csize(sub);
	while (m_curLen + len >= m_maxLen)//如果空间不够 重新分配
		ReAlloc();
	for (int i = m_curLen + len - 1;i >= local;i--)
		m_string[i] = m_string[i - len];
	for (int i = 0;i < len;i++)
		m_string[i + local] = sub[i];
	m_curLen += len;
}

/*
* function			统计字符出现过的次数
* param    ch		要查找的字符
* return		    返回字符出现的次数
*/
int String::AppearTimes(char ch)
{
	if (!m_string)  //防止引用空指针
		return 0;
	int count = 0;
	for (int i = 0;i < m_curLen;i++)
		if (m_string[i] == ch)
			++count;
	return count;
}

/*
* function			统计子串出现过的次数
* param    sub		要查找的子串
* return		    返回字符出现的次数
*/
int String::AppearTimes(char* sub)
{
	if (!m_string)  //防止引用空指针
		return 0;
	int len = _csize(sub);
	int pos = 0;
	if ((pos = FindFirst(sub)) == -1)
		return 0;
	int count = 1;
	while ((pos = Find(sub, pos + len)) != -1)
		++count;
	return count;
}

/*
* function			比较两个String是否相等
* param    s1		字符串1
* param    s2		字符串2
* return		    相等返回true
*/
bool String::Equal(String& s1, String& s2)
{
	if (!s1.m_string || !s2.m_string)  //防止引用空指针
		return false;
	int len1 = s1.Size();
	int len2 = s2.Size();
	if (len1 != len2)
		return false;
	for (int i = 0;i < len1;i++)
		if (s1.m_string[i] != s2.m_string[i])
			return false;
	return true;
}

/*
* function			比较两个String是否相等
* param    s1		字符串1
* param    s2		字符串2
* return		    相等返回true
*/
bool String::Equal(const char* s1, const char* s2)
{
	if (!s1 || !s2)  //防止引用空指针
		return false;
	int len1 = _csize(s1);
	int len2 = _csize(s2);
	if (len1 != len2)
		return false;
	for (int i = 0;i < len1;i++)
		if (s1[i] != s2[i])
			return false;
	return true;
}

/*
* function			清除字符串
* return		    无
*/
void String::Clear()
{
	m_curLen = 0;
}

/*
* function			销毁字符串
* return		    无
*/
void String::Destroy()
{
	if (m_string)
		delete[] m_string;
	m_string = NULL;
	m_curLen = 0;
}

/*
* function			获取字符串
* param    str		字符串
* return		    返回data
*/
char* String::GetString()
{
	if (!m_string)  //防止引用空指针
		return NULL;
	return m_string;
}

/*
* function			打印字符串
* param    start    起始位置
* param    end      终点位置
* return		    无
*/
void String::Print(int start, int end)
{
	if (!m_string)  //防止引用空指针
		return;
	start = start<0 || start > m_curLen - 1 ? 0 : start;	//防止越界
	end = end<0 || end > m_curLen - 1 ? m_curLen : end;	//防止越界
	if (end < start)											//防止倒置
	{
		int temp = 0;
		temp = start;
		start = end;
		end = start;
	}
	for (int i = start;i < end;i++)
		cout<<m_string[i];
	cout << endl;
}
