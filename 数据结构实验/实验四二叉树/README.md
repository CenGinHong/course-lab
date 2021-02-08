## 实验题目

​		二叉树实现学生健康管理系统



## 中文摘要

​		在计算机科学中，二叉树是每个结点最多有两个子树的树结构。通常子树被称作“左子树”（left subtree）和“右子树”（right subtree）。二叉树常被用于实现二叉查找树和二叉堆。

## 实验目的

- 掌握二叉树的定义和抽象数据储存表示。
- 掌握二叉树的基本算法，如建树，遍历（前序中序后序遍历的递归实现及非递归实现），求树高，求叶子总数等。

## 实验内容

### 问题描述

​       构造二叉树，再实现二叉树的先序，中序，后序遍历，最后调用求树高，求叶子节点总数等。

实现二叉树的基本功能如下：

### 实验内容

1------建立一棵二叉树

2------前序遍历递归算法

3------前序遍历非递归算法

4------中序遍历递归算法

5------中序遍历非递归算法

6------后序遍历递归算法

7------后序遍历非递归算法

8------求树高

9------求叶子总数

10-----输出二叉树

11-----退出

### 实验思路：

- 根据二叉树的抽象数据类型，利用二叉链表实现一个二叉树。
- 二叉树内的前序中序后序遍历算法利用递归与非递归两种方式实现，非递归算法只要通过结合栈来实现。
- 因为二叉树本身的定义是递归的，所以二叉树的求树高与求叶子结点数结合递归算法实现要来的直观简便。



### 实验设计

##### 存储结构

###### 采用二叉链表的结构进行存储

![image-20210208114725620](https://gitee.com/chen_jian_hang/pic/raw/master/image/image-20210208114725620.png)

```c++
template<class T>
struct BinTreeNode
{
	T data;
	BinTreeNode *leftchild;
	BinTreeNode *rightchild;
	BinTreeNode(T data, BinTreeNode *leftchild = nullptr, BinTreeNode *rightchild = nullptr) :data(data), rightchild(rightchild), leftchild(leftchild) {};
	BinTreeNode(BinTreeNode *leftchild = nullptr, BinTreeNode *rightchild = nullptr) :leftchild(leftchild), rightchild(rightchild) {};
};
```



##### 关键算法设计

###### 建立二叉树

```c++
template<class T>
inline void BinaryTree<T>::createTree(BinTreeNode<T>* &subtree)
{
	T data;
	data = cin.get();
	if (data == RefValue) {
		return;
	}
	else {
		BinTreeNode<T> *newnode = new BinTreeNode<T>(data);
		subtree = newnode;
		createTree(subtree->leftchild);
		createTree(subtree->rightchild);
	}
}
```

-  利用前序遍历进行建树，先构建根节点，将输入值存进结点
- 询问是否继续建树，是则将该结点的左孩子作为参数进行递归，然后重复该思路将右孩子作为参数传进递归函数中
- 在递归函数中，递归终止条件时输入的是‘ ‘（空格），否则将输入值作为结点数据

###### 前序遍历

```c++
template<class T>
inline void BinaryTree<T>::preOrder(BinTreeNode<T>& subtree, void(*visit)(BinTreeNode<T>*subtree))//前序遍历输出
{
	if (subtree == nullptr) {
		return;
	}
	visit(subtree);
	preOrder(subtree->leftchild, visit);
	preOrder(subtree->rightchild, visit);
}
```

- 利用先访问根节点，然后访问在左子树中递归访问，再再右子树中进行递归访问 
- 该函数递归的出口是当前访问的节点为空
- 后序遍历，中序遍历的思路与前序遍历相似，只是调换了访问函数（visit）的位置，此处不在赘述

###### 前序遍历非递归算法

```c++
template<class T>
inline void BinaryTree<T>::preOrder1(void(*visit)(BinTreeNode<T>*subtree))//前序非递归遍历
{
	stack<BinTreeNode<T> * > s;
	BinTreeNode *p = root;
	while (!s.empty()) {
		visit(p);
		if (p->rightchild != nullptr) {
			s.push(p->rightchild);
		}
		if (p->leftchild != nullptr) {
			p = p->leftchild;
		}
		else {
			p = s.top();
			s.pop();
		}
	}
}
```

- 在二叉树先序遍历非递归算法中，先将根结点压栈，在栈不为空的时候执行循环：
- 让栈顶元素p出栈，访问栈顶元素p，如果p的右孩子不为空，则让其右孩子先进栈，如果p的左孩子不为空，则再让其左孩子进栈(进栈顺序为先右孩子，再左孩子)。

###### 求树高算法

```c++
template<class T>
inline int BinaryTree<T>::getHeight(BinTreeNode<T>* subtree)//求树高
{
	if (subtree != nullptr) {
		return 1 + (getHeight(subtree->leftchild) > getHeight(subtree->leftchild)) ? getgetHeight(subtree->leftchild) : getHeight(subtree->leftchild);
	}
	else {
		return 0;
	}
}
```

- 在二叉树求树高算法中，通过递归调用求树高算法来求出左右子树中较高的一侧然后加上1（自身的高度）后返回给上一级：
- 该递归函数的出口为当前节点为空

###### 求叶子节点算法

```c++
template<class T>
inline int BinaryTree<T>::getHeight(BinTreeNode<T>* subtree)//求树高
{
	if (subtree != nullptr) {
		int leftheight = getHeight(subtree->leftchild);
		int rightheight= getHeight(subtree->rightchild);
		return 1 + (leftheight>rightheight) ? leftheight:rightheight;
	}
	else {
		return 0;
	}
}
```

- 在二叉树求叶子节点数算法中，通过递归调用求求叶子总数算法来求出子树中的叶子节点：
- 判断是否为叶子节点的条件是它的左右子树是否为空，若为空则返回1
- 当某某节点的某一子树为空且递归调用函数访问到该空节点时返回0

#### 流程图

![](https://gitee.com/chen_jian_hang/pic/raw/master/image/image-20210208115046994.png)

#### 部分源代码展示

##### 初始化函数

```c++
template<class T, class K>
inline void LinkedList<T, K>::initialize()
{
	LinkNode<T> *newnode, *last = first;
	makeEmpty();
	string flag;
	do {
		T temp;
		cin >> temp;
		newnode = new LinkNode<T>(temp);
		last->link = newnode;
		last = last->link;
		cout << "是否继续新建信息：Y or N?：";
		cin >> flag;
	} while (flag == "Y" || flag == "y");
}
```

##### 销毁函数：

```c++
template<class T, class K>
inline void LinkedList<T, K>::makeEmpty()
{
	LinkNode<T> *cur = first->link;
	if (first->link != nullptr) {
		cur = first->link;
		first = cur->link;
		delete cur;
	}
}
```

##### 搜索函数

```
template<class T, class K>
inline LinkNode<T> * LinkedList<T, K>::search(K key)
{
	LinkNode<T> *cur = first;
	//工作指针
	while (cur->link != nullptr) {
		if (cur->data == key) {
			return cur;
		}
		cur = cur->link;
	}
	return nullptr;
}
```

##### 插入函数

```
template<class T, class K>
inline bool LinkedList<T, K>::insert(const LinkNode<T> & x)
{
	LinkNode<T> *cur = first;
	while (cur->link != nullptr)
	{
		cur = cur->link;
	}
	//新建工作指针并定位到尾部
	LinkNode<T>* newnode = new LinkNode<T>(x);
	if (newnode == nullptr) {
		cerr << "内存分配失败" << endl;
		return false;
	}
	cur->link = newnode;
	return true;
}
```

##### 删除函数

```
template<class T, class K>
inline bool LinkedList<T, K>::remove(K key)
{
	LinkNode<T>* cur = first;
	while (cur->link != nullptr) {
		if (cur->link->data == key) {//找到被删元素，重新拉链
			LinkNode<T> *del = cur->link;
			cur->link = del->link;
			delete del;
			return true;
		}
		cur = cur->link;
	}
	return false;//查找失败
}
```



## 程序主要界面图

![](https://gitee.com/chen_jian_hang/pic/raw/master/image/image-20210208115055164.png)

![](https://gitee.com/chen_jian_hang/pic/raw/master/image/image-20210208115057419.png)

![image-20210208115102805](https://gitee.com/chen_jian_hang/pic/raw/master/image/image-20210208115102805.png)



## 实验心得

​		树是常用的数据结构。通过实验加深了我对树的遍历的认识，巩固了课本中所学的关于树的基本算法。按要求完成了实验内容。  

通过实验，有如下几点收获和体会：

1. 二叉树这一实验让我更进一步理解了树形结构在数据结构中的重要性，二叉链表在树结构的应用也让我更能透彻理解链表的意义。
2. 在二叉树中大量运用的递归算法需要编写的时候逻辑清晰，层次分明，其让我对递归的了解和运用有了新的进步。
3. 在递归算法中极其容易出现思路与实现的结果不一致的情况，这就要求我们要有耐心，进行多次调试，甚至跟踪进去进行单步调试，同时要注意一些编程的细节规范，例如花括号，指针、引用符号的添加位置等等

​        经过本次实验基本上解决的一些所遇到的问题，我对二叉树的结构等有了较为深入的理解。我会继续我的兴趣编写程序的，相信在越来越多的尝试之后，自己会不断进步。

## 参考文献

1. 《数据结构》，朱振元，2003，清华大学出版社
2. 《数据结构实验指导书》，2008，华南师范大学计算机学院自用教材
3. 殷人昆. 数据结构（用面向对象方法与C++描述），清华大学出版社，1999