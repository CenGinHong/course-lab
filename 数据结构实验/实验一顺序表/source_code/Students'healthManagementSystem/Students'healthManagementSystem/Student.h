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
	cout << "ѧ�ţ�" << right.num << endl;
	cout << "������" << right.name << endl;
	cout << "�Ա�" << right.sex << endl;
	cout << "���գ�" << right.birthday << endl;
	cout << "�������" << right.body << endl;
	cout << "========================" << endl;
	return out;
}

inline istream & operator>>(istream & in, Student & right)
{
	cout << "��ʼ����ѧ����Ϣ��" << endl;
	cout << "====================" << endl;
	cout << "������ѧ�ţ�";
	cin >> right.num;
	cout << "������������";
	cin >> right.name;
	cout << "�������Ա�";
	cin >> right.sex;
	cout << "���������գ�";
	cin >> right.birthday;
	cout << "���������������";
	cin >> right.body;
	cout << "��Ϣ�������"<<endl;
	cout << "====================" << endl;
	return in;
}

