## 实验题目

​		链表实现学生健康管理系统



## 中文摘要

​		链表是一种物理存储单元上非连续、非顺序的存储结构，数据元素的逻辑顺序是通过链表中的指针链接次序实现的。链表由一系列结点（链表中每一个元素称为结点）组成，结点可以在运行时动态生成。

## 实验目的

- 掌握链表和抽象数据储存表示。
- 掌握链表类的基本算法，如插入，搜素，删除，求长度等。

- 在实际应用场景中使用链表实现功能

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

- 编写结构体存放单个学生的信息。

- 根据链表的抽象数据类型，编写单链表的模板类。

- 把单链表应用到实际场景------学生健康管理系统中



### 实验设计

##### 存储结构

###### 学生结点

```c++
struct Student {
	friend ostream& operator << (ostream& out, Student &right);//重载<<
	friend istream& operator >>(istream& in, Student &right);//重载>>
	bool operator ==(string num) {//用于与关键码（学号）比较
		return (this->num == num) ? true : false;
	}
	string num;
	string name;
	string birthday;
	string sex;
	string body;
	Student(string num, string name, string sex, string birthday, string body)
		:num(num), name(name), sex(sex), birthday(birthday), body(body) {}
	Student() {}
};
```



##### 功能模块设计

###### 插入算法

```c++
inline bool LinkedList<T, K>::insert(const LinkNode<T> & x)
```

- 传入被查节点信息，返回值为插入是否成功（当内存分配失败是返回失败）

- 创建一个工作指针cur，定位到链表的末尾。

- 把传进来的节点新的添加到工作指针的后面，即链表的末端

###### 删除算法

```c++
inline bool LinkedList<T, K>::remove(K key)
```

- 传进来被删结点的关键码，在学生管理系统中关键码为学生的学号

- 在遍历链表，若未找到该结点信息则返回false

- 如成功找到该节点信息就重新拉链。

- 注意：因为删除结点在链表中间时需要重新拉链，故需要创建两个工作指针

###### 搜索算法

```c++
inline LinkNode<T> * LinkedList<T, K>::search(K key)
```

- 创建一个工作指针，遍历数组比对数组元素的关键码和传入关键码
- 若找到则返回该元素的指针，否则返回NULL

###### 新建表算法

```c++
inline void LinkedList<T, K>::initialize()
```

- 利用尾插法建立单链表，创建一个指向尾部的指针last

- 把新增的结点添加到last后面，再把last移动到新增节点尾部，即last永远指向单链表尾部

###### 销毁链表算法

```c++
inline void LinkedList<T, K>::makeEmpty()
```

- 定义一个指针指向附加头节点的下一个结点，若该节点不为空，则重新拉链

- 把该节点从该链表中脱离后delete

- 循环该过程知道附加头节点后的link为空

#### 流程图

![image-20210208113814373](https://gitee.com/chen_jian_hang/pic/raw/master/image/image-20210208113814373.png)

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

![image-20210208114203234](https://gitee.com/chen_jian_hang/pic/raw/master/image/image-20210208114203234.png)

![image-20210208114206934](https://gitee.com/chen_jian_hang/pic/raw/master/image/image-20210208114206934.png)



## 实验心得

​		链表是数据结构的基础。在数据结构中很多的结构都是运用链表作为基础而发展出来的，掌握链表对于学习其他数据结构有着重大深远的意义。  

通过实验，有如下几点收获和体会：

1. 链表这一实验让我能更直观理解链表的结构，同时对于之前指针的理解有了更上一个层次。
2. 链表类的算法编写让我对数据的组织管理有了更好的实践掌握。
3. 编写管理系统让我同时对c++的语法知识有了进一步的了解

​    经过本次实验基本上解决的一些所遇到的问题，我对链表的结构等有了较为深入的理解。我会继续我的兴趣编写程序的，相信在越来越多的尝试之后，自己会不断进步。

## 参考文献

1. 《数据结构》，朱振元，2003，清华大学出版社
2. 《数据结构实验指导书》，2008，华南师范大学计算机学院自用教材
3. 殷人昆. 数据结构（用面向对象方法与C++描述），清华大学出版社，1999