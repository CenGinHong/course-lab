#pragma once
#include"stack.h"
#include<iostream>
#include<string>
using namespace std;

class Calculator
{
private:
	void addOprands(double value);//��������ջ
	bool get2Operands(double& right, double& left); //��ջcal��ȡ������������
	void doOperator(char op);//���м���
	stack<double> cal;
	int isp(char op);
	int icp(char op);
public:
	Calculator();
	~Calculator();
	void Run();
	void clear();
	void postfix(string &input,string &output);
};

