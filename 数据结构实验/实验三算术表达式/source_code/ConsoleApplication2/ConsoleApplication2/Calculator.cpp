#include "pch.h"
#include "Calculator.h"


void Calculator::addOprands(double value)
{
	cal.Push(value);
}

bool Calculator::get2Operands(double & right, double & left)
{
	if (cal.IsEmpty()) {
		cerr << "缺少左操作数" << endl;
	}
	cal.Pop(right);
	if (cal.IsEmpty()) {
		cerr << "缺少右操作数" << endl;
	}
	cal.Pop(left);
	return true;
}

void Calculator::doOperator(char op)
{
	double left, right, value;
	if (get2Operands(right, left)) {
		//进行计算
		switch (op) {
		case'+':value = right + left; break;
		case'-':value = right - left; break;
		case'*':value = right * left; break;
		case'/':
			if (left == 0.0) {
				cerr << "被除数为零" << endl;
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
	//e是输入的表达式
	while (cin >> e[counte++]);
	string post[10];
	//post是逆波兰表达式
	for (int i = 0; i <counte; i++) {
		postfix(e[i], post[i]);
	}
	for(int count=0,i=0;i<counte-1;i++){
		while (post[i][count] != '\0') {
			//如果是操作符就进行运算
			if (post[i][count] == '+' || post[i][count] == '-' || post[i][count] == '*' || post[i][count] == '/') {
				doOperator(post[i][count]);
			}
			else {
				addOprands(post[i][count] - '0');
				//否则进栈(字符码转数字进栈)
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
	stack<char> s;//定义栈对象
	char ch = '#', ch1, op;
	input.append("#");
	s.Push(ch);//栈底放一个#
	int countin = 0;
	ch = input[countin];
	countin++;
	while (!s.IsEmpty()||ch!='#') {//连续处理
		if (isdigit(ch)) {
			output.append(1, ch);
			ch = input[countin];
			countin++;
		}
		else {
			s.getTop(ch1);//取栈顶
			if (isp(ch1) < icp(ch)) {//新输入栈优先级高
				s.Push(ch);
				ch = input[countin];
				countin++;
			}
			else if (isp(ch1) > icp(ch)) {//新输入栈优先级低
				s.Pop(op);
				output.append(1, op);
			}
			else {
				s.Pop(op);//入栈优先级等于栈顶优先级
				if (op == '(') {
					ch = input[countin];
					countin++;
				}
			}
		}
	}
}
