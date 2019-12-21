#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<memory.h>
#include<set>
#include<string>
#include<vector>
#include<map>
using namespace std;
/* 排序算法也要复习！尤其归并,快排,Shell等
 * 注意参数范围！N没溢出不代表cnt不溢出！
 * 【归并】是表象，【分治】是本质！
 */
const int MAX = 100010;
int N, A[MAX], TempA[MAX];
long long cnt = 0;
void Merge(int left, int right) {	
	int mid = (left + right) / 2, p = left;
	int i1 = left, i2 = mid + 1;
	for (int i = left; i <= right; i++)
		TempA[i] = A[i];
	while (i1 <= mid && i2 <= right) {
		if (TempA[i1] < TempA[i2]) {
			cnt += mid + 1 - i1;	//把这一区间的逆序对消化掉
			A[p++] = TempA[i2++];
		}
		else 
			A[p++] = TempA[i1++];
	}
	while (i1 <= mid) A[p++] = TempA[i1++];
	while (i2 <= right) A[p++] = TempA[i2++];
}
void MergeSort(int left, int right) {	//Divide and conquer！
	if (left < right) {
		int mid = (left + right) / 2;
		MergeSort(left, mid);		//Divide！
		MergeSort(mid + 1, right);	//Divide！
		Merge(left, right);			//Conquer！
	}
}
int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) 
		scanf("%d", &A[i]);
	MergeSort(0, N - 1);
	printf("%lld\n", cnt);
	return 0;
}