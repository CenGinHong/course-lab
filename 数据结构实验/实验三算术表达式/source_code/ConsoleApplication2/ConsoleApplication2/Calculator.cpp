#include "pch.h"
#include "Calculator.h"


void Calculator::addOprands(double value)
{
	cal.Push(value);
}

bool Calculator::get2Operands(double & right, double & left)
{
	if (cal.IsEmpty()) {
		cerr << "ȱ���������" << endl;
	}
	cal.Pop(right);
	if (cal.IsEmpty()) {
		cerr << "ȱ���Ҳ�����" << endl;
	}
	cal.Pop(left);
	return true;
}

void Calculator::doOperator(char op)
{
	double left, right, value;
	if (get2Operands(right, left)) {
		//���м���
		switch (op) {
		case'+':value = right + left; break;
		case'-':value = right - left; break;
		case'*':value = right * left; break;
		case'/':
			if (left == 0.0) {
				cerr << "������Ϊ��" << endl;
				break;
			}
			else {
				value = left / right; break;
			}
		}
		cal.Push(value);
	}
	else {
		clear();
	}
	
}

int Calculator::isp(char op)
{
	int result = 0;
	switch (op){
	case'#':result = 0; break;
	case'(':result = 1; break;
	case'*':
	case'/':
	case'%':result = 5; break;
	case'+':
	case'-':result = 3; break;
	case')':result = 6; break;
	}
	return result;
}

int Calculator::icp(char op)
{
	int result = 0;
	switch (op) {
	case'#':result = 0; break;
	case'(':result = 6; break;
	case'*':
	case'/':
	case'%':result = 4; break;
	case'+':
	case'-':result = 2; break;
	case')':result = 1; break;
	}
	return result;
}

Calculator::Calculator()
{
}


Calculator::~Calculator()
{
}

void Calculator::Run()
{
	string e[10]; int counte=0;
	//e������ı��ʽ
	while (cin >> e[counte++]);
	string post[10];
	//post���沨�����ʽ
	for (int i = 0; i <counte; i++) {
		postfix(e[i], post[i]);
	}
	for(int count=0,i=0;i<counte-1;i++){
		while (post[i][count] != '\0') {
			//����ǲ������ͽ�������
			if (post[i][count] == '+' || post[i][count] == '-' || post[i][count] == '*' || post[i][count] == '/') {
				doOperator(post[i][count]);
			}
			else {
				addOprands(post[i][count] - '0');
				//�����ջ(�ַ���ת���ֽ�ջ)
			}
			count++;
		}
		double result;
		cal.getTop(result);
		cout << result<<endl;
		count = 0;
	}
}

void Calculator::clear()
{
	cal.makeEmpty();
}




void Calculator::postfix(string &input, string &output)
{
	stack<char> s;//����ջ����
	char ch = '#', ch1, op;
	input.append("#");
	s.Push(ch);//ջ�׷�һ��#
	int countin = 0;
	ch = input[countin];
	countin++;
	while (!s.IsEmpty()||ch!='#') {//��������
		if (isdigit(ch)) {
			output.append(1, ch);
			ch = input[countin];
			countin++;
		}
		else {
			s.getTop(ch1);//ȡջ��
			if (isp(ch1) < icp(ch)) {//������ջ���ȼ���
				s.Push(ch);
				ch = input[countin];
				countin++;
			}
			else if (isp(ch1) > icp(ch)) {//������ջ���ȼ���
				s.Pop(op);
				output.append(1, op);
			}
			else {
				s.Pop(op);//��ջ���ȼ�����ջ�����ȼ�
				if (op == '(') {
					ch = input[countin];
					countin++;
				}
			}
		}
	}
}
