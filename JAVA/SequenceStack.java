
/*
* author: acme
*   date: 2017-1-22
*  blogs: http://blog.csdn.net/qq_18297675
*/
public class SequenceStack<T> {

	private T[] data;    //栈数据空间
	private int top;     //栈顶指示
	private int MAX_SIZE;//栈最大长度
	
	//有参构造函数
	SequenceStack(int stackSize) {   //构造栈的时候，给出栈的大小
		MAX_SIZE = stackSize;
		initStack();
	}
	
	//初始化栈
	private void initStack() {   
		data = (T[])new Object[MAX_SIZE] ;  //new 一个object数组，然后强转为T[]
		top = -1;
	}
	
	//栈是否为空
	public boolean isEmpty() {       
		return top == -1 ? true : false;
	}
	
	//栈是否满了
	public boolean isFull() {       
		return top == MAX_SIZE - 1 ? true : false;
	}
	
	//获取当前栈的长度
	public int getSize() {
		return top + 1;
	}
	
	//入栈
	public void push(T e) throws Exception{       
		if(isFull()) {   //如果栈满了，就什么也不做
			throw new Exception("栈已满，入栈操作失败.");
		} else {
			data[++top] = e;
		}
	}
	
	//出栈(不返回栈顶元素)
	public void pop() throws Exception{          
		if(isEmpty()) {  //如果栈为空，就什么也不做
			throw new Exception("栈为空，出栈操作失败.");
		} else {
			--top;
		}
	}
	
	//出栈(返回栈顶元素)
	public T popE() throws Exception{            
		if(isEmpty()) {  //如果栈为空，就什么也不做
			throw new Exception("栈为空，出栈操作失败.");
		} else {
			return data[(--top) + 1];
		}
	}
	
	//获取栈顶元素
	public T getTop() throws Exception{           
		if(isEmpty()) {  //如果栈为空，就什么也不做
			throw new Exception("栈为空，获取栈顶元素操作失败.");
		} else {
			return data[top];
		}
	}
	
	//遍历栈
	public void print() throws Exception {         
		if(isEmpty()) {  //如果栈为空，就什么也不做
			throw new Exception("栈为空，遍历栈操作失败.");
		} else {
			do {
				System.out.println(data[top]);
			} while (top-- != 0);
		}
	}
	
	//清空栈
	public void clearStack() throws Exception {    
		if(isEmpty()) {  //如果栈为空，就什么也不做
			throw new Exception("栈为空，清空栈操作失败.");
		} else {
			top = -1;
		}
	}
}
