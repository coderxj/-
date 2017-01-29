#pragma once
#include <iostream>
#include <string>
#include <stack>
using namespace std;

class Calculator   //计算器类
{
public:
	Calculator();
	~Calculator();
public:
	double GetResult(const string& infix);		//获取结果
private:
	bool IsDigit(char ch);						//判断是否是数字			  
	bool IsOperator(char ch);					//判断是否是操作符					
	int GetPriority(char op1, char op2);		//判断运算符的优先级，-1表示小于，0表示等于，1表示大于								
	double Calc(double op1, double op2, char op);//根据运算符计算两数			
	void InfixToSuffix(const string& infix, string& suffix);//中缀转后缀表达式
	double CalcSuffix(const string& suffix);				//后缀表达式计算
};

