
/*
* author: acme
*   date: 2017-3-30
*  blogs: http://blog.csdn.net/qq_18297675
*/
import java.util.ArrayDeque;
import java.util.Stack;

public class NonRecursionBTree<T> {

	public static void main(String[] args) {
		NonRecursionBTree<Integer> btree = new NonRecursionBTree<>();
		long iS = 0;
		long iE = 0;
		long iStart = 0;
		long iEnd = 0;
		iS = iStart =  System.currentTimeMillis();
		for (int i = 0; i < 10000; i++) {
			btree.addValue(i);
		}
		iEnd = System.currentTimeMillis();
		System.out.println("添加元素个数: 100000");
		System.out.println("用时:" + ((iEnd - iStart) / 1000.0) + " s");
//		btree.addValue("A");
//		btree.addValue("B");
//		btree.addValue("C");
//		btree.addValue("D");
//		btree.addValue("E");
//		btree.addValue("F");
//		btree.addValue("G");
//		btree.addValue("H");
//		System.out.println("前序遍历:");
//		btree.preOrder();
//		System.out.println("中序遍历:");
//		btree.inOrder();
//		System.out.println("后序遍历:");
//		btree.postOrder();
//		System.out.println("层次遍历:");
//		btree.translevel();
		iStart =  System.currentTimeMillis();
		System.out.println("深度:" + btree.depth());
		iEnd = System.currentTimeMillis();
		System.out.println("用时:" + ((iEnd - iStart) / 1000.0) + " s");
		
		iStart =  System.currentTimeMillis();
		System.out.println("双分支节点数:" + btree.getN2());
		iEnd = System.currentTimeMillis();
		System.out.println("用时:" + ((iEnd - iStart) / 1000.0) + " s");
		
		iStart =  System.currentTimeMillis();
		System.out.println("单分支节点数:" + btree.getN1());
		iEnd = System.currentTimeMillis();
		System.out.println("用时:" + ((iEnd - iStart) / 1000.0) + " s");
		
		iStart =  System.currentTimeMillis();
		System.out.println("叶子节点数:" + btree.getN0());
		iEnd = System.currentTimeMillis();
		System.out.println("用时:" + ((iEnd - iStart) / 1000.0) + " s");
		
		iStart =  System.currentTimeMillis();
		System.out.println("搜索：" + btree.search(9999));
		iE = iEnd = System.currentTimeMillis();
		System.out.println("用时:" + ((iEnd - iStart) / 1000.0) + " s");
		System.out.println('\n' + '\n' + "总共用时:" + ((iE - iS) / 1000.0) + " s");
	}
	
	private Node root = null;  //根节点
	
	//节点类
	private class Node {
		private T data;
		private boolean bLCExits;			//左孩子是否存在
		private boolean bRCExits;			//左孩子是否存在
		private Node left;					//左节点
		private Node right;					//右节点
		public Node(T data){
			this.data = data;
		}
		public Node(Character data){
			this.data = (T)data;
		}
		
	}

	//默认构造函数
	public NonRecursionBTree(){
		
	}

	//有参构造
	public NonRecursionBTree(String s){
		create(s);
	}

	/*
	* function				创建二叉树(前序创建)
	* param		String s    根据给定串创建
	* return                无
	*/
	public void create(String s) {
		if (s.isEmpty())  //如果s为空 则树也为空
			return ;
		Stack<Node> st = new Stack<Node>();	//创建一个栈
		int i = 0;
		// 1.先创建根节点
		root = new Node(s.charAt(i++));
		Node btree = root;		//用一个临时的指针代替root，因为最后要返回root指针，所以它不能改变
		st.push(btree);				//将根节点压入栈中
		int len = s.length();
		while (i < len) {
			// 2.如果当前读到的字符不为空，并且当前节点的左孩子不存在，则创建它
			if (s.charAt(i) != ' ' && btree.bLCExits == false) {
				btree.left = new Node(s.charAt(i));	//创建左孩子
				btree.bLCExits = true;			//左孩子存在
				btree = btree.left;
				st.push(btree);  //入栈
				++i;
			}
			// 3.如果当前读到的字符不为空，并且当前节点的右孩子不存在，则创建它
			else if (s.charAt(i) != ' ' && btree.bRCExits == false) {
				btree.right = new Node(s.charAt(i));	//创建右孩子
				btree.bRCExits = true;			//右孩子存在
				btree = btree.right;
				st.push(btree);  //入栈
				++i;
			}
			// 4.如果当前读到的字符为空，并且当前节点的左孩子不存在，则将当前节点的左孩子置为存在（空也算孩子）
			else if (s.charAt(i) == ' ' && btree.bLCExits == false) {//空节点
				btree.bLCExits = true;
				++i;  //左孩子存在
			}	
			// 5.如果当前读到的字符为空，并且当前节点的右孩子不存在，则将当前节点的右孩子置为存在（空也算孩子）
			else if (s.charAt(i) == ' ' && btree.bRCExits == false) {
				btree.bRCExits = true;
				++i;  //右孩子存在		
			}
				
			// 6.回溯回去,当该节点的度为2的时候(就是左右孩子都存在的情况)
			if (btree.bLCExits && btree.bRCExits) {
				st.pop();
				btree = st.peek();
			}
				
		}
		st.clear(); //最后销毁栈
	}

	/*
	* function				是否为空
	* return                空返回true，否则返回false
	*/
	public boolean isEmpty() {
		return root == null;
	}

	/*
	* function				二叉树深度
	* return                无
	*/
	public int depth() {
		if (root == null) return 0;
		ArrayDeque<Node> q = new ArrayDeque<>();//创建一个队列					
		Node cur = root;						//当前节点
		int iDepth = 0;
		q.addLast(cur);							//先将根节点加入队列中
		while (!q.isEmpty()) {					//当队列中没有元素时，遍历完成
			++iDepth;							//外层循环控制层数
			int curLevelNodes = q.size();		//当前层数的节点数
			int temp = 0;						//临时记录已经遍历的节点数
			while (temp++ < curLevelNodes) {	//当遍历完当前层数后，退出内层循环，继续遍历下一层
				cur = q.peek();					//获取当前队头元素
				q.pop();						//遍历过后就出队
				if (cur.left != null)			//如果左孩子不为空，则入队等待遍历
					q.addLast(cur.left);
				if (cur.right != null)			//如果右孩子不为空，则入队等待遍历
					q.addLast(cur.right);
			}
		}
		return iDepth;
	}

	/*
	* function				二叉树双分支节点数
	* return                无
	*/
	
	public int getN2() {
		Stack<Node> st = new Stack<>();		//创建一个栈
		Node btree = root;					//创建临时指针指向root
		int count = 0;
		//利用前序遍历来访问所有的节点
		while (btree != null || !st.isEmpty()) {
			while (btree != null) {
				st.push(btree);
				btree = btree.left;
			}
			if (!st.isEmpty()) {
				btree = st.peek();
				if (btree != null)                            		//再这里能保证所有的节点都能被判断到
					if (btree.left != null && btree.right != null) 	//当该节点有两个分支的时候+1
						++count;
				st.pop();
				btree = btree.right;
			}
		}
		return count;
	}

	/*
	* function				二叉树单分支节点数
	* return                无
	*/
	public int getN1() {
		Stack<Node> st = new Stack<>();		//创建一个栈
		Node btree = root;					//创建临时指针指向root
		int count = 0;
		//利用前序遍历来访问所有的节点
		while (btree != null || !st.isEmpty()) {
			while (btree != null) {
				st.push(btree);
				btree = btree.left;
			}
			if (!st.empty()) {
				btree = st.peek();
				if (btree != null)                            //再这里能保证所有的节点都能被判断到
					if ((btree.left != null && btree.right == null) || 
						(btree.left == null && btree.right != null))  //当该节点仅且只有一个分支的时候+1
						++count;
				st.pop();
				btree = btree.right;
			}
		}
		return count;
	}

	/*
	* function				二叉树叶子节点数
	* return                无
	*/
	public int getN0() {
		return getN2() + 1; //计算公式n0 = n2 + 1;
	}

	/*
	* function				前序遍历
	* return                无
	*/
	public void preOrder() {
		Stack<Node> st = new Stack<>();				//创建一个栈
		Node btree = root;				//创建临时指针指向root
		// 1. 若当前节点不为空，或者栈中元素不为空（相当于还没有遍历完所有节点）
		while (btree != null || !st.isEmpty()) {
			// 2. 先遍历左子树，一直到左子树为空为止。
			while (btree != null) {
				System.out.print(btree.data + " ");
				st.push(btree);
				btree = btree.left;
			}
			// 3.若栈中还有元素，则将当前btree赋值为它的右子树，然后再重复 1~2步骤
			if (!st.empty()) {
				btree = st.peek();
				st.pop();
				btree = btree.right;
			}
		}
		System.out.println();
	}

	/*
	* function				中序遍历
	* return                无
	*/
	public void inOrder() {
		Stack<Node> st = new Stack<>();	//创建一个栈
		Node btree = root;				//创建临时指针指向root
		// 1. 若当前节点不为空，或者栈中元素不为空（相当于还没有遍历完所有节点）
		while (btree != null || !st.isEmpty()) {
			// 2. 先遍历左子树，一直到左子树为空为止。
			while (btree != null) {
				st.push(btree);
				btree = btree.left;
			}
			// 3.若栈中还有元素，则将当前btree赋值为它的右子树，然后再重复 1~2步骤
			if (!st.isEmpty()) {
				btree = st.peek();
				System.out.print(btree.data + " ");//遍历完左子树后输出它们的根节点
				st.pop();
				btree = btree.right;
			}
		}
		System.out.println();
	}

	/*
	* function				后序遍历
	* return                无
	*/	
	public void postOrder() {
		if (root == null)return;
		Stack<Node> st = new Stack<>();				//创建一个栈
		Node cur;							//当前结点 
		Node pre = null;					//前一次访问的结点 
		st.push(root);						//先将根节点入栈
		while (!st.isEmpty()) {
			cur = st.peek();          //这里的cur就像是每颗子树的根节点，然后重复这些步骤
			if ((cur.left  == null && cur.right == null) ||
				(pre != null && (pre == cur.left || pre == cur.right))) {
				System.out.print(cur.data + " ");//如果当前结点没有孩子结点或者孩子节点都已被访问过  
				st.pop();
				pre = cur;
			}
			else {
				if (cur.right != null)      //这里先将右孩子入栈，这样出栈的时候，左孩子就先出栈
					st.push(cur.right);
				if (cur.left != null)
					st.push(cur.left);
			}
		}
		System.out.println();
	}

	/*
	* function				层次遍历
	* return                无
	*/
	public void translevel() {
		if (root == null) return;
		ArrayDeque<Node> q = new ArrayDeque<>();	//创建一个队列
		Node cur = root;							//当前节点
		q.addLast(cur);								//先将根节点加入队列中
		while (!q.isEmpty()) {						//当队列中没有元素时，遍历完成 
			cur = q.peek();							//获取当前队头元素
			q.pop();								//遍历过后就出队
			System.out.print(cur.data  + " "); 		//先输出该子树的根节点
			if (cur.left != null)					//如果左孩子不为空，则入队等待遍历
				q.addLast(cur.left);
			if (cur.right != null)				    //如果右孩子不为空，则入队等待遍历
				q.addLast(cur.right);
		}
		System.out.println();
	}

	/*
	* function				添加节点值(添加的位置是不确定的)
	* param		T			data
	* return                无
	*/
	public void addValue(T data) {
		//采用层次遍历的办法，一层层扫描，若有空的地方，则添加到该地方
		if (root == null) {
			root = new Node(data);
			return;
		}
		ArrayDeque<Node> q = new ArrayDeque<>();						//创建一个队列
		Node cur = root;							//当前节点
		q.addLast(cur);								//先将根节点加入队列中
		while (!q.isEmpty()) {						//当队列中没有元素时，遍历完成 
			cur = q.peek();							//获取当前队头元素
			q.pop();								//遍历过后就出队
			if (cur.left != null)					//如果左孩子不为空，则入队等待遍历
				q.addLast(cur.left);
			else { 									//否则就添加值，然后退出
				cur.left = new Node(data);
				break;
			}
			if (cur.right != null)				    //如果右孩子不为空，则入队等待遍历
				q.addLast(cur.right);
			else {									//否则就添加值，然后退出
				cur.right = new Node(data);//否则就添加值，然后退出
				break;
			}
		}
	}

	/*
	* function				查找该值
	* param		char	    ch
	* return                若存在则返回true，否则返回false
	*/
	public boolean search(T data) {
		//利用层次遍历来查找
		if (root == null) return false;
		ArrayDeque<Node> q = new ArrayDeque<>();	//创建一个队列
		Node cur = root;							//当前节点
		q.addLast(cur);								//先将根节点加入队列中
		while (!q.isEmpty()) {						//当队列中没有元素时，遍历完成 
			cur = q.peek();							//获取当前队头元素
			if (cur.data.equals(data))
				return true;
			q.pop();								//遍历过后就出队
			if (cur.left != null)					//如果左孩子不为空，则入队等待遍历
				q.addLast(cur.left);
			if (cur.right != null)				    //如果右孩子不为空，则入队等待遍历
				q.addLast(cur.right);
		}
		return false;
	}
}
