#include "pch.h"
#include "HuffmanTree.h"


//�����������treesizeΪ�µ����������±�
void HuffmanTree::mergeTree(int first, int second, int treesize)
{
	data[treesize].weight = data[first].weight + data[second].weight;
	data[treesize].leftchild = first;
	data[treesize].rightchild = second;
	data[first].parent = treesize;
	data[second].parent = treesize;
}

//�õ�����δ�������������Сֵ
void HuffmanTree::getMin(int & first, int & second)
{
	double min=0;
	for (int i = 0 ; i < 2*size-1; i++) {
		if (data[i].parent != -1||data[i].weight==-1) {
			continue;
		}
		else {
			if (min == 0) {
				min = data[i].weight;
				first = i;
				//��ʼ����С���ֵ
			}
			if (data[i].weight < min) {
				min = data[i].weight;
				first = i;
			}
		}
	}
	min = 0;
	for (int i = 0; i < 2*size-1; i++) {
		if (data[i].parent != -1||i==first||data[i].weight == -1) {
			continue;
		}
		else {
			if (min == 0) {
				min = data[i].weight;
				second = i;
			}
			if (data[i].weight < min) {
				min = data[i].weight;
				second = i;
			}
		}
	}

}

void HuffmanTree::outputTree()
{
	ofstream out("hfmTree.txt");
	for (int i = 0; i < 2 * size - 1; i++) {
		out << data[i].ch << " " << data[i].code << " " << data[i].weight << " " << data[i].leftchild 
			<< " " << data[i].rightchild <<" "<< data[i].parent;
		out << endl;
	}
}


//���룬sΪҪ������ַ���
string HuffmanTree::Decode(string s)
{
	string result="";//������
	string temp = "";//���ǰ׺�������ʱ����
	for (int i = 0; i <s.size(); i++) {
		temp += s[i];//����������
		for (int j= 0; j < size; j++) {
			if (data[j].code == temp) {
				result += data[j].ch;
				temp = "";//���
				break;
			}
			else if (i == s.size() - 1 && j == size - 1 && temp != "") {
				result = "����ʧ��";
			}
		}
	}
	return result;
}

//���ַ������б���
string HuffmanTree::Encode(string s)
{
	string result;
	for (int i = 0; i < s.size(); i++) {
		for (int j = 0; j < size; j++) {
			//����size�ǹ����������ַ�������
			if (s[i] == data[j].ch) {
				result += data[j].code;
				break;
			}
			if (j == size - 1) {
				cout << "����ʧ��" << endl;
				result = "����ʧ��";
				return result;
			}
		}
	}
	return result;
}

//չʾ�˵�
void HuffmanTree::showMenu()
{
	cout << "==========================����������=================" << endl;
	cout << "I.---------Initialization" << endl;
	cout << "E.---------Encoding" << endl;
	cout << "D.---------Decoding" << endl;
	cout << "P.---------Print" << endl;
	cout << "Q.---------Quit" << endl;
	cout << "=====================================================" << endl;
}

void HuffmanTree::print()
{
	ifstream in("CodeFile.txt");
	if (!in.is_open()) {
		cout << "��ʧ��" << endl;
		return;
	}
	ofstream out("CodePrin.txt");
	char ch;
	while (in.peek() != EOF) {
		string s;
		for (int i = 0; i < 50; i++) {
			in >> ch;
			s += ch;
		}
		cout << s << endl;
		out << s;
	}
	out.close();
	cout << "�ѽ�CodeFile�Խ��ո�ʽ��ʾ���ն��ϣ�ͬʱ�����ַ���ʽ�ı����ļ�д���ļ�CodePrin" << endl;
}


//�����ַ�����
void HuffmanTree::save(string file,string s)
{
	ofstream out(file);
	out << s;
	out.close();
}

bool HuffmanTree::read(string file,string &result)
{
	ifstream in(file);
	if (in.is_open()) {
		getline(in, result);
		in.close();
		return true;
	}
	else {
		return false;
	}

}

bool HuffmanTree::isEmpty()
{
	return data==nullptr;
}

HuffmanTree::HuffmanTree()
{
	data = nullptr;
}

HuffmanTree::~HuffmanTree()
{
	delete[]data;
}

//����
void HuffmanTree::code()
{
	for (int i=0; i < size; i++) {
		//���������ַ���Ԫ��
		int j = i;
		string code;
		while (data[j].parent != -1) {
			if (data[data[j].parent].leftchild == j) {
				//����ý�����丸ĸ��������
				code += "0";
			}
			else {
				code += "1";
			}
			j = data[j].parent;
		}
		reverse(code.begin(), code.end());
		data[i].code = code;//�ѱ���洢����Ӧ��㣬�������
		cout << data[i].ch << ":" << code << endl;
	}
}

void HuffmanTree::Initialize(int sz, char *ch, double *weight)
{
	size = sz;
	int curTree = size - 1;
	data = new HuffNode[2 * size - 1];
	for (int i = 0; i < size; i++) {
		data[i].ch = ch[i];
		data[i].weight = weight[i];
	}
	int first, second;
	while (curTree + 1 != 2 * size - 1) {
		getMin(first, second);//�õ�������Сֵ
		curTree++;//����λ�ý�һ
		mergeTree(first, second, curTree);//�ϳ���
	}
	code();
	outputTree();//�����txt
	cout << "�ѽ������������������ڹ��̸�Ŀ¼��hfmTree.txt" << endl;
}



