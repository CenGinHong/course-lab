#include "pch.h"
#include "HuffmanTree.h"


//扩充二叉树，treesize为新的树根结点的下标
void HuffmanTree::mergeTree(int first, int second, int treesize)
{
	data[treesize].weight = data[first].weight + data[second].weight;
	data[treesize].leftchild = first;
	data[treesize].rightchild = second;
	data[first].parent = treesize;
	data[second].parent = treesize;
}

//得到两个未被扩充的子树最小值
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
				//初始化最小标记值
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


//译码，s为要解码的字符串
string HuffmanTree::Decode(string s)
{
	string result="";//编码结果
	string temp = "";//存放前缀编码的临时变量
	for (int i = 0; i <s.size(); i++) {
		temp += s[i];//逐个编码添加
		for (int j= 0; j < size; j++) {
			if (data[j].code == temp) {
				result += data[j].ch;
				temp = "";//清空
				break;
			}
			else if (i == s.size() - 1 && j == size - 1 && temp != "") {
				result = "解码失败";
			}
		}
	}
	return result;
}

//对字符串进行编码
string HuffmanTree::Encode(string s)
{
	string result;
	for (int i = 0; i < s.size(); i++) {
		for (int j = 0; j < size; j++) {
			//这里size是哈夫曼树中字符的数量
			if (s[i] == data[j].ch) {
				result += data[j].code;
				break;
			}
			if (j == size - 1) {
				cout << "编码失败" << endl;
				result = "编码失败";
				return result;
			}
		}
	}
	return result;
}

//展示菜单
void HuffmanTree::showMenu()
{
	cout << "==========================哈夫曼编码=================" << endl;
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
		cout << "打开失败" << endl;
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
	cout << "已将CodeFile以紧凑格式显示在终端上，同时将此字符形式的编码文件写入文件CodePrin" << endl;
}


//保存字符编码
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

//编码
void HuffmanTree::code()
{
	for (int i=0; i < size; i++) {
		//遍历含有字符的元素
		int j = i;
		string code;
		while (data[j].parent != -1) {
			if (data[data[j].parent].leftchild == j) {
				//如果该结点是其父母的是左孩子
				code += "0";
			}
			else {
				code += "1";
			}
			j = data[j].parent;
		}
		reverse(code.begin(), code.end());
		data[i].code = code;//把编码存储到对应结点，方便解码
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
		getMin(first, second);//得到两个最小值
		curTree++;//数组位置进一
		mergeTree(first, second, curTree);//合成树
	}
	code();
	outputTree();//输出到txt
	cout << "已建立哈夫曼树，并存于工程根目录下hfmTree.txt" << endl;
}



