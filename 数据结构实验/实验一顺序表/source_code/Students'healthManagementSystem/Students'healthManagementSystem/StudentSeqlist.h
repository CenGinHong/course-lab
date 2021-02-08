#pragma once
#include "Seqlist.h"
#include"Student.h"
class StudentSeqlist :
	public Seqlist<Student>
{
public:
	StudentSeqlist();
	~StudentSeqlist();
	int search(string num);//ÓÃÑ§ºÅËÑË÷
	void showMenu();
	bool readTxt();
	bool writeTxt();
};

