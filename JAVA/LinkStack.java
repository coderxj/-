package acme.list;
/*
* author: acme
*   date: 2017-1-22
*  blogs: http://blog.csdn.net/qq_18297675
* update: 2017-1-25
*   info: change node class become inner private class
*/
public class LinkStack<T> {  //链栈类
	
	class Node {  //节点类
		
		public T data;
		public Node next;
		
		public Node(T d) {
			data = d;
		}
	}
	private Node top;   //栈顶指针
	private int count;     //记录栈的大小
	
	public LinkStack() {
		initStack();
	}
	
	//初始化栈
	private void initStack() {  
		top = new Node(null);  //创建栈顶指针
		count = 0;
	}
	//栈是否为空
	public boolean isEmpty() {       
		return count == 0 ? true : false;
	}
		
	//获取当前栈的长度
	public int getSize() {
		return count;
	}
	
	//入栈
	public void push(T e) {       
		Node node = new Node(e);  //创建一个新的节点
		node.next = top.next;  
		top.next = node;          //让栈顶指针指向新的栈顶节点
		++count;
	}
		
	//出栈(不返回栈顶元素)
	public void pop() throws Exception{          
		if(isEmpty()) {  
			throw new Exception("栈为空，出栈操作失败.");
		} else {
			top.next = top.next.next;
			--count;
		}
	}
	
	//出栈(返回栈顶元素)
	public T popE() throws Exception{            
		if(isEmpty()) {  
			throw new Exception("栈为空，出栈操作失败.");
		} else {
			T data = top.next.data; //先把要返回的值保存下来
			top.next = top.next.next;
			--count;
			return data;
		}
	}
		
	//获取栈顶元素
	public T getTop() throws Exception{           
		if(isEmpty()) {  
			throw new Exception("栈为空，获取栈顶元素操作失败.");
		} else {
			return top.next.data;
		}
	}
		
	//遍历栈
	public void print() throws Exception {         
		if(isEmpty()) {  //如果栈为空，就什么也不做
			throw new Exception("栈为空，遍历栈操作失败.");
		} else {
			Node cur = top;    //和链表遍历一样
			while ((cur = cur.next) != null)  
				System.out.println(cur.data);
		}
	}
	
	//清空栈
	public void clearStack() throws Exception {    
		if(isEmpty()) {  //如果栈为空，就什么也不做
			throw new Exception("栈为空，清空栈操作失败.");
		} else {
			while(count != 0)
				pop();
			top.next = null;
		}
	}
}
