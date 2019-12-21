#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
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
int a[5060][5060] = { 0 }, n, maxMatr = 0;
pair<int, int> numOfAdd(int x) {
	int numOfLine = n, ans = 1;
	while (x > numOfLine) {
		x = x - numOfLine;
		numOfLine--;
		ans++;
	}
	return pair<int, int>(ans, x);
}
int calcSumR(int r, pair<int, int> tmp) {  //��a[r][tmp.x]��a[r][tmp.x+ans]�ĺ�
	int sum = 0;
	for (int i = tmp.second; i <= tmp.second + tmp.first - 1; i++) {
		sum += a[r][i];
	}
	return sum;
}
int calcSumC(int c, pair<int, int> tmp) {  //��a[tmp.x][c]��a[tmp.x+ans][c]�ĺ�
	int sum = 0;
	for (int i = tmp.second; i <= tmp.second + tmp.first - 1; i++) {
		sum += a[i][c];
	}
	return sum;
}
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> a[i][j];
			if (a[i][j] > maxMatr)maxMatr = a[i][j];
		}
	}
	clock_t startTime = clock();
	for (int i = 1; i <= n; i++) {   //��ʼ�����Ͼ���
		int numOfAdder = 2, stAdderAt = 1;
		for (int j = n + 1; j <= (n + 1)*n / 2; j++) {
			if (stAdderAt + numOfAdder - 1 > n) {
				stAdderAt = 1;
				numOfAdder += 1;
			}
			for (int p = stAdderAt; p <= stAdderAt + numOfAdder - 1; p++) {
				a[i][j] += a[i][p];
			}
			stAdderAt++;
			/*
			pair<int, int> tmp = numOfAdd(j);
			a[i][j] = calcSumR(i, tmp);*/
			if (a[i][j] > maxMatr)maxMatr = a[i][j];
		}
	}
	for (int i = n + 1; i < (n + 1)*n / 2; i++) {  //��ʼ���±ߵľ���
		int numOfAdder = 2, stAdderAt = 1;
		for (int j = 1; j <= (n + 1)*n / 2; j++) {
			if (stAdderAt + numOfAdder - 1 > n) {
				stAdderAt = 1;
				numOfAdder += 1;
			}
			for (int p = stAdderAt; p <= stAdderAt + numOfAdder - 1; p++) {
				a[i][j] += a[p][j];
			}
			stAdderAt++;
			/*
			pair<int, int> tmp = numOfAdd(i);
			a[i][j] = calcSumC(j, tmp);*/
			if (a[i][j] > maxMatr)maxMatr = a[i][j];
		}
	}
	cout << maxMatr << endl;

	clock_t endTime = clock();
	//cout<< "���������ʱ��:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	return 0;
}