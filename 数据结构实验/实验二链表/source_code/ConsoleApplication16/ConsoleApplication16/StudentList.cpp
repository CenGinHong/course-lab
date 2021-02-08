#include "pch.h"
#include "StudentList.h"


StudentList::StudentList()
{
}


StudentList::~StudentList()
{
}

bool StudentList::writeTxt()
{
	ofstream out;
	out.open("record.txt");
	if (!out.is_open()) {
		return false;
	}
	LinkNode<Student> *cur = first->link;
	while (cur != nullptr)
	{
		out << cur->data.num << endl;
		out << cur->data.name << endl;
		out << cur->data.sex << endl;
		out << cur->data.birthday << endl;
		out << cur->data.body << endl;
		cur = cur->link;
	}
	return true;
}

bool StudentList::readTxt()
{
	ifstream in("record.txt");
	if (!in.is_open()) {
		return false;//打开失败
	}
	string num, name, sex, birthday, body;
	LinkNode<Student> *cur = first;
	while (cur->link != nullptr)
	{
		cur = cur->link;//将指针定位到链表尾
	}
	while (in.peek() != -1)
	{
		getline(in, num);
		getline(in, name);
		getline(in, sex);
		getline(in, birthday);
		getline(in, body);
		Student temp(num, name, sex, birthday, body);//新建对象
		LinkNode<Student> *newnode = new LinkNode<Student>(temp);//新建节点
		cur->link = newnode;//拉链
		cur = cur->link;
	}
	return true;
}

void StudentList::showMenu()
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