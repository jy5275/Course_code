/* http://dapractise.openjudge.cn/2018hw6/003/ */
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
#include<memory.h>
#include<bitset>
#include<map>
using namespace std;
/* 坑太多了,无语...但这题也带来很多启发:
   1.多case情形下,所有global必须在Init()中更新!别添全局变量后忘了往里Init加代码
   2.无向图判连通很简单——任取一点遍历(如本题Tarjan),遍历过的结点总数为sumVis,
     最后判断(sumVis==N)? 有向图缩点复杂些,参考popular cow
   3.无向图dfs,必须考虑不能直接走向父结点,要求增加father参数记录当前结点的父亲
*/
const int MAX = 1010;
typedef vector<int> Edge;    //邻接表存图,每个节点编号i~N
vector<Edge> G(MAX);         //G[i][0]~G[i][j]是i号结点出发到达的所有终点
int dfn[MAX], low[MAX], nTime = 1, Father[MAX], N, M, weight[MAX][MAX];
bool duBridge[MAX][MAX] = { 0 };
int minSoldier = 1 << 30, uMin = 1 << 30, vMin = 1 << 30, sumVis = 0;
void Init() {
	G.clear(); G.resize(MAX);
	memset(duBridge, 0, sizeof(duBridge));
	memset(dfn, 0, sizeof(dfn));
	memset(weight, -1, sizeof(weight));
	memset(low, 0, sizeof(low));
	memset(Father, 0, sizeof(Father));
	nTime = 1; sumVis = 0; minSoldier = 1 << 30, uMin = 1 << 30, vMin = 1 << 30;
}
void Tarjan(int u, int father = 0) {
	sumVis++;
	Father[u] = father;           //不能走向父结点,无向图专属!
	dfn[u] = low[u] = nTime++;
	int scan = G[u].size(), out = 0;
	for (int i = 0; i < scan; i++) {    //逐条扫描u的所有出边
		int v = G[u][i];
		if (!dfn[v]) {            //如果v没被访问过,就访问一下v
			Tarjan(v, u);
			low[u] = min(low[u], low[v]);
		}
		else if (father != v)     //v已访问过,且u-->v不是原路返回,更新low[u]
			low[u] = min(low[u], dfn[v]);
	}
}
void findBridge(int u, int v) {    // (u,v)是bridge!
	if (duBridge[u][v]) return;    //不去炸duBridge
	if (weight[u][v] < minSoldier) {
		minSoldier = weight[u][v];
		uMin = u; vMin = v;
	}
}
void Count() {
	Tarjan(1, 0);        //0表示没有father,这也是从1开始编号的原因  
	for (int v = 1; v <= N; v++) {
		int u = Father[v];             //u不是Root且(u,v)不可回 ==> 是桥
		if (u > 0 && dfn[u] < low[v])  //★★判桥依据:low[v]>dfn[u]★★
			findBridge(u, v);
	}
	if (sumVis != N) minSoldier = 0;     //【坑2】岛屿可能本不连通,不用炸,输出0
}
int main() {
	while (1) {
		scanf("%d %d", &N, &M);
		if (N == 0 && M == 0) break;
		Init();          //【BUG1】Init的位置找准了!早了晚了都不行!
		while (M--) {
			int u, v, w; scanf("%d %d %d", &u, &v, &w);
			G[u].push_back(v);
			G[v].push_back(u);
			if (weight[u][v] >= 0)    //【坑1】多桥连的岛不去炸,findBridge时避开
				duBridge[u][v] = duBridge[v][u] = true;
			else if (w == 0)          //【坑3】没人把守的桥也要派一人去送炸弹
				weight[u][v] = 1, weight[v][u] = 1;
			else 
				weight[u][v] = w, weight[v][u] = w;
		}
		Count();
		if (minSoldier == 1 << 30) printf("-1\n");
		else  printf("%d\n", minSoldier);
	}

	return 0;
}