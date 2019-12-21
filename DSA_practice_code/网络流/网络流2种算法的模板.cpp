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
int n, m, G[MAX][MAX], Layer[MAX], parent[MAX];  //n个点,m条边
void Init() {
	memset(G, 0, sizeof(G));
}
void AugInit() {
	memset(parent, 0, sizeof(parent));
	visited.reset();
}
bool CountLayer() {
	int layer = 0;
	deque<int> q;
	memset(Layer, -1, sizeof(Layer));
	Layer[1] = 0; q.push_back(1);
	while (!q.empty()) {       //广搜递推Layer[i]
		int v = q.front(); q.pop_front(); //v可达的每个终点的Layer都设为Layer[v]+1
		for (int j = 1; j <= n; j++) {
			if (G[v][j] > 0 && Layer[j] == -1) {
				Layer[j] = Layer[v] + 1;
				if (j == n) return true;  //分层到达汇点n即返回
				else q.push_back(j);
			}
		}
	}
	return false;
}
int Dinic() {
	int maxFlow = 0;
	deque<int> q;
	while (CountLayer()) {      //只要G能分层,就继续增广！
		visited.reset();
		q.push_back(1); visited.set(1);
		while (!q.empty()) {
			int nd = q.back();
			if (nd == n) {     //nd是汇点n,在栈中寻找容量最小的边
				int minC = 1 << 29, minC_vs;

				for (int i = 1; i < q.size(); i++) {
					// 逐点更新minC = min(minC, G[vs][ve]),瓶颈边起点用minC_vs保存
					int vs = q[i - 1], ve = q[i];
					if (G[vs][ve] <= 0) continue;
					if (G[vs][ve] < minC) {
						minC = G[vs][ve];
						minC_vs = vs;
					}
				}

				//增广,改图！所有边容量减去minC并添加反向边
				maxFlow += minC;
				for (int i = 1; i < q.size(); i++) {
					int vs = q[i - 1], ve = q[i];
					G[vs][ve] -= minC;
					G[ve][vs] += minC;
				}

				//退栈到minC_vs,待会继续dfs
				while (!q.empty() && q.back() != minC_vs) {
					visited[q.back()] = 0;
					q.pop_back();
				}
			}

			else {    //nd非汇点==>选出下一步要去的结点(可达 && 下一层 && 未访问过)
				int i = 1;
				for (i = 1; i <= n; i++) {
					if (G[nd][i] > 0 && Layer[i] == Layer[nd] + 1 && !visited[i]) {
						visited.set(i);
						q.push_back(i);
						break;
					}
				}
				if (i > n) q.pop_back();  //找不到符合要求的点,回溯继续dfs
			}
		}
	}
	return maxFlow;
}
int Augment() {       //一次增广,返回收集到的流量
	deque<int> q;
	AugInit();
	bool bFindPath = false;
	parent[1] = 0;
	visited.set(1);
	q.push_back(1);
	while (!q.empty()) {
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
	while (parent[v]) {     //从终点向前逐结点向前找瓶颈流量
		minFlow = min(minFlow, G[parent[v]][v]);
		v = parent[v];
	} v = n;
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
	//=============Edmonds-Karp算法================
	
	int maxFlow = 0, aug;
	while (aug = Augment())    //这次增广后下次不一定能成功增广!
		maxFlow += aug;        //..无法增广意味着已穷尽所有路径
	printf("%d\n", maxFlow);
	//===============Dinic快速算法=================
	printf("%d\n", Dinic());

	return 0;
}