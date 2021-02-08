#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include <algorithm>
using namespace std;

struct HuffNode
{
	char ch;//该结点所存储的编码字符
	string code;//若该结点中为叶结点则存储其字符的编码
	double weight;//权值
	int parent;//父母在数组中的下标
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


class HuffmanTree
{
private:
	HuffNode *data;
	int size;//总数组长
	void mergeTree(int first,int second,int treesize);
	void getMin(int &first, int &second);
	void outputTree();
	void code();//对字符进行编码
public:
	HuffmanTree();
	~HuffmanTree();
	void Initialize(int sz, char *ch, double *weight);
	string Decode(string s);//对编码进行译码
	string Encode(string s);//对字符串进行编码
	void save(string file, string s);//保存字符串到指定文件
	bool read(string file,string &code);//从指定文件读取字符串
	bool isEmpty();
	void showMenu();
	void print();
};

