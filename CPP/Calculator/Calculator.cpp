#include "Calculator.h"



Calculator::Calculator()
{
}


Calculator::~Calculator()
{
}

//判断是否是数字
bool Calculator::IsDigit(char ch)
{
	return (ch >= '0' && ch <= '9') || ch == '.' ? true : false;
}

//判断是否是操作符
bool Calculator::IsOperator(char ch)
{
	return ch == '+' || ch == '-' || ch == '*' || ch == '/' ? true : false;
}

//判断运算符的优先级，-1表示小于，0表示等于，1表示大于
int Calculator::GetPriority(char op1, char op2)
{
	if ((op1 == '+' || op1 == '-') && (op2 == '-' || op2 == '+'))
		return 0;
	else if (op1 == op2)
		return 0;
	else if ((op1 == '+' || op1 == '-') && (op2 == '*' || op2 == '/'))
		return 1;
	else if ((op1 == '*' || op1 == '/') && (op2 == '-' || op2 == '+'))
		return -1;
	else if ((op1 == '*' || op1 == '/') && (op2 == '*' || op2 == '/') && op1 != op2)
		return 0;
}

//根据运算符计算两数
double Calculator::Calc(double op1, double op2, char op)
{
	switch (op)
	{
	case '+': return op2 + op1;
	case '-': return op2 - op1;
	case '*': return op2 * op1;
	case '/': if (op1 != 0) return op2 / op1;
			  else return 0;
	default:  return 0;
	}
}

//中缀转后缀表达式
void Calculator::InfixToSuffix(const string& infix, string& suffix)
{
	stack<char> s;					//创建一个栈
	int iLen = infix.size();            //计算长度用来控制循环
	double num = 0;
	for (int i = 0;i < iLen;i++)
	{
		//1.略过空格
		if (infix[i] == ' ')
			continue;
		//2.如果是数字(包括小数)直接输出
		else if (IsDigit(infix[i]))
			suffix.push_back(infix[i]);
		//3.如果是左括号，则直接入栈
		else if (infix[i] == '(')
			s.push(infix[i]);
		//4.如果是右扩号，则出栈，直到遇到‘（’为止，并把‘（’出栈
		else if (infix[i] == ')')
		{
			while (s.top() != '(')
			{
				suffix.push_back(s.top());
				s.pop();
			}		
			s.pop();
		}
		//5.如果是+-,若栈中无元素或者栈顶有‘（’，则直接入栈，否则全部出栈(遇到'('也停止)后再入栈（因为+-运算符优先级最低）
		else if (infix[i] == '+' || infix[i] == '-')
		{
			//加一个分隔符，区分2位以上的数字
			suffix.push_back(' ');
			if (s.empty() || s.top() == '(')
				s.push(infix[i]);
			else
			{
				do
				{
					suffix.push_back(s.top());
					s.pop();
				} while (!s.empty() && s.top() != '(');
				s.push(infix[i]);
			}
		}
		//6.如果是*/,若栈顶优先级低于当前运算符，则直接入栈，否则先出栈再入栈
		else if (infix[i] == '*' || infix[i] == '/')
		{
			//加一个分隔符，区分2位以上的数字
			suffix.push_back(' ');
			//当前运算符的优先级大于栈顶的优先级的时候直接入栈
			if (GetPriority(s.top(), infix[i]) == 1)
				s.push(infix[i]);
			else
			{   //当栈不为空，且当前运算符的优先级小于等于栈顶的优先级，栈顶不是‘（’，才能出栈
				while (!s.empty() && (GetPriority(s.top(), infix[i]) < 1) && s.top() != '(')
				{
					suffix.push_back(s.top());
					s.pop();
				}
				s.push(infix[i]);
			}
		}
	}
	//7.最后把栈中的运算符都出栈
	while (!s.empty())
	{
		suffix.push_back(s.top());
		s.pop();
	}
}

//后缀表达式计算
double Calculator::CalcSuffix(const string& suffix)
{
	stack<double> s;   //创建一个栈
	int iLen = suffix.size();			 //计算长度用来控制循环
	double result = 0;                   //表达式最终结果
	string temp;						 //临时存放数字
	for (int i = 0;i < iLen;i++)
	{
		//1.扫描到数字则入栈
		if (IsDigit(suffix[i]))
			temp.push_back(suffix[i]);
		else if (suffix[i] == ' ')      //如果遇到分隔符，则把temp转换为数字，压入栈
		{
			if (temp.size() > 0)   //防止运算符后面跟分隔符，所以判断一下temp里面是否有数字
			{
				s.push(atof(temp.c_str()));
				temp.clear();
			}
		}
		//2.扫描到运算符则将栈顶的两个元素依次出栈做相应的运算,把结果再入栈
		else if (IsOperator(suffix[i]))
		{
			//防止数字后面直接跟运算符，所以这里也要判断一下temp是否还有数字没有提取出来
			if (temp.size() > 0)
			{
				s.push(atof(temp.c_str()));
				temp.clear();
			}
			double op1 = s.top();
			s.pop();
			double op2 = s.top();
			s.pop();
			result = Calc(op1, op2, suffix[i]);
			s.push( result);
		}
	}
	return s.top();
}

//获取结果
double Calculator::GetResult(const string& infix)
{
	string suffix;
	InfixToSuffix(infix, suffix);
	return CalcSuffix(suffix);
}
