#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stack>
#include<string>
#include<cstring>
#include<cmath>
#include<memory>
#include<algorithm>
#include<fstream>
using namespace std;
/* Loop：依次顺序读用户键入的符号序列，组成并判别语法成分的类别
do{
  1.遇到Num:push;
  2.遇到ops:2次从栈中top出Num,Compute,将计算结果push入栈
} until(c == '＝') 这时s.top()就是表达式的值
*/
class Calculator {
	stack<double> s;
	bool Get2Num(double &op1, double &op2);
	void Compute(char op);
public:
	void Run();
	void Clear() {
		while (!s.empty()) s.pop();
	}
};
bool Calculator::Get2Num(double &op1, double &op2) {  //【改参】从栈中取两个数并弹出
	if (s.empty()) { cerr << "No Operand!" << endl; Clear(); }
	op1 = s.top();
	s.pop();
	if (s.empty()) { cerr << "No Operand!" << endl; Clear(); }
	op2 = s.top();
	s.pop();
	return true;
}
void Calculator::Compute(char op) {   //运算后压入栈中
	double num1, num2;
	if (!Get2Num(num1, num2)) { delete this; Clear(); return; }
	switch (op) {
	case '+':s.push(num1 + num2); break;
	case '-':s.push(num1 - num2); break;
	case '*':s.push(num1 * num2); break;
	case '/':
		if (num2 == 0.0) { cerr << "Divided by Zero!" << endl; Clear(); return; }
		s.push(num2 / num1); break;
	}
}
void Calculator::Run() {
	char c;
	double newNum;
	while (cin >> c, c != '=') {  //执行循环读入字符,进行一次栈操作(Comp/push_Num)
		switch (c) {
		case '+':
		case '-':
		case '*':
		case '/':Compute(c); break;
		default:
			cin.putback(c);
			cin >> newNum;
			s.push(newNum);
			break;
		}
	}
	cout << s.top() << endl;
}
int main() {
	ifstream in("in.txt");
	cin.rdbuf(in.rdbuf());
	Calculator c;
	c.Run();
	return 0;
}
