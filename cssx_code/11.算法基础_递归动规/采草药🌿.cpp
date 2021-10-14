//http://noi.openjudge.cn/ch0206/1775/
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
//★核心状态转移方程:（在实际实现中分离）★
//★MaxValue(m, t) = max(MaxValue(m - 1, t), MaxValue(m - 1, t - t[m]) + v[m]);★
int T, M, maxValue[102][1002], cost[102], value[102];

//计算在前 [m] 种草药中采,[t] 时间内可采的最大 [value] 值
int calcMaxValue(int m, int t) { 
	if (t == 0 || m == 0) return 0;
	if (maxValue[m][t] != -1) return maxValue[m][t];

	int nopick, dopick = 0;
	nopick = calcMaxValue(m - 1, t);	// 不采这种药的最大value
	if (t >= cost[m])					// 时间够采m号草药
		dopick = calcMaxValue(m - 1, t - cost[m]) + value[m];
	maxValue[m][t] = max(nopick, dopick);	//【采还是不采？这是一个问题】
	
	return maxValue[m][t];
}

int main() {
	cin >> T >> M;
	for (int i = 1; i <= M; i++)
		cin >> cost[i] >> value[i];
	//clock_t startTime = clock();

	//-----------递归方案---------------------------------
	memset(maxValue, -1, sizeof(maxValue));
	cout << calcMaxValue(M, T) << endl;
	//-----------动规方案---------------------------------
	for (int i = 1; i <= M; i++) maxValue[i][0] = 0;
	for (int i = 0; i <= T; i++) maxValue[0][i] = 0;
	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= T; j++) {
			int nopick = maxValue[i - 1][j];	// 不采i号草药, maxValue同无i草药时
			int dopick;
			if (j >= cost[i])
				dopick = maxValue[i - 1][j - cost[i]] + value[i];	// ★核心状态转移方程★
			maxValue[i][j] = max(dopick, nopick);	// To pick or not to pick? That's a Q
		}
	}
	cout << maxValue[M][T] << endl;
	//----------------------------------------------------
	//clock_t endTime = clock();
	//cout<< "程序段运行时间:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	return 0;
}/*
 注意低级错误！譬如a[i]<=j写成a[i]<=i,a[n_case]写成a[n]这种就杯具了,逐行执行半天才发现得了...
 出现WA或RE,测试【特殊】数据→发现错误→逐行执行→debug,
 如果算法思路不清可以考虑在递归/动规种换一种
 */