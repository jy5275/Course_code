#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<string.h>
#include<queue>
#include<cmath>
#include<memory.h>
#include<algorithm>
using namespace std;
const int MAXN = 2010;
int Next[2 * MAXN];
int ans = 0, n, len0;
string line[6], cb;
int findnext(int s) {
	memset(Next, 0, sizeof(Next));
	int i = s, k = s - 1, m = cb.length();
	int Max = 0;
	Next[i] = s - 1;
	while (i < m - 1) {
		while (k >= s && cb[i] != cb[k])
			k = Next[k];
		i++, k++;
		Next[i] = k;
		if (i - k + s + 1 >= len0)
			Max = max(Max, k - s);
	}
	return Max;
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		cin >> line[i];
	len0 = line[1].length();
	for (int i = 0; i < len0; i++) {	//从line[1]的i位开始匹配其它line
		int min0 = 1 << 29;
		for (int j = 2; j <= n; j++) {
			cb = line[1] + '-' + line[j] + '-';
			int tmp = findnext(i);	//返回line[1]与line[j]从line[1]的i位开始公共子串
			if (tmp <= ans){	//第i位匹配结果不超过ans,就不再继续匹配i位了
				min0 = 0;
				break;
			}
			min0 = min(min0, tmp);	//min0记录所有line中的最小匹配长度
		}
		ans = max(min0, ans);	//
	}
	printf("%d\n", ans);
	return 0;
}