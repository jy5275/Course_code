//用栈代替递归
#include<iostream>
#include<cmath>
#include<memory>
#include<algorithm>
#include<stack>
using namespace std;
struct Problem {    //每个Problem对象描述一个子问题：将src上的盘子以mid为中介移动到dest
	int n;
	char src, mid, dest;
	Problem(int n_, char s_, char m_, char d_) :n(n_), src(s_), mid(m_), dest(d_) {}
};
stack<Problem> stk;  //用来模拟信封堆的栈,一个元素代表一个信封
int main() {
	int n; cin >> n;
	stk.push(Problem(n, 'A', 'B', 'C'));
	while (!stk.empty()) {
		Problem curPrb = stk.top();
		stk.pop();
		if (curPrb.n == 1) cout << curPrb.src << "->" << curPrb.dest << endl;
		else {      //分解子问题,先把分解得到的3个子问题,压入栈中,注意倒序压入
			stk.push(Problem(n - 1, curPrb.mid, curPrb.src, curPrb.dest));
			stk.push(Problem(1, curPrb.src, curPrb.mid, curPrb.dest));
			stk.push(Problem(n - 1, curPrb.src, curPrb.dest, curPrb.mid));
		}
		//stk.pop();  //扔掉栈顶的信封
	}
	return 0;
}