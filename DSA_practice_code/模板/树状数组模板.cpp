#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<thread>
#include<string.h>
#include<math.h>
#include<atomic>
#include<queue>
using namespace std;
const int MAX = 1000;
int N;
int C[MAX], a[MAX];
int lowbit(int x) { return x & (-x); }
/* 树状数组初始化C
 * C[i] = a[i - lowbit(i) + 1] + a[i - lowbit(i) + 2]... + a[i]
 * C[14] = a13 + a14
 * C[21] = a21 + a20 + a16
 */
void BuildTree() {
	for (int i = 1; i <= N; i++) {
		C[i] = 0;
		for (int j = i; j > i - lowbit(i); j--)
			C[i] += a[j];
	}
}

/* 树状数组求和sum(val)：
 * iterator i follows a binary decrease sequence：
 * sum(val) = C[i1] + C[i2] + ... + C[im]
 * i：(from val to 0) i = i - lowbit(i)
 * sum(6) = C6 + C4;
 * sum(14) = C14 + C12 + C8;
 * sum(29) = C29 + C28 + C24 + C16;
 */
int QuerySum(int k) {
	int sum = 0;
	for (int i = k; i >= 1; i = i - lowbit(i))
		sum += C[i];
	return sum;
}

/* 树状数组单点更新a[val]：
 * i螺旋上升：需要更新C[i1], C[i2], ... C[im]
 * i：(from 0 to N) i = i + lowbit(i)
 * a[4]：C[4], C[8], C[16]...
 * a[7]：C[7], C[8], C[16]...
 * a[9]：C[9], C[10], C[12], C[16], C[32]...
 */
void Renew(int k, int val) {
	for (int i = k; i <= N; i = i + lowbit(i))
		C[i] = val;
}
int main(){
	
	return 0;
}