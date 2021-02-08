#pragma once
#include<iostream>
#include<string>
#include <fstream>
using namespace std;

const int defualtsize = 20;
template<class T>
class Seqlist
{
protected:
	T* data=nullptr;
	int maxsize;
	int last ;
	void expand();
public:
	Seqlist(int sz= defualtsize);//新建列表
	~Seqlist();//析构函数
	Seqlist(Seqlist<T> &L);//复制构造函数
	void getData(int i, T &value);//获得数据表元素函数
	void insert(T &x);//插入到表尾
	bool remove(int i);//删除第i项
	int getLength();//获得当前长度
	bool isFull();
	bool isEmpty();
	void output(int i);
};

template<class T>
inline void Seqlist<T>::expand()
{
	T *newdata = new T[maxsize * 2];
	//新建顺序表
	for (int i = 0; i < last; i++) {
		newdata[i] = data[i];
		//遍历赋值
	}
	delete[]data;
	//删除旧空间
	data = newdata;
}

template<class T>
inline Seqlist<T>::Seqlist(int sz)
{
	if (sz <= 0) {
		sz = defualtsize;
		cout << "顺序表大小设置有误，已调整为" <<defualtsize<< endl;
	}
	maxsize = sz;
	last = -1;
	data = new T[maxsize];
	if (data == nullptr) {
		cerr << "内存分配错误" << endl;
	}
}

template<class T>
inline Seqlist<T>::~Seqlist()
{
	delete []data;
}

template<class T>
inline Seqlist<T>::Seqlist(Seqlist<T>& L)
{
	maxsize = L.getLength();
	last = L.getLength() - 1;
	T value;
	data = new T[maxsize];
	if (data = nullptr) {
		cerr << "内存分配错误" << endl;
		exit(1);
	}
	for (int i = 0; i < last ; i++) {
		L.getData(i, value);
		data[i] = value;
	}
}

template<class T>
inline void Seqlist<T>::getData(int i, T &value)
{
	value = data[i];
}

template<class T>
inline void Seqlist<T>::insert(T & x)
{
	if (isFull()) {
		expand();
	}
	else {
		last++;
		data[last] = x;
	}
}

template<class T>
inline bool Seqlist<T>::remove(int i)
{
	if (i == -1) {
		return false;
	}
	else {
		for (int j = i; j < last; j++) {
			data[j] = data[j+1];
		}
		last--;
		return true;
	}
}

template<class T>
inline int Seqlist<T>::getLength()
{
	return last + 1;
}

template<class T>
inline bool Seqlist<T>::isFull()
{
	return last + 1 == maxsize ? true : false;
}

template<class T>
inline bool Seqlist<T>::isEmpty()
{
	return last == -1 ? true:false;
}

template<class T>
inline void Seqlist<T>::output(int i)
{
	if (i == -1) {
		return;
	}
	else {
		cout << data[i];
	}
}
