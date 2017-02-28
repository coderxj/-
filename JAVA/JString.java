
/*
* author: acme
*   date: 2017-2-28
*  blogs: http://blog.csdn.net/qq_18297675
*/
public class JString {

	private char[] string;   
	private int curLen = 0;
	private int maxLen = 256;
	/*
	* function			默认长度，空字符串
	*/
	public JString() {													
		string = new char[maxLen];			//为数据区分配空间
	}

	/*
	* function			可以指定字符串最大长度
	* param    len		长度
	*/
	public JString(int maxLen) {											
		string = new char[maxLen];			//为数据区分配空间
		curLen = 0;                         //当前串长度为0
		this.maxLen = maxLen;				//串的最大长度为用户指定的maxLen
	}

	/*
	* function			可以指定字符串初始化
	* param    s		字符串
	*/
	public JString(String s) {
		string = new char[maxLen];			//为数据区分配空间
		curLen = s.length();				//当前串长度为str的长度
		for (int i = 0;i < curLen;i++)
			string[i] = s.charAt(i);
	}
	
	/*
	* function			可以指定字符串初始化
	* param    s		字符串
	*/
	public JString(char[] s) {
		string = new char[maxLen];			//为数据区分配空间
		curLen = csize(s);					//当前串长度为str的长度
		for (int i = 0;i < curLen;i++)
			string[i] = s[i];
	}

	/*
	* function			获取字符串大小
	* return   int      返回字符串大小
	*/
	public int size() {
		return curLen;
	}

	/*
	* function			重新分配空间
	* return   int      返回分配空间的大小，失败返回-1
	*/
	private int reAlloc() {
		if (string == null)  //防止引用空指针
			return -1;
		int len =maxLen;
		char[] temp = new char[len];
		for (int i = 0;i < len;i++)						//将数据暂存起来
			temp[i] = string[i];
		maxLen *= 2;									//扩大为原来的两倍
		string = new char[maxLen];
		for (int i = 0;i < len;i++)						//将数据暂存起来
			string[i] = temp[i];						//恢复数据 
		return maxLen;
	}

	/*
	* function			计算字符串长度(窄字符)
	* param    str		字符串
	* return		    返回长度
	*/
	private int csize(final char[] str)
	{
		if (str == null) return 0;
		int len = 0;
		for (int i = 0; i < str.length; i++) {
			if ((int)str[i] < 0)  //中文第一个字节为负数
				i++;
			++len;
		}
		return len;
	}

	/*
	* function			添加一个字符到最后
	* param    char		字符
	* return		    无
	*/
	public void pushRear(char ch) {
		if (string == null)  //防止引用空指针
			return;
		if (curLen == maxLen)  //如果空间满了 需要重新分配
			reAlloc();
		string[curLen++] = ch;
	}

	/*
	* function			添加字符串到最后
	* param    sub		字符串
	* return		    无
	*/
	public void pushRear(char[] sub) {
		if (string == null)  //防止引用空指针
			return;
		int len = csize(sub);
		while (curLen + len >= maxLen)  //如果空间满了 需要重新分配
			reAlloc();
		for (int i = 0;i < len;i++)
			string[curLen + i] = sub[i];
	}

	/*
	* function			添加一个字符到前面
	* param    char		字符
	* return		    无
	*/

	public void pushFront(char ch) {
		if (string == null)  //防止引用空指针
			return;
		if (curLen == maxLen)  //如果空间满了 需要重新分配
			reAlloc();
		for (int i = curLen;i > 0;i--)
			string[i] = string[i - 1];
		string[0] = ch;
		curLen++;
	}

	/*
	* function			添加字符串到前面
	* param    sub		字符串
	* return		    无
	*/

	public void pushFront(char[] sub) {
		if (string == null)  //防止引用空指针
			return;
		int len = csize(sub);
		while (curLen + len >= maxLen)  //如果空间满了 需要重新分配
			reAlloc();
		for (int i = curLen + len - 1;i >= 0;i--)
			string[i] = string[i - len];
		for (int i = 0;i < len;i++)
			string[i] = sub[i];
		curLen += len;
	}

	/*
	* function			删除最后n个字符
	* return		    无
	*/
	public void popRear(int n) {
		curLen = curLen - n > 0 ? (curLen -= n) : 0;
	}

	/*
	* function			删除前n个字符
	* return		    无
	*/
	public void popFront(int n) {
		if (string == null)  //防止引用空指针
			return;
		if (curLen - n > 0) {
			for (int i = 0;i < curLen - n;i++)
				string[i] = string[i + n];
			curLen -= n;
		}
		else
			curLen = 0;
	}

	/*
	* function			删除子串
	* param    start	删除的起始位置
	* param    end		删除的终点位置
	* return		    删除失败返回-1
	*/
	public int deletesub(int start, int end) {
		if (string == null)  //防止引用空指针
			return -1;
		if (start < 0 || start > curLen - 1 || end < 0 ||
			end >  curLen - 1 || end < start)
			return -1;
		int len = end - start;
		curLen -= len;
		for (int i = start;i <= curLen;i++)
			string[i] = string[i + len + 1];
		return len + 1;
	}

	/*
	* function			删除子串
	* param    start	删除的起始位置
	* param    len		要删除的长度
	* return		    删除失败返回-1
	*/
	public int deletesubLen(int start, int len) {
		if (string == null)  //防止引用空指针
			return -1;
		if (start < 0 || start > curLen - 1)
			return -1;
		if (start + len > curLen)
			len = curLen - start;
		curLen -= len;
		for (int i = start;i <= curLen;i++)
			string[i] = string[i + len];
		return len;
	}

	/*
	* function			截取子串
	* param    start	截取的起始位置
	* param    end		截取的终点位置
	* return		    截取失败返回NULL
	*/
	public char[] subString(int start, int end) {
		if (string == null)  //防止引用空指针
			return null;
		if (start < 0 || start > curLen - 1 || end < 0 ||
			end >  curLen - 1 || end < start)
			return null;
		char[] sub = new char[end - start];
		for (int i = start; i <= end;i++)
			sub[i] = string[i];
		//sub[end - start + 1] = '\0';   //最后要记得加上‘\0’结束符，不然输出的时候会有乱码出来
		return sub;
	}

	/*
	* function			截取子串
	* param    start	截取的起始位置
	* param    len		截取的长度
	* return		    截取失败返回NULL
	*/
	public char[] subStringLen(int start, int len) {
		if (string == null)  //防止引用空指针
			return null;
		if (start < 0 || start > curLen - 1)
			return null;
		if (start + len > curLen)
			len = curLen;
		char[] sub = new char[len];
		for (int i = start; i <= start + len;i++)
			sub[i] = string[i];
		//sub[len] = '\0';   //最后要记得加上‘\0’结束符，不然输出的时候会有乱码出来
		return sub;
	}

	/*
	* function			替换字符
	* param    s		替换的源字符
	* param    d		替换后的字符
	* return		    替换失败返回-1
	*/
	public int replace(char s, char d) {
		if (string == null)  //防止引用空指针
			return -1;
		int pos = 0;
		int count = 0;
		if ((pos = findFirst(s)) == -1)      //如果该字符不存在，则替换失败
			return -1;
		do {
			string[pos] = d;
			++count;
		} while ((pos = find(s, pos + 1)) != -1);
		return count;                              //返回成功替换的字符数
	}

	/*
	* function			替换字符
	* param    local	替换的位置
	* param    d		替换后的字符
	* return		    替换失败返回-1
	*/
	public int replace(int local, char d) {
		if (string == null)  //防止引用空指针
			return -1;
		if (local < 0 || local > curLen - 1)
			return -1;
		string[local] = d;
		return local;
	}

	/*
	* function			替换子串
	* param    s		替换的源串
	* param    d		替换的目标串
	* return		    替换失败返回-1
	*/
	public int replace(char[] s, char[] d) {
		if (string == null)  //防止引用空指针
			return -1;
		int pos = 0;
		int count = 0;
		int lens = csize(s);
		int lend = csize(d);
		if ((pos = findFirst(s)) == -1)      //如果该字符不存在，则替换失败
			return -1;
		do {
			//如果s串和d串长度相等，则直接覆盖即可
			if (lens == lend) {
				for (int i = 0;i < lens;i++)
					string[i + pos] = d[i];
			} else if (lens > lend) {//如果s串大于d串，则需要覆盖后往前移（填充位置）
				for (int i = 0;i < lend;i++)    //覆盖
					string[i + pos] = d[i];
				int p = lens - lend;            //往前移动的距离
				for (int i = pos + lend;i < curLen;i++)    //往前移
					string[i] = string[i + p];
				curLen -= p;
			} else {//如果s串小于d串，则需要覆盖前往后移（空出位置）
				int p = lend - lens;            //往后移动的距离
				for (int i = curLen + p;i >= pos + lens;i--)    //往后移
					string[i] = string[i - p];
				for (int i = 0;i < lend;i++)    //覆盖
					string[i + pos] = d[i];
				curLen += p;
			}
			++count;
		} while ((pos = find(s, pos + lend)) != -1);
		return count;                              //返回成功替换的字符数
	}

	/*
	* function			替换子串
	* param    local	替换的起始位置
	* param    d		替换的目标串
	* return		    替换失败返回-1
	*/
	public int replace(int local, char[] d) {
		if (string == null)  //防止引用空指针
			return -1;
		if (local < 0 || local > curLen - 1)
			return -1;
		int len = csize(d);
		if (local + len >= maxLen)   //空间不够 重新分配
			reAlloc();
		for (int i = 0;i < len;i++)
			string[i + local] = d[i];
		curLen += len;
		return local;
	}

	/*
	* function			查找字符第一次出现的位置
	* param    ch		要查找的字符
	* return		    查找失败返回-1
	*/
	public int findFirst(char ch) {
		if (string == null)  //防止引用空指针
			return -1;
		for (int i = 0;i < curLen;i++)
			if (string[i] == ch)
				return i;
		return -1;
	}

	/*
	* function			查找子串第一次出现的位置
	* param    sub		要查找的子串
	* return		    查找失败返回-1
	*/
	public int findFirst(char[] sub) {
		if (string == null)  //防止引用空指针
			return -1;
		int i = 0, j = 0;
		int len = csize(sub);
		for (;i < curLen;i++) {
			for (j = 0;j < len;j++)
				if (string[i + j] != sub[j])
					break;
			if (j == len)
				return i;
		}
		return -1;
	}

	/*
	* function			查找字符最后一次出现的位置
	* param    ch		要查找的字符
	* return		    查找失败返回-1
	*/
	public int findLast(char ch) {
		if (string == null)  //防止引用空指针
			return -1;
		for (int i = curLen - 1;i >= 0;i--)
			if (string[i] == ch)
				return i;
		return -1;
	}

	/*
	* function			查找子串最后一次出现的位置
	* param    ch		要查找的子串
	* return		    查找失败返回-1
	*/
	public int findLast(char[] sub) {
		if (string == null)  //防止引用空指针
			return -1;
		int i = curLen - 1, j = 0;
		int len = csize(sub);
		for (;i >= 0;i--) {
			for (j = 0;j < len;j++)
				if (string[i - j] != sub[len - 1 - j])  //从后往前比
					break;
			if (j == len)
				return i - len + 1;
		}
		return -1;
	}

	/*
	* function			给定起始位置查找字符出现的位置
	* param    ch		要查找的字符
	* param    start	起始位置
	* return		    查找失败返回-1
	*/
	public int find(char ch, int start) {
		if (string == null)  //防止引用空指针
			return -1;
		for (int i = start;i < curLen;i++)
			if (string[i] == ch)
				return i;
		return -1;
	}

	/*
	* function			查找子串最后一次出现的位置
	* param    sub		要查找的子串
	* param    start	起始位置
	* return		    查找失败返回-1
	*/
	public int find(char[] sub, int start) {
		if (string == null)  //防止引用空指针
			return -1;
		int i = start, j = 0;
		int len = csize(sub);
		for (;i < curLen;i++) {
			for (j = 0;j < len;j++)
				if (string[i + j] != sub[j])
					break;
			if (j == len)
				return i;
		}
		return -1;
	}

	/*
	* function			插入字符
	* param    ch		要插入的字符
	* param    local    要插入的位置
	* return		    无
	*/
	public void Insert(char ch, int local) {
		if (string == null)  //防止引用空指针
			return;
		local = local < 0 ? 0 : local >= curLen ? curLen : local;
		if (curLen + 1 >= maxLen)  //如果空间不够 重新分配
			reAlloc();
		for (int i = curLen;i > local;i--)
			string[i] = string[i - 1];
		string[local] = ch;
		curLen++;
	}

	/*
	* function			插入字符串
	* param    sub		要插入的字符串
	* param    local    要插入的位置
	* return		    无
	*/
	public void Insert(char[] sub, int local)
	{
		if (string == null)  //防止引用空指针
			return;
		local = local < 0 ? 0 : local >= curLen ? curLen : local;
		int len = csize(sub);
		while (curLen + len >= maxLen)//如果空间不够 重新分配
			reAlloc();
		for (int i = curLen + len - 1;i >= local;i--)
			string[i] = string[i - len];
		for (int i = 0;i < len;i++)
			string[i + local] = sub[i];
		curLen += len;
	}

	/*
	* function			统计字符出现过的次数
	* param    ch		要查找的字符
	* return		    返回字符出现的次数
	*/
	public int AppearTimes(char ch)
	{
		if (string == null)  //防止引用空指针
			return 0;
		int count = 0;
		for (int i = 0;i < curLen;i++)
			if (string[i] == ch)
				++count;
		return count;
	}

	/*
	* function			统计子串出现过的次数
	* param    sub		要查找的子串
	* return		    返回字符出现的次数
	*/
	public int AppearTimes(char[] sub)
	{
		if (string == null)  //防止引用空指针
			return 0;
		int len = csize(sub);
		int pos = 0;
		if ((pos = findFirst(sub)) == -1)
			return 0;
		int count = 1;
		while ((pos = find(sub, pos + len)) != -1)
			++count;
		return count;
	}

	/*
	* function			比较两个String是否相等
	* param    s1		字符串1
	* param    s2		字符串2
	* return		    相等返回true
	*/
	public boolean equal(JString s1, JString s2) {
		if (s1.string == null || s2.string == null)  //防止引用空指针
			return false;
		int len1 = s1.size();
		int len2 = s2.size();
		if (len1 != len2)
			return false;
		for (int i = 0;i < len1;i++)
			if (s1.string[i] != s2.string[i])
				return false;
		return true;
	}

	/*
	* function			比较两个String是否相等
	* param    s1		字符串1
	* param    s2		字符串2
	* return		    相等返回true
	*/
	public boolean equal(final char[] s1, final char[] s2) {
		if (s1 == null || s2 == null)  //防止引用空指针
			return false;
		int len1 = csize(s1);
		int len2 = csize(s2);
		if (len1 != len2)
			return false;
		for (int i = 0;i < len1;i++)
			if (s1[i] != s2[i])
				return false;
		return true;
	}

	/*
	* function			清除字符串
	* return		    无
	*/
	public void clear() {
		curLen = 0;
	}

	/*
	* function			销毁字符串
	* return		    无
	*/
	public void destroy() {
		string = null;
		curLen = 0;
	}

	/*
	* function			获取字符串
	* param    str		字符串
	* return		    返回data
	*/
	char[] GetString() {
		if (string == null)  //防止引用空指针
			return null;
		return string;
	}

	/*
	* function			打印字符串
	* param    start    起始位置
	* param    end      终点位置
	* return		    无
	*/
	public void print(int start, int end) {
		if (string == null)  //防止引用空指针
			return;
		start = start<0 || start > curLen - 1 ? 0 : start;	//防止越界
		end = end<0 || end > curLen - 1 ? curLen : end;	//防止越界
		if (end < start) {//防止倒置
			int temp = 0;
			temp = start;
			start = end;
			end = start;
		}
		for (int i = start;i < end;i++)
			System.out.print(string[i]);
		System.out.println();
	}
	@Override
	public String toString() {
		return new String(string);
	}
}
