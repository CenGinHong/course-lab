#pragma once
#include<iostream>
#include<string>
using namespace std;

struct Student {
	friend ostream& operator << (ostream& out, Student &right);
	friend istream& operator >>(istream& in, Student &right);
	bool operator ==(string num) {
		return (this->num == num) ? true : false;
	}
	string num;
	string name;
	string birthday;
	string sex;
	string body;
	Student(string num, string name, string sex, string birthday, string body)
		:num(num),name(name),sex(sex),birthday(birthday),body(body) {}
	Student() {}

};

inline ostream& operator << (ostream& out, Student &right) {
	cout <<"========================" << endl;
	cout << "学号：" << right.num << endl;
	cout << "姓名：" << right.name << endl;
	cout << "性别：" << right.sex << endl;
	cout << "生日：" << right.birthday << endl;
	cout << "身体情况" << right.body << endl;
	cout << "========================" << endl;
	return out;
}

inline istream & operator>>(istream & in, Student & right)
{
	cout << "开始输入学生信息：" << endl;
	cout << "====================" << endl;
	cout << "请输入学号：";
	cin >> right.num;
	cout << "请输入姓名：";
	cin >> right.name;
	cout << "请输入性别：";
	cin >> right.sex;
	cout << "请输入生日：";
	cin >> right.birthday;
	cout << "请输入身体情况：";
	cin >> right.body;
	cout << "信息输入完成"<<endl;
	cout << "====================" << endl;
	return in;
}

