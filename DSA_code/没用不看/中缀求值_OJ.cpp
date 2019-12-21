//http://dsa.openjudge.cn/stack/solution/15508326/
//Accepted
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<list>
#include<queue>
#include<stack>
#include<bitset>
#include<set>
#include<map>
#include<string>
#include<cstring>
#include<cmath>
#include<memory>
#include<stdexcept>
#include<time.h>
#include<algorithm>
#include<iomanip>
#include<fstream>
using namespace std;
stack<int> nums;
stack<char> ops;
bool notPrior(const char c1, const char c2) {
	if ((c2 == '+' || c2 == '-') && (c1 == '*' || c1 == '/' || c1 == '^'))
		return false;
	else return true;
}
void Compute() {   //运算后压入栈中
	int num1, num2; char op;
	num2 = nums.top(); nums.pop();
	num1 = nums.top(); nums.pop();
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
	char op; int newNum;
	while (op = getchar()) {
		if (op == '\n') {
			while (!ops.empty()) {
				Compute();
			}
			cout << nums.top() << endl;
			return;
		}
		if (op == ' ')continue;
		if (op == '(') ops.push(op);
		else if (op == '+' || op == '-' || op == '*' || op == '/' || op == '^') {
			while (1) {
				if (!ops.empty() && ops.top() != '(' && notPrior(op, ops.top()))
					Compute();
				else {
					ops.push(op); break;
				}
			}
		}
		else if (op == ')') {
			while (ops.top() != '(')
				Compute();
			ops.pop();
		}
		else {
			cin.putback(op);
			cin >> newNum;
			//newNum = op - '0';
			nums.push(newNum);
		}
	}
}

int main() {
	int N; cin >> N; getchar();
	while (N--) {
		Run();
	}
	return 0;
}