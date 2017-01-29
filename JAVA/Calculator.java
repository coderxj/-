/*
* author: acme
*   date: 2017-1-29
*  blogs: http://blog.csdn.net/qq_18297675
*/

import java.util.Stack;

public class Calculator {

	public static void main(String[] args) throws Exception {
		Calculator calc = new Calculator();
		System.out.println(calc.GetResult("2+2+2*((3-2/1+2*3.5)-1.5)*2"));
	}
	
	//获取结果
	public double GetResult(String infix) throws Exception {	
		StringBuffer suffix = new StringBuffer();
		InfixToSuffix(infix, suffix);
		return CalcSuffix(suffix.toString());
	}
	
	
	//中缀转后缀表达式
	private void InfixToSuffix(String infix, StringBuffer suffix) throws Exception {
		Stack<Character> s = new Stack<>();	//创建一个栈
		int iLen = infix.length();            //计算长度用来控制循环
		double num = 0;
		for (int i = 0;i < iLen;i++) {
			//1.略过空格
			if (infix.charAt(i) == ' ')
				continue;
			//2.如果是数字(包括小数)直接输出
			else if (IsDigit(infix.charAt(i)))
				suffix.append(infix.charAt(i));
			//3.如果是左括号，则直接入栈
			else if (infix.charAt(i) == '(')
				s.push(infix.charAt(i));
			//4.如果是右扩号，则出栈，直到遇到‘（’为止，并把‘（’出栈
			else if (infix.charAt(i) == ')') {
				while (s.peek() != '(') {
					suffix.append(s.peek());
					s.pop();
				}		
				s.pop();
			}
			//5.如果是+-,若栈中无元素或者栈顶有‘（’，则直接入栈，否则全部出栈(遇到'('也停止)后再入栈（因为+-运算符优先级最低）
			else if (infix.charAt(i) == '+' || infix.charAt(i) == '-') {
				//加一个分隔符，区分2位以上的数字
				suffix.append(' ');
				if (s.empty() || s.peek() == '(')
					s.push(infix.charAt(i));
				else {
					do {
						suffix.append(s.peek());
						s.pop();
					} while (!s.empty() && s.peek() != '(');
					s.push(infix.charAt(i));
				}
			}
			//6.如果是*/,若栈顶优先级低于当前运算符，则直接入栈，否则先出栈再入栈
			else if (infix.charAt(i) == '*' || infix.charAt(i) == '/'){
				//加一个分隔符，区分2位以上的数字
				suffix.append(' ');
				//当前运算符的优先级大于栈顶的优先级的时候直接入栈
				if (GetPriority(s.peek(), infix.charAt(i)) == 1)
					s.push(infix.charAt(i));
				else {   //当栈不为空，且当前运算符的优先级小于等于栈顶的优先级，栈顶不是‘（’，才能出栈
					while (!s.empty() && (GetPriority(s.peek(), infix.charAt(i)) < 1) && s.peek() != '(') {
						suffix.append(s.peek());
						s.pop();
					}
					s.push(infix.charAt(i));
			}
		}
	}
		//7.最后把栈中的运算符都出栈
		while (!s.empty()) {
			suffix.append(s.peek());
			s.pop();
		}
	}
	
	//后缀表达式计算
	private double CalcSuffix(String suffix) {				
		Stack<Double> s = new Stack<>();   	//创建一个栈
		int iLen = suffix.length();			 //计算长度用来控制循环
		double result = 0;                   //表达式最终结果
		StringBuffer temp = new StringBuffer();						 //临时存放数字
		for (int i = 0;i < iLen;i++) {
			//1.扫描到数字则入栈
			if (IsDigit(suffix.charAt(i)))
				temp.append(suffix.charAt(i));
			else if (suffix.charAt(i) == ' ') { //如果遇到分隔符，则把temp转换为数字，压入栈
				if (temp.length() > 0) {//防止运算符后面跟分隔符，所以判断一下temp里面是否有数字
					s.push(Double.valueOf(temp.toString()));
					temp.setLength(0);
				}
			}
			//2.扫描到运算符则将栈顶的两个元素依次出栈做相应的运算,把结果再入栈
			else if (IsOperator(suffix.charAt(i))) {
				//防止数字后面直接跟运算符，所以这里也要判断一下temp是否还有数字没有提取出来
				if (temp.length() > 0){
					s.push(Double.valueOf(temp.toString()));
					temp.setLength(0);
				}
				double op1 = s.peek();
				s.pop();
				double op2 = s.peek();
				s.pop();
				result = Calc(op1, op2, suffix.charAt(i));
				s.push( result);
			}
		}
		return s.peek();
	}
	
	//判断是否是数字
	private boolean IsDigit(char ch) {									  
		return (ch >= '0' && ch <= '9') || ch == '.' ? true : false;
	}
	
	//判断是否是操作符	
	private boolean IsOperator(char ch) {									
		return ch == '+' || ch == '-' || ch == '*' || ch == '/' ? true : false;
	}
	
	//判断运算符的优先级，-1表示小于，0表示等于，1表示大于								
	private int GetPriority(char op1, char op2) throws Exception {
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
		else 
			throw new Exception("两个运算符优先级未定义.");
	}
	
	//根据运算符计算两数
	private double Calc(double op1, double op2, char op) {			
		switch (op) {
		case '+': return op2 + op1;
		case '-': return op2 - op1;
		case '*': return op2 * op1;
		case '/': if (op1 != 0) return op2 / op1;
				  else return 0;
		default:  return 0;
		}
	}

}
