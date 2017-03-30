/*
* author: acme
*   date: 2017-3-30
*  blogs: http://blog.csdn.net/qq_18297675
*/


/*
 * 二叉树递归实现
 * */
public class BTree<T> {

	public static void main(String[] args) {
		BTree<Integer> btree = new BTree<>();
		long iS = 0;
		long iE = 0;
		long iStart = 0;
		long iEnd = 0;
		iS = iStart =  System.currentTimeMillis();
		for (int i = 0; i < 1000; i++) {
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
		System.out.println();
		System.out.println("总共用时:" + ((iE - iS) / 1000.0) + " s");
	}
	
	private Node root;				//根节点
	private int iPos;				//数组下标
	private int n2Count;            //双分支节点数
	private int n1Count;			//单分支节点数
	private boolean bAdd;           //是否添加节点成功
	private boolean bFind;          //是否查找成功
	
	//节点类
	private class Node {  
		private T data;
		private Node left;
		private Node right;
		public Node(T data) {
			this.data = data;
		}
		public Node(Character data) {
			this.data = (T)data;
		}
		
		public void setLeft(Node node) {
			this.left = node;
		}
		
		public void setRight(Node node) {
			this.right = node;
		}
		
		public Node getLeft() {
			return this.left;
		}
		
		public Node getRight() {
			return this.right;
		}
	}
	
	//无参构造
	public BTree() {
		
	}
	
	//有参构造
	public BTree(String s) {
		create(s);
	}
	
	/***************private function*******************/

	/*
	* function				创建二叉树
	* param		Node		node
	* param		string		s
	* return                返回根节点
	*/
	private Node createBtree(Node node, String s) {
		++iPos;
		//如果s为空，即二叉树为空,若s=""或者到达末尾s[i]都等于'\0'，这里空节点用空格表示
		if (s.isEmpty() || s.charAt(iPos) == ' ')
			return null;
		else {
			node = new Node(s.charAt(iPos));
			node.setLeft(createBtree(node.getLeft(),s));
			node.setRight(createBtree(node.getRight(),s));
			return node;
		}
	}

	/*
	* function				计算二叉树深度
	* param		Node		root
	* return                返回二叉树深度
	*/
	private int depth(Node root) {
		if (root == null)
			return 0;
		else {
			int lDepth = depth(root.left);   //递归计算左子树的深度
			int rDepth = depth(root.right);  //递归计算右子树的深度
												   //返回较深的那个+1
			if (lDepth >= rDepth)
				return lDepth + 1;
			else
				return rDepth + 1;
		}
	}

	/*
	* function				计算二叉树双分支节点数
	* param		Node		root
	* return                返回二叉树双分支节点数
	*/
	private void getN2(Node root) {
		if (root == null)   //如果二叉树为空，则返回0
			return;
		else {
			if (root.left != null && root.right != null)  //当该节点有两个分支的时候+1
				++n2Count;
			getN2(root.left);    //遍历左子树
			getN2(root.right);   //遍历右子树
		}
	}

	/*
	* function				计算二叉树单分支节点数
	* param		Node		root
	* return                二叉树单分支节点数
	*/
	private void getN1(Node root) {
		if (root == null)   //如果二叉树为空，则返回0
			return;
		else {
			if ((root.left != null && root.right == null) || (root.left == null && root.right != null))  //当该节点仅且只有一个分支的时候+1
				++n1Count;
			getN1(root.left);    //遍历左子树
			getN1(root.right);   //遍历右子树
		}
	}

	/*
	* function				计算二叉树终端节点数
	* param		Node		root
	* return                二叉树终端节点数
	*/
	private int getN0(Node root) {
		return n2Count + 1;		//计算公式n0 = n2 + 1;
	}

	/*
	* function				前序遍历
	* param		Node		root
	* return                无
	*/
	private void preOrder(Node root) {
		if (root != null) {
			System.out.print(root.data + " ");
			preOrder(root.left);
			preOrder(root.right);
		}
	}

	/*
	* function				中序遍历
	* param		Node		root
	* return                无
	*/
	private void inOrder(Node root) {
		if (root != null) {
			inOrder(root.left);
			System.out.print(root.data + " ");
			inOrder(root.right);
		}
	}

	/*
	* function				后序遍历
	* param		Node		root
	* return                无
	*/
	private void postOrder(Node root) {
		if (root != null) {
			postOrder(root.left);
			postOrder(root.right);
			System.out.print(root.data + " ");
		}
	}

	/*
	* function				层次遍历
	* param		Node		root
	* return                无
	*/
	private void translevel(Node root) {
		if (null == root)
			return;
		int depth = depth(root);
		for (int i = 1; i <= depth; i++)
			printNodeAtLevel(root, i);
		System.out.println();
	}

	/*
	* function				层次变量辅助函数
	* param		int			level,层数
	* return                无
	*/
	private void printNodeAtLevel(Node root,int level) {
		// 空树或层级不合理
		if (null == root || level < 1)
			return;

		if (1 == level) {
			System.out.print(root.data + " ");
			return;
		}

		// 左子树的 level - 1 级
		printNodeAtLevel(root.left, level - 1);

		// 右子树的 level - 1 级
		printNodeAtLevel(root.right, level - 1);
	}

	/*
	* function				添加节点的辅助函数
	* param		int			level
	* param		T			data
	* return                无
	*/
	private void levelAdd(Node root, int level, T data) {
		//用来标记新的节点是否已经添加，如果添加了就退出了，避免重复添加
		if (bAdd)return;
		//如果该节点为空，则可以将ch赋值给该节点
		if (root.getLeft() == null || root.getRight() == null) {
			Node node = new Node(data);	//创建节点
			if (root.getLeft() == null)
				root.setLeft(node);
			else
				root.setRight(node);
			bAdd = true;
			return;
		}
		//层级不合理
		if (level < 1)
			return;
		//递归结束条件
		if (1 == level)
			return;

		// 左子树的 level - 1 级
		levelAdd(root.getLeft(), level - 1, data);

		// 右子树的 level - 1 级
		levelAdd(root.getRight(), level - 1, data);
	}

	/*
	* function				查找该值
	* param		Node		root
	* param		T			data
	* return                若存在则返回true，否则返回false
	*/
	private boolean search(Node root, T data) {
		if (bFind)return true;    //如果已经找到了就不需要继续查找了
		//利用前序遍历来查找						 
		if (root != null) {
			if (root.data.equals(data))
				bFind = true;
			search(root.left, data);
			search(root.right, data);
		}
		return false;
	}

	/******************private function*****************/

	/******************public function*******************/

	/*
	* function				创建二叉树(前序创建)
	* param		String s    根据给定串创建
	* return                无
	*/
	public void create(String s) {
		iPos = -1;
		root = createBtree(root,s);
	}

	/*
	* function				是否为空
	* return                空返回true，否则返回false
	*/
	public boolean isEmpty() {
		return this.root == null;
	}

	/*
	* function				求二叉树深度
	* return                二叉树深度
	*/
	public int depth() {
		return depth(root);
	}

	/*
	* function				求二叉树双分支节点数
	* return                二叉树双分支节点数
	*/
	public int getN2() {
		getN2(root);
		return n2Count;
	}

	/*
	* function				求二叉树单分支节点数
	* return                二叉树单分支节点数
	*/
	public int getN1() {
		getN1(root);
		return n1Count;
	}

	/*
	* function				求二叉树叶子节点数
	* return                二叉树叶子节点数
	*/
	public int getN0() {
		return getN0(root);
	}

	/*
	* function				前序遍历
	* return                无
	*/
	public void preOrder() {
		preOrder(root);
		System.out.println();
	}

	/*
	* function				中序遍历
	* return                无
	*/
	public void inOrder() {
		inOrder(root);
		System.out.println();
	}

	/*
	* function				后序遍历
	* return                无
	*/
	public void postOrder() {
		postOrder(root);
		System.out.println();
	}

	/*
	* function				层次遍历
	* return                无
	*/
	public void translevel() {
		translevel(root);
	}

	/*
	* function				添加节点值(添加的位置是不确定的)
	* param		T			data	
	* return                无
	*/
	public void addValue(T data) {
		//采用层次遍历的办法，一层层扫描，若有空的地方，则添加到该地方
		if (null == root) {//如果此时二叉树为空，则创建根节点
			root = new Node(data);	//创建根节点
			return;
		}
		int depth = depth(root);
		bAdd = false;   //每次都要重置一下这个标记
		for (int i = 1; i <= depth; i++) {
			if (bAdd)   //如果已经添加成功，则退出
				break;
			levelAdd(root, i, data);
		}
	}

	/*
	* function				查找该值
	* param		char	    ch
	* return                若存在则返回true，否则返回false
	*/
	public boolean search(T data) {
		bFind = false;
		search(root, data);
		return bFind;
	}


	/******************public function*******************/
	
}
