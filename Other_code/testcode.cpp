#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<algorithm>
using namespace std;
const int MAX = 1000;
int bi1s(int x) {
	int sum = 0;
	while (x){
		sum += x & 1;
		x = x >> 1;
	}
	return sum;
}
int v[MAX], f1[MAX], f2[MAX];
int f(int n) {
	if (n == 1) {
		f2[n] = 0; return 0;
	}
	int tmpmax = 0;
	if (f2[n] != -1) return f2[n];
	for (int k = 1; k <= n - 1; k++) 
		tmpmax = max(tmpmax, (min(k, n - k) + f(k) + f(n - k)));
	f2[n] = tmpmax;
	return tmpmax;
}
void Init() {
	memset(f2, -1, sizeof(f2));
	for (int i = 0; i < MAX; i++)
		v[i] = bi1s(i);
	f1[0] = 0;
	for (int i = 1; i < MAX; i++)
		f1[i] = f1[i - 1] + v[i - 1];
}
bool Test() {
	for (int i = 1; i < MAX; i++)
		if (f1[i] != f2[i])return false;
	return true;
}
int main() {
	Init();
	f(MAX - 1);
	cout << Test() << endl;
	return 0;
}