#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include <algorithm>
using namespace std;

struct HuffNode
{
	char ch;//�ý�����洢�ı����ַ�
	string code;//���ý����ΪҶ�����洢���ַ��ı���
	double weight;//Ȩֵ
	int parent;//��ĸ�������е��±�
	int leftchild;//������ָ���е��±�
	int rightchild;//�Һ�����ָ���е��±�
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
	int size;//�����鳤
	void mergeTree(int first,int second,int treesize);
	void getMin(int &first, int &second);
	void outputTree();
	void code();//���ַ����б���
public:
	HuffmanTree();
	~HuffmanTree();
	void Initialize(int sz, char *ch, double *weight);
	string Decode(string s);//�Ա����������
	string Encode(string s);//���ַ������б���
	void save(string file, string s);//�����ַ�����ָ���ļ�
	bool read(string file,string &code);//��ָ���ļ���ȡ�ַ���
	bool isEmpty();
	void showMenu();
	void print();
};

