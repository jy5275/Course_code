#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<cstring>
#include<cmath>
#include<memory>
#include<time.h>
#include<algorithm>
#include<fstream>
using namespace std;
string s1, s2;
int change[1001][1001] = { 0 };   //change保存s1前i子串与s2前j子串的距离
int triMin(int a, int b, int c) { return min(min(a, b), c); }

int calcChange(int n, int m) {
	if (change[n][m] != -1) return change[n][m];
	
	int ans = 0;
	if (n == 0 || m == 0)		//case1：边界条件
		ans = max(n, m);
	else if (s1[n] == s2[m])	//case2：末字符同
		ans = calcChange(n - 1, m - 1);
	else		//case3：s1添末字符 or s2添末字符 or s1s2修改末字符
		ans = triMin(calcChange(n - 1, m),		//How to change？That's a Q
			calcChange(n, m - 1), calcChange(n - 1, m - 1)) + 1;
	change[n][m] = ans;
	return ans;
}

int main() {
	int n;
	cin >> n;
	while (n--) {
		cin >> s1 >> s2;
		int len1 = s1.size(), len2 = s2.size();
		s1 = " " + s1; s2 = " " + s2;

		//-----------递归方案---------------------------------
		memset(change, -1, sizeof(change));
		cout << calcChange(len1, len2) << endl;
		//-----------动规方案---------------------------------
		for (int i = 0; i <= len1; i++) {
			for (int j = 0; j <= len2; j++) {   //看看s1前缀i和s2前缀j
				if (i == 0 || j == 0) 
					change[i][j] = max(i, j);
				else if (s1[i] == s2[j])        //若s1的i位与s2的j位相同,此位不用修改！
					change[i][j] = change[i - 1][j - 1];
				else               //如果s1的i位与s2的j位不同,三种路径选最短的一条！
					change[i][j] = triMin(change[i - 1][j],
						change[i][j - 1], change[i - 1][j - 1]) + 1;
			}
		}
		cout << change[len1][len2] << endl;
		//----------------------------------------------------
	}

	//clock_t startTime = clock();
	//clock_t endTime = clock();
	//cout<< "程序段运行时间:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	return 0;
}/*
 真是想不到这种问题都能用递归解答
 */