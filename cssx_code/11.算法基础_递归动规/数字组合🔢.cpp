#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<set>
#include<string>
#include<cstring>
#include<cmath>
#include<memory>
#include<stdexcept>
#include<time.h>
#include<algorithm>
#include<iomanip>
#include<fstream>
using namespace std;
int a[1002], n, t, cache[22][1002];
int combination(int n_case, int t_case) { //ǰn_case�������Ӻ�Ϊt_case����Ϸ�ʽ
	if (t_case == 0)return 1;
	if (n_case == 0)return 0;
	if (cache[n_case][t_case] != -1) return cache[n_case][t_case];
	if (t_case >= a[n_case]) {
		int ans = combination(n_case - 1, t_case - a[n_case]) + combination(n_case - 1, t_case);
		cache[n_case][t_case] = ans;
		return ans;
	}
	else {
		int ans = combination(n_case - 1, t_case);
		cache[n_case][t_case] = ans;
		return ans;
	}
}
int main() {
	cin >> n >> t;
	for (int i = 1; i <= n; i++) 
		cin >> a[i];
	clock_t startTime = clock();
	
	//-----------�ݹ鷽��---------------------------------
	memset(cache, -1, sizeof(cache));
	cout << combination(n, t) << endl;
	//-----------���淽��---------------------------------
	memset(cache[0], 0, sizeof(cache[0]));
	for (int j = 0; j <= t; j++)cache[j][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= t; j++) {
			if (a[i] <= j)cache[i][j] = cache[i - 1][j - a[i]] + cache[i - 1][j];
			else cache[i][j] = cache[i - 1][j];
		}
	}
	cout << cache[n][t] << endl;
	//----------------------------------------------------
	
	clock_t endTime = clock();
	//cout<< "���������ʱ��:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	return 0;
}/*
 ע��ͼ�����Ʃ��a[i]<=jд��a[i]<=i,a[n_case]д��a[n]���־ͱ�����,����ִ�а���ŷ��ֵ���...
 */