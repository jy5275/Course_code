#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<set>
#include<vector>
using namespace std;
const int LEN = 111;
//原始元素集合为Array
double Array[LEN];

int findMid(vector<int> &S, int l, int len = 5) {
	//【Bug3】算法中两处调用findMid,没有customize不同需求！
	//【Bug2】函数中修改参数数组要传引用&！
	//对S中[l,l+len)区间按指向Array中的元素大小进行排序(索引排序)
	for (int i = l; i < l + len; i++)
		for (int j = i + 1; j < l + len; j++)
			if (Array[S[j]] < Array[S[i]]) {
				int tmp = S[j];
				S[j] = S[i];
				S[i] = tmp;
			}
	return S[l + len / 2];	//【Bug3】只有len=5时返回值才有意义
}

int Select(vector<int> &S, int k) {	//返回S集合中第k小元素的下标索引
	if (S.size() < 5) {				//【Bug1】没加递归出口！导致无穷递归！
		findMid(S, 0, S.size());
		return S[k - 1];		//【Bug4】第k小者是排序后的S[k-1]而非S[k]
	}
	vector<int> M, A, B, C, D;

	// 1.为每5元组排序+找Mid->M
	for (int i = 0; i + 4 < S.size(); i += 5)
		M.push_back(findMid(S, i));	//排序S[i,i+4],并返回中位数索引mid
	
	// 2.找中位数集的中位数
	int m_index = Select(M, (M.size() / 2) + 1);
	double m = Array[m_index];

	// 3.把S中各元素扔进ABCD
	int i = 0;
	for (i = 0; i + 4 < S.size(); i += 5) {
		int index = S[i + 2];
		if (Array[index] < m) {
			C.push_back(S[i]);
			C.push_back(S[i + 1]);
			C.push_back(S[i + 2]);
			A.push_back(S[i + 3]);
			A.push_back(S[i + 4]);
		}
		else if (Array[index] > m) {
			D.push_back(S[i]);
			D.push_back(S[i + 1]);
			B.push_back(S[i + 2]);
			B.push_back(S[i + 3]);
			B.push_back(S[i + 4]);
		}
		else {
			C.push_back(S[i]);
			C.push_back(S[i + 1]);
			B.push_back(S[i + 3]);
			B.push_back(S[i + 4]);
		}
	}	//剩下没分组的元素统统扔进D
	for (; i < S.size(); i++)
		D.push_back(S[i]);

	// 3.处理AD中所有元素,并入BC
	for (int j = 0; j < A.size(); j++) {
		int index = A[j];
		if (Array[index] < m)
			C.push_back(index);
		else if (Array[index] > m)
			B.push_back(index);
	}
	for (int j = 0; j < D.size(); j++) {
		int index = D[j];
		if (Array[index] < m)
			C.push_back(index);
		else if (Array[index] > m)
			B.push_back(index);
	}

	// 5.判断返回！
	if (k == C.size() + 1)
		return m_index;
	else if (k <= C.size())
		return Select(C, k);	//【Bug6】写漏了return
	else
		return Select(B, k - C.size() - 1);
}
int main() {
	vector<int> S;
	for (int i = 0; i < LEN; i++) {
		Array[i] = rand();
		S.push_back(i);
	}
	for (int i = 0; i < LEN; i++)
		printf("%.2lf ", Array[i]);
	printf("\n");
	for (int i = 1; i <= LEN; i++)
		printf("%.2lf ", Array[Select(S, i)]);

	return 0;
}