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
int change[1001][1001] = { 0 };   //change����s1ǰi�Ӵ���s2ǰj�Ӵ��ľ���
int triMin(int a, int b, int c) { return min(min(a, b), c); }
int calcChange(int n, int m) {
	if (change[n][m] != -1) return change[n][m];
	int ans = 0;
	if (n == 0 || m == 0)		//case1���߽�����
		ans = max(n, m);
	else if (s1[n] == s2[m])	//case2��ĩ�ַ�ͬ
		ans = calcChange(n - 1, m - 1);
	else		//case3��s1��ĩ�ַ� or s2��ĩ�ַ� or s1s2�޸�ĩ�ַ�
		ans = triMin(calcChange(n - 1, m),		//How to change��That's a Q
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

		//-----------�ݹ鷽��---------------------------------
		memset(change, -1, sizeof(change));
		cout << calcChange(len1, len2) << endl;
		//-----------���淽��---------------------------------
		for (int i = 0; i <= len1; i++) {
			for (int j = 0; j <= len2; j++) {   //����s1ǰ׺i��s2ǰ׺j
				if (i == 0 || j == 0) 
					change[i][j] = max(i, j);
				else if (s1[i] == s2[j])        //��s1��iλ��s2��jλ��ͬ,��λ�����޸ģ�
					change[i][j] = change[i - 1][j - 1];
				else               //���s1��iλ��s2��jλ��ͬ,����·��ѡ��̵�һ����
					change[i][j] = triMin(change[i - 1][j],
						change[i][j - 1], change[i - 1][j - 1]) + 1;
			}
		}
		cout << change[len1][len2] << endl;
		//----------------------------------------------------
	}

	//clock_t startTime = clock();
	//clock_t endTime = clock();
	//cout<< "���������ʱ��:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	return 0;
}/*
 �����벻���������ⶼ���õݹ���
 */