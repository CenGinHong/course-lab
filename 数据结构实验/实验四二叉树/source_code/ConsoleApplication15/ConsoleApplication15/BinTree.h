#pragma once
#include<iostream>
#include<string>
#include"stack.h"
using namespace std;

//����㶨��
template<class T>
struct BinTreeNode
{
	T data;
	BinTreeNode *leftchild;
	BinTreeNode *rightchild;
	BinTreeNode(T data, BinTreeNode *leftchild = nullptr, BinTreeNode *rightchild = nullptr) :data(data), rightchild(rightchild), leftchild(leftchild) {};
	BinTreeNode(BinTreeNode *leftchild = nullptr, BinTreeNode *rightchild = nullptr) :leftchild(leftchild), rightchild(rightchild) {};
};

//��������
template<class T>
class BinaryTree
{
protected:
	BinTreeNode<T> *root;
	T RefValue;
	void createTree(BinTreeNode<T> *&subtree);//���캯��
	void destory(BinTreeNode<T>* subtree);//������
	int getHeight(BinTreeNode<T> *subtree);//�������߶�
	int getSize(BinTreeNode<T> *subtree);//���ؽ����
	BinTreeNode<T> *getParent(BinTreeNode<T>* subtree, BinTreeNode<T>* current);//���ظ����
	void traverse(BinTreeNode<T> *subtree, ostream& out);//ǰ��������
	void preOrder(BinTreeNode<T>* subtree);//ǰ�����
	void inOrder(BinTreeNode<T>* subtree);//�������
	void postOrder(BinTreeNode<T>* subtree);//�������
	int getleaf(BinTreeNode<T> *subtree);//�õ�Ҷ������
	void output(BinTreeNode<T> *subtree);//��������
	
public:
	~BinaryTree();
	BinaryTree(T value);
	bool isEmpty();//�п�
	BinTreeNode<T>* getParent(BinTreeNode<T>* current);//���ظ����
	int getHeight();//�������߶�
	BinTreeNode<T>* getRoot();//ȡ��
	void preOrder();//ǰ�����
	void preOrder1();//ǰ��ǵݹ����
	void inOrder();//�������
	void inOrder1();//����ǵݹ����
	void postOrder();//�������
	void traverse();//ǰ��������
	int getleaf();//�õ�Ҷ������
	void output();//��������������
	void showMenu();//չʾ�˵�
	void createTree();//������
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
		destory(subtree->leftchild);//��������������
		destory(subtree->rightchild);//��������������
		delete subtree;//
	}
}

template<class T>
inline int BinaryTree<T>::getHeight(BinTreeNode<T>* subtree)//������
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
inline int BinaryTree<T>::getSize(BinTreeNode<T>* subtree)//���С
{
	if (subtree != nullptr) {
		return 1 + getSize(subtree->rightchild) + getSize(subtree->leftchild);
	}
	else {
		return 0;
	}
}

template<class T>
inline BinTreeNode<T>* BinaryTree<T>::getParent(BinTreeNode<T>* subtree, BinTreeNode<T>* current)//ȡ��ĸ
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
inline void BinaryTree<T>::traverse(BinTreeNode<T>* subtree, ostream & out)//ǰ�����
{
	if (subtree != nullptr) {
		out << subtree->data << " ";
		traverse(subtree->leftchild, out);
		traverse(subtree->rightchild, out);
	}
}

template<class T>
inline void BinaryTree<T>::preOrder(BinTreeNode<T>* subtree)//ǰ��������
{
	if (subtree == nullptr) {
		return;
	}
	cout<<subtree->data;
	preOrder(subtree->leftchild);
	preOrder(subtree->rightchild);
}

template<class T>
inline void BinaryTree<T>::preOrder1()//ǰ��ǵݹ����
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
inline void BinaryTree<T>::inOrder(BinTreeNode<T>* subtree)//�������
{
	if (subtree == nullptr) {
		return ;
	}
	inOrder(subtree->leftchild);
	cout << subtree->data;
	inOrder(subtree->rightchild);
}

template<class T>
inline void BinaryTree<T>::postOrder(BinTreeNode<T>* subtree)//�������
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
	cout << "1------����һ�ö�����" << endl; 
	cout << "2------ǰ������ݹ��㷨" << endl;
	cout << "3------ǰ������ǵݹ��㷨" << endl;
	cout << "4------��������ݹ��㷨" << endl;
	cout << "5------��������ǵݹ��㷨" << endl;
	cout << "6------��������ݹ��㷨" << endl;
	cout << "7------��������ǵݹ��㷨" << endl;
	cout << "8------������" << endl;
	cout << "9------��Ҷ������" << endl;
	cout << "10---- - ���������" << endl;
	cout << "11---- - �˳�" << endl;
	cout << "===========================" << endl;
}

template<class T>
inline void BinaryTree<T>::createTree()
{
	createTree(root);
}

