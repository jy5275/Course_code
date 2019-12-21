/* http://dapractise.openjudge.cn/2018hw7/002/ */
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<stack>
#include<memory.h>
#include<algorithm>
#include<bitset>
#include<queue>
#include<map>
using namespace std;
/* 无向连通图求割点 + 求连通数,求割点:dfn[u]<=low[v](非root) && nRootSon >
   求连通数:图N次遍历涂色法,优先选广搜遍历,简单易写
*/
const int MAX = 1010;
typedef vector<int> Edge;    //邻接表存图,每个节点编号i~N
vector<Edge> G(MAX);         //G[i][0]~G[i][j]是i号结点出发到达的所有终点
int dfn[MAX], low[MAX], nTime = 1, Father[MAX], N, M, t = 0;
map<int, int> subnet;
queue<int> cuts;
void Init() {
	G.clear(); G.resize(MAX);
	subnet.clear(); while (!cuts.empty()) cuts.pop();
	memset(dfn, 0, sizeof(dfn));
	memset(low, 0, sizeof(low));
	memset(Father, 0, sizeof(Father));
	nTime = 1, N = 0;
}

void Tarjan(int u, int father = 0) {
	Father[u] = father;
	dfn[u] = low[u] = nTime++;
	int scan = G[u].size(), out = 0;
	for (int i = 0; i < scan; i++) {    //逐条扫描u的所有出边
		int v = G[u][i];
		N = max(N, v);           //竟然要这样记录结点总数,荒谬!
		if (!dfn[v]) {           //如果v没被访问过,就访问一下v
			Tarjan(v, u);
			low[u] = min(low[u], low[v]);
		}
		else if (father != v)    //v已访问过,且u-->v不是原路返回,更新low[u]
			low[u] = min(low[u], dfn[v]);
	}
}

void Tranvsex(int ex) {
	bitset<MAX> visited;
	int sum = 0;
	for (int i = 1; i <= N; i++) {
		if (i == ex || visited[i]) continue;
		queue<int> q;  q.push(i);
		while (!q.empty()) {
			int u = q.front(); q.pop();
			visited.set(u);
			for (int i = 0; i < G[u].size(); i++) {
				int v = G[u][i];
				if (!visited[v] && v != ex) q.push(v);
			}
		} //循环结束即该种颜色涂完
		sum++;
	}// 外循环结束即所有颜色涂完
	subnet[ex] = sum;
}

void Count() {
	cout << "Network #" << ++t << endl;
	int nRootSons = 0;   //nRootSons保存Root结点(1)的son(子树)数目
	Tarjan(1, 0);        //0表示没有father,这也是从1开始编号的原因  
	for (int v = 2; v <= N; v++) {
		int u = Father[v];
		if (u == 1) nRootSons++;
		else if (dfn[u] <= low[v])   //★★从v出发回不到u ==> u是割点★★
			cuts.push(u); //u入队,准备在Tranvsex中取出分析剩图
	}
	if (nRootSons > 1) cuts.push(1);
	if (cuts.empty()) {   //没有割点,回去吧
		cout << "  No SPF nodes" << endl << endl;
		return;
	}
	while (!cuts.empty()) {   //Tranvsex逐个割点求剩图残肢数
		Tranvsex(cuts.front());
		cuts.pop();
	}
	auto it = subnet.begin();
	for (; it != subnet.end(); ++it)
		printf("  SPF node %d leaves %d subnets\n", it->first, it->second);
	cout << endl;
}

int main() {
	while (1) {
		Init();
		int u, v; scanf("%d", &u);
		if (u == 0) break;   //输入文件截止判定
		scanf("%d", &v);
		G[u].push_back(v);
		G[v].push_back(u);
		while (1) {
			scanf("%d", &u); if (u == 0) break;   //该case输入截止判定
			scanf("%d", &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}

		Count();
	}

	return 0;
}