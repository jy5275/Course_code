/* http://bailian.openjudge.cn/practice/3243/ */
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
#include<memory.h>
#include<bitset>
#include<queue>
using namespace std;
const int MAX = 10010;
int Left(int x) { return 2 * x + 1; }
int Right(int x) { return 2 * x + 2; }
class CNode {
public:
	int L, R, sum = 0, inc = 0;
	int Mid() { return (L + R) / 2; }
}tree[4 * MAX + 10];

void BuildTree(int root, int a, int b) {
	tree[root].L = a, tree[root].R = b;
	if (a == b)return;
	int mid = (a + b) / 2;
	BuildTree(Left(root), a, mid);
	BuildTree(Right(root), mid + 1, b);
}

//每个结点的【sum + inc*len】+【所有上层inc】才是该时刻正确区间和！
void Add(int root, int a, int b, int c) {	//区间更新++
	if (tree[root].L == a && tree[root].R == b) {	//恰好覆盖==>更新inc
		tree[root].inc += c; return;
	}
	//不能覆盖==>往下传！
	tree[root].sum += (b + 1 - a)*c;
	int mid = tree[root].Mid();
	if (b <= mid)
		Add(Left(root), a, b, c);
	else if (a > mid)
		Add(Right(root), a, b, c);
	else {
		Add(Left(root), a, mid, c);
		Add(Right(root), mid + 1, b, c);
	}
}

//消去一路上所有inc
int QuerySum(int root, int a, int b) {	//求root下[a, b]区间和
	if (tree[root].L == a && tree[root].R == b)
		return tree[root].sum + tree[root].inc*(b + 1 - a);

	//该结点inc转sum,下传区间和
	int len = tree[root].R + 1 - tree[root].L;
	tree[root].sum += tree[root].inc*len;
	tree[Left(root)].inc += tree[root].inc;
	tree[Right(root)].inc += tree[root].inc;
	tree[root].inc = 0;

	int mid = tree[root].Mid();
	if (b <= mid)
		return QuerySum(Left(root), a, b);
	else if (a > mid)
		return QuerySum(Right(root), a, b);
	else {
		return QuerySum(Left(root), a, mid) +
			QuerySum(Right(root), mid + 1, b);
	}
}

int main() {
	int N, Q, a_, b_, c_, v_;
	char cmd;
	scanf("%d %d", &N, &Q);
	BuildTree(0, 1, N);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &v_);
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
			printf("%d\n", QuerySum(0, a_, b_));
		}
	}

	return 0;
}