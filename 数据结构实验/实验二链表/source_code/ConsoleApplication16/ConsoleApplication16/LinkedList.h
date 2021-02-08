#pragma once
#include<iostream>
#include<string>
using namespace std;

template<class T>
struct LinkNode
{
	T data;
	LinkNode<T> *link;
	LinkNode(LinkNode<T> *ptr = nullptr) :link(ptr) {}
	LinkNode(const T& x, LinkNode<T> *ptr = nullptr) :data(x), link(ptr) {}
};


template<class T, class K>
class LinkedList
{
protected:
	LinkNode<T> *first;
public:
	LinkedList();
	~LinkedList();
	void initialize();
	void makeEmpty();
	bool isEmpty();
	int length();
	bool insert(const LinkNode<T> &x);
	LinkNode<T> * search(K key);
	bool remove(K key);
	void output();
};

template<class T, class K>
inline LinkedList<T, K>::LinkedList()
{
	first = new LinkNode<T>();
}

template<class T, class K>
inline LinkedList<T, K>::~LinkedList()
{
	makeEmpty();
}

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

template<class T, class K>
inline bool LinkedList<T, K>::isEmpty()
{
	if (first->link == nullptr) {
		return true;
	}
	else {
		return false;
	}
}

template<class T, class K>
inline int LinkedList<T, K>::length()
{
	int length = 0;
	LinkNode<T> *cur = first;
	while (cur->link != nullptr) {
		length++;
		cur = cur->link;
	}
	return length;
}

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

template<class T, class K>
inline void LinkedList<T, K>::output()
{
	LinkNode<T> *cur = first->link;
	while (cur != nullptr)
	{
		cout << cur->data;
		cur = cur->link;
	}
}

