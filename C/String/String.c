#include "String.h"


/*
* function			默认长度，空字符串,类似C++的构造函数
* return   PString  字符串结构体指针
*/
String String1()
{
	String str;										  //为结构体分配空间
	str.data = (char*)malloc(sizeof(char)*MAX_LEN);   //为数据区分配空间
	InitStr(str.data, 0, MAX_LEN);					  //初始化字符串	
	str.curLen = 0;                                   //当前串长度为0
	str.maxLen = MAX_LEN;                             //串的最大长度默认为MAX_LEN
	return str;
}

/*
* function			可以指定字符串长度初始化结构体,类似C++的构造函数
* param    len		长度
* return   PString  字符串结构体指针
*/
String String2(int maxLen)
{
	String str;										//为结构体分配空间
	str.data = (char*)malloc(sizeof(char)*maxLen);	//为数据区分配空间
	InitStr(str.data, 0, maxLen);					//初始化字符串	
	str.curLen = 0;                                 //当前串长度为0
	str.maxLen = maxLen;							//串的最大长度为用户指定的maxLen
	return str;
}

/*
* function			可以用字符串初始化结构体,类似C++的构造函数
* param    str		字符串
* return   String	字符串结构体
*/
String String3(char* s)
{
	String str;		//为结构体分配空间
	str.data = (char*)malloc(sizeof(char)*MAX_LEN);		//为数据区分配空间
	InitStr(str.data, 0, MAX_LEN);						//初始化字符串
	str.curLen = _csize(s);								//当前串长度为str的长度
	str.maxLen = MAX_LEN;								//串的最大长度默认为MAX_LEN
	for (int i = 0;i < str.curLen;i++)
		str.data[i] =  s[i];
	return str;
}

/*
* function			可以用数组初始化结构体,类似C++的构造函数
* param    array	int数组
* param    arraySize数组大小
* param    separator分隔符
* return   PString  字符串结构体指针
*/
String String4(int a[], int arraySize, char separator)
{
	String str;		//为结构体分配空间
	str.data = (char*)malloc(sizeof(char)*MAX_LEN + arraySize);		//为数据区分配空间
	InitStr(str.data, 0, MAX_LEN);						//初始化字符串
	str.curLen = 0;
	str.maxLen = MAX_LEN + arraySize;								//串的最大长度默认为MAX_LEN
	for (int i = 0;i < arraySize;i++)
	{
		char buf[64] = "";
		sprintf(buf, "%d", a[i]);
		int len = _csize(buf);
		for (int j = 0;j < len;j++)
			str.data[str.curLen + j] = buf[j];
		if( i != arraySize - 1)
			str.data[str.curLen + len] = separator;   //插入分隔符
		str.curLen += len + 1;
	}
	return str;
}

/*
* function			可以用数组初始化结构体,类似C++的构造函数
* param    array	double数组
* param    arraySize数组大小
* param    separator分隔符
* return   PString  字符串结构体指针
*/
String String5(double a[], int arraySize, char separator)
{
	String str;		//为结构体分配空间
	str.data = (char*)malloc(sizeof(char)*MAX_LEN + arraySize);		//为数据区分配空间
	InitStr(str.data, 0, MAX_LEN);						//初始化字符串
	str.curLen = 0;
	str.maxLen = MAX_LEN + arraySize;								//串的最大长度默认为MAX_LEN
	for (int i = 0;i < arraySize;i++)
	{
		char buf[64] = "";
		sprintf(buf, "%lf", a[i]);
		int len = _csize(buf);
		for (int j = 0;j < len;j++)
			str.data[str.curLen + j] = buf[j];
		if (i != arraySize - 1)
			str.data[str.curLen + len] = separator;   //插入分隔符
		str.curLen += len + 1;
	}
	return str;
}

/*
* function			重新分配空间
* param    PString  字符串结构体指针
* return   int      返回分配空间的大小，失败返回-1
*/
int Realloc(PString pstr)
{
	if (!pstr->data)  //防止引用空指针
		return -1;
	int len = pstr->maxLen;
	char* temp = (char*)malloc(sizeof(char)*len);
	for (int i = 0;i < len;i++)                   //将数据暂存起来
		temp[i] = pstr->data[i];
	pstr->maxLen *= 2;    //扩大为原来的两倍
	pstr->data = (char*)malloc(sizeof(char)*pstr->maxLen);
	InitStr(pstr->data, 0, pstr->maxLen);               //初始化
	for (int i = 0;i < len;i++)                   //将数据暂存起来
		pstr->data[i] = temp[i];                  //恢复数据 
	free(temp);
	return pstr->maxLen;
}

/*
* function			获取字符串大小
* param    PString  字符串结构体指针
* return   int      返回字符串大小
*/
int Size(PString pstr)
{
	if (!pstr->data)  //防止引用空指针
		return -1;
	return pstr->curLen;
}

/*
* function			添加一个字符到最后
* param    PString  字符串结构体指针
* param    char		字符
* return		    无
*/
void PushRear(PString pstr, char ch)
{
	if (!pstr->data)  //防止引用空指针
		return;
	if (pstr->curLen == pstr->maxLen)  //如果空间满了 需要重新分配
		Realloc(pstr);
	pstr->data[pstr->curLen++] = ch;
}

/*
* function			添加一个字符到前面
* param    PString  字符串结构体指针
* param    char		字符
* return		    无
*/

void PushFront(PString pstr, char ch)
{
	if (!pstr->data)  //防止引用空指针
		return;
	if (pstr->curLen == pstr->maxLen)  //如果空间满了 需要重新分配
		Realloc(pstr);
	for (int i = pstr->curLen;i > 0;i--)
		pstr->data[i] = pstr->data[i - 1];
	pstr->data[0] = ch;
	pstr->curLen++;
}

/*
* function			删除最后一个字符
* param    PString  字符串结构体指针
* return		    无
*/
void PopRear(PString pstr)
{
	if(pstr->curLen > 0)
		pstr->curLen--;
}

/*
* function			删除第一个字符
* param    PString  字符串结构体指针
* return		    无
*/
void PopFront(PString pstr)
{
	if (!pstr->data)  //防止引用空指针
		return;
	for (int i = 0;i < pstr->curLen - 1;i++)
		pstr->data[i] = pstr->data[i + 1];
	pstr->curLen--;
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
	if (!pstr->data)  //防止引用空指针
		return -1;
	if (start < 0 || start > pstr->curLen - 1 || end < 0 ||
		end >  pstr->curLen - 1 || end < start)
		return -1;
	int len = end - start;
	pstr->curLen -= len;
	for (int i = start;i <= pstr->curLen;i++)
		pstr->data[i] = pstr->data[i + len + 1];
	return len + 1;
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
	if (!pstr->data)  //防止引用空指针
		return -1;
	if (start < 0 || start > pstr->curLen - 1)
		return -1;
	if (start + len > pstr->curLen)
		len = pstr->curLen - start;
	pstr->curLen -= len;
	for (int i = start;i <= pstr->curLen;i++)
		pstr->data[i] = pstr->data[i + len];
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
	if (!pstr->data)  //防止引用空指针
		return NULL;
	if (start < 0 || start > pstr->curLen - 1 || end < 0 ||
		end >  pstr->curLen - 1 || end < start)
		return NULL;
	char* sub = (char*)malloc(sizeof(char)*(end - start));
	for (int i = start; i <= end;i++)
		sub[i] = pstr->data[i];
	sub[end - start + 1] = '\0';   //最后要记得加上‘\0’结束符，不然输出的时候会有乱码出来
	return sub;
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
	if (!pstr->data)  //防止引用空指针
		return NULL;
	if (start < 0 || start > pstr->curLen - 1)
		return NULL;
	if (start + len > pstr->curLen)
		len = pstr->curLen;
	char* sub = (char*)malloc(sizeof(char)*(len));
	for (int i = start; i <= start + len;i++)
		sub[i] = pstr->data[i];
	sub[len] = '\0';   //最后要记得加上‘\0’结束符，不然输出的时候会有乱码出来
	return sub;
}

/*
* function			替换字符
* param    PString  字符串结构体指针
* param    s		替换的源字符
* param    d		替换后的字符
* return		    替换失败返回-1
*/
int ReplaceChar1(PString pstr, char s, char d)
{
	if (!pstr->data)  //防止引用空指针
		return -1;
	int pos = 0;
	int count = 0;
	if ((pos = FindFirst(pstr, s)) == -1)      //如果该字符不存在，则替换失败
		return -1;
	do 
	{
		pstr->data[pos] = d;
		++count;
	} while ((pos = Find(pstr, s, pos + 1)) != -1);
	return count;                              //返回成功替换的字符数
}

/*
* function			替换字符
* param    PString  字符串结构体指针
* param    local	替换的位置
* param    d		替换后的字符
* return		    替换失败返回-1
*/
int ReplaceChar2(PString pstr, int local, char d)
{
	if (!pstr->data)  //防止引用空指针
		return -1;
	if (local < 0 || local > pstr->curLen - 1)
		return -1;
	pstr->data[local] = d;
	return local;
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
	if (!pstr->data)  //防止引用空指针
		return -1;
	int pos = 0;
	int count = 0;
	int lens = _csize(s);
	int lend = _csize(d);
	if ((pos = FindSubFirst(pstr, s)) == -1)      //如果该字符不存在，则替换失败
		return -1;
	do
	{
		//如果s串和d串长度相等，则直接覆盖即可
		if (lens == lend)
		{
			for (int i = 0;i < lens;i++)
				pstr->data[i + pos] = d[i];
		}
		else if (lens > lend)  //如果s串大于d串，则需要覆盖后往前移（填充位置）
		{  
			for (int i = 0;i < lend;i++)    //覆盖
				pstr->data[i + pos] = d[i];
			int p = lens - lend;            //往前移动的距离
			for (int i = pos + lend;i < pstr->curLen;i++)    //往前移
				pstr->data[i] = pstr->data[i + p];
			pstr->curLen -= p;
		}
		else   //如果s串小于d串，则需要覆盖前往后移（空出位置）
		{
			int p = lend - lens;            //往后移动的距离
			for (int i = pstr->curLen + p;i >=  pos + lens;i--)    //往后移
				pstr->data[i] = pstr->data[i - p];
			for (int i = 0;i < lend;i++)    //覆盖
				pstr->data[i + pos] = d[i];
			pstr->curLen += p;
		}
		++count;
	} while ((pos = FindSub(pstr, s, pos + lend)) != -1);
	return count;                              //返回成功替换的字符数
}

/*
* function			替换子串
* param    PString  字符串结构体指针
* param    local	替换的起始位置
* param    d		替换的目标串
* return		    替换失败返回-1
*/
int ReplaceSubStr2(PString pstr, int local, char* d)
{
	if (!pstr->data)  //防止引用空指针
		return -1;
	if (local < 0 || local > pstr->curLen - 1)
		return -1;
	int len = _csize(d);
	if (local + len >= pstr->maxLen)   //空间不够 重新分配
		Realloc(pstr);
	for (int i = 0;i < len;i++)
		pstr->data[i + local] = d[i];
	pstr->curLen += len;
	return local;
}

/*
* function			查找字符第一次出现的位置
* param    PString  字符串结构体指针
* param    ch		要查找的字符
* return		    查找失败返回-1
*/
int FindFirst(PString pstr, char ch)
{
	if (!pstr->data)  //防止引用空指针
		return -1;
	for (int i = 0;i < pstr->curLen;i++)
		if (pstr->data[i] == ch)
			return i;
	return -1;
}

/*
* function			查找字符最后一次出现的位置
* param    PString  字符串结构体指针
* param    ch		要查找的字符
* return		    查找失败返回-1
*/
int FindLast(PString pstr, char ch)
{
	if (!pstr->data)  //防止引用空指针
		return -1;
	for (int i = pstr->curLen - 1;i >= 0;i--)
		if (pstr->data[i] == ch)
			return i;
	return -1;
}

/*
* function			给定起始位置查找字符出现的位置
* param    PString  字符串结构体指针
* param    ch		要查找的字符
* param    start	起始位置
* return		    查找失败返回-1
*/
int Find(PString pstr, char ch, int start)
{
	if (!pstr->data)  //防止引用空指针
		return -1;
	for (int i = start;i < pstr->curLen;i++)
		if (pstr->data[i] == ch)
			return i;
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
	if (!pstr->data)  //防止引用空指针
		return -1;
	int i = 0,j = 0;
	int len = _csize(sub);
	for (;i < pstr->curLen;i++)
	{	
		for (j = 0;j < len;j++)
			if (pstr->data[i + j] != sub[j])
				break;
		if (j == len)
			return i;
	}
	return -1;
}

/*
* function			查找子串最后一次出现的位置
* param    PString  字符串结构体指针
* param    ch		要查找的子串
* return		    查找失败返回-1
*/
int FindSubLast(PString pstr, char* sub)
{
	if (!pstr->data)  //防止引用空指针
		return -1;
	int i = pstr->curLen - 1, j = 0;
	int len = _csize(sub);
	for (;i >= 0 ;i--)
	{
		for (j = 0;j < len;j++)
			if (pstr->data[i - j] != sub[len - 1- j])  //从后往前比
				break;
		if (j == len)
			return i - len + 1;
	}
	return -1;
}

/*
* function			查找子串最后一次出现的位置
* param    PString  字符串结构体指针
* param    sub		要查找的子串
* param    start	起始位置
* return		    查找失败返回-1
*/
int FindSub(PString pstr, char* sub, int start)
{
	if (!pstr->data)  //防止引用空指针
		return -1;
	int i = start, j = 0;
	int len = _csize(sub);
	for (;i < pstr->curLen;i++)
	{
		for (j = 0;j < len;j++)
			if (pstr->data[i + j] != sub[j])
				break;
		if (j == len)
			return i;
	}
	return -1;
}

/*
* function			插入字符
* param    PString  字符串结构体指针
* param    ch		要插入的字符
* param    local    要插入的位置
* return		    无
*/
void InsertChar(PString pstr, char ch, int local)
{
	if (!pstr->data)  //防止引用空指针
		return;
	local = local < 0 ? 0 : local >= pstr->curLen ? pstr->curLen : local;
	if (pstr->curLen + 1 >= pstr->maxLen)  //如果空间不够 重新分配
		Realloc(pstr);
	for (int i = pstr->curLen;i > local;i--)
		pstr->data[i] = pstr->data[i - 1];
	pstr->data[local] = ch;
	pstr->curLen++;
}

/*
* function			插入字符串
* param    PString  字符串结构体指针
* param    sub		要插入的字符串
* param    local    要插入的位置
* return		    无
*/
void InsertSub(PString pstr, char* sub, int local)
{
	if (!pstr->data)  //防止引用空指针
		return;
	local = local < 0 ? 0 : local >= pstr->curLen ? pstr->curLen : local;
	int len = _csize(sub);
	while (pstr->curLen + len >= pstr->maxLen)//如果空间不够 重新分配
		Realloc(pstr);
	for (int i = pstr->curLen + len - 1;i >= local;i--)
		pstr->data[i] = pstr->data[i - len];
	for (int i = 0;i < len;i++)
		pstr->data[i + local] = sub[i];
	pstr->curLen += len;
}

/*
* function			统计字符出现过的次数
* param    PString  字符串结构体指针
* param    ch		要查找的字符
* return		    返回字符出现的次数
*/
int AppearTimes(PString pstr, char ch)
{
	if (!pstr->data)  //防止引用空指针
		return 0;
	int count = 0;
	for (int i = 0;i < pstr->curLen;i++)
		if (pstr->data[i] == ch)
			++count;
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
	if (!pstr->data)  //防止引用空指针
		return 0;
	int len = _csize(sub);
	int pos = 0;
	if ((pos = FindSubFirst(pstr, sub)) == -1)
		return 0;
	int count = 1;
	while ((pos = FindSub(pstr, sub, pos + len)) != -1)
		++count;
	return count;
}

/*
* function			比较两个String是否相等
* param    PString  字符串结构体指针
* param    str1		字符串1
* param    str2		字符串2
* return		    相等返回true
*/
bool Equal(PString pstr1, PString pstr2)
{
	if (!pstr1->data || !pstr2->data)  //防止引用空指针
		return false;
	int len1 = Size(pstr1);
	int len2 = Size(pstr2);
	if (len1 != len2)
		return false;
	for (int i = 0;i < len1;i++)
		if (pstr1->data[i] != pstr2->data[i])
			return false;
	return true;
}

/*
* function			清除字符串
* param    PString  字符串结构体指针
* return		    无
*/
void Clear(PString pstr)
{
	pstr->curLen = 0;
}

/*
* function			销毁字符串
* param    PString  字符串结构体指针
* return		    无
*/
void Destroy(PString pstr)
{
	if(pstr->data)
		free(pstr->data);
	pstr->data = NULL;
	pstr->curLen = 0;
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
* function			计算字符串长度(宽字符)
* param    str		字符串
* return		    返回长度
*/
int _wsize(wchar_t* str)
{
	if (!str) return 0;
	int len = 0;
	while (*str++)
		++len;
	return len;
}

/*
* function			初始化字符串
* param    str		字符串
* parma    value    初始值
* param    len      长度
* return		    无
*/
void InitStr(char* str, int value, int len)
{
	for (int i = 0;i < len;i++)
		str[i] = value;
}

/*
* function			获取字符串
* param    str		字符串
* return		    返回data
*/
char* GetString(PString pstr)
{
	if (!pstr->data)  //防止引用空指针
		return NULL;
	return pstr->data;
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
	if (!pstr->data)  //防止引用空指针
		return;
	start = start<0 || start > pstr->curLen - 1 ? 0 : start;	//防止越界
	end = end<0 || end > pstr->curLen - 1 ? pstr->curLen : end;	//防止越界
	if (end < start)											//防止倒置
	{
		int temp = 0;
		temp = start;
		start = end;
		end = start;
	}
	for (int i = start;i < end;i++)
		printf("%c", pstr->data[i]);
	printf("\n");
}
