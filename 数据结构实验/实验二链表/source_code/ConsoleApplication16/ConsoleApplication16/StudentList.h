#pragma once
#include"LinkedList.h"
#include"Student.h"
#include<fstream>


class StudentList :public LinkedList<Student, string>
{
public:
	StudentList();
	~StudentList();
	bool writeTxt();//写入txt
	bool readTxt();//读取txt
	void showMenu();//展示菜单
};
