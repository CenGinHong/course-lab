#pragma once
#include"LinkedList.h"
#include"Student.h"
#include<fstream>


class StudentList :public LinkedList<Student, string>
{
public:
	StudentList();
	~StudentList();
	bool writeTxt();//д��txt
	bool readTxt();//��ȡtxt
	void showMenu();//չʾ�˵�
};
