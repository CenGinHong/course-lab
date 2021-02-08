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
	return -1;//û���ҵ�
}

void StudentSeqlist::showMenu()
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
