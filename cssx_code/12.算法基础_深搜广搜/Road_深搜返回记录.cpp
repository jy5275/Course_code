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
int N, K, R, maxLen, cache[102][10002];
class CCity {
public:
	vector<int> destCity, cost, len;  //destCity中用int代表一个城市
} city[102];
bitset<102> visited;
//靠返回值记录minLen的搜索方案
int findShortest(int src, int left) {   //从src走到N的最短路程=从src下一个走到N的路程+从src
	if (left < 0) return maxLen;
	if (cache[src][left] != -1) return cache[src][left];
	if (visited[src]) return maxLen;
	if (src == N) return 0;
	int tmpShort = maxLen;
	visited.set(src);
	for (int i = 0; i < city[src].destCity.size(); i++) { //类似采草药、数字组合、糖果拯救世界
		int tmp = findShortest(city[src].destCity[i], left - city[src].cost[i])
			+ city[src].len[i];
		tmpShort = min(tmpShort, tmp);
	}
	cache[src][left] = tmpShort;
	visited.reset(src);            //要退回！城堡问题不用退回,有趣
	return tmpShort;
}
int main() {
	cin >> K >> N >> R;
	memset(cache, -1, sizeof(cache));
	maxLen = 1 << 30;    //所有的路走完len也不可能超过maxLen
	for (int i = 1; i <= R; i++) {
		int src, dest, costT, lenT;
		cin >> src >> dest >> lenT >> costT;
		city[src].destCity.push_back(dest);
		city[src].cost.push_back(costT);
		city[src].len.push_back(lenT);
	}
	clock_t startTime = clock();

	int ans = findShortest(1, K);
	if (ans == maxLen) cout << -1 << endl;
	else  cout << ans << endl;

	clock_t endTime = clock();
	cout << "程序段运行时间:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	return 0;
}