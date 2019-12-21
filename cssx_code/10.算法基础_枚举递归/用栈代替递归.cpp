//��ջ����ݹ�
#include<iostream>
#include<cmath>
#include<memory>
#include<algorithm>
#include<stack>
using namespace std;
struct Problem {    //ÿ��Problem��������һ�������⣺��src�ϵ�������midΪ�н��ƶ���dest
	int n;
	char src, mid, dest;
	Problem(int n_, char s_, char m_, char d_) :n(n_), src(s_), mid(m_), dest(d_) {}
};
stack<Problem> stk;  //����ģ���ŷ�ѵ�ջ,һ��Ԫ�ش���һ���ŷ�
int main() {
	int n; cin >> n;
	stk.push(Problem(n, 'A', 'B', 'C'));
	while (!stk.empty()) {
		Problem curPrb = stk.top();
		stk.pop();
		if (curPrb.n == 1) cout << curPrb.src << "->" << curPrb.dest << endl;
		else {      //�ֽ�������,�Ȱѷֽ�õ���3��������,ѹ��ջ��,ע�⵹��ѹ��
			stk.push(Problem(n - 1, curPrb.mid, curPrb.src, curPrb.dest));
			stk.push(Problem(1, curPrb.src, curPrb.mid, curPrb.dest));
			stk.push(Problem(n - 1, curPrb.src, curPrb.dest, curPrb.mid));
		}
		//stk.pop();  //�ӵ�ջ�����ŷ�
	}
	return 0;
}