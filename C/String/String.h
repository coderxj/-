#pragma once
#include<stdio.h>
#include<stdlib.h>
#define MAX_LEN 256    //默认最大长度是256

//字符串结构
typedef struct _string
{
	char* data;   //字符串
	int curLen;  //当前字符串长度
	int maxLen;  //最大长度
}String,*PString;

/*
* function			默认长度，空字符串,类似C++的构造函数
* return   PString  字符串结构体指针
*/
String String1();

/*
* function			可以指定字符串长度初始化结构体,类似C++的构造函数
* param    len		长度
* return   PString  字符串结构体指针
*/
String String2(int maxLen);

/*
* function			可以用字符串初始化结构体,类似C++的构造函数
* param    str		字符串
* return   PString  字符串结构体指针
*/
String String3(char* s);

/*
* function			可以用数组初始化结构体,类似C++的构造函数
* param    array	int数组
* param    arraySize数组大小 
* param    separator分隔符
* return   PString  字符串结构体指针
*/
String String4(int a[],int arraySize,char separator);

/*
* function			可以用数组初始化结构体,类似C++的构造函数
* param    array	double数组
* param    arraySize数组大小
* param    separator分隔符
* return   PString  字符串结构体指针
*/
String String5(double a[], int arraySize, char separator);

/*
* function			重新分配空间
* param    PString  字符串结构体指针
* return   int      返回分配空间的大小，失败返回-1
*/
int Realloc(PString pstr);

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
void PushRear(PString pstr,char ch);

/*
* function			添加一个字符到前面
* param    PString  字符串结构体指针
* param    char		字符
* return		    无
*/
void PushFront(PString pstr, char ch);

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
int DeleteSub1(PString pstr,int start,int end);

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
* function			替换字符
* param    PString  字符串结构体指针
* param    s		替换的源字符
* param    d		替换后的字符
* return		    替换失败返回-1
*/
int ReplaceChar1(PString pstr, char s, char d);

/*
* function			替换字符
* param    PString  字符串结构体指针
* param    local	替换的位置
* param    d		替换后的字符
* return		    替换失败返回-1
*/
int ReplaceChar2(PString pstr, int local, char d);

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
* return		    替换失败返回-1
*/
int ReplaceSubStr2(PString pstr, int local, char* d);

/*
* function			查找字符第一次出现的位置
* param    PString  字符串结构体指针
* param    ch		要查找的字符
* return		    查找失败返回-1
*/
int FindFirst(PString pstr, char ch);

/*
* function			查找字符最后一次出现的位置
* param    PString  字符串结构体指针
* param    ch		要查找的字符
* return		    查找失败返回-1
*/
int FindLast(PString pstr, char ch);

/*
* function			给定起始位置查找字符出现的位置
* param    PString  字符串结构体指针
* param    ch		要查找的字符
* param    start	起始位置
* return		    查找失败返回-1
*/
int Find(PString pstr, char ch, int start);

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
* function			查找子串最后一次出现的位置
* param    PString  字符串结构体指针
* param    sub		要查找的子串
* param    start	起始位置
* return		    查找失败返回-1
*/
int FindSub(PString pstr, char* sub,int start);

/*
* function			插入字符
* param    PString  字符串结构体指针
* param    ch		要插入的字符
* param    local    要插入的位置
* return		    无
*/
void InsertChar(PString pstr, char ch,int local);

/*
* function			插入字符串
* param    PString  字符串结构体指针
* param    sub		要插入的字符串
* param    local    要插入的位置
* return		    无
*/
void InsertSub(PString pstr, char* sub, int local);

/*
* function			统计字符出现过的次数
* param    PString  字符串结构体指针
* param    ch		要查找的字符
* return		    返回字符出现的次数
*/
int AppearTimes(PString pstr, char ch);

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
* function			计算字符串长度(窄字符)
* param    str		字符串
* return		    返回长度
*/
int _csize(char* str);

/*
* function			计算字符串长度(宽字符)
* param    str		字符串
* return		    返回长度
*/
int _wsize(wchar_t* str);

/*
* function			初始化字符串
* param    str		字符串
* parma    value    初始值
* param    len      长度
* return		    无
*/
void InitStr(char* str,int value,int len);

/*
* function			获取字符串
* param    str		字符串
* return		    返回data
*/
char* GetString(PString pstr);

/*
* function			打印字符串
* param    str		字符串
* param    start    起始位置
* param    end      终点位置
* return		    无
*/
void Print(PString pstr,int start,int end);

/*
* function			清除字符串
* param    PString  字符串结构体指针
* return		    无
*/
void Clear(PString pstr);

/*
* function			销毁字符串
* param    PString  字符串结构体指针
* return		    无
*/
void Destroy(PString pstr);
