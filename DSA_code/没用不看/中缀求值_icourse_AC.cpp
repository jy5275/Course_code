//http://www.icourse163.org/learn/PKU-1002534001?tid=1003136008#/learn/ojhw?id=1003986010
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stack>
#include<cmath>
#include<algorithm>
using namespace std;
stack<double> nums;
stack<char> ops;
bool notPrior(const char c1, const char c2) {
	if ((c2 == '+' || c2 == '-') && (c1 == '*' || c1 == '/' || c1 == '^'))
		return false;
	else return true;
}
void Compute() {     //运算后压入栈中
	double num1, num2; char op;
	num2 = nums.top(); nums.pop();  //弹出操作数2
	num1 = nums.top(); nums.pop();  //弹出操作数1
	op = ops.top(); ops.pop();
	switch (op) {
	case '+':nums.push(num1 + num2); break;
	case '-':nums.push(num1 - num2); break;
	case '*':nums.push(num1 * num2); break;
	case '/':nums.push(num1 / num2); break;
	case '^':nums.push(pow(num1, num2)); break;
	}
}
void Run() {
	char op; double newNum;
	while ((op = cin.get()) != EOF) {  
		if (op == '\n') {         //读到'\n',游戏结束
			while (!ops.empty()) 
				Compute();
			cout << nums.top() << endl;
			return;
		}
		if (op == ' ')continue;   //读到空格,直接跳过
		if (op == '(') ops.push(op);   //读到'(', 不管三七二十一压入！
		else if (op == '+' || op == '-' || op == '*' || op == '/' || op == '^') {
			while (1) {
				if (!ops.empty() && ops.top() != '(' && notPrior(op, ops.top()))
					Compute();    //如果要后缀转中缀,这一步为【弹栈并输出到后缀序列中】
				else {
					ops.push(op); break;
				}
			}
		}
		else if (op == ')') {      //把上一个'('之前的所有运算都执行完毕
			while (ops.top() != '(')
				Compute();        //如果要后缀转中缀,这一步为【弹栈并输出到后缀序列中】
			ops.pop();
		}
		else {      //读到的是数字,压入
			cin.putback(op);
			cin >> newNum;
			nums.push(newNum);    //如果要后缀转中缀,这一步为【输出newNum到后缀序列中】
		}
	}
	while (!ops.empty()) 
		Compute();
	cout << nums.top() << endl;
	return;
}

int main() {
	Run();
	return 0;
}