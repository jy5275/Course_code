#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<queue>
#include<memory>
using namespace std;
void RandGen(int n, int upper_limit = INT_MAX, FILE *ofile = NULL) {
	if (!ofile) ofile = fopen("sort_raw.txt", "w+");   //set default output file
	for (int i = 0; i < n; i++)
		fprintf(ofile, "%d ", rand() % upper_limit);
	fclose(ofile);
}
template<class T>
void Swap(T A[], int i, int j) {
	T temp = A[i];	A[i] = A[j];	A[j] = temp;
}
//=========================================================================
template<class T>
void ShellSort(T A[], int n) {
	for (int delta = n / 2; delta > 0; delta /= 2)
		for (int j = 0; j < delta; j++)
			//对A[j]开始,长为n-j的序列做步长为delta的插入排序
			ModifiedInsertSort(&A[j], n - j, delta);
}
template<class T>
void ModifiedInsertSort(T A, int n, int delta) {  //步长为delta的插入排序
	for (int i = delta; i < n; i += delta)
		for (int j = i; j >= delta; j -= delta) {
			if (A[j - delta] > A[j])
				Swap(A, j, j - delta);
			else break;
		}
}
//=====================================================================
template<class T>
int Partition(T A[], int left, int right) {     //返回轴位
	int i = left, j = right;
	T pivotValue = A[left];	//选最左元素为轴值
	while (i != j) {		//Divide!
		while (A[j] > pivotValue && i < j)		//j左移至<=轴值的元素
			j--;
		if (i < j) { 		//..移它到i位(j变空)
			A[i] = A[j];  i++; 
		}
		while (A[i] <= pivotValue && i < j)		//i右移至<轴值的元素
			i++;
		if (i < j) {		//..移它到j位(i变空)
			A[j] = A[i];  j--;
		}
	}   //每个循环结束时,i指向区域都为空
	A[i] = pivotValue;
	return i;
}
template<class T>
void QuickSort(T A[], int left, int right) {
	if (left < right) {
		int pivot = Partition(A, left, right);
		QuickSort(A, left, pivot - 1);
		QuickSort(A, pivot + 1, right);
	}
}
//===================================================================
template<class T>
void MergeSort(T A[], T TempA[], int left, int right) {
	int mid;
	if (left < right) {      //如果已经Divide到单个元素,就不用再MergeSort
		mid = (left + right) / 2;
		MergeSort(A, TempA, left, mid);
		MergeSort(A, TempA, mid + 1, right);
		Merge(A, TempA, left, right, mid);
	}
}
template<class T>
void Merge(T A[], T TempA[], int left, int right, int mid) {
	int i = left, i1 = left, i2 = mid + 1;
	for (int j = left; j <= right; j++)     //先把原数组copy到临时数组中,再处理
		TempA[j] = A[j];
	while (i1 <= mid && i2 <= right) {
		if (TempA[i1] <= TempA[i2])   //copy左元素,移左指针
			A[i++] = TempA[i1++];
		else A[i++] = TempA[i2++];     //copy右元素,移右指针
	}
	//处理尾巴
	while (i1 <= mid) A[i++] = TempA[i1++];
	while (i2 <= right) A[i++] = TempA[i2++];
}
//=========堆排序============================
template<class T>
void HeapSort(T A[], int n) {
	priority_queue<T> max_heap(A, A + n);
	for (int i = 0; i < n; i++) {
		A[n - i - 1] = max_heap.top();
		max_heap.pop();
	}
}
//============================================
/* 桶排序:使用前提是已知A的range在0~m,且range不太离散.O(m+n) */
template<class T>
void BucketSort(T A[], int n, int m) {   //A中n个元素分布在0~m间
	T *TempA = new T[n];            //1.初始化count,TempA
	int *count = new int[m];
	memset(count, 0, m * sizeof(int));
	for (int i = 0; i < n; i++)
		TempA[i] = A[i];
	for (int i = 0; i < n; i++) {         //2.收集:把A[]中元素放进m个垃圾桶
		int k = A[i];	//提取排序码
		count[k]++;
	}
	for (int i = 1; i < m; i++)         //3.桶累进更新
		count[i] = count[i - 1] + count[i];
	for (int i = n - 1; i >= 0; i--) {  //4.分配:倒扫原A,分配指定桶的垃圾
		int k = TempA[i];	//提取排序码
		count[k]--;
		A[count[k]] = TempA[i];
	}
	delete[]TempA; delete[]count;
}
/* 基数排序:收集/分配与直接桶排序不同,这里的桶编号(排序码)要计算一番
这给我们2个启示:
1)收集时被扔桶里的并非【元素本身】,而是元素的【排序码】
2)累进更新时,桶中信息由【i号桶装了几个ele】-->【i号桶的ele放在新A哪段】
这使得分配时只要得知TempA[j]的排序码k,就能一步将TempA[j]分派到新A正确位置A[count[k]]
排序码相同的元素即视为相同！ O(d*(r+n))
*/
template<class T>
void RadixSort(T A[], int n, int d, int r) {  //十进制数中r=10
	T *TempA = new T[n];
	int *count = new int[r], Radix = 1;
	for (int i = 1; i <= d; i++) {        // d个排序码,r个桶,装桶d次
		memset(count, 0, r * sizeof(int));    //【1.初始化】count和TempA
		for (int i = 0; i < n; i++)
			TempA[i] = A[i];
		for (int j = 0; j < n; j++) {         //【2.收集】按照排序码k装桶
			int k = (TempA[j] / Radix) % r;   //提取排序码
			count[k]++;       //按排序码装桶
		}
		for (int j = 1; j < r; j++)           //【3.累进更新】
			count[j] = count[j - 1] + count[j];
		for (int j = n - 1; j >= 0; j--) {    //【4.分配】倒扫A的n个元素
			int k = (TempA[j] / Radix) % r;  //提取排序码
			count[k]--;
			A[count[k]] = TempA[j];   //按照桶中信息分配位置
		}
		Radix *= r;
	}
	delete[]TempA; delete[]count;
}
//=========================================================================
template<class T>
void AdjustRecord(T A[], int IndexA[], int n) {
	T temp;
	for (int i = 0; i < n; i++) {
		int j = i;
		temp = A[i];
		while (IndexA[j] != i) {
			int k = IndexA[j];
			A[j] = A[k];
			IndexA[j] = j;
			j = k;
		}
		A[j] = temp;
		IndexA[j] = j;
	}
}
template<class T>
bool IsLarger(const T A[], const T IndexA[], int i, int j) {
	return A[IndexA[i]] > A[IndexA[j]];
}
template<class T>
void IndexSort(T A[], int n) {
	int *IndexA = new int[n];
	for (int i = 0; i < n; i++) IndexA[i] = i;
	for (int i = 0; i < n; i++) {    //对IndexA[]排序,重载<即可
		for (int j = i; j > 0; j--) {
			if (IsLarger(A, IndexA, j - 1, j)) {
				T temp = IndexA[j];
				IndexA[j] = IndexA[j - 1];
				IndexA[j - 1] = temp;
			}
			else break;    //前已排好序
		}
	}
	AdjustRecord(A, IndexA, n); //按照排好序的IndexA调整A
}
template<class It>
void Print(It f, It l) {
	for (It it = f; it != l; ++it)
		cout << *it << " ";
	printf("\n");
}
int main() {
	int n; scanf("%d", &n);
	RandGen(n, 100);
	int *p = (int*)malloc(n * sizeof(int));
	int *pTemp = (int*)malloc(n * sizeof(int));
	FILE *infile = fopen("sort_raw.txt", "r+");
	for (int i = 0; i < n; i++) fscanf(infile, "%d", p + i);
	//QuickSort(p, 0, n - 1);

	printf("Original A: \n"); Print(p, p + n);
	IndexSort(p, n);
	printf("BucketSort: \n"); Print(p, p + n);

	fclose(infile);
	remove("sort_raw.txt");
	free(p);
	free(pTemp);
	return 0;
}