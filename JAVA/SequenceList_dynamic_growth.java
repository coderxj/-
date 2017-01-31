
/*
* author: acme
*   date: 2017-1-31
*  blogs: http://blog.csdn.net/qq_18297675
*/

public class SequenceList {  //顺序表类
   
	public static void main(String[] args) {
		SequenceList list = new SequenceList();
		for (int i = 0; i < 100000; i++) {
			list.addFromHead(i);
		}
	}
	
	private int max = 100;	//元素的最大个数 
	
	private int e[] = new int[max]; 
	private int count = 0;    		//表中元素个数
	
	private void realloc() {
		int maxSize = max;  //用来下面的复制数据用
		int[] buf = new int[maxSize];  //用来暂时存放原来的数据
		max *= 2;			  //空间增大一倍
		for (int i = 0;i < maxSize;i++) //暂存原来的数据
			buf[i] = e[i];
		e = new int[max];//重新分配空间
		for (int i = 0;i < maxSize;i++) //恢复原来的数据
			e[i] = buf[i];
	}
	
	//判断表是否已满
	public boolean isFull() {
		return this.count == max ? true : false;
	}
	
	//判断表是否为空
	public boolean isEmpty() {
		return this.count == 0 ? true : false;
	}
	
	//获取元素个数
	public int getElementCount() {
		return this.count;
	}
	
	//添加数据（头添加）
	public void addFromHead(int e) {
		if (isFull()) {
			realloc();
		}
		//如果数组中有元素，则往后移，否则直接添加到头部
		if (!isEmpty()) {
			//往后移
			for (int i = this.count;i > 0;i--)
				this.e[i] = this.e[i - 1];
		}
		this.e[0] = e;
		++this.count;
	}
	
	//添加数据（尾添加）
	public void addFromTail(int e) {				
		if (isFull()) {
			realloc();
		}
		this.e[this.count++] = e;
	}
	
	//插入数据（指定位置）
	public void  insert(int local,int e) {			
		if (isFull()) {
			realloc();
		}
		//往后移
		for (int i = this.count;i > local;i--)
			this.e[i] = this.e[i - 1];
		this.e[local] = e;
		++this.count;
	}
	
	//返回元素位置
	public int getLocal(int e) {
		for (int i = 0;i < this.count;i++)
			if (this.e[i] == e)
				return i;
		return -1;  //表示不存在
	}
	
	//删除数据 （指定位置）
	public void deleteFromLocal(int local) {
		//先判断是否为空
		if (isEmpty()) {
			System.out.println("表中无元素，删除操作失败.");
			return;
		}
		if (local >= this.count) {
			System.out.println("指定的位置超过了当前表中的元素个数，删除操作失败.");
			return;
		}
		//直接往前移，覆盖掉
		for (int i = local;i < this.count;i++)
			this.e[i] = this.e[i + 1];
		--this.count;
	}
	
	//删除数据 （指定元素）
	public void deleteFromElement(int e) {		
		//先判断是否为空
		if (isEmpty()) {
			System.out.println("表中无元素，删除操作失败.");
			return;
		}
		int local = getLocal(e);
		//直接往前移，覆盖掉
		for (int i = local;i < this.count;i++)
			this.e[i] = this.e[i + 1];
		--this.count;
	}
	
	//根据指定元素查找，返回位置
	public int searchFromElmemt(int e) {         
		return getLocal(e);
	}
	
	//根据位置查找指定元素 
	public int searchFromLocal(int local) { 
		return local < this.count ? this.e[local] : -1;
	}
	
	//逆转表
	public void reverse() {                     
		int temp;
		for (int i = 0;i < this.count / 2;i++) {
			temp = this.e[i];
			this.e[i] = this.e[this.count - i - 1];
			this.e[this.count - i - 1] = temp;
		}
	}
	
	//遍历元素
	public void print() {                       
		if (isEmpty()) {
			System.out.println("表中无元素.");
			return;
		}
		for (int i = 0;i < this.count;i++)
			System.out.println(this.e[i]);
	}
	
	//复制表
	public void copyList(SequenceList sl) { 
		for (int i = 0;i < this.count;i++)
			sl.addFromTail(this.e[i]);
	}
	
	//排序 （从小到大）
	public void sortByMinToMax() {
		int temp;
		for (int i = 0; i < this.count; i++) {
			for (int j = i + 1; j < this.count; j++) {
				if(this.e[i] > this.e[j]) {
					temp = this.e[i];
					this.e[i] = this.e[j];
					this.e[j] = temp;
				}
			}
		}
	}
	
	//排序 （从大到小）
	public void sortByMaxToMin() {
		int temp;
		for (int i = 0; i < this.count; i++) {
			for (int j = i + 1; j < this.count; j++) {
				if(this.e[i] < this.e[j]) {
					temp = this.e[i];
					this.e[i] = this.e[j];
					this.e[j] = temp;
				}
			}
		}
	}
	
	//修改数据
	public void rewrite(int local, int e)
	{
		if (local < this.count && local >= 0)
			this.e[local] = e;
	}
}
