/* 示例题目:求无向连通图的割点与桥 */
//这个cpp代码bug百出,求无向连通图桥请参考Caocao's Bridge
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<stack>
#include<memory.h>
#include<algorithm>
#include<bitset>
#include<map>
using namespace std;
const int MAX = 10010;
typedef vector<int> Edge;    //邻接表存图,每个节点编号i~N
vector<Edge> G(MAX);         //G[i][0]~G[i][j]是i号结点出发到达的所有终点
bitset<MAX> bIsCut;
int dfn[MAX], low[MAX], nTime = 1, Father[MAX], N, M;
void Init() {
	G.clear(); G.resize(MAX);
	memset(dfn, 0, sizeof(dfn));
	memset(low, 0, sizeof(low));
	memset(Father, 0, sizeof(Father));
	nTime = 0;
	bIsCut.reset();
}
void Tarjan(int u, int father = 0) {
	Father[u] = father;
	dfn[u] = low[u] = nTime++;
	int scan = G[u].size(), out = 0;
	for (int i = 0; i < scan; i++) {    //逐条扫描u的所有出边
		int v = G[u][i];
		if (!dfn[v]) {           //如果v没被访问过,就访问一下v
			Tarjan(v, u);
			low[u] = min(low[u], low[v]);
		}
		else if (father != v)    //v已访问过,且u-->v不是原路返回,更新low[u]
		 	low[u] = min(low[u], dfn[v]); 
	}
}
void Count() {
	int nRootSons = 0;   //nRootSons保存Root结点(1)的son(子树)数目
	Tarjan(1, 0);        //0表示没有father,这也是从1开始编号的原因  
	for (int v = 2; v <= N; v++) {
		int u = Father[v];
		if (u == 1) nRootSons++;
		else if (dfn[u] <= low[v])   //从v出发回不到u ==> u是割点
			bIsCut.set(u);
	}
	if (nRootSons > 1) bIsCut.set(1);
	for (int i = 1; i <= N; i++)     //逐个输出割点
		if (bIsCut[i])  printf("%d\n", i);
	for (int v = 1; v <= N; v++) {
		int u = Father[v];           //u不是Root且(u,v)不可回 ==> 是桥
		if (u > 0 && dfn[u] < low[v]) printf("%d, %d\n", u, v);
	}
}
int main() {
	cin >> N >> M;
	Init();
	while (M--) {
		int u, v; scanf("%d%d", &u, &v);
		G[u].push_back(v); 
		G[v].push_back(u);
	}
	Count();
	
	return 0;
}