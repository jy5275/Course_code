#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<memory.h>
#include<set>
#include<string>
#include<vector>
#include<map>
#include<stack>
using namespace std;
vector<int> ans;
const int MAX = 400010;
int Next[MAX];
void FindNext(string P) {	//找出Next数组就大功告成了！
	int len = P.length();
	Next[0] = -1;
	int i = 0, k = -1;
	while (i < len) {
		while (k >= 0 && P[k] != P[i])
			k = Next[k];	//递归地往前找匹配的前后缀
		i++, k++;
		Next[i] = k;
	}
}
void PrintAns(int len) {
	int i = len;
	bool f = 1;
	stack<int> s;
	s.push(len);	//P本身也是一个"逆序对"
	while (Next[i] > 0) {	//递归地往前找前后缀匹配的i
		s.push(Next[i]);
		i = Next[i];
	}
	while (!s.empty()) {
		if (!f) printf(" ");
		printf("%d", s.top());
		s.pop();
		f = 0;
	}
	printf("\n");
}
int main() {
	string str, pref, suf;
	char tmp[MAX];
	while (scanf("%s", tmp) != EOF) {
		str = tmp;
		int len = str.length();
		FindNext(str);
		PrintAns(len);
	}
	return 0;
}