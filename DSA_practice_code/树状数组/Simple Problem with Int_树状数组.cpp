/* http://dapractise.openjudge.cn/2018hw4/1/ */
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<limits.h>
#include<stack>
#include<memory.h>
#include<vector>
#include<algorithm>
using namespace std;
const int MAX = 100010;
int a[MAX], C[MAX], N;
int lowbit(int x) { return x & (-x); }
void Build() {
	for (int i = 1; i <= N; i++) {
		C[i] = 0;
		int leftmost = i - lowbit(i);
		for (int j = i; j > leftmost; j--)
			C[i] += a[j];	//【分清i与j！】
	}
}
long long QuerySum(int k) {
	long long sum = 0;
	for (int i = k; i >= 1; i = i - lowbit(i)) 
		sum += C[i];
	return sum;
}
long long Query(int s, int e) {
	return QuerySum(e) - QuerySum(s-1);	//【记得s-1！】
}
void Renew(int k, int delta) {
	for (int i = k; i <= N; i = i + lowbit(i))
		C[i] += delta;
}
void Add(int a, int b, int delta) {
	for (int i = a; i <= b; i++)
		Renew(i, delta);
}
int main() {
	int Q, a_, b_, c_;
	long long v_;
	char cmd;
	scanf("%d %d", &N, &Q);
	for (int i = 1; i <= N; i++) {
		scanf("%lld", &a[i]);
	}
	Build();
	for (int i = 0; i < Q; i++) {
		scanf("\n%c", &cmd);
		if (cmd == 'C') {
			scanf("%d %d %d", &a_, &b_, &c_);
			Add(a_, b_, c_);
		}
		else {
			scanf("%d %d", &a_, &b_);
			printf("%lld\n", Query(a_, b_));
		}
	}
	return 0;
}