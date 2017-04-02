
/*
* author: acme
*   date: 2017-4-2
*  blogs: http://blog.csdn.net/qq_18297675
*/
import java.util.Random;

public class BTreeSearch {

	public static void main(String[] args) {

		BTreeSearch btree = new BTreeSearch();
	 	btree.add(41);
	 	btree.add(34);
	 	btree.add(30);
	 	btree.add(39);
	 	btree.add(35);
	 	btree.add(40);
	 	btree.add(67);
	 	btree.add(58);
	 	btree.add(69);
	 	btree.add(68);
	 	btree.add(78);
	 	btree.delete(34);
	 	btree.delete(35);
//	 	btree.delete(67);
//	 	btree.delete(39);
//	 	btree.delete(69);
//	 	btree.delete(30);
//	 	btree.delete(41);

//		Random rand = new Random();
//		for (int i = 0;i < 1000;i++)
//		{
//			btree.add(rand.nextInt(1000));
//		}
//		
//		for (int i = 0;i < 10;i++)
//		{
//			btree.delete(rand.nextInt(1000));
//		}
	 	System.out.println("min:" + btree.getMinValue());
	 	System.out.println("max:" + btree.getMaxValue());
	 	System.out.println("size:" + btree.size());
	 	
		btree.print(true);
		//btree.print(false);
		System.out.println(btree.search(78));
		System.out.println(btree.search(1));
	}
	
	private class Node {
		private int value;
		private int count = 1;
		private Node left = null;
		private Node right = null;
		public Node(int v) {
			value = v;
		}
		
		/*
		 * 重复节点自增
		 * */
		public void nodeGrow(){
			count++;
		}
		
		/*
		 * 获取左孩子
		 * */
		public Node getLeft() {
			return left;
		}
		
		/*
		 * 获取右孩子
		 * */
		public Node getRight() {
			return right;
		}
		
		/*
		 * 设置左孩子
		 * */
		public void setLeft(Node node) {
			left = node;
		}
		
		/*
		 * 设置右孩子
		 * */
		public void setRight(Node node){
			right = node;
		}
		
		/*
		 * 左孩子是否为空，若为空返回true，否则返回false
		 * */
		public boolean isLNull() {
			return left == null;
		}
		
		/*
		 * 右孩子是否为空，若为空返回true，否则返回false
		 * */
		public boolean isRNull() {
			return right == null;
		}
		
		/*
		 * 左右孩子是否为空，若为空返回true，否则返回false
		 * */
		public boolean isLRNull() {
			return isLNull() && isRNull();
		}
		
		/*
		 * 是否只有一个孩子，若是返回true，否则返回false
		 * */
		public boolean isOnlyOne() {
			return (isLNull() && !isRNull()) || (!isLNull() && isRNull());
		}
		
		/*
		 * 值是否相等
		 * */
		public int compare(int value) {
			return this.value == value ? 0 : this.value < value ? -1 : 1;
		}
	}

	private Node root = null;
	private int nodeCount = 0;
	private int NO_FIND = ~(1<<31);
	
	/**********************private function***********************/

	/*
	* function				查找节点
	* param	   Node			节点
	* param    int value    要查找的值
	* return   Node			成功返回该结点，否则返回null
	*/
	private Node searchNode(Node btree,int value) {
		// 1.如果该节点为空，则退出
		if (btree == null)
			return null;
		// 2.如果该节点的值等于value，则返回该节点
		else if (btree.compare(value) == 0)
			return btree;
		// 3.如果该节点的值大于value，则递归遍历左子树
		else if (btree.compare(value) == 1)
			return searchNode(btree.getLeft(), value);  //这里记得要加个return，否则最后会执行最后的return null
		// 4.如果该节点的值小于value，则递归遍历右子树
		else if (btree.compare(value) == -1)
			return searchNode(btree.getRight(), value);
		return null;
	}

	/*
	* function				查找父节点
	* param	   Node			节点指针
	* param    int value    要查找的值
	* return   Node			成功返回父节点，否则返回null
	*/
	private Node searchParentNode(Node btree,int value) {
		// 1.如果该节点为空，则退出
		if (btree == null || btree.isLRNull())
			return null;
		// 2.如果该节点的值等于value，则返回该节点
		else if (!btree.isLNull() && btree.getLeft().compare(value) == 0)
			return btree;
		else if (!btree.isRNull() && btree.getRight().compare(value) == 0)
			return btree;
		// 3.如果该节点的值大于value，则递归遍历左子树
		else if (btree.compare(value) == 1)
			return searchParentNode(btree.getLeft(), value);
		// 4.如果该节点的值小于value，则递归遍历右子树
		else if (btree.compare(value) == -1)
			return searchParentNode(btree.getRight(), value);
		return null;
	}

	/*
	* function				创建节点
	* param   value			节点值
	* return  Node			返回创建的节点
	*/
	private Node createNode(int value) {
		return new Node(value);
	}

	/*
	* function				添加节点辅助函数
	* param		Node		节点指针
	* param		Node		要添加的节点
	* return                无
	*/
	private void add(Node btree,Node node) {
		if (btree == null)
			btree = node;
		// 1.如果该节点的值大于value，且其左节点为null，则将node作为该节点的左孩子
		else if (btree.compare(node.value) == 1  && btree.isLNull())
			btree.setLeft(node);
		// 2.如果该节点的值小于value，且其右节点为null，则将node作为该节点的右孩子
		else if (btree.compare(node.value) == -1  && btree.isRNull())
			btree.setRight(node);
		// 3.如果该节点的值大于value，且其左节点不为null，则递归左子树
		else if (btree.compare(node.value) == 1  && !btree.isLNull())
			add(btree.getLeft(), node);
		// 4.如果该节点的值小于value，且其右节点不为null，则递归右子树
		else if (btree.compare(node.value) == -1  && !btree.isRNull())
			add(btree.getRight(), node);
	}

	/*
	* function				删除节点辅助函数
	* param   cur			需要删除的节点
	* param   par			需要删除节点的父节点
	* param   bLeft         cur是左节点还是右节点
	* return                无
	*/
	private void delete(Node cur, Node par, boolean bLeft) {
		// 1.若该节点无孩子，则直接删除
		if (cur.isLRNull()) {
			if (bLeft)
				par.setLeft(null);
			else
				par.setRight(null);
		}
		// 2.若该节点只有一个孩子，则将该孩子直接顶替到原来的位置上
		else if (cur.isOnlyOne()) {
			if (!cur.isLNull())  //根据bLeft的值来修改孩子节点
				if (bLeft)
					par.setLeft(cur.getLeft());
				else
					par.setRight(cur.getLeft());
			else
				if (bLeft)
					par.setLeft(cur.getRight());
				else
					par.setRight(cur.getRight());
		}
		// 3.若该节点有两个孩子，则将该节点的右子树中最小的那个节点替换上去
		else {
			Node minNode = findMinNode(cur.getRight());  //找到需要删除的节点的右子树中最小的节点
			Node parent = searchParentNode(cur, minNode.value); //同样，获取父节点是为了置孩子节点为null
			cur.value = minNode.value; //修改值就好
			if (parent.getLeft().compare(minNode.value) == 0)  //如果是在左孩子中找到最小值
				parent.setLeft(null);
			else if (parent.getRight().compare(minNode.value) == 0) //如果是在右孩子中找到，则左孩子肯定为null，这时只需要修改指向即可
				cur.setRight(minNode.getRight());
		}
	}

	/*
	* function				查找最小节点
	* param   Node			指定从哪个根节点开始查找
	* return                无
	*/
	private Node findMinNode(Node btree) {
		if (btree == null)
			return null;
		Node cur = btree;
		while (!cur.isLNull())
			cur = cur.getLeft();
		return cur;
	}

	/*
	* function				打印二叉树辅助函数
	* param	  Node			节点指针
	* param   boolean		true(从小到大输出)，false（从大到小输出）
	* return                无
	*/
	private void print(Node btree, boolean bMinToMax)
	{
		if (bMinToMax)
		{
			if (btree != null)
			{
				print(btree.getLeft(),bMinToMax);
				int i = btree.count;
				while (i-- != 0)                     	//循环输出相同的值
					System.out.print(btree.value + " ");
				print(btree.getRight(), bMinToMax);
			}
		}
		else
		{
			if (btree != null)
			{
				print(btree.getRight(), bMinToMax);
				int i = btree.count;
				while (i-- != 0)                       //循环输出相同的值
					System.out.print(btree.value + " ");
				print(btree.getLeft(), bMinToMax);
			}
		}
	}

	/**********************private function***********************/
	
	
	/**********************public function***********************/

	/*
	* function				查找值
	* param    int value    要查找的值
	* return				成功返回该值，失败返回NO_FIND
	*/
	public int search(int value) {
		Node node = searchNode(root, value);
		return node == null ? NO_FIND : node.value;
	}

	/*
	* function				添加值
	* param   int			要添加的值
	* return                无
	*/
	public void add(int value) {
		// 1.如果root为null，说明当前是第一次添加根节点
		if (root == null)
			root = createNode(value);
		else {
			// 2.先查找value值，如果存在，则直接count++
			Node node = searchNode(root, value);
			if (node != null)
				node.nodeGrow();
			else {
				// 3.如果该值不存在，则创建新结点
				node = createNode(value);

				// 4.添加节点
				add(root, node);
			}
		}
		nodeCount++;
	}

	/*
	* function				删除值
	* param    int value    要删除的值
	* return                删除失败返回false，否则返回true
	*/
	public boolean delete(int value) {
		// 1.如果btree为空则退出
		if (root == null) return false;
		// 2.如果该节点是根节点的话
		else if (root.compare(value) == 0) {
			Node rootPar = new Node(0);
			rootPar.setLeft(root);
			delete(root, rootPar, true);   		//这里模拟下面的，声明一个root的父节点，然后以同样的方式调用它
			root = rootPar.getLeft();			   	//最后要将root节点的指向修改	
			--nodeCount;		
		}
		else {
			// 3.查找需要删除节点的父节点  (需要找到父节点是因为最后要将它的孩子置为null)
			Node par = searchParentNode(root, value);
			if (par == null)
				return false;
			// 4.删除该节点(因为不懂是左还是右，所以要进一步判断)
			if (!par.isLNull() && par.getLeft().compare(value) == 0)
				delete(par.getLeft(), par, true);
			else
				delete(par.getRight(), par, false);
			--nodeCount;
		}
		return true;
	}

	/*
	* function				获取二叉树节点个数(包括重复的)
	* return                返回节点个数
	*/
	public int size() {
		return nodeCount;
	}

	/*
	* function				获取最小值
	* return                返回二叉树的最小值
	*/
	public int getMinValue() {
		Node node = findMinNode(root);
		return node != null ? node.value : NO_FIND;
	}

	/*
	* function				获取最大值
	* return                返回二叉树的最大值
	*/
	public int getMaxValue() {
		if (root == null)
			return NO_FIND;
		Node cur = root;
		while (!cur.isRNull())
			cur = cur.getRight();
		return cur.value;
	}

	/*
	* function				遍历二叉查找树
	* param   bool			true(从小到大输出)，false（从大到小输出）
	* return                无
	*/
	public void print(boolean bMinToMax) {
		print(root, bMinToMax);
		System.out.println();
	}

	/**********************public function***********************/
}
