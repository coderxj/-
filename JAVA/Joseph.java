
/*
* author: acme
*   date: 2017-1-26
*  blogs: http://blog.csdn.net/qq_18297675
*/
public class Joseph {

	public static void main(String[] args) {
		Joseph j = new Joseph();
		j.print(41, 3);
		System.out.println(j.getLastOne(41, 3));
	}
	
	private class Node {  //节点类
		
		private int data;
		Node next;
	}

	private Node createCycleList(int n) {
		Node head = new Node(); //头节点只是中转作用
		Node tail = new Node(); //尾指针，最后用来连接头尾
		for (int i = n;i > 0;i--) {
			Node node = new Node();
			node.data = i;
			if (i == n)
				tail.next = node;   //尾指针指向最后一个节点
			node.next = head.next;//利用头添加法  ,所以序号i要倒着添加
			head.next = node;
		}
		tail.next.next = head.next;//尾指针指向第一个节点 
		return head.next;    //去掉头节点返回
	}
	
	//打印出死亡顺序
	public void print(int n, int k) {
		if (k <= 0) return;
		Node cur = createCycleList(n);
		if (k == 1) {//如果自杀规则是 1 的话，那肯定是最后一个不死了
			for (int i = 0;i < n;i++, cur = cur.next)
				System.out.print(cur.data+"->");
			System.out.println();
		} else {
			while (cur != cur.next) {//当只剩下最后一个元素后，clist就不等于clist->next
				for (int i = 0;i < k - 2;i++)  //这个循环只能循环到要删掉的节点的前一个 
					cur = cur.next;        //（因为后面删除节点的时候，需要前一个指向后后一个节点）
				System.out.print(cur.next.data+"->"); //打印出后一个节点的值
				cur.next = cur.next.next;
				cur = cur.next;
			}
			System.out.println(cur.data);
		}
	}
	
	//获取最后一个dead位置
	int getLastOne(int n, int k) {
		if (k < 1) return -1;
		Node cur = createCycleList(n);
		if (k == 1)  //如果自杀规则是 1 的话，那肯定是最后一个不死了
			for (int i = 0;i < n;i++, cur = cur.next);
		else {
			while (cur != cur.next) {//当只剩下最后一个元素后，clist就不等于clist->next
				for (int i = 0;i < k - 2;i++)  //这个循环只能循环到要删掉的节点的前一个 
					cur = cur.next;        //（因为后面删除节点的时候，需要前一个指向后后一个节点）
				cur.next = cur.next.next;
				cur = cur.next;
			}
		}
		return cur.data;
	}
	
	//获取最后一个dead的规则
	int getRule(int n, int local) {
		int k = 0;
		while (true) {
			if (getLastOne(n, k++) == local)
				return k - 1;
		}
	}
}
