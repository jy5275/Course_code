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
typedef pair<int, int> status;
int al[1001], N, maxA[1001][2];
int myMax(int a, int b, int c) {
	if (a >= b && a >= c)return a;
	if (b >= a && b >= c)return b;
	if (c >= a && c >= b)return c;
}
int calcMaxA(int n, int descend) {    //以No.n为终点的最长游览路线
	int tmpMaxA = 1;
	//descend=1表示至n时一直在上升,descend=1表示至n前已开始下降
	//tmpDescmaxA为接下来走下降路线的话之前最多走的步数
	if (maxA[n][descend] != -1) return maxA[n][descend];
	for (int i = 1; i < n; i++) {
		if (descend == 0) {
			if (al[i] < al[n])    //应该在上升！
				tmpMaxA = max(tmpMaxA, calcMaxA(i, 0) + 1);
		}
		else if (descend == 1) {
			if (al[i] > al[n])    //只能下降！
				tmpMaxA = myMax(tmpMaxA, calcMaxA(i, 0) + 1, calcMaxA(i, 1) + 1);
		}
	}
	maxA[n][descend] = tmpMaxA;
	return tmpMaxA;
}
int main() {
	int tmpMax = 1;
	cin >> N;
	for (int i = 1; i <= N; i++)
		cin >> al[i];
	clock_t startTime = clock();

	//-----------------动规方案-----------------------------------
	for (int i = 1; i <= N; i++) {	//从i出发走一走
		//maxA[i][0]为以i为终点的无下降路线长度max
		//maxA[i][1]为以i为终点的有下降路线长度max
		maxA[i][0] = 1, maxA[i][1] = 1;
		for (int j = 1; j < i; j++) {
			if (al[j] < al[i])	//可从j点往上走到i,更新以i为终点的最长上升路线长度
				maxA[i][0] = max(maxA[i][0], maxA[j][0] + 1);
			else if (al[j] > al[i])	//可从j点往下走到i,更新以i为终点的最长有下降路线长度
				maxA[i][1] = myMax(maxA[i][1], maxA[j][0] + 1, maxA[j][1] + 1);
		}
		tmpMax = myMax(tmpMax, maxA[i][0], maxA[i][1]);
	}
	cout << tmpMax << endl;
	//-----------------递归方案----------------------------------
	memset(maxA, -1, sizeof(maxA));
	for (int i = 1; i <= N; i++)
		tmpMax = myMax(tmpMax, calcMaxA(i, 0), calcMaxA(i, 1));
	cout << tmpMax << endl;
	//----------------------------------------------------------------

	clock_t endTime = clock();
	//cout<< "程序段运行时间:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	return 0;
}
/*递归return条件比较复杂的,动规之,
最适合要分析我上一个如何如何(上一步是否下降),
而不是下一个如何如何(下一行哪个最大)的情形
有的时候要在main函数遍历以i为起/终点的所有点找到最优解
*/