#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
int *findNext(string P) {  //特征向量Next算法(存疑???)
	int m = P.size();
	int *next = new int[m];
	next[0] = -1;
	for (int i = 0, k = -1; i < m - 1; i++, k++) {
		while (k >= 0 && P[k] != P[i]) 
			k = next[k];
		next[i] = k;
	}
	return next;
}
//想象成T绝对静止,匹配时ij和谐移动,不匹配时ij不动,P相对移动
int KMP(const string T, const string P, int *Next, int start) {  //KMP模式匹配算法
	int i = 0, j = start;
	int pLen = P.size(), tLen = T.size();
	if (tLen - start < pLen) return -1;
	while (i < pLen && j < tLen) {
		if (i == -1 || T[j] == P[i])  //只要匹配成功,就移动i,j的位置
			i++, j++;
		else i = Next[i];  //匹配不成功,i回到N[i](P整体向右移动),j不动
	}
	if (i >= pLen) return j - pLen + 1;
	else return -1;
}
int main() {
	string s1 = "abcdaabcab";
	int *pNext = findNext(s1);
	for (int i = 0; i < s1.size(); i++)
		cout << pNext[i] << endl;
	return 0;
}