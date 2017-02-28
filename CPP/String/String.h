#pragma once
#include<iostream>
using namespace std;
#define MAX_LEN 256    //默认最大长度是256

class String 
{
public:
	String();													//默认构造
	String(int maxLen);											//指定字符串最大长度
	String(char* s);											//指定字符串
	template<typename T>
	String(T a[], int arraySize, char separator = ' ');         //根据给定数组初始化字符串
	~String();

public:
	int Size();										//获取字符串大小
	void PushRear(char ch);							//添加一个字符到最后
	void PushRear(char* sub);						//添加字符串到最后
	void PushFront(char ch);						//添加一个字符到前面
	void PushFront(char* sub);						//添加字符串到前面
	void PopRear(int n = 1);						//删除最后n个字符
	void PopFront(int n = 1 );						//删除前面n个字符
	int DeleteSub(int start, int end);				//根据范围删除子串
	int DeleteSubLen(int start, int len);           //根据起始位置和长度删除子串
	char* SubString(int start, int end);            //根据范围截取子串
	char* SubStringLen(int start, int len);         //根据起始位置和长度截取子串
	int Replace(char s, char d);					//替换字符(符合的都会替换)
	int Replace(int local, char d);					//替换指定位置字符
	int Replace(char* s, char* d);					//替换子串(符合的都会替换)
	int Replace(int local, char* d);				//替换指定位置子串
	int FindFirst(char ch);                         //查找字符第一次出现的位置
	int FindFirst(char* sub);                       //查找子串第一次出现的位置
	int FindLast(char ch);                          //查找字符最后一次出现的位置
	int FindLast(char* sub);                        //查找子串最后一次出现的位置
	int Find(char ch, int start);                   //给定起始位置查找字符出现的位置
	int Find(char* sub, int start);                 //给定起始位置查找子串出现的位置
	void Insert(char ch, int local);                //插入字符
	void Insert(char* sub, int local);              //插入子串
	int AppearTimes(char ch);                       //统计字符出现过的次数
	int AppearTimes(char* sub);                     //统计子串出现过的次数
	bool Equal(String& s1,String& s2);            //比较两个String是否相等
	bool Equal(const char* s1, const char* s2);   //比较两个String是否相等
	char* GetString();                              //获取字符串
	void Print(int start, int end);					//打印字符串
	void Clear();                                   //清除字符串
	void Destroy();                                 //销毁字符串
private: 
	int ReAlloc();									//重新分配空间
	void InitStr(char* str, int value, int len);	//初始化字符串
	int _csize(const char* str);					//计算字符串长度(窄字符)
	int _wsize(const wchar_t* str);					//计算字符串长度(宽字符)
private:
	char* m_string;   
	int m_curLen;
	int m_maxLen;
};

/*
*  模板函数要和类声明写在同一个文件下
*/
template<typename T>
String::String(T a[], int arraySize, char separator)
{
	m_string = new char[MAX_LEN + arraySize];		//为数据区分配空间
	InitStr(m_string, 0, MAX_LEN);					//初始化字符串
	m_curLen = 0;
	m_maxLen = MAX_LEN + arraySize;					//串的最大长度默认为MAX_LEN
	String s;
	for (int i = 0;i < arraySize;i++)
	{
		char buf[64] = "";
		if(s.Compare(typeid(T).name() , "int"))
			sprintf_s(buf, "%d", a[i]);
		else if(s.Compare(typeid(T).name(), "double"))
			sprintf_s(buf, "%lf", a[i]);
		else
			sprintf_s(buf, "%s", a[i]);
		int len = _csize(buf);
		for (int j = 0;j < len;j++)
			m_string[m_curLen + j] = buf[j];
		if (i != arraySize - 1)
			m_string[m_curLen + len] = separator;   //插入分隔符
		m_curLen += len + 1;
	}
}
