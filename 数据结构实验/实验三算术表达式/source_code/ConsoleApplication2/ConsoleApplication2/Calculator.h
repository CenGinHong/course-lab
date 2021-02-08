#pragma once
#include"stack.h"
#include<iostream>
#include<string>
using namespace std;

class Calculator
{
private:
	void addOprands(double value);//操作数进栈
	bool get2Operands(double& right, double& left); //从栈cal中取出两个操作数
	void doOperator(char op);//进行计算
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

