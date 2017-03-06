/*
* author: acme
*   date: 2017-3-6
*  blogs: http://blog.csdn.net/qq_18297675
*/
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct _node
{
	char c;			//窄字节
	wchar_t w;		//宽字节
	_node* next;
}Node,*PNode;

typedef struct _string
{
	int count;		  //字符个数
	PNode headNode;   //存放数据的节点（可以理解为一个String有一个头节点，然后访问数组的时候通过这个头节点访问）
	PNode endNode;    //方便访问最后一个节点
}String,*PString;


/*
* function			默认长度，空字符串,类似C++的构造函数
* return   PString  字符串结构体指针
*/
String String1();

/*
* function			可以用字符串初始化结构体,类似C++的构造函数
* param    str		字符串
* return   PString  字符串结构体指针
*/
String String2(char* s);

/*
* function			可以用数组初始化结构体,类似C++的构造函数
* param    array	int数组
* param    arraySize数组大小
* param    separator分隔符
* return   PString  字符串结构体指针
*/
String String3(int a[], int arraySize, int separator);

/*
* function			可以用数组初始化结构体,类似C++的构造函数
* param    array	double数组
* param    arraySize数组大小
* param    separator分隔符
* return   PString  字符串结构体指针
*/
String String4(double a[], int arraySize, char separator);

/*
* function			创建结点
* param    PString  字符串结构体指针
* return   PNode    返回一个结点
*/
PNode CreateNode(int ch);

/*
* function			获取字符串大小
* param    PString  字符串结构体指针
* return   int      返回字符串大小
*/
int Size(PString pstr);

/*
* function			添加一个字符到最后
* param    PString  字符串结构体指针
* param    char		字符
* return		    无
*/
void PushRear(PString pstr, int ch);

/*
* function			添加一个字符到前面
* param    PString  字符串结构体指针
* param    char		字符
* return		    无
*/
void PushFront(PString pstr, int ch);

/*
* function			删除最后一个字符
* param    PString  字符串结构体指针
* return		    无
*/
void PopRear(PString pstr);

/*
* function			删除第一个字符
* param    PString  字符串结构体指针
* return		    无
*/
void PopFront(PString pstr);

/*
* function			删除子串
* param    PString  字符串结构体指针
* param    start	删除的起始位置
* param    end		删除的终点位置
* return		    删除失败返回-1
*/
int DeleteSub1(PString pstr, int start, int end);

/*
* function			删除子串
* param    PString  字符串结构体指针
* param    start	删除的起始位置
* param    len		要删除的长度
* return		    删除失败返回-1
*/
int DeleteSub2(PString pstr, int start, int len);

/*
* function			截取子串
* param    PString  字符串结构体指针
* param    start	截取的起始位置
* param    end		截取的终点位置
* return		    截取失败返回NULL
*/
char* SubString1(PString pstr, int start, int end);

/*
* function			截取子串
* param    PString  字符串结构体指针
* param    start	截取的起始位置
* param    len		截取的长度
* return		    截取失败返回NULL
*/
char* SubString2(PString pstr, int start, int len);

/*
* function			替换字符  (窄字符替换窄字符)
* param    PString  字符串结构体指针
* param    s		替换的源字符
* param    d		替换后的字符
* return		    替换失败返回-1
*/
int ReplaceChar1(PString pstr, char s, char d);

/*
* function			替换字符  (窄字符替换宽字符)
* param    PString  字符串结构体指针
* param    s		替换的源字符
* param    d		替换后的字符
* return		    替换失败返回-1
*/
int ReplaceChar2(PString pstr, char s, wchar_t d);

/*
* function			替换字符  (宽字符替换窄字符)
* param    PString  字符串结构体指针
* param    s		替换的源字符
* param    d		替换后的字符
* return		    替换失败返回-1
*/
int ReplaceChar3(PString pstr, wchar_t s, char d);

/*
* function			替换字符  (宽字符替换宽字符)
* param    PString  字符串结构体指针
* param    s		替换的源字符
* param    d		替换后的字符
* return		    替换失败返回-1
*/
int ReplaceChar4(PString pstr, wchar_t s, wchar_t d);

/*
* function			替换字符(窄字符)
* param    PString  字符串结构体指针
* param    local	替换的位置
* param    d		替换后的字符
* return		    替换失败返回-1
*/
int ReplaceChar5(PString pstr, int local, char d);

/*
* function			替换字符(宽字符)
* param    PString  字符串结构体指针
* param    local	替换的位置
* param    d		替换后的字符
* return		    替换失败返回-1
*/
int ReplaceChar6(PString pstr, int local, wchar_t d);

/*
* function			替换子串
* param    PString  字符串结构体指针
* param    s		替换的源串
* param    d		替换的目标串
* return		    替换失败返回-1
*/
int ReplaceSubStr1(PString pstr, char* s, char* d);

/*
* function			替换子串
* param    PString  字符串结构体指针
* param    local	替换的起始位置
* param    d		替换的目标串
* return		    替换失败返回NULL
*/
PNode ReplaceSubStr2(PString pstr, int local, char* d);

/*
* function			查找字符第一次出现的位置
* param    PString  字符串结构体指针
* param    ch		要查找的字符
* return		    查找失败返回-1
*/
int FindFirst(PString pstr, int ch);

/*
* function			查找字符最后一次出现的位置
* param    PString  字符串结构体指针
* param    ch		要查找的字符
* return		    查找失败返回-1
*/
int FindLast(PString pstr, int ch);

/*
* function			给定起始位置查找字符出现的位置
* param    PString  字符串结构体指针
* param    ch		要查找的字符
* param    start	起始位置
* return		    查找失败返回-1
*/
int Find(PString pstr, int ch, int start);

/*
* function			查找子串第一次出现的位置
* param    PString  字符串结构体指针
* param    sub		要查找的子串
* return		    查找失败返回-1
*/
int FindSubFirst(PString pstr, char* sub);

/*
* function			查找子串最后一次出现的位置
* param    PString  字符串结构体指针
* param    sub		要查找的子串
* return		    查找失败返回-1
*/
int FindSubLast(PString pstr, char* sub);

/*
* function			查找子串出现的位置
* param    PString  字符串结构体指针
* param    sub		要查找的子串
* param    start	起始位置
* return		    查找失败返回-1
*/
int FindSub(PString pstr, char* sub, int start);

/*
* function			插入字符
* param    PString  字符串结构体指针
* param    local    要插入的位置
* param    ch		要插入的字符
* return		    无
*/
void InsertChar(PString pstr, int local, int ch);

/*
* function			插入字符串
* param    PString  字符串结构体指针
* param    local    要插入的位置
* param    sub		要插入的字符串
* return		    无
*/
void InsertSub(PString pstr, int local, char* sub);

/*
* function			统计字符出现过的次数
* param    PString  字符串结构体指针
* param    ch		要查找的字符
* return		    返回字符出现的次数
*/
int AppearTimes(PString pstr, int ch);

/*
* function			统计子串出现过的次数
* param    PString  字符串结构体指针
* param    sub		要查找的子串
* return		    返回字符出现的次数
*/
int CountSubTimes(PString pstr, char* sub);

/*
* function			比较两个String是否相等
* param    PString  字符串结构体指针
* param   pstr1		字符串1
* param   pstr2		字符串2
* return		    相等返回true
*/
bool Equal(PString pstr1, PString pstr2);

/*
* function			计算字符串字节数(窄字符)
* param    str		字符串
* return		    返回长度
*/
int _cbytes(char* str);

/*
* function			计算字符串长度(窄字符)
* param    str		字符串
* return		    返回长度
*/
int _csize(char* str);

/*
* function			获取字符串
* param    PString  字符串结构体指针
* return		    返回data
*/
char* GetString(PString pstr);

/*
* function			打印字符串
* param    PString  字符串结构体指针
* param    start    起始位置
* param    end      终点位置
* return		    无
*/
void Print(PString pstr, int start, int end);

/*
* function			清除字符串
* param    PString  字符串结构体指针
* return		    无
*/
void Clear(PString pstr);

/*
* function			释放节点
* param    PString  字符串结构体指针
* param    start    释放的节点的起始位置
* param    num      释放节点的个数
* return		    无
*/
void FreeNode(PString pstr, int start, int num);

/*
* function			获取节点
* param    PString  字符串结构体指针
* param    start    获取节点的起始位置
* param    num      获取节点的个数
* return		    返回获取到的节点
*/
PNode GetNodes(PString pstr, int start, int num);  

/*
* function			初始化缓冲区
* param    buf		字符串缓冲区
* param    value    初始化的值
* param    len      缓冲区大小
* return		    无
*/
void InitBuf(char* buf, int value, int len);

/*
* function			从节点中获取到字符串
* param    nodes	字符节点
* param    num		节点个数
* return		    无
*/
char* GetStringFromNodes(PNode nodes, int num);

/*
* function			窄字符转化为宽字符
* param    ch1		第一个字节
* param    ch2		第二个字节
* return		    返回一个宽字符
*/
wchar_t CToW(char ch1, char ch2);
