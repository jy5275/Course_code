#include<iostream>
#include<string>
#include<cmath>
#include<map>
#include<stack>
#include<queue>
#include<algorithm>
using namespace std;
int main() {
	priority_queue<double, vector<double>, greater<double> > prio;
	prio.push(3.2);	prio.push(9.8);
	prio.push(5.4);	prio.push(1.8);
	queue<int> q;
	while (!prio.empty()) {
		cout << prio.top() << " ";
		prio.pop();
	}cout << endl;
	//--------------------------------------------------------------
	//栈stack先进先出，push()压入,pop()弹出,top()返回引用
	int n, k; cin >> n >> k;
	stack<int> stk;
	while (n) {
		stk.push(n%k);
		n = n / k;
	}
	while (!stk.empty()) {
		cout << stk.top();
		stk.pop();
	}
	return 0;
}
