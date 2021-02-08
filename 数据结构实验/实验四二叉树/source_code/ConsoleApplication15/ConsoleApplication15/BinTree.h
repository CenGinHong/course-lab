#pragma once
#include<iostream>
#include<string>
#include"stack.h"
using namespace std;

//树结点定义
template<class T>
struct BinTreeNode
{
	T data;
	BinTreeNode *leftchild;
	BinTreeNode *rightchild;
	BinTreeNode(T data, BinTreeNode *leftchild = nullptr, BinTreeNode *rightchild = nullptr) :data(data), rightchild(rightchild), leftchild(leftchild) {};
	BinTreeNode(BinTreeNode *leftchild = nullptr, BinTreeNode *rightchild = nullptr) :leftchild(leftchild), rightchild(rightchild) {};
};

//二叉树类
template<class T>
class BinaryTree
{
protected:
	BinTreeNode<T> *root;
	T RefValue;
	void createTree(BinTreeNode<T> *&subtree);//构造函数
	void destory(BinTreeNode<T>* subtree);//销毁树
	int getHeight(BinTreeNode<T> *subtree);//返回树高度
	int getSize(BinTreeNode<T> *subtree);//返回结点数
	BinTreeNode<T> *getParent(BinTreeNode<T>* subtree, BinTreeNode<T>* current);//返回父结点
	void traverse(BinTreeNode<T> *subtree, ostream& out);//前序遍历输出
	void preOrder(BinTreeNode<T>* subtree);//前序遍历
	void inOrder(BinTreeNode<T>* subtree);//中序遍历
	void postOrder(BinTreeNode<T>* subtree);//后序遍历
	int getleaf(BinTreeNode<T> *subtree);//得到叶子总数
	void output(BinTreeNode<T> *subtree);//广义表输出
	
public:
	~BinaryTree();
	BinaryTree(T value);
	bool isEmpty();//判空
	BinTreeNode<T>* getParent(BinTreeNode<T>* current);//返回父结点
	int getHeight();//返回树高度
	BinTreeNode<T>* getRoot();//取根
	void preOrder();//前序遍历
	void preOrder1();//前序非递归遍历
	void inOrder();//中序遍历
	void inOrder1();//中序非递归遍历
	void postOrder();//后序遍历
	void traverse();//前序遍历输出
	int getleaf();//得到叶子总数
	void output();//广义表输出二叉树
	void showMenu();//展示菜单
	void createTree();//建立树
};

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

template<class T>
inline void BinaryTree<T>::destory(BinTreeNode<T> * subtree)
{
	if (subtree != nullptr) {
		destory(subtree->leftchild);//在左子树中销毁
		destory(subtree->rightchild);//在右子树中销毁
		delete subtree;//
	}
}

template<class T>
inline int BinaryTree<T>::getHeight(BinTreeNode<T>* subtree)//求树高
{
	if (subtree != nullptr) {
		int leftheight = getHeight(subtree->leftchild);
		int rightheight= getHeight(subtree->rightchild);
		return 1 + ((leftheight>rightheight) ? leftheight:rightheight);
	}
	else {
		return 0;
	}
}

template<class T>
inline int BinaryTree<T>::getSize(BinTreeNode<T>* subtree)//求大小
{
	if (subtree != nullptr) {
		return 1 + getSize(subtree->rightchild) + getSize(subtree->leftchild);
	}
	else {
		return 0;
	}
}

template<class T>
inline BinTreeNode<T>* BinaryTree<T>::getParent(BinTreeNode<T>* subtree, BinTreeNode<T>* current)//取父母
{
	if (subtree == nullptr) {
		return nullptr;
	}
	else if (subtree->leftchild == current || subtree->rightchild == current) {
		return subtree;
	}
	BinTreeNode *p = nullptr;
	if (p = getParent(subtree->leftchild) != nullptr) return p;
	else {
		return getParent(subtree->rightchild);
	}
}

template<class T>
inline void BinaryTree<T>::traverse(BinTreeNode<T>* subtree, ostream & out)//前序输出
{
	if (subtree != nullptr) {
		out << subtree->data << " ";
		traverse(subtree->leftchild, out);
		traverse(subtree->rightchild, out);
	}
}

template<class T>
inline void BinaryTree<T>::preOrder(BinTreeNode<T>* subtree)//前序遍历输出
{
	if (subtree == nullptr) {
		return;
	}
	cout<<subtree->data;
	preOrder(subtree->leftchild);
	preOrder(subtree->rightchild);
}

template<class T>
inline void BinaryTree<T>::preOrder1()//前序非递归遍历
{
	stack<BinTreeNode<T> * > s;
	BinTreeNode<T> *p = root;
	s.Push(p);
	while (!s.IsEmpty()) {
		cout << p->data;
		if (p->rightchild != nullptr) {
			s.Push(p->rightchild);
		}
		if (p->leftchild != nullptr) {
			p = p->leftchild;
		}
		else {
			s.Pop(p);
		}
	}
}

template<class T>
inline void BinaryTree<T>::inOrder(BinTreeNode<T>* subtree)//中序遍历
{
	if (subtree == nullptr) {
		return ;
	}
	inOrder(subtree->leftchild);
	cout << subtree->data;
	inOrder(subtree->rightchild);
}

template<class T>
inline void BinaryTree<T>::postOrder(BinTreeNode<T>* subtree)//后序遍历
{
	if (subtree == nullptr) {
		return nullptr;
	}
	postOrder(subtree->leftchild);
	postOrder(subtree->rightchild);
	cout << subtree->data;
}

template<class T>
inline int BinaryTree<T>::getleaf(BinTreeNode<T>* subtree)
{
	if (subtree == nullptr) {
		return 0;
	}
	if (subtree->leftchild == nullptr && subtree->rightchild == nullptr) {
		return 1;
	}
	return getleaf(subtree->leftchild) + getleaf(subtree->rightchild);
}


template<class T>
inline void BinaryTree<T>::output(BinTreeNode<T>* subtree)
{
	cout << subtree->data;
	if (subtree->leftchild != nullptr) {
		cout << "(";
		output(subtree->leftchild);
		if (subtree->rightchild == nullptr) {
			cout << ")";
		}
	}
	if (subtree->rightchild != nullptr) {
		if (subtree->leftchild == nullptr) {
			cout << "(";
		}
		if (subtree->leftchild != nullptr) {
			cout << ",";
		}
		output(subtree->rightchild);
		cout << ")";
	}
}





template<class T>
inline BinaryTree<T>::~BinaryTree()
{
	destory(root);
}

template<class T>
inline BinaryTree<T>::BinaryTree(T value)
{
	RefValue = value;
	root = nullptr;
}

template<class T>
inline bool BinaryTree<T>::isEmpty()
{
	return root == nullptr ? true : false;
}

template<class T>
inline BinTreeNode<T>* BinaryTree<T>::getParent(BinTreeNode<T>* current)
{
	return getParent(root);
}

template<class T>
inline int BinaryTree<T>::getHeight()
{
	return getHeight(root);
}

template<class T>
inline BinTreeNode<T>* BinaryTree<T>::getRoot()
{
	return root;
}

template<class T>
inline void BinaryTree<T>::preOrder()
{
	preOrder(root);
}

template<class T>
inline void BinaryTree<T>::inOrder()
{
	inOrder(root);
}

template<class T>
inline void BinaryTree<T>::inOrder1()
{
	stack<BinTreeNode<T> *> s;
	BinTreeNode<T> *p = root;
	do {
		while (p != nullptr) {
			s.push(p);
			p = p->leftchild;
		}
		if (!s.empty()) {
			s.Pop(p);
			cout << p->data;
			p = p->rightchild;
		}
	} while (p != nullptr || !s.IsEmpty());
}

template<class T>
inline void BinaryTree<T>::postOrder()
{
	postOrder(root);
}

template<class T>
inline void BinaryTree<T>::traverse()
{
	traverse(root, cout);
}

template<class T>
inline int BinaryTree<T>::getleaf()
{
	return getleaf(root);
}

template<class T>
inline void BinaryTree<T>::output()
{
	output(root);
}

template<class T>
inline void BinaryTree<T>::showMenu()
{
	cout << "===========================" << endl;
	cout << "1------建立一棵二叉树" << endl; 
	cout << "2------前序遍历递归算法" << endl;
	cout << "3------前序遍历非递归算法" << endl;
	cout << "4------中序遍历递归算法" << endl;
	cout << "5------中序遍历非递归算法" << endl;
	cout << "6------后序遍历递归算法" << endl;
	cout << "7------后序遍历非递归算法" << endl;
	cout << "8------求树高" << endl;
	cout << "9------求叶子总数" << endl;
	cout << "10---- - 输出二叉树" << endl;
	cout << "11---- - 退出" << endl;
	cout << "===========================" << endl;
}

template<class T>
inline void BinaryTree<T>::createTree()
{
	createTree(root);
}

