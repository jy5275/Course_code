//http://bailian.openjudge.cn/practice/1724/
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
int N, K, R , cache[102][10002], minLen = 1 << 30;
class CCity {
public:
	vector<int> destCity, cost, len;  //destCity中用int代表一个城市
} city[102];
bitset<102> visited;
//靠返回值记录minLen的搜索方案
void findShortest(int src, int left, int currentLen) {
	//从src走到N的最短路程=从src下一个走到N的路程+从src
	if (left < 0) return ;
	if (visited[src]) return ;
	if (src == N) {
		minLen = min(minLen, currentLen);
		return ;
	}
	if (currentLen >= minLen) return;   //不是全局最优！
	if (currentLen >= cache[src][left]) return;  //不是局部最优！
	visited.set(src);
	for (int i = 0; i < city[src].destCity.size(); i++) { //类似采草药、数字组合、糖果拯救世界
		findShortest(city[src].destCity[i], left - city[src].cost[i],
			currentLen + city[src].len[i]);
	}
	cache[src][left] = currentLen;
	visited.reset(src);            //要退回！城堡问题不用退回,有趣
}
int main() {
	cin >> K >> N >> R;
	memset(cache, -1, sizeof(cache));
	for (int i = 1; i <= R; i++) {
		int src, dest, costT, lenT;
		cin >> src >> dest >> lenT >> costT;
		city[src].destCity.push_back(dest);
		city[src].cost.push_back(costT);
		city[src].len.push_back(lenT);
	}
	clock_t startTime = clock();
	
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= K; j++)
			cache[i][j] = 1 << 30;
	}
	findShortest(1, K, 0);
	if (minLen == 1 << 30) cout << -1 << endl;
	else  cout << minLen << endl;

	clock_t endTime = clock();
	//cout << "程序段运行时间:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	return 0;
}