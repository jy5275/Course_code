//http://noi.openjudge.cn/ch0206/2989/
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
int N, K, sugarPack[102], mostSugar[102][102];
const int MIN = -1000000 * 100;
int calcMostSugar(int n, int rem) {  //计算只有前N种糖果包的情况下取K*k+rem个糖果最多取法
	if (mostSugar[n][rem] != -1) return mostSugar[n][rem];
	if (n == 0) {
		if (rem != 0) return 1 << 31;
		else return 0;
	}
	int noPick = calcMostSugar(n - 1, rem);
	int doPick = calcMostSugar(n - 1, (rem + K - sugarPack[n] % K) % K) + sugarPack[n];
	mostSugar[n][rem] = max(noPick, doPick);
	return mostSugar[n][rem];
}
int main() {
	cin >> N >> K;
	for (int i = 1; i <= N; i++)
		cin >> sugarPack[i];
	//clock_t startTime = clock();

	//-----------------动规方案-----------------------------------
	for (int i = 1; i < K; i++)   //边界条件1:从0个糖果中取使总数%K满足余数为rem,直接失败！ 
		mostSugar[0][i] = 1 << 31;
	mostSugar[0][0] = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < K; j++) {
			mostSugar[i][j] = max(mostSugar[i - 1][j],
				mostSugar[i - 1][(j + K - sugarPack[i] % K) % K] + sugarPack[i]);
		}
	}
	cout << mostSugar[N][0] << endl;
	//-----------------递归方案----------------------------------
	memset(mostSugar, -1, sizeof(mostSugar));
	cout << calcMostSugar(N, 0) << endl;
	//----------------------------------------------------------------

	//clock_t endTime = clock();
	//cout<< "程序段运行时间:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	return 0;
}/*
 好题！二维数组看似是二维边界,实则仅一维边界
 糖果、采草药、数字组合都是无序pick类问题,紧紧抓住"拿走某元素对pool整体条件影响",
 子问题是"从前n-1个元素中任取若干,总和满足条件k-1"
 每个递归环节中仅有pick or not两种选择,对应新一层的两种状态
 */