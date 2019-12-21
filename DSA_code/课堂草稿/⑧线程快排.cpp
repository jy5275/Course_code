

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<memory.h>
#include<thread>
#include<string.h>
#include<math.h>
#include<atomic>
#include<time.h>
using namespace std;
const int MAX = 1 << 24;
short A[MAX], TempA[MAX];
int Partition(int left, int right) {     //返回轴位
	int i = left, j = right;
	short pivotValue = A[left];       //选最左元素为轴值
	while (i != j) {       //Divide!
		while (A[j] > pivotValue && i < j) j--;   //j左移至<=轴值的元素
		if (i < j) { A[i] = A[j]; i++; }      //..移它到i位(j变空)
		while (A[i] <= pivotValue && i < j) i++;  //i右移至<轴值的元素
		if (i < j) { A[j] = A[i]; j--; }      //..移它到j位(i变空)
	}   //每个循环结束时,i指向区域都为空
	A[i] = pivotValue;
	return i;
}
void QuickSort(int left, int right) {
	if (left < right) {
		int pivot = Partition(left, right);
		QuickSort(left, pivot - 1);
		QuickSort(pivot + 1, right);
	}
	return;
}
void MergeSort(int left, int right, int mid) {
	for (int i = left; i <= right; i++)
		TempA[i] = A[i];
	int i1 = left, i2 = mid + 1, p = left;// , mid = (left + right) / 2;
	while (i1 <= mid && i2 <= right) {
		if (TempA[i1] <= TempA[i2])
			A[p++] = TempA[i1++];
		else A[p++] = TempA[i2++];
	}
	while (i1 <= mid) A[p++] = TempA[i1++];
	while (i2 <= right) A[p++] = TempA[i2++];
}
int main() {
	for (int i = 0; i < MAX; i++)
		A[i] = (rand() % 8192);
	clock_t startTime = clock();
	int div = MAX / 8;

	thread t1(QuickSort, 0, div);
	thread t2(QuickSort, div + 1, 2 * div);
	thread t3(QuickSort, 2 * div + 1, 3 * div);
	thread t4(QuickSort, 3 * div + 1, 4 * div);
	thread t5(QuickSort, 4 * div + 1, 5 * div);
	thread t6(QuickSort, 5 * div + 1, 6 * div);
	thread t7(QuickSort, 6 * div + 1, 7 * div);
	thread t8(QuickSort, 7 * div + 1, MAX - 1);
	t1.join(); t2.join(); t3.join(); t4.join();
	t5.join(); t6.join(); t7.join(); t8.join();
	MergeSort(0, 2 * div, div);
	MergeSort(2 * div + 1, 4 * div, 3 * div);
	MergeSort(4 * div + 1, 6 * div, 5 * div);
	MergeSort(6 * div + 1, MAX - 1, 7 * div);
	MergeSort(0, 4 * div, 2 * div);
	MergeSort(4 * div + 1, MAX - 1, 6 * div);
	MergeSort(0, MAX - 1, 4 * div);
	//QuickSort(0, MAX - 1);
	clock_t endTime = clock();
	for (int i = 1; i < MAX; i++) {
		if (A[i - 1] > A[i]) {
			printf("A[%d]=%d, A[%d]=%d\n", i - 1, A[i - 1], i, A[i]);
			break;
		}
	}
	cout << "程序段运行时间:" <<
		(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

	return 0;
}