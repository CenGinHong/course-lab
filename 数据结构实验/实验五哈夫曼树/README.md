## 实验题目

​		哈夫曼编码/译码



## 中文摘要

​		利用霍夫曼编码进行通信可以大大提高信道利用率，缩短信息传输时间，降低传输成本。这要求在发送端通过一个编码系统对待传输数据预先编码，在接收端将传来的数据进行译码（复原）。对于双工信道（即可以双向传输信息的信道），每端都需要一个完整的编/译码系统。试为这样的信息收发站编写一个霍夫曼码的编/译码系统。

## 实验目的

- 掌握哈夫曼树抽象数据储存表示。
- 掌握哈夫曼树的基本算法。
- 应用哈夫曼树解决实际问题

## 实验内容

### 实验内容

- I：初始化（Initialization）。从终端读入字符集大小n，以及n个字符和n个权值，建立霍夫曼树，并将它存于文件hfmTree中。
-  E：编码（Encoding）。利用已建好的霍夫曼树（如不在内存，则从文件hfmTree中读入），对文件ToBeTran中的正文进行编码，然后将结果存入文件CodeFile中。
- D：译码（Decoding）。利用已建好的霍夫曼树将文件CodeFile中的代码进行译码，结果存入文件Textfile中。

### 实验思路：

- 利用数组的实现哈夫曼树
- 编写哈夫曼树的抽象数据类型及其算法。
- 利用哈夫曼树实现测试用例



### 实验设计

##### 存储结构

利用顺序表的形式实现哈夫曼树

###### 哈夫曼结点

```c++
struct HuffNode
{
	char ch;//该结点所存储的编码字符
	string code;//若该结点中为叶结点则存储其字符的编码
	double weight;//权值	int parent;//父母在数组中的下标
	int leftchild;//左孩子在指针中的下标
	int rightchild;//右孩子在指针中的下标
	HuffNode(char ch,int data=-1,int parent = -1, int leftchhild = -1, int rightchild = -1):
		weight(data),ch(ch), parent(parent), leftchild(leftchild), rightchild(rightchild) {}
	HuffNode(int parent = -1, int data = -1, int leftchhild = -1, int rightchild = -1) :
		weight(data),parent(parent), leftchild(leftchild), rightchild(rightchild) {}
	bool operator > (HuffNode &right) {
		return this->weight > right.weight;
	}
	bool operator < (HuffNode &right) {
		return this->weight < right.weight;
	}
};
```

其中所有节点都被存放在一个一维数组中，用int类型的数据指示父母域和孩子域在数组中的下标。



##### 功能模块设计

###### 构造哈夫曼树算法

```c++
void HuffmanTree::Initialize(int sz, char *ch, double *weight)
```

- 传入相关参数，包括字符数组ch，权值数组weight和数组长度n
- 进行n-1次循环，从数组中将两个根节点权值最小的树挑选出来构造新的扩充二叉树
- 进行完n-1次循环后最后一个结点即为哈夫曼树的根节点

###### 构造扩充二叉树算法

```c++
void HuffmanTree::mergeTree(int first, int second, int treesize)
```

- 传入数组的三个元素下标，分别对应其要合成的两棵子树和新的扩充二叉树
- 把两颗子树的权值相加，赋值新的根树得权值
- 把三者得对应的父母域，孩子域值设置好

###### 对数组中的字符进行编码算法

```c++
void HuffmanTree::code()
```

- 对每个具有字符的结点进行沿根节点向上的过程
- 根据判断该节点是父结点的左右孩子从而觉得赋值0还是1
- 到根节点后退出循环，把字符串逆序后存到原来的字符节点中
- 循环该过程直至所有有字符结点都完成此过程

###### 对字符串编码算法

```c++
string HuffmanTree::Encode(string s)
```

- 对传入的字符串进行每个字符的遍历
- 如果数组中未找到对应字符的编码则编码失败

###### 译码算法

```c++
string HuffmanTree::Decode(string s)
```

- 创建一个临时变量，用来逐字符添加编码，已存在数组的哈夫曼编码进行比对。
- 找到该编码就把对应字符添加到结果字符串中，然后清空临时变量，循环该过程。
- 若找不到则添加下一个编码，继续与已有的哈夫曼数组比对
- 如果编码已全部添加到temp中却依然找不到对应字符则说明编码失败

#### 流程图

![](https://gitee.com/chen_jian_hang/pic/raw/master/image/image-20210208120319275.png)

![image-20210208120323371](https://gitee.com/chen_jian_hang/pic/raw/master/image/image-20210208120323371.png)

#### 部分源代码展示

##### 构造哈夫曼树算法

```c++
void HuffmanTree::Initialize(int sz, char *ch, double *weight)
{
	size = sz;
	int curTree = size - 1;
	data = new HuffNode[2 * size - 1];
	for (int i = 0; i < size; i++) {
		data[i].ch = ch[i];
		data[i].weight = weight[i];
	}
	int first, second;
	while (curTree + 1 != 2 * size - 1) {
		getMin(first, second);//得到两个最小值
		curTree++;//数组位置进一
		mergeTree(first, second, curTree);//合成树
	}
	code();
	outputTree();//输出到txt
	cout << "已建立哈夫曼树，并存于工程根目录下hfmTree.txt" << endl;
}
```

##### 构造扩充二叉树算法

```c++
void HuffmanTree::mergeTree(int first, int second, int treesize)
{
	data[treesize].weight = data[first].weight + data[second].weight;
	data[treesize].leftchild = first;
	data[treesize].rightchild = second;
	data[first].parent = treesize;
	data[second].parent = treesize;
}
```

##### 对数组中的字符进行编码算法

```
void HuffmanTree::code()
{
	for (int i=0; i < size; i++) {
		//遍历含有字符的元素
		int j = i;
		string code;
		while (data[j].parent != -1) {
			if (data[data[j].parent].leftchild == j) {
				//如果该结点是其父母的是左孩子
				code += "0";
			}
			else {
				code += "1";
			}
			j = data[j].parent;
		}
		reverse(code.begin(), code.end());
		data[i].code = code;//把编码存储到对应结点，方便解码
		cout << data[i].ch << ":" << code << endl;
	}
}
```

##### 对字符串编码算法

```
string HuffmanTree::Encode(string s)
{
	string result;
	for (int i = 0; i < s.size(); i++) {
		for (int j = 0; j < size; j++) {
			//这里size是哈夫曼树中字符的数量
			if (s[i] == data[j].ch) {
				result += data[j].code;
				break;
			}
			if (j == size - 1) {
				cout << "编码失败" << endl;
				result = "编码失败";
				return result;
			}
		}
	}
	return result;
}
```

##### 译码算法

```
string HuffmanTree::Decode(string s)
{
	string result="";//编码结果
	string temp = "";//存放前缀编码的临时变量
	for (int i = 0; i < s.size(); i++) {
		temp += s[i];//逐个编码添加
		for (int j= 0; j < size; j++) {
			if (data[j].code == temp) {
				result += data[j].ch;
				temp = "";//清空
				break;
			}
			else if (i == s.size() - 1 && j == size - 1 && temp != "") {
				result = "解码失败";
			}
		}
	}
	return result;
}
```



## 程序主要界面图

![](https://gitee.com/chen_jian_hang/pic/raw/master/image/image-20210208120527016.png)

![](https://gitee.com/chen_jian_hang/pic/raw/master/image/image-20210208120529513.png)

![image-20210208120531764](https://gitee.com/chen_jian_hang/pic/raw/master/image/image-20210208120531764.png)

![image-20210208120537188](https://gitee.com/chen_jian_hang/pic/raw/master/image/image-20210208120537188.png)

![image-20210208120540711](https://gitee.com/chen_jian_hang/pic/raw/master/image/image-20210208120540711.png)

![image-20210208120544728](C:\Users\jankin\AppData\Roaming\Typora\typora-user-images\image-20210208120544728.png)

## 实验心得

​		树是常用的数据结构。哈夫曼树是树结构的一个重要应用，在数据结构的一个重要知识点，掌握哈夫曼树的结构对于进一本掌握树型结构的引用有着重大意义。

通过实验，有如下几点收获和体会：

1.在哈夫曼树的实验中我使用数组去实现的而不是用三叉链表，这让我对于数据结构的灵活应用有了新的体会。

2.在本实验中遇到的问题因为书上没有具体的实现代码，需要到网上去查阅资料，所以又很多细节没有注意到，出现问题时甚至要逐步跟踪的方法才能找到根源

## 参考文献

1. 《数据结构》，朱振元，2003，清华大学出版社
2. 《数据结构实验指导书》，2008，华南师范大学计算机学院自用教材
3. 殷人昆. 数据结构（用面向对象方法与C++描述），清华大学出版社，1999