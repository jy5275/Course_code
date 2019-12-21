#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<queue>
#include<stack>
#include<string>
#include<cmath>
#include<memory>
#include<algorithm>
using namespace std;
fstream fout("cache.txt", ios::out);
bool Inferior(const char c1, const char c2) {
	if ((c1 == '+' || c1 == '-') && (c2 == '*' || c1 == '/' || c1 == '^'))
		return true;
	else return false;
}
stack<char> ops;
void Transform() {
	char c; double newNum;
	while (c = getchar()) {
		if (c == '\n') {
			while (!ops.empty()) {
				fout << ops.top() << " ";
				ops.pop();
			}
			return;
		}
		if (c == ' ')continue;
		if (c == '(') ops.push(c);
		else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
			while (1) {
				if (!ops.empty() && ops.top() != '(' && Inferior(c, ops.top())) {
					fout << ops.top() << " ";
					ops.pop();
				}
				else {
					ops.push(c); break;
				}
			}
		}
		else if (c == ')') {
			while (ops.top() != '(') {
				fout << ops.top() << " ";
				ops.pop();
			}
			if (ops.top() == '(') ops.pop();
			int a = 1;
		}
		else {
			cin.putback(c);
			cin >> newNum;
			fout << newNum << " ";
			int a = 1;
		}
	}
}
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
bool Calculator::Get2Num(double &op1, double &op2) {   //从栈中取两个数并弹出它们
	if (s.empty()) { cerr << "No Operand!" << endl; Clear(); }
	op2 = s.top();
	s.pop();
	if (s.empty()) { cerr << "No Operand!" << endl; Clear(); }
	op1 = s.top();
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
		s.push(num1 / num2); break;
	case '^':s.push(pow(num1, num2)); break;
	}
}
void Calculator::Run() {
	char c;
	int flag = 0;
	double newNum;
	while (cin >> c, c != '=') {  //执行循环读入字符,进行一次栈操作(Comp/push_Num)
		switch (c) {
		case '\n':flag++; break;
		case ' ':break;
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
		if (flag) break;
	}
	cout << s.top() << endl;
}
int main() {
	Transform();  //★★★
	fout << " =";
	fout.close();

	ifstream in("cache.txt");
	cin.rdbuf(in.rdbuf());
	Calculator c; //★★★
	c.Run(); //★★★
	return 0;
}