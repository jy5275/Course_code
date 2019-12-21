#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<string.h>
#include<queue>
#include<cmath>
#include<memory.h>
#include<algorithm>
using namespace std;
/* 秒速AC！Oh Yeah！分治大法好,不管啥“逆序对”，统统“归并+”
 * 左右各自消化内部逆序对，再归并统计总逆序对数
 * 本题注意设置critical指针记录 2*a[i2] 位置
 */
const int MAXN = 200010;
int A[MAXN], TempA[MAXN];
long long cnt = 0;
void Merge(int left, int right) {
	int mid = (left + right) / 2;
	for (int i = left; i <= right; i++)
		TempA[i] = A[i];
	int i1 = left, i2 = mid + 1, p = left, crit = left;
	while (i1 <= mid && i2 <= right) {
		if (TempA[i1] <= TempA[i2])
			A[p++] = TempA[i1++];
		else {		//移动i2指针时需要更新cnt
			while (TempA[crit] <= 2 * TempA[i2] && crit <= mid) 
				crit++;		//维护critcal指针,指向左归并串刚好超过2*TempA[i2]处
			cnt += mid + 1 - crit;
			A[p++] = TempA[i2++];
		}
	}
	while (i1 <= mid) A[p++] = TempA[i1++];
	while (i2 <= right) A[p++] = TempA[i2++];
}
void MergeSort(int left, int right) {
	if (left >= right)return;
	int mid = (left + right) / 2;
	MergeSort(left, mid);
	MergeSort(mid + 1, right);
	Merge(left, right);
}
int main() {
	int N;
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &A[i]);
	MergeSort(0, N - 1);
	printf("%lld", cnt);
	return 0;
}