#include "pch.h"
#include "StudentSeqlist.h"


StudentSeqlist::StudentSeqlist()
{
}


StudentSeqlist::~StudentSeqlist()
{
}

int StudentSeqlist::search(string num)
{
	for (int i = 0; i <= last; i++) {
		if (data[i].num == num) {
			return i;
		}
	}
	return -1;//没有找到
}

void StudentSeqlist::showMenu()
{
	cout << "======================================================" << endl;
	cout << "1------新建学生健康表" << endl;
	cout << "2------向学生健康表插入学生信息" << endl;
	cout << "3------在健康表删除学生信息" << endl;
	cout << "4------从文件中读取健康表信息" << endl;
	cout << "5------向文件写入学生健康表信息" << endl;
	cout << "6------在健康表中查询学生信息（按学生学号来进行查找）" << endl;
	cout << "7------在屏幕中输出全部学生信息" << endl;
	cout << "8-----退出" << endl;
	cout << "======================================================" << endl;
}

bool StudentSeqlist::readTxt()
{
	ifstream in;
	in.open("record.txt");
	if (!in.is_open()) {
		return false;
	}
	else {
		string num, name, sex, birthday, body;
		for (; in.peek() != -1;) {
			in >> num;
			in >> name;
			in >> sex;
			in >> birthday;
			in >> body;
			Student temp(num, name, sex, birthday, body);
			last++;
			data[last] = temp;
		}
	}
	return true;
}

bool StudentSeqlist::writeTxt()
{
	ofstream out;
	out.open("record.txt");
	if (!out.is_open()) {
		return false;
	}
	int length = getLength();
	for (int i = 0; i < length; i++) {
		out << data[i].num << endl;
		out << data[i].name << endl;
		out << data[i].sex << endl;
		out << data[i].birthday << endl;
		out << data[i].body << endl;
	}
	return true;
}
