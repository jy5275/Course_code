#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<string>
#include<cstring>
#include<set>
#include<memory>
#include<list>
#include<map>
#include<time.h>
#include<algorithm>
#define MAX 1005
using namespace std;
int cacheMaxLen[MAX] = { 0 }, a[MAX], n;
int calcMaxLen(int end) {  //������a[end]Ϊ�յ������������г���
	if (cacheMaxLen[end] != -1) return cacheMaxLen[end];
	if (end == 0) return 1;
	int R = 0;    //RΪa[end]ǰ��������������г���
	for (int i = end - 1; i >= 0; i--) {
		if (a[i] < a[end])
			R = max(R, calcMaxLen(i));
	}
	cacheMaxLen[end] = R + 1;
	return R + 1;
}
int main() {
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];

	//--------------�ݹ鷽��------------------------------------------
	int maxL = 0;
	memset(cacheMaxLen, -1, sizeof(cacheMaxLen));
	for (int i = 0; i < n; i++)
		maxL = max(maxL, calcMaxLen(i));
	cout << maxL << endl;
	//--------------���淽��֮����Ϊ��----------------------------
	for (int i = 1; i <= n; i++)
		cacheMaxLen[i] = 1;  //�߽�����:i����a[i]��β������������ж�ֻ���Լ�
	for (int i = 2; i <= n; i++) {    //������a[i]��β������������г���
		for (int j = 1; j < i; j++) { //������a[j]Ϊend,�ɽ���a[i]���������г���
			if (a[j] < a[i])
				cacheMaxLen[i] = max(cacheMaxLen[i], cacheMaxLen[j] + 1);
		}
	}
	cout << *max_element(cacheMaxLen + 1, cacheMaxLen + n + 1) << endl;
	//--------------���淽��֮��Ϊ����----------------------------
	for (int i = 1; i <= n; i++)
		cacheMaxLen[i] = 1;  //�߽�����:i����a[i]��β������������ж�ֻ���Լ�
	clock_t startTime = clock();
	for (int i = 1; i <= n; i++) {           //a[i]����"��"
		for (int j = i + 1; j <= n; j++) {   //a[j]����"����"
			if (a[j] > a[i])
				//ȷ��a[j]����������a[i]Ϊ�յ����������
				//"��"�������źŴ��ݸ�i
				cacheMaxLen[j] = max(cacheMaxLen[j], cacheMaxLen[i] + 1);
		}
	}
	cout << *max_element(cacheMaxLen + 1, cacheMaxLen + n + 1) << endl;
	//-----------------------------------------------------------------

	clock_t endTime = clock();
	//cout << "Total Time: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	
	return 0;
}