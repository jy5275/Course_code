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
const int MAX = 1000;
bitset<MAX> visited;
int n, m, G[MAX][MAX], parent[MAX];  //n个点,m条边
void Init() {
	memset(G, 0, sizeof(G));
}
void AugInit() {
	memset(parent, 0, sizeof(parent));
	visited.reset();
}

int Augment() {       //一次增广,返回收集到的流量
	deque<int> q;
	AugInit();
	bool bFindPath = false;
	parent[1] = 0;
	visited.set(1);
	q.push_back(1);
	while (!q.empty()) {   //【KE增广三步走之一：广搜(到终点立即停止)】
		int v = q.front(); q.pop_front();
		for (int i = 1; i <= n; i++) {
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
	while (parent[v]) {     //从终点向前逐结点向前找瓶颈流量
		minFlow = min(minFlow, G[parent[v]][v]);
		v = parent[v];
	} v = n;

	/*【KE三步走战略之三：后退增广(减容量、添反向)】*/
	while (parent[v]) {     //从终点向前逐结点减去minFlow并设置反向边
		G[parent[v]][v] -= minFlow;
		G[v][parent[v]] += minFlow;
		v = parent[v];
	}
	return minFlow;
}
int main() {
	Init();
	scanf("%d %d", &m, &n);
	for(int i=0;i<m;i++){
		int s, e, w; scanf("%d %d %d", &s, &e, &w);
		G[s][e] += w;
	}
	int maxFlow = 0, aug;

	while (aug = Augment())    //这次增广后下次不一定能成功增广!
		maxFlow += aug;        //..无法增广意味着已穷尽所有路径
	printf("%d\n", maxFlow);


	return 0;
}