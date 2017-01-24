
/*
* author: acme
*   date: 2017-1-25
*  blogs: http://blog.csdn.net/qq_18297675
*/
public class CycleQueue<T> { //循环队列类
	
	private T[] data;	//队列数据区域
	int front;			//队头
	int rear;			//队尾
	int queueSize;		//队列的最大长度
	int count;
	
	
	public CycleQueue(int queueSize) {
		initQueue(queueSize);
	}	
	//初始化队列,并且指定队列大小
	private	void initQueue(int queueSize) {	
		data = (T[])new Object[queueSize];  //分配数据区域大小
		front = 0;  //初始队头指向0，表示队中无元素
		rear = 0;   //初始队尾指向0，表示队中无元素
		count = 0;
		this.queueSize = queueSize;
	}
	
	//队列是否为空					
	private	boolean isEmpty() {			
		return count == 0 ? true : false;
	}
	
	//队列是否满
	private	boolean isFull() {						
		return count == queueSize ? true : false;
	}
	
	//入队      
	public void enQueue(T e) throws Exception {				   
		if (isFull())
			throw new Exception("队列已满，入队操作失败.");
		else {//如果队列没有满，则循环到数组的第一个a[0]继续存放,把空间利用完
			data[rear % queueSize] = e;
			rear = ++rear % queueSize;
			++count;
		}
	}
	
	//出队
	public void deQueue() throws Exception {						
		if (isEmpty())
			throw new Exception("队列为空，出队操作失败.");
		else {    //队头指针向后移,移到最后，如果没有满，则循环到a[0]继续	 	
			front = ++front % queueSize;
			--count;
		}	
	}
	
	//获取队列长度
	public int getSize() {				   
		return count;
	}
	
	//获取队头
	public T getQueueHead() throws Exception {					
		if (isEmpty())
			throw new Exception("队列为空，获取队头操作失败.");
		else
			return data[front];
	}
	
	//遍历队列
	public void print() throws Exception {					   
		if (isEmpty())
			throw new Exception("队列为空，遍历操作失败.");
		else {
			if (front < rear) {//这是正常的，没有循环的时候
				for (int i = front;i < rear;i++)
					System.out.println(data[i]);
			}
			else {
				for (int i = front;i < queueSize;i++)  //分段遍历
					System.out.println(data[i]);
				for (int i = 0;i < rear;i++)
					System.out.println(data[i]);
			}			
		}
	}
	
	 //清空队列
	public void clearQueue() throws Exception {				  
		if (isEmpty())
			throw new Exception("队列为空，清空操作失败.");
		else {
			front = 0;//不用清空数据，入队的时候直接覆盖就好
			rear = 0;
			count = 0;
		}
	}
}
