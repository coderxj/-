/*
* author: acme
*   date: 2017-1-18
*  blogs: http://blog.csdn.net/qq_18297675
*/


public class LinkList {

	private Node head = new Node(0);    //头节点
	private int iCount = 0;      			//链表大小
	
	//判断表是否为空
	public boolean isEmpty() {
		return iCount == 0 ? true : false;
	}
	
	//获取元素个数
	public int size() {
		return iCount;
	}
	
	//添加数据（头添加）
	public void addFromHead(Node node) {		
		node.next = head.next;
		head.next = node;
		++iCount;
	}
	
	//添加数据（尾添加）
	public void addFromTail(Node node) {		
		Node cur = head;
		for (int i = 0; i < iCount; i++) {
			cur = cur.next;          //遍历到链表末尾
		}
		cur.next = node;     //直接把新的节点挂在链表末尾
		++iCount;
	}
	
	//插入数据（指定位置）
	public void insert(int local, Node node) {	
		Node cur = head;   					
		for (int i = 0;i < local;i++, cur = cur.next); //遍历到local这个位置
		node.next = cur.next;
		cur.next = node;       //这里的操作就和头添加一样,就是改变指向
		++iCount;
	}
	
	//删除数据 （指定位置）
	public void deleteFromLocal(int local) {		
		if (local < iCount && local >= 0) {//当删除的位置合法的时候才进行删除操作
			Node pre = head;
			Node cur = head.next;
			for (int i = 0;i < local;i++, cur = cur.next, pre = pre.next);  //遍历到指定位置
			pre.next = cur.next;  //例如:pre->cur->next,现在直接让pre->next
			--iCount;
		}
	}
	
	//删除数据 （指定元素）
	public void deleteFromElement(int e) {			
		Node pre = head;
		Node cur = head.next;
		for (int i = 0;i < iCount;i++, cur = cur.next, pre = pre.next)  //遍历到指定位置
			if (cur.data == e) {
				pre.next = cur.next;  //例如:pre->cur->next,现在直接让pre->next
				--iCount;
				break;
			}
	}
	
	//根据指定元素查找，返回位置
	public int searchFromElmemt(int e) {				
		return getLocal(e);
	}
	
	//根据位置查找指定元素  
	public int searchFromLocal(int local) {		
		if (local < iCount && local >= 0) {//当搜索的位置合法的时候才进行搜索操作
			Node cur = head;
			for (int i = 0; i < local; i++, cur = cur.next);
			return cur.data;
		}
		else
			return -1;
	}
	
	////逆转表(方法1，牺牲时间换取空间，速度很慢，时间复杂度为0(n^2))
	public void reverse1() {						
		int temp;
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
		Node tHead = new Node(0);     //临时头节点
		Node cur = head.next;
		for (int i = 0;i < iCount;i++) {
			Node node = new Node(0);
			node = (Node)cur.clone();		//这里一定要复制，而不是赋值=，如果是=，则两指针指向的是同一个节点
			node.next = tHead.next;			  //这里采用头添加，结束后，就会自动逆转过来了         
			tHead.next = node;
			cur = cur.next;
		}
		head = (Node)tHead.clone();   //因为头添加已经是逆转了，所以直接复制到原来的链表中即可
	}
	
	//遍历元素
	public void print() {
		if(isEmpty())   //如果链表为空，则不做任何操作，防止空指针异常
			return;
		Node cur = head.next;
		for (int i = 0; i < iCount; i++,cur = cur.next) {
			System.out.println(cur.data);
		}
	}
	
	//复制表
	public LinkList copyList() {	//不能直接用clone方法，必须要一个个节点复制
		LinkList list = new LinkList();
		Node cur = head.next;
		for (int i = 0; i < iCount; i++,cur = cur.next) {
			Node temp = (Node)cur.clone();  //节点复制,不要直接赋值引用
			list.addFromHead(temp);  //头添加效率高
		}
		list.reverse2();        //逆转回来
		return list;
	}
	
	//修改元素
	public void rewrite(int local, int e) {			
		if (local < iCount && local >= 0) {
			Node cur = head.next;
			for (int i = 0;i < local;i++, cur = cur.next);
			cur.data = e;
		}
	}
	
	//清空链表
	public void clearLinkList() {                   
		head.next = null;       //因为java有垃圾回收机制，所以不需要手动释放节点，只要让头节点为空就好
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
	private int getLocal(int e) { 						
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
				int temp;
				if (bAsc) {//升序
					if (node1.data > node2.data) {
						temp = node1.data;
						node1.data = node2.data;
						node2.data = temp;
					}
				}
				else  {//降序
					if (node1.data < node2.data) {
						temp = node1.data;
						node1.data = node2.data;
						node2.data = temp;
					}
				}
			}
		}
	}
	
}

class Node implements Cloneable{  //实现该接口后，可进行对象的复制
	
	public int data;
	public Node next;
	Node(int d) {
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
