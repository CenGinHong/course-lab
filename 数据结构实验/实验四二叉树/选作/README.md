## 实验题目

​		二叉树实现学生健康管理系统（选做）



## 中文摘要

​		在计算机科学中，二叉树是每个结点最多有两个子树的树结构。通常子树被称作“左子树”（left subtree）和“右子树”（right subtree）。二叉树常被用于实现二叉查找树和二叉堆。

## 实验目的

- 掌握二叉树的定义和抽象数据储存表示。
- 掌握二叉树的基本算法，如建树，遍历（前序中序后序遍历的递归实现及非递归实现），求树高，求叶子总数等。
- 掌握基于二叉树的动态搜索结构，提高对信息管理系统中操作的效率

## 实验内容

### 问题描述

 		实现学生健康情况管理的几个操作功能（新建、插入、删除、从文件读取、写入文件和查询、屏幕输出等功能）。健康表中学生的信息有学号、姓名、出生日期、性别、身体状况等。

### 实验内容

1．系统的菜单功能项如下：

1------新建学生健康表

2------向学生健康表插入学生信息

3------在健康表删除学生信息

4------从文件中读取健康表信息

5------向文件写入学生健康表信息

6------在健康表中查询学生信息（按学生学号来进行查找）

7------在屏幕中输出全部学生信息

8------按学生学好来查找学生信息

9-----退出

### 实验思路：

- 根据二叉树的抽象数据类型，利用二叉链表实现一个二叉树。
- 因为要对学生的信息进行管理以及查看等操作，所以要结合搜索结构中的二叉搜索树进行编写
- 因为二叉搜索树要进行多次元素的比对，如二叉搜索树利用模板类写的话就要在其data域中所要用的类或结构体重载运算符函数
- 根据二叉搜索树的特点编写插入，删除，查找等算法



### 实验设计

##### 存储结构

###### 采用二叉链表的结构进行存储

![image-20210208114725620](https://gitee.com/chen_jian_hang/pic/raw/master/image/image-20210208114725620.png)

###### 树节点定义

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

###### 学生结构体

```
struct Student
{
	string num;
	string name;
	string sex;
	string body;
	string birthday;
	Student(string num, string name, string sex, string body, string birthday) 
		:num(num), name(name), sex(sex), body(body), birthday(birthday) {};
	Student() {}
	friend istream& operator >> (istream& in, Student &right);//重载输入流函数
	friend ofstream& operator <<(ofstream & out, Student & right);//重载文件输入流函数
	friend ostream& operator << (ostream& out, Student &right);//重载输出流函数
	bool operator ==(Student &right) {return this->num == right.num ? true : false;}
	bool operator <(Student &right) {	return this->num < right.num ? true : false;}
	bool operator > (Student &right) {	return this->num > right.num ? true : false;}
	bool operator ==(string num) {	return this->num == num ? true : false;}
	bool operator >(string num) {	return this->num > num ? true : false;}
	bool operator<(string num) {	return this->num < num ? true : false;}
};
```



##### 关键算法设计

###### 插入算法

```c++
template<class E, class K>
inline bool BST<E, K>::Insert(E & e1, BSTNode<E, K>*& ptr)
{
	if (ptr == nullptr) {
		ptr = new BSTNode<E, K>(e1);
		return true;
	}
	else if (ptr->data > e1) {
		Insert(e1, ptr->leftchild);
	}
	else if (ptr->data < e1) {
		Insert(e1, ptr->rightchild);
	}
	else {
		return false;
	}
}
```

- 从根结点开始进行插入，如在当前结点为空，说明没有具有相同的关键码的元素，把结点加到树上

-  否则比对当前指针的data域的关键码和插入元素的关键码

  iii. 若插入元素关键码大在右子树递归进行，否则在左子树中递归进行，相等则不符合二叉搜索树的构建规则,返回false

###### 前序遍历

```c++
inline BSTNode<E, K>* BST<E, K>::Search(K x, BSTNode<E, K>* ptr)
{
	if (ptr == nullptr) {
		return nullptr;
	}
	else if (ptr->data > x) {
		return Search(x, ptr->leftchild);
		//关键码比当前结点关键码小，左子树递归
	}
	else if (ptr->data < x) {
		return Search(x, ptr->rightchild);
		//同理右子树递归
	}
	else {
		return ptr;
	}
}
```

- 利用二叉搜索树类似于折半查找的判定树性质快速逼近所查找关键码对应元素
- 通过比对关键码进行判定，思想与插入算法类似，此处不再赘述

###### 新建树算法

就是循环调用插入函数，此处不再赘述

###### 输出学生信息函数

 利用搜索算法返回的指针，打印该节点的data

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

![](https://gitee.com/chen_jian_hang/pic/raw/master/image/image-20210208115821467.png)

![](https://gitee.com/chen_jian_hang/pic/raw/master/image/image-20210208115827054.png)



## 实验心得

​		树是常用的数据结构。通过二叉搜索树实验加深了我对树形结构和搜索结构结合的认识，巩固了课本中所学的关于树的基本算法。按要求完成了实验内容。  

通过实验，有如下几点收获和体会：

1. 二叉搜索树这一实验让我更进一步理解了树形结构和搜索结构在数据结构中的重要性，二叉链表在树结构的应用也让我更能透彻理解链表的意义。

经过本次实验基本上解决的一些所遇到的问题，我对二叉搜索树的结构等有了较为深入的理解。我会继续我的兴趣编写程序的，相信在越来越多的尝试之后，自己会不断进步。

## 参考文献

1. 《数据结构》，朱振元，2003，清华大学出版社
2. 《数据结构实验指导书》，2008，华南师范大学计算机学院自用教材
3. 殷人昆. 数据结构（用面向对象方法与C++描述），清华大学出版社，1999