//http://bailian.openjudge.cn/practice/4121/
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stack>
#include<vector>
#include<bitset>
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
/*深搜用栈实现,一条路走到死,再返回换条路走;
广搜用队列实现,所有路都一步一步走*/
const int MAX = 100002;
int T, N, price[MAX], pre[MAX], post[MAX], min_price[MAX], max_price[MAX];
int strategy(int p1, int s1, int p2, int s2) {
	return price[s1] - price[p1] + price[s2] - price[p2];
}
//动归分解:第i天前完成首次买卖最大收益=max(第i天卖最大收益,i-1天前完成买卖最大收益)
//动归分解:第j天后完成二次买卖最大收益=max(第j天买最大收益,j+1天后完成买卖最大收益)
int main() {
	cin >> T;
	while (T--) {
		scanf("%d", &N);   //scanf极大省时！尤其大量数据输入的时候！
		pre[1] = 0;
		for (int i = 1; i <= N; i++) {   //妙!pre[i]与post[i]分别作为单独动归问题
			scanf("%d",&price[i]);
			if (i == 1) 
				min_price[i] = price[i];
			else {
				min_price[i] = min(price[i], min_price[i - 1]);
				pre[i] = max(pre[i - 1], price[i] - min_price[i]);
			}
		}
		clock_t startTime = clock();
		max_price[N] = price[N];
		post[N] = 0;
		for (int i = N - 1; i > 0; i--) {
			max_price[i] = max(price[i], max_price[i + 1]);
			post[i] = max(post[i + 1], max_price[i] - price[i]);
		}
		int tmpMax = 0;
		for (int i = 1; i <= N; i++)   //遍历i=1:N,寻找最小的pre[i]+post[i]
			tmpMax = max(tmpMax, pre[i] + post[i]);
		cout << tmpMax << endl;
		clock_t endTime = clock();
		//cout << "程序段运行时间:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	}
	return 0;
}