
/*
* author: acme
*   date: 2017-1-24
*  blogs: http://blog.csdn.net/qq_18297675
*/

public class LinkQueue<T> {  //链队类
	/*
	 * 1.因为java会默认给变量赋值，赋值原则是整数类型int、byte、short、long的自动赋值为0，
	 * 带小数点的float、double自动赋值为0.0，boolean的自动赋值为false，其他各供引用类型
	 * 变量自动赋值为null。 所以这里Node初始化的时候可以省略赋值为null，最后一个节点的指向也可以省略手动赋值
	 * 
	 * 2.因为是内部类，所以不再需要Node<T>
	 * */
	private Node front; 	//头节点，指向队首
	private Node rear;  	//尾节点，指向队尾
	private int count;		//队列大小
	
	//把Node作为内部类，不让外部访问
	private class Node {    //节点类
		
		private T data;
		private	Node next;
	}
	
	public LinkQueue() {
		initQueue();     //初始化队列
	}
	
	//初始化队列
	public void initQueue() {		
		front = new Node();  //创建首尾两个节点
		rear = new Node();
		count = 0;
	}
	
	//队列是否为空
	public boolean isEmpty() {			
		return count == 0 ? true : false;
	}
	
	//入队 
	public void enQueue(T e) {
		Node node = new Node();  //创建新的节点
		node.data = e;
		if (count == 0)			//如果是第一次添加，则让front和rear同时指向它
			front.next = node;
		else
			rear.next.next = node;  //原来最后一个节点指向新的最后一个节点
		rear.next = node;			//rear指向最后一个节点
		++count;
	}
	
	//出队
	public void deQueue() throws Exception {			
		if (isEmpty())
			throw new Exception("队列为空，出队操作失败");  //抛出异常
		else
		{
			front.next = front.next.next;    //front指向后一个节点
			--count;
		}
	}
	
	//获取队列长度
	public int getSize() {			
		return count;
	}
	
	//获取队头
	public T getQueueHead() throws Exception {	
		if(isEmpty())
			throw new Exception("队列为空，获取队头操作失败");
		else
			return front.next.data;
	}
	
	//遍历队列
	public void print() {           
		Node cur = front.next;
		for (int i = 0; i < count; i++, cur = cur.next)
			System.out.println(cur.data);
	}
	
	//清空队列
	public void clearQueue() throws Exception {   
		for (int i = 0; i < count; i++)
			deQueue();					//挨个出队即可 
	}
}
