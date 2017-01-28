/*
* author: acme
*   date: 2017-1-28
*  blogs: http://blog.csdn.net/qq_18297675
*/
#include "LinkStack.h"

//判断是否是数字
bool IsDigit(char ch)
{
	return (ch >= '0' && ch <= '9') || ch == '.' ? true : false;
}

//判断是否是操作符
bool IsOperator(char ch)
{
	return ch == '+' || ch == '-' || ch == '*' || ch == '/'? true : false;
}

//判断运算符的优先级，-1表示小于，0表示等于，1表示大于
int GetPriority(char op1 , char op2)
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
		return -1;
}

//根据运算符计算两数
double Calc(double op1, double op2, char op)
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
void InfixToSuffix(const char* infix, char* suffix)
{
	LPLINKSTACK stack = CreateStack();   //创建一个栈
	int iLen = strlen(infix);            //计算长度用来控制循环
	double num = 0;
	int k = 0;
	for (int i = 0;i < iLen;i++)
	{
		//1.略过空格
		if(infix[i] == ' ')
			continue;
		//2.如果是数字(包括小数)直接输出
		else if (IsDigit(infix[i]))   
			suffix[k++] = infix[i];
		//3.如果是左括号，则直接入栈
		else if (infix[i] == '(')
			PushC(stack, infix[i]);
		//4.如果是右扩号，则出栈，直到遇到‘（’为止，并把‘（’出栈
		else if (infix[i] == ')')
		{
			while (GetTopC(stack) != '(')	
				suffix[k++] = PopC(stack);
			Pop(stack);
		}
		//5.如果是+-,若栈中无元素或者栈顶有‘（’，则直接入栈，否则全部出栈(遇到'('也停止)后再入栈（因为+-运算符优先级最低）
		else if (infix[i] == '+' || infix[i] == '-')
		{
			//加一个分隔符，区分2位以上的数字
			suffix[k++] = ' ';
			if (IsEmpty(stack) || GetTopC(stack) == '(')
				PushC(stack, infix[i]);
			else
			{
				do
				{
					suffix[k++] = PopC(stack);
				} while (!IsEmpty(stack) && GetTopC(stack) != '(');
				PushC(stack, infix[i]);
			}
		}
		//6.如果是*/,若栈顶优先级低于当前运算符，则直接入栈，否则先出栈再入栈
		else if (infix[i] == '*' || infix[i] == '/')
		{
			//加一个分隔符，区分2位以上的数字
			suffix[k++] = ' ';
			//当前运算符的优先级大于栈顶的优先级的时候直接入栈
			if (GetPriority(GetTopC(stack), infix[i]) == 1)
				PushC(stack, infix[i]);
			else
			{   //当栈不为空，且当前运算符的优先级小于等于栈顶的优先级，栈顶不是‘（’，才能出栈
				while (!IsEmpty(stack) && (GetPriority(GetTopC(stack), infix[i]) < 1) && GetTopC(stack) != '(')
					suffix[k++] = PopC(stack);
				PushC(stack, infix[i]);
			}
		}
	}
	//7.最后把栈中的运算符都出栈
	while (!IsEmpty(stack))
		suffix[k++] = PopC(stack);
}

//后缀表达式计算
double CalcSuffix(const char* suffix)
{
	LPLINKSTACK stack = CreateStack();   //创建一个栈
	int iLen = strlen(suffix);			 //计算长度用来控制循环
	double result = 0;                   //表达式最终结果
	char temp[32] = "";                  //临时存放数字
	int k = 0;
	for (int i = 0;i < iLen;i++)
	{
		//1.扫描到数字则入栈
		if (IsDigit(suffix[i]))
			temp[k++] = suffix[i];
		else if (suffix[i] == ' ')      //如果遇到分隔符，则把temp转换为数字，压入栈
		{
			if (k > 0)   //防止运算符后面跟分隔符，所以判断一下temp里面是否有数字
			{
				PushD(stack, atof(temp));
				memset(temp, 0, sizeof(temp));
				k = 0;
			}
		}
		//2.扫描到运算符则将栈顶的两个元素依次出栈做相应的运算,把结果再入栈
		else if (IsOperator(suffix[i]))
		{
			//防止数字后面直接跟运算符，所以这里也要判断一下temp是否还有数字没有提取出来
			if (k > 0)
			{
				PushD(stack, atof(temp));
				memset(temp, 0, sizeof(temp));
				k = 0;
			}
			double op1 = PopD(stack);
			double op2 = PopD(stack);
			result = Calc(op1,op2 , suffix[i]);
			PushD(stack, result);
		}
	}
	return PopD(stack);
}

int main()
{
	char suffix[32] = "";
	InfixToSuffix("2*(2 + 2 -2 +3 -3)*2*3", suffix);
	printf("%s\n", suffix);
	printf("%lf\n", CalcSuffix(suffix));
	return 0;
}
