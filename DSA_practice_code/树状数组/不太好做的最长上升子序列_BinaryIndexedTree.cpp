/* http://dapractise.openjudge.cn/2018wk2/3/ */
//AC了,但仍不是很懂如何做到的？？？
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<list>
#include<vector>
#include<algorithm>
using namespace std;
const int MAX = 100000005;
int N, LIS[MAX], C[MAX] = { 0 };
int lowbit(int x) { return x & (-x); }
class CNum {
public:
	int val, pos;
	CNum(int p_, int v_) :pos(p_), val(v_) {}
};
vector<CNum> a;
vector<CNum> n;
bool operator<(const CNum n1, const CNum n2) {
	if (n1.val != n2.val) return n1.val < n2.val;
	return n1.pos > n2.pos;
}
int Query(int k) {
	int ans = 0, n = k;
	while (n > 0) {
		ans = max(ans, C[n]);
		n = n - lowbit(n);
	}
	return ans;
}
void Change(int k, int renew) {
	int n = k;
	while (n <= N) {
		C[n] = max(C[n], renew);
		n = n + lowbit(n);
	}
}
int main() {
	cin >> N; int v_;
	a.push_back(CNum(0, 0));
	n.push_back(CNum(0, 0));
	for (int i = 1; i <= N; i++) {
		scanf("%d", &v_);
		a.push_back(CNum(i, v_));
		n.push_back(CNum(i, v_));
	}
	sort(n.begin(), n.end());
	for (int i = 1; i <= N; i++) {
		LIS[n[i].pos] = Query(n[i].pos) + 1;
		Change(n[i].pos, LIS[n[i].pos]);
	}
	int tmpMax = 0;
	for (int i = N; i >= 1; i--) {
		if (C[i] > tmpMax) tmpMax = C[i];
	}
	cout << tmpMax << endl;
	return 0;
}