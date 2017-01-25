
/*
* author: acme
*   date: 2017-1-18
*  blogs: http://blog.csdn.net/qq_18297675
* update: 2017-1-25
*   info: add tail ptr,improve the efficiency of adding data,change node class become inner private class
*/

public class LinkList<T> {
	
	private class Node implements Cloneable{  //实现该接口后，可进行对象的复制
		
		public T data;
		public Node next;
		Node(T d) {
			data = d;
		} 
		
		//重写clone  用来进行浅复制
		public Object clone() {
			Node node = null;
			try {
				node = (Node)super.clone();
			} catch (CloneNotSupportedException e) {
				e.printStackTrace();
			}
			return node;
		}
	}
	
	private Node head;    //头节点
	private Node tail;    //尾指针
	private int iCount;   //链表大小
	
	public LinkList() {
		initList();
	}
	
	private void initList() {
		head = new Node(null);    		//头节点
		tail = new Node(null);    		//尾指针    
		iCount = 0;
	}
	
	//判断表是否为空
	public boolean isEmpty() {
		return iCount == 0 ? true : false;
	}
	
	//获取元素个数
	public int size() {
		return iCount;
	}
	
	//添加数据（头添加）
	public void addFromHead(T e) {		
		Node node = new Node(e);   //用e来创建新的节点
		if (isEmpty())//如果链表为空，第一次添加的时候，就让尾指针指向第一个添加的节点
			tail.next = node;
		node.next = head.next;
		head.next = node;
		++iCount;
	}
	
	//添加数据（尾添加）
	public void addFromTail(T e) {		
		if (isEmpty())
			addFromHead(e);
		else {
			Node node = new Node(e);
			tail.next.next = node;//让最后一个节点指向新添进来的节点
			tail.next = node;	  //修改tail的指向
			++iCount;
		}
	}
	
	//插入数据（指定位置）
	public void insert(int local, T e) {	
		if (local < iCount && local >= 0) {
			Node cur = head;   //注意，这里千万不能是m_head->next,因为如果当前链表为空插入的位置
								  //是0，则会直接执行cur->next这个表达式，解引用空指针会出错
			Node node = new Node(e);
			for (int i = 0;i < local;i++, cur = cur.next); //遍历到local这个位置
			node.next = cur.next;
			cur.next = node;       //这里的操作就和头添加一样,就是改变指向
			++iCount;
		}
		else if (local == iCount)//如果是插入尾部，直接调用AddFromTail函数即可
			addFromTail(e);
	}
	
	//删除数据 （指定位置）
	public void deleteFromLocal(int local) {		
		if (local < iCount && local >= 0) {//当删除的位置合法的时候才进行删除操作
			Node pre = head;
			Node cur = head.next;
			for (int i = 0;i < local;i++, cur = cur.next, pre = pre.next);  //遍历到指定位置
			pre.next = cur.next;  //例如:pre->cur->next,现在直接让pre->next
			if(pre.next == null)  //如果是删除最后一个元素，则需要修改尾指针
				tail.next = pre;
			--iCount;
		}
	}
	
	//删除数据 （指定元素）
	public void deleteFromElement(T e) {			
		int local = getLocal(e);
		deleteFromLocal(local);
	}
	
	//根据指定元素查找，返回位置
	public int searchFromElmemt(T e) {				
		return getLocal(e);
	}
	
	//根据位置查找指定元素  
	public T searchFromLocal(int local) throws Exception {		
		Node node = getNode(local);
		if (node != null) {
			return node.data;
		}
		else
			throw new Exception("查找的位置不存在，查找失败.");
	}
	
	////逆转表(方法1，牺牲时间换取空间，速度很慢，时间复杂度为0(n^2))
	public void reverse1() {						
		T temp;
		for (int i = 0;i < iCount / 2;i++) {
			Node node1 = getNode(i);                   //获取节点
			Node node2 = getNode(iCount - i - 1);
			temp = node1.data;                         //交换数据项，千万别交换节点
			node1.data = node2.data;
			node2.data = temp; 
		}
	}
	
	//逆转表(方法2，牺牲空间换取时间，速度很快，时间复杂度为0(n))
	public void reverse2() {
		Node tHead = new Node(null);     //临时头节点
		Node cur = head.next;
		for (int i = 0;i < iCount;i++) {
			Node node = new Node(cur.data);   //创建新的节点
			node.next = tHead.next;			  //这里采用头添加，结束后，就会自动逆转过来了         
			tHead.next = node;
			cur = cur.next;
		}
		head = (Node)tHead.clone();   //因为头添加已经是逆转了，所以直接复制到原来的链表中即可
	}
	
	//遍历元素
	public void print() {
		Node cur = head.next;
		for (int i = 0; i < iCount; i++,cur = cur.next) {
			System.out.println(cur.data);
		}
	}
	
	//复制表
	public LinkList<T> copyList() {	//不能直接用clone方法，必须要一个个节点复制
		LinkList<T> list = new LinkList<>();
		Node cur = head.next;
		for (int i = 0; i < iCount; i++,cur = cur.next) {
			list.addFromTail(cur.data);  //加了尾指针，头添加和尾添加都一样了
		}
		return list;
	}
	
	//修改元素
	public void rewrite(int local, T e) {			
		Node node = getNode(local);
		if (node != null)
			node.data = e;
	}
	
	//清空链表
	public void clearLinkList() {                   
		head.next = null;       //因为java有垃圾回收机制，所以不需要手动释放节点，只要让头节点为空就好
		tail.next = null;
		iCount = 0;
	}
	
	//获取指定位置的节点
	public Node getNode(int local) {            
		if (local < iCount && local >= 0) {//当获取的位置合法的时候才进行获取操作
			Node cur = head.next;
			for (int i = 0;i < local;i++, cur = cur.next);
			return cur;
		}
		else
			return null;
	}
	
	//返回元素位置
	private int getLocal(T e) { 						
		Node cur = head.next;
		for (int i = 0;i < iCount;i++, cur = cur.next)
			if (cur.data == e)
				return i;
		return -1;
	}
	
	//升序
	public void sortByAsc() {
		selectSort(true);
	}
	
	//降序
	public void sortByDesc() {
		selectSort(false);
	}
	
	//选择排序法
	private void selectSort(boolean bAsc) {
		for (int i = 0;i < iCount;i++) {
			Node node1 = getNode(i);
			for (int j = i + 1;j<iCount;j++) {
				Node node2 = getNode(j);
				T temp;
				if (bAsc) {//升序
					if ((int)node1.data > (int)node2.data) {  //排序只对整型有效
						temp = node1.data;
						node1.data = node2.data;
						node2.data = temp;
					}
				}
				else  {//降序
					if ((int)node1.data < (int)node2.data) {
						temp = node1.data;
						node1.data = node2.data;
						node2.data = temp;
					}
				}
			}
		}
	}
	
}
