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
int calcMaxLen(int end) {  //返回以a[end]为终点的最长上升子序列长度
	if (cacheMaxLen[end] != -1) return cacheMaxLen[end];
	if (end == 0) return 1;
	int R = 0;    //R为a[end]前的最大上升子序列长度
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

	//--------------递归方案------------------------------------------
	int maxL = 0;
	memset(cacheMaxLen, -1, sizeof(cacheMaxLen));
	for (int i = 0; i < n; i++)
		maxL = max(maxL, calcMaxLen(i));
	cout << maxL << endl;
	//--------------动规方案之人人为我----------------------------
	for (int i = 1; i <= n; i++)
		cacheMaxLen[i] = 1;  //边界条件:i条以a[i]结尾的最长上升子序列都只有自己
	for (int i = 2; i <= n; i++) {    //计算以a[i]结尾的最长上升子序列长度
		for (int j = 1; j < i; j++) { //计算以a[j]为end,可接上a[i]的上升序列长度
			if (a[j] < a[i])
				cacheMaxLen[i] = max(cacheMaxLen[i], cacheMaxLen[j] + 1);
		}
	}
	cout << *max_element(cacheMaxLen + 1, cacheMaxLen + n + 1) << endl;
	//--------------动规方案之我为人人----------------------------
	for (int i = 1; i <= n; i++)
		cacheMaxLen[i] = 1;  //边界条件:i条以a[i]结尾的最长上升子序列都只有自己
	clock_t startTime = clock();
	for (int i = 1; i <= n; i++) {           //a[i]就是"我"
		for (int j = i + 1; j <= n; j++) {   //a[j]就是"人人"
			if (a[j] > a[i])
				//确保a[j]可以延伸以a[i]为终点的上升序列
				//"我"把延伸信号传递给i
				cacheMaxLen[j] = max(cacheMaxLen[j], cacheMaxLen[i] + 1);
		}
	}
	cout << *max_element(cacheMaxLen + 1, cacheMaxLen + n + 1) << endl;
	//-----------------------------------------------------------------

	clock_t endTime = clock();
	//cout << "Total Time: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	
	return 0;
}