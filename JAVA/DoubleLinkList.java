
/*
* author: acme
*   date: 2017-1-21
*  blogs: http://blog.csdn.net/qq_18297675
* update: 2017-1-25
*   info: change node class become inner private class
*/

public class DoubleLinkList<T> {

	private class Node{ 
		
		public T data;
		public Node pre;   //前驱
		public Node next;  //后继
		Node(T d) {
			data = d;
		} 
	}
	
	private Node head;    //头节点
	private Node tail;    //尾指针
	private int iCount;      		//链表大小
	
	public DoubleLinkList() {
		initList();
	}
	
	//初始化链表
	private void initList() {
		head = new Node(null);  //创建头尾节点
		tail = new Node(null);
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
		Node node = new Node(e);
		if (isEmpty()) {//如果链表为空，第一次添加的时候，就让尾指针指向第一个添加的节点
			tail.next = node;       //例如 head->NULL,现在添加了个node1,则node1->NULL,head->node1,先把正方向连好			
			node.next = head.next;  //然后node1->head
			head.next = node;
			node.pre = head;
		} else {
			node.next = head.next;     //例如 head->node1,现在添加了个node2,则node2->node1,head->node2,先把正方向连好
			head.next = node;       //然后node1 -> node2,node2->head
			node.next.pre = node;
			node.pre = head;
		}
		++iCount;
	}
	
	//添加数据（尾添加）
	public void addFromTail(T e) {	
		Node node = new Node(e);
		if (isEmpty())                      //如果链表为空则直接调用AddFromHead，放置下一条语句引用空指针
			addFromHead(e);
		else {
			tail.next.next = node;  //tail.next表示最后一个节点，这句代码的意思是，让最后一个节点指向新添进来的节点
			node.pre = tail.next;   //新添进来的节点的前驱指向原来的最后一个节点
			tail.next = node;       //修改tail的指向
			++iCount;
		}
	}
	
	//插入数据（指定位置）
	public void insert(int local, T e) {	
		if (local < iCount && local >= 0) {
			Node node = new Node(e);
			Node cur = head;   //注意，这里千万不能是m_head->next,因为如果当前链表为空插入的位置
			   					//是0，则会直接执行cur->next这个表达式，解引用空指针会出错							
			for (int i = 0;i < local;i++, cur = cur.next); //遍历到local这个位置
			node.next = cur.next;			//在该位置插入
			cur.next = node;
			node.next.pre = node;
			node.pre = cur;
			++iCount;
		} else if(local == iCount)//如果是插入尾部，直接调用AddFromTail函数即可
			addFromTail(e);
	}
	
	//删除数据 （指定位置）
	public void deleteFromLocal(int local) throws Exception {		
		if (local < iCount - 1 && local >= 0) {//当要删除的位置合理的情况下才能删除
			Node cur = head;
			for (int i = 0;i < local;i++)
				cur = cur.next;
			cur.next = cur.next.next;           //删除该位置下的元素
			cur.next.pre = cur;
			--iCount;                    
		} else if (local == iCount - 1) {//删除的是最后一个元素的话
			tail.next = tail.next.pre; //指向最后一个节点的前一个节点
			tail.next.next = null;
			--iCount;
		} else {
			throw new Exception("删除的位置不存在，删除操作失败.");
		}
	}
	
	//删除数据 （指定元素）
	public void deleteFromElement(T e) throws Exception {			
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
		if (node != null)
			return node.data;
		else
			throw new Exception("查找的位置不存在，查找操作失败.");
	}
	
	//逆转表
	public void reverse() {						
		Node node1 = head.next;
		Node node2 = tail.next;
		while (node1 != node2) {
			swapNodeData(node1, node2);   //交换数据项，千万别交换节点
			node1 = node1.next;   //往后
			node2 = node2.pre;    //往前
			if (node1 == node2.pre) {//如果元素个数是偶数，则要多进行一步交换操作
				swapNodeData(node1, node2);   //交换数据项，千万别交换节点
				break;
			}
		}
	}
	
	//遍历元素
	public void print(boolean bReverse) {
		if (bReverse) {//倒序
			Node cur = tail.next;
			if (cur == null) return;
			do {
				System.out.println(cur.data);
			} while ((cur = cur.pre) != head);
		} else {
			Node cur = head;
			while ((cur = cur.next) != null)
				System.out.println(cur.data);
		}
	}
	
	//复制表
	public DoubleLinkList<T> copyList() {	//不能直接用clone方法，必须要一个个节点复制
		DoubleLinkList<T> list = new DoubleLinkList<>();
		Node cur = head.next;
		for (int i = 0; i < iCount; i++,cur = cur.next) {
			list.addFromTail(cur.data);   //因为加了个尾指针，现在头添加和尾添加时间复杂度都是0(1)
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
		head.next = null;       //因为java有垃圾回收机制，所以不需要手动释放节点，只要让头节点指向自己,尾指针为空就好
		tail.next = null;
		iCount = 0;
	}
	
	//获取指定位置的节点
	public Node getNode(int local) {            
		if (local < iCount / 2 && local >= 0) {//如果local在前半部分，则从前往后找
			Node cur = head.next;
			for (int i = 0;i < local;i++)  //遍历
				cur = cur.next;
			return cur;
		} else if (local >= iCount / 2 && local < iCount - 1) {//如果local在后半部分，则从后往前找
			Node cur = tail.next;
			for (int i = 0;i < iCount - local - 1;i++)  //遍历
				cur = cur.pre;
			return cur;
		} else if (local == iCount - 1)  //如果是查找最后一个节点，直接返回tail指向的节点即可
			return tail.next;
		else
			return null;
	}
	
	//交换两个节点的数据
	public void swapNodeData(Node node1, Node node2) {
		T temp;
		temp = node1.data;
		node1.data = node2.data;
		node2.data = temp;
	}
	
	//获取最后一个节点
	public Node getTailNode() {                 
		return tail.next;
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
			for (int j = i + 1;j < iCount;j++) {
				Node node2 = getNode(j);
				if (bAsc) {//升序
					if ((int)node1.data > (int)node2.data)
						swapNodeData(node1, node2);
				} else {//降序
					if ((int)node1.data < (int)node2.data)
						swapNodeData(node1, node2);
				}	
			}
		}
	}
	//合并链表  ,需要注意的是，合并后，原来的表就会被改变。
	public void mergeList(DoubleLinkList<T> sl) {
		if (isEmpty())  //如果目的表为空
			head.next = sl.head.next;  //直接让头节点指向表2的第一个节点
		else {
			tail.next.next = sl.head.next;     //表1的最后一个节点指向表2的第一个节点
			sl.head.next.pre = tail.next;      //表2的第一个节点指向表1的最后一个节点
		}
		tail.next = sl.tail.next;           //表1的尾指针指向表二的最后一个元素 
		iCount += sl.iCount;                  //还要把元素个数加起来
	}

	//合并链表(有序)
	public void mergeListOrder(DoubleLinkList<T> sl,boolean bAsc) {
		mergeList(sl);
		selectSort(bAsc);
	}

	//合并链表(无序)，不会改变原表
	void mergeListNoChange(DoubleLinkList<T> sl) {
		DoubleLinkList<T> list = new DoubleLinkList<>();
		list = sl.copyList();            //复制链表,这样就不会改变原表
		mergeList(list);          
	}

	//合并链表(有序),不会改变原表
	void mergeListNoChangeOrder(DoubleLinkList<T> sl, boolean bAsc) {
		DoubleLinkList<T> list = new DoubleLinkList<>();
		list = sl.copyList();           //复制链表,这样就不会改变原表
		mergeListOrder(list, bAsc);
	}
}
