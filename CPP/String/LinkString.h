/*
* author: acme
*   date: 2017-3-6
*  blogs: http://blog.csdn.net/qq_18297675
*/
#pragma once
#include <iostream>
#include <locale.h>
using namespace std;

class String
{
private:  //节点类
		class Node
		{
		public:
			Node(int ch = 0, Node* next = nullptr, Node* pre = nullptr)
				:c(0), w(0), next(next), pre(pre)
			{
				if (ch > 255)
					w = (wchar_t)ch;
				else
					c = (char)ch;
			}
		private:
			Node* next;   //后继节点
			Node* pre;    //前驱节点
			char c;
			wchar_t w;
			friend class String;
		};
public:		
	String();											//默认空串
	String(char* s);									//可用指定字符串初始化
	template<typename T>
	String(T a[], int arraySize, int separator);		//可用数组来初始化String

	~String();
public:
	int Size();											//获取字符串大小
	int Bytes();										//获取字符串字节数
	bool IsEmpty();                                     //是否为空
	void PushFront(int ch);							    //添加一个字符到前面
	void PushRear(int ch);								//添加一个字符到最后
	void PushFront(char* s);							//添加字符串到前面
	void PushRear(char* s);								//添加字符串到后面
	void PopRear(int n = 1);							//删除后面n个字符
	void PopFront(int n = 1);                           //删除前面n个字符
	int Delete(int local);								//删除指定位置字符
	int DeleteSub(int start, int end);					//根据指定范围删除子串
	int DeleteSubLen(int start, int len);				//根据指定长度删除子串
	char* SubString(int start, int end);				//根据指定范围截取子串
	char* SubStringLen(int start, int len);				//根据指定长度截取子串
	int Replace(int s, int d);							//根据给定字符替换字符
	int ReplaceLocal(int local, int d);                 //根据指定位置替换字符
	int Replace(char* s, char* d);                      //根据给字符串替换字符串
	Node* Replace(int local, char* d);                  //根据给定位置替换字符串
	int FindFirst(int ch);                              //查找字符第一次出现的位置
	int FindLast(int ch);                               //查找字符最后一次出现的位置 
	int Find(int ch, int start);						//根据给定起始位置查找字符出现的位置
	int FindFirst(char* s);                             //查找字符串第一次出现的位置
	int FindLast(char* s);                              //查找字符串最后一次出现的位置 
	int Find(char* s, int start);						//根据给定起始位置查找字符串出现的位置
	void Insert(int local, int ch,int n = 1);			//在指定位置插入n个字符
	void Insert(int local, char* sub,int n = 1);        //在指定位置插入n个字符串
	int AppearTimes(int ch);							//统计字符出现的次数							
	int AppearTimes(char* s);							//统计字符串出现的次数
	bool Equal(String& s);								//比较两个String是否相等
	bool Equal(const char* s);							//比较两个String是否相等
	char* GetString();									//获取字符串
	void Print(int start, int end);						//打印字符串
	void Clear();										//清空字符串
	void Reverse();										//逆转字符串
	void ConCat(char* s);								//连接字符串
	void ConCat(String& s);								//连接字符串
	void Assign(char* s);                               //赋值
	void Assign(String& s);                             //赋值
	int GetAt(int iPos);                                //获取指定位置的值 
	String& operator +(String& s);                      //重载+号运算符      
	String& operator +(char* s);						//重载+号运算符     
	String& operator =(String& s);                      //重载=号运算符 
	String& operator =(char* s);						//重载=号运算符
	String& operator +=(String& s);                     //重载+=号运算符 
	String& operator +=(char* s);						//重载+=号运算符
	int operator [](int iPos);							//重载[]运算符   
private:
	Node* CreateNode(int ch = 0);                        //创建节点
	int _cbytes(char* str);                              //计算字符串字节数(窄字符)
	int _csize(char* str);								 //计算字符串长度(窄字符)
	void FreeNode(int start, int num);					 //释放节点
	Node* GetNodes(int start, int num);					 //获取节点
	void InitBuf(char* buf, int value, int len);		 //初始化缓冲区
	char* GetStringFromNodes(Node* nodes, int num);		 //从节点中获取到字符串
	wchar_t CToW(char ch1, char ch2);					 //窄字符转化为宽字符
	char* WToC(wchar_t ch);								 //宽字符转化为窄字符
	Node* GetNode(int start);                            //获取起始位置的那个节点
private:
	Node* m_head;
	Node* m_tail;
	int m_count;
};

/*
* function			可以用数组初始化String
* param    array	int数组
* param    arraySize数组大小
* param    separator分隔符
* return   String	字符串类
*/
template<typename T>
String::String(T a[], int arraySize, int separator)
{
	m_head = new Node();    //创建头节点
	m_tail = new Node();    //创建尾节点
	m_count = 0;
	String s;
	for (int i = 0;i < arraySize;i++)
	{
		char buf[64] = "";
		if(s.Equal(typeid(T).name(),"int"))
			sprintf(buf, "%d", a[i]);
		else if(s.Equal(typeid(T).name(), "double"))
			sprintf(buf, "%lf", a[i]);
		int len = _csize(buf);
		for (int j = 0;j < len;j++)
			PushRear(buf[j]);
		if (i != arraySize - 1)
			PushRear(separator);   //插入分隔符
	}

	return *pstr;
}
