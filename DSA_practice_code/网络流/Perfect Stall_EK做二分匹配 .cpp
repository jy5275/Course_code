#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
#include<bitset>
#include<memory.h>
#include<stack>
using namespace std;
/* 注意题目"several cases",而样例只有一个case,简直不能更坑
   统一用 while (scanf(...) != EOF)处理multiple cases 的情况
*/
const int MAX = 450;
bitset<MAX> visited;
int N, M, n, G[MAX][MAX], parent[MAX];  //n个点,m条边
void Init() {
	memset(G, 0, sizeof(G));
	n = N + M + 1;
}
void AugInit() {
	memset(parent, 0, sizeof(parent));
	visited.reset();
}
int Augment() {       //一次增广,返回收集到的流量
	deque<int> q;
	AugInit();
	bool bFindPath = false;
	parent[0] = -1;
	visited.set(0);
	q.push_back(0);
	while (!q.empty()) {   //【KE增广三步走之一：广搜(到终点立即停止)】
		int v = q.front(); q.pop_front();
		for (int i = 0; i <= n; i++) {
			if (G[v][i] <= 0 || visited[i]) continue; //通不到 || 访问过了,不走!
			parent[i] = v;
			visited.set(i);
			if (i == n) {         //一旦找到通路,就返回并清空q,增广后再找下一条路
				bFindPath = true;
				break;
			}
			q.push_back(i);
		}
	}
	if (!bFindPath) return 0;   //广搜完也没找到通往m的路径,停止搜索！
	int minFlow = 1 << 29, v = n;

	/*【KE三步走战略之二：后退找minFlow】 */
	while (parent[v] != -1) {     //从终点向前逐结点向前找瓶颈流量
		minFlow = min(minFlow, G[parent[v]][v]);
		v = parent[v];
	} v = n;

	/*【KE三步走战略之三：后退增广(减容量、添反向)】*/
	while (parent[v] != -1) {     //从终点向前逐结点减去minFlow并设置反向边
		G[parent[v]][v] -= minFlow;
		G[v][parent[v]] += minFlow;
		v = parent[v];
	}
	return minFlow;
}
int main() {
	while (scanf("%d %d", &N, &M) != EOF) {   //★★★
		Init();
		for (int i = M + 1; i <= M + N; i++) {
			int num, go; scanf("%d", &num);
			while (num--) {
				scanf("%d", &go);
				G[i][go] = 1 << 28;
			}
		}
		for (int i = M + 1; i <= N + M; i++)
			G[0][i] = 1;
		for (int i = 1; i <= M; i++)
			G[i][M + N + 1] = 1;
		int maxFlow = 0, aug;

		while (aug = Augment())    //这次增广后下次不一定能成功增广!
			maxFlow += aug;        //..无法增广意味着已穷尽所有路径
		cout << maxFlow << endl;
	}
	return 0;
}