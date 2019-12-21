/* Warning：This is a buggy program！*/
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<string.h>
#include<cmath>
#include<memory.h>
#include<algorithm>
using namespace std;
char s1[100], s2[100];
int maxLen[100][100];
int calcMaxLen(int i, int j) {		//求s1的前i与s2的前j个字符中的公共串
	if (i == 0 || j == 0)return 0;
	if (s1[i - 1] == s2[j - 1])
		return calcMaxLen(i - 1, j - 1) + 1;
	else
		return max(calcMaxLen(i - 1, j), calcMaxLen(i, j - 1));
}
int main() {
	cin >> s1 >> s2;
	int len1 = strlen(s1), len2 = strlen(s2);
	//clock_t startTime = clock();

	//-----------递归方案---------------------------------
	cout << calcMaxLen(strlen(s1), strlen(s2)) << endl;
	//-----------动规方案---------------------------------
	for (int i = 0; i < len1; i++) {
		for (int j = 0; j < len2; j++) {
			if (i == 0 || j == 0)
				maxLen[i][j] = 0;
			//边界条件是i,j有一个是0的情况
			if (s1[i] == s2[j])
				maxLen[i][j] = maxLen[i - 1][j - 1] + 1;
			else
				maxLen[i][j] = max(maxLen[i - 1][j], maxLen[i][j - 1]);
		}
	}
	cout << maxLen[len1 - 1][len2 - 1] << endl;
	//----------------------------------------------------

	//clock_t endTime = clock();
	//cout << "程序段运行时间:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	return 0;
}