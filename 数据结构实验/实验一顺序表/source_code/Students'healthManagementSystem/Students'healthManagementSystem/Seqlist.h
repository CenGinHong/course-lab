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
	Seqlist(int sz= defualtsize);//�½��б�
	~Seqlist();//��������
	Seqlist(Seqlist<T> &L);//���ƹ��캯��
	void getData(int i, T &value);//������ݱ�Ԫ�غ���
	void insert(T &x);//���뵽��β
	bool remove(int i);//ɾ����i��
	int getLength();//��õ�ǰ����
	bool isFull();
	bool isEmpty();
	void output(int i);
};

template<class T>
inline void Seqlist<T>::expand()
{
	T *newdata = new T[maxsize * 2];
	//�½�˳���
	for (int i = 0; i < last; i++) {
		newdata[i] = data[i];
		//������ֵ
	}
	delete[]data;
	//ɾ���ɿռ�
	data = newdata;
}

template<class T>
inline Seqlist<T>::Seqlist(int sz)
{
	if (sz <= 0) {
		sz = defualtsize;
		cout << "˳����С���������ѵ���Ϊ" <<defualtsize<< endl;
	}
	maxsize = sz;
	last = -1;
	data = new T[maxsize];
	if (data == nullptr) {
		cerr << "�ڴ�������" << endl;
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
		cerr << "�ڴ�������" << endl;
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
