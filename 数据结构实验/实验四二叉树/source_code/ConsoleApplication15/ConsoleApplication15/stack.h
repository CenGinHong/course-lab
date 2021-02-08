#pragma once

template<class T>
class stack
{
	T *data;
	int top;
	int maxsize;
	void overflowProcess();
public:
	stack(int sz=50);
	~stack();
	bool getTop(T &x);
	bool IsEmpty();
	bool IsFull();
	bool Pop(T &x);
	void Push(T &x);
};

template<class T>
inline void stack<T>::overflowProcess()
{
	T *newdata = new T[maxsize * 2];
	for (int i = 0; i <= top; i++) {
		data[i] = newdata[i];
	}
	delete[]data;
	data = newdata;
}

template<class T>
inline stack<T>::stack(int sz)
{
	if (sz <= 0) {
		sz = 50;
	}
	data = new T[sz];
	top = -1;
	maxsize = sz;
}

template<class T>
inline stack<T>::~stack()
{
	delete[]data;
}

template<class T>
inline bool stack<T>::getTop(T & x)
{
	if (IsEmpty()) {
		return false;
	}
	else {
		x = data[top];
		return true;
	}
	
}

template<class T>
inline bool stack<T>::IsEmpty()
{
	return top == -1;
}

template<class T>
inline bool stack<T>::IsFull()
{
	return maxsize==top;
}

template<class T>
inline bool stack<T>::Pop(T & x)
{
	if (IsEmpty()) {
		return  false;
	}
	else {
		x = data[top];
		top--;
		return true;
	}
}

template<class T>
inline void stack<T>::Push(T & x)
{
	if (IsFull()) {
		overflowProcess();
		//栈的溢出处理
	}
	else {
		top++;
		data[top] = x;
	}
}





