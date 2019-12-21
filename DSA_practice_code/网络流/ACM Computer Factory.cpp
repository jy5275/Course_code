/* http://dapractise.openjudge.cn/2018hw8/001/ */
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
/* 网络流的Dinic算法太复杂了,EK记住就不错了...抓住EK核心：多次广搜直到aug==0
   本题除了建立图嫁接KE,还要记录最大流流向！用Cop[][]记录实际流.这里隐藏bug来
   了！原图已被增广得面目全非,需要判断一下当前经过的边是 原有边or添加的反向边.

   这种造数据特别困难的题目,WA时以逻辑分析为主,适当将样例改为特殊情况
*/
const int MAX = 120;
bitset<MAX> visited;
int n, m, P, N, Original[MAX][MAX], G[MAX][MAX], parent[MAX], cntCop = 0;  //n个点,m条边
int Cop[MAX][MAX], Begin[11] = { 0 }, End[11];
void AugInit() {
	memset(parent, 0, sizeof(parent));
	visited.reset();
}
class Cooperation {
public:
	int s, e, w;
	Cooperation(int s_, int e_, int w_) :s(s_), e(e_), w(w_) {}
};
vector<Cooperation> v;
int Augment() {       //一次增广,返回收集到的流量
	queue<int> q;
	AugInit();
	bool bFindPath = false;
	parent[1] = 0;
	visited.set(1);
	q.push(1);   //【KE增广三步走之一：广搜(到终点立即停止)】
	while (!q.empty()) {
		int v = q.front(); q.pop();
		for (int i = 1; i <= n; i++) {
			if (G[v][i] <= 0 || visited[i]) continue; //通不到 || 访问过了,不走!
			parent[i] = v;
			visited.set(i);
			if (i == n) {       //一旦找到通路,就返回并清空q,增广后再找下一条路
				bFindPath = true;
				break;
			}
			q.push(i);
		}
	}
	if (!bFindPath) return 0;   //广搜完也没找到通往m的路径,停止搜索！
	int minFlow = 1 << 27, v = n;  
	
	//【KE三步走战略之二：后退找minFlow】
	while (parent[v]) {         //从终点向前逐结点向前找瓶颈流量
		minFlow = min(minFlow, G[parent[v]][v]);
		v = parent[v];
	} v = n;

	//【KE三步走战略之三：后退增广(减容量、添反向)】
	while (parent[v]) {         //从终点向前逐结点减去minFlow并设置反向边
		if (parent[v] != 1 && G[parent[v]][v] > (1 << 19) && v != n)
			//这条边是machine间合作,记录下来
			Cop[parent[v]][v] += minFlow;
		if (!Original[parent[v]][v])    //【BUG】这条边是添加出来的,映射到Cop数组上
			Cop[v][parent[v]] -= minFlow;    //..是负数,要减去！
		G[parent[v]][v] -= minFlow;
		G[v][parent[v]] += minFlow;
		v = parent[v];
	}
	return minFlow;
}
class CMachine {
public:
	int initial[10], processed[10], No, performance;
}machine[51];
bool ArrayCmp(int A1[], int A2[]) {
	for (int i = 0; i < P; i++) {    //A[0]~A[P-1]出现01冲突则返回false
		if ((A1[i] == 0 && A2[i] == 1) || (A1[i] == 1 && A2[i] == 0))
			return false;
	}
	return true;
}
int InitPoint(int x) { return 2 * x; }
int ProcessPoint(int x) { return 2 * x + 1; }
int GetMachine(int x) {
	if (x % 2) return (x - 1) / 2;
	else return x / 2;
}
void Init() {
	memset(G, 0, sizeof(G));
	memset(Cop, 0, sizeof(Cop));
	for (int i = 0; i < P; i++) {
		Begin[i] = 0;
		End[i] = 1;
	}
	n = 2 * N + 2;
	cntCop = 0;
}
int main() {
	scanf("%d %d", &P, &N);
	Init();

	for (int i = 1; i <= N; i++) {    //输入到machine
		scanf("%d", &machine[i].performance);
		for (int j = 0; j < P; j++)
			scanf("%d", &machine[i].initial[j]);
		for (int j = 0; j < P; j++)
			scanf("%d", &machine[i].processed[j]);
	}
	for (int i = 1; i <= N; i++) {    //建立图！
		G[InitPoint(i)][ProcessPoint(i)] = machine[i].performance;  //i自己首尾相连
		if (ArrayCmp(machine[i].initial, Begin))   //尝试连接i与原点
			G[1][InitPoint(i)] = 1 << 27;
		for (int j = 1; j <= N; j++) {      //试试j能否接i的盘
			if (i == j) continue;
			if (ArrayCmp(machine[i].processed, machine[j].initial))
				G[ProcessPoint(i)][InitPoint(j)] = 1 << 27;
		}
		if (ArrayCmp(machine[i].processed, End))   //尝试连接i与汇点
			G[ProcessPoint(i)][n] = 1 << 27;
	}
	memcpy(Original, G, sizeof(G));

	//=============Edmonds-Karp算法================

	int maxFlow = 0, aug;
	while (aug = Augment())    //这次增广后下次不一定能成功增广!
		maxFlow += aug;        //..无法增广意味着已穷尽所有路径

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i == j) continue;
			if (Cop[i][j] != 0) {
				cntCop++;
				int deliver = GetMachine(i), receive = GetMachine(j);
				v.push_back(Cooperation(deliver, receive, Cop[i][j]));
			}
		}
	}

	printf("%d %d", maxFlow, cntCop);
	int s = v.size() - 1;
	while (s >= 0) {
		printf("\n%d %d %d", v[s].s, v[s].e, v[s].w);
		v.pop_back(); s--;
	}
	printf("\n");
	return 0;
}