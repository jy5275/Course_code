#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<queue>
#include<memory.h>
using namespace std;
const int MAX = 500010;
int n = 0;
long long Array[MAX], ans, TempArray[MAX];
void Merge(int left, int right, int mid) {
	int i = left, j, index_left = left, index_right = mid + 1;
	for (j = left; j <= right; j++)   //先把原数组copy到临时数组中,再处理
		TempArray[j] = Array[j];
	while (index_left <= mid && index_right <= right) {
		if (TempArray[index_left] <= TempArray[index_right]) //copy左元素,移左指针
			Array[i++] = TempArray[index_left++];
		else {
			Array[i++] = TempArray[index_right++];   //copy右元素,移右指针
			ans += mid + 1 - index_left;
		}
	}
	//处理尾巴
	while (index_left <= mid) 
		Array[i++] = TempArray[index_left++];
	while (index_right <= right) 
		Array[i++] = TempArray[index_right++];
}
void MergeSort(int left, int right) {
	int mid;
	if (left < right) {    //如果已经Divide到单个元素,就不用再MergeSort
		mid = (left + right) >> 1;
		MergeSort(left, mid);
		MergeSort(mid + 1, right);
		Merge(left, right, mid);
	}
}

int main() {
	//scanf("%d", &n);
	while (cin >> n) {
		ans = 0;
		for (int i = 1; i <= n; i++)
			scanf("%lld", &Array[i]);
		MergeSort(1, n);
		printf("%lld\n", ans);
		//scanf("%d", &n);
	}

	return 0;
}