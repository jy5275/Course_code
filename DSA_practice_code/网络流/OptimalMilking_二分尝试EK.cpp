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
/* 建图比较麻烦,建好之后嫁接EK即可,巧妙之处在于并非直接寻找maxdist,而是二分地去尝试，
   每次尝试都对应一个不同的G图,铁打的Floyd,流水的EK...
   跟线段树题目"寻找第k小的数"有点像
   ★二分尝试用(right, left]标定尝试区间, mid = (right + left)/2, left = mid + 1★
*/
const int MAX = 6000;
bitset<MAX> visited;
int C, K, M;
int n, G[MAX][MAX], A[MAX][MAX], parent[MAX];  //n个点,m条边
void Init() {
	memset(A, 0, sizeof(A));
	memset(G, 0, sizeof(G));
	n = K + C + 1;
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
void Floyd() {
	for (int k = 1; k <= K + C; k++) 
		for (int i = 1; i <= K + C; i++) 
			for (int j = 1; j <= K + C; j++) 
				A[i][j] = min(A[i][j], A[i][k] + A[k][j]);
}
int main() {
	scanf("%d %d %d", &K, &C, &M);
	Init(); 
	for (int i = 1; i <= K + C; i++)
		for (int j = 1; j <= K + C; j++) {
			scanf("%d", &A[i][j]);
			if (A[i][j] == 0) A[i][j] = 1 << 28;
		}
	Floyd();

	int right = 100000, left = 0, maxdist;
	while (1) {
		memset(G, 0, sizeof(G));
		maxdist = (right + left) / 2;
		if (left == right) break;
		for (int i = 1; i <= K; i++)
			G[i][K + C + 1] = M;
		for (int i = K + 1; i <= K + C; i++)
			G[0][i] = 1;
		int maxLen = 0;
		for (int machine = 1; machine <= K; machine++) {
			for (int cow = K + 1; cow <= K + C; cow++) {
				if (A[cow][machine] <= maxdist) 
					G[cow][machine] = 1;
			}
		}
		int maxFlow = 0, aug;
		while (aug = Augment())    //这次增广后下次不一定能成功增广!
			maxFlow += aug;        //..无法增广意味着已穷尽所有路径
		if (maxFlow < C)
			left = maxdist + 1;
		else if (maxFlow = C) 
			right = maxdist;
		else cerr << "maxFlow > C" << endl;
	}
	cout << maxdist << endl;
	return 0;
}