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
		return false;//��ʧ��
	}
	string num, name, sex, birthday, body;
	LinkNode<Student> *cur = first;
	while (cur->link != nullptr)
	{
		cur = cur->link;//��ָ�붨λ������β
	}
	while (in.peek() != -1)
	{
		getline(in, num);
		getline(in, name);
		getline(in, sex);
		getline(in, birthday);
		getline(in, body);
		Student temp(num, name, sex, birthday, body);//�½�����
		LinkNode<Student> *newnode = new LinkNode<Student>(temp);//�½��ڵ�
		cur->link = newnode;//����
		cur = cur->link;
	}
	return true;
}

void StudentList::showMenu()
{
	cout << "======================================================" << endl;
	cout << "1------�½�ѧ��������" << endl;
	cout << "2------��ѧ�����������ѧ����Ϣ" << endl;
	cout << "3------�ڽ�����ɾ��ѧ����Ϣ" << endl;
	cout << "4------���ļ��ж�ȡ��������Ϣ" << endl;
	cout << "5------���ļ�д��ѧ����������Ϣ" << endl;
	cout << "6------�ڽ������в�ѯѧ����Ϣ����ѧ��ѧ�������в��ң�" << endl;
	cout << "7------����Ļ�����ȫ��ѧ����Ϣ" << endl;
	cout << "8-----�˳�" << endl;
	cout << "======================================================" << endl;
}