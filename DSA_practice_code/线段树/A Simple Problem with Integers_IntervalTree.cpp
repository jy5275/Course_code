/* http://bailian.openjudge.cn/practice/3243/ */
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<limits.h>
#include<algorithm>
#define Left(p) 2*(p)+1
#define Right(p) 2*(p)+2
using namespace std;
/*【延迟更新】更新时未必要彻底更新,推迟到查询时才去更新足以应付查询的部分 */
const int MAX = 100010;
class CNode {
public:
	int L, R;
	long long sum = 0;	//已下传的区间和！
	long long inc = 0;	//未下传的区间和！
	int Mid() { return (L + R) / 2; }
}tree[4 * MAX + 10];

void BuildTree(int root, int L, int R) {
	tree[root].L = L;
	tree[root].R = R;
	if (L == R) return;
	int mid = (L + R) / 2;
	BuildTree(Left(root), L, mid);
	BuildTree(Right(root), mid + 1, R);
}

//每个结点的【sum + inc*len】+【所有上层inc】才是该时刻正确区间和！
void Add(int root, int a, int b, long long c) {		//给区间[a, b]的元素每个加c
	if (tree[root].L == a && tree[root].R == b) {	//恰好覆盖==>更新inc
		tree[root].inc += c; return;
	}
	//不能覆盖==>往下传！
	tree[root].sum += (b + 1 - a)*c;
	if (b <= tree[root].Mid())
		Add(Left(root), a, b, c);
	else if (a > tree[root].Mid())
		Add(Right(root), a, b, c);
	else {
		Add(Left(root), a, tree[root].Mid(), c);
		Add(Right(root), tree[root].Mid() + 1, b, c);
	}
}

//消去一路上所有inc
long long QuerySum(int root, int a, int b) {	//求root下[a, b]区间和
	if (tree[root].L == a && tree[root].R == b)
		return tree[root].inc * (b + 1 - a) + tree[root].sum;
	int len = tree[root].R + 1 - tree[root].L;

	//该结点inc转sum,下传区间和
	tree[root].sum += tree[root].inc * len;
	tree[Left(root)].inc += tree[root].inc;
	tree[Right(root)].inc += tree[root].inc;
	tree[root].inc = 0;

	if (b <= tree[root].Mid())
		return QuerySum(Left(root), a, b);
	else if (a > tree[root].Mid())
		return QuerySum(Right(root), a, b);
	else
		return QuerySum(Left(root), a, tree[root].Mid()) +
		QuerySum(Right(root), tree[root].Mid() + 1, b);
}

int main() {
	int N, Q, a_, b_, c_;
	long long v_;
	char cmd;
	scanf("%d %d", &N, &Q);
	BuildTree(0, 1, N);
	for (int i = 1; i <= N; i++) {
		scanf("%lld", &v_);
		Add(0, i, i, v_);
	}
	for (int i = 0; i < Q; i++) {
		scanf("\n%c", &cmd);
		if (cmd == 'C') {
			cin >> a_ >> b_ >> c_;
			Add(0, a_, b_, c_);
		}
		else {
			scanf("%d %d", &a_, &b_);
			printf("%lld\n", QuerySum(0, a_, b_));
		}
	}
	return 0;
}