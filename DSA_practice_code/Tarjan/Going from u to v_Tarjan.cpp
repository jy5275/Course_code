/* http://dapractise.openjudge.cn/2018hw6/002/ */
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
#include<memory.h> 
#include<string.h>
#include<bitset>
#include<map>
using namespace std;
/* 类似Popular Cow模板题,不同点在于图中出度=0与入度=0的结点都只能有一个,
   不用维护sum,以及考虑多个case的情形(写个Init函数清空全局变量即可)
*/
const int MAX = 1010;
typedef vector<int> Edge;    //邻接表存图,每个节点编号i~N
vector<Edge> G(MAX);         //G[i][0]~G[i][j]是i号结点出发到达的所有终点
map<int, int> mSec;          //城市到国家的映射
bitset<MAX> visited, path;
int dfn[MAX], low[MAX], nTime;
int N, M, TNum = 0;
stack<int> s;
void Init() {
	G.clear(); G.resize(MAX);
	memset(dfn, 0, sizeof(dfn));
	memset(low, 0, sizeof(low));
	mSec.clear();  while (!s.empty())s.pop();
	visited.reset(); path.reset();
	TNum = 0; nTime = 1;
}
void Tarjan(int u) {
	dfn[u] = low[u] = nTime++;
	int scan = G[u].size(), out = 0;
	s.push(u);	path.set(u); visited.set(u);
	for (int i = 0; i < scan; i++) {    //逐条扫描u的所有出边
		int v = G[u][i];
		if (!visited[v]) {     //如果v没被访问过,就访问一下v
			Tarjan(v);
			low[u] = min(low[u], low[v]);
		}
		else if (path[v])      //v没被访问过且在当前路径上==>更新low[u]
			low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u]) {    //回到u时,如果从u到不了更早点,pop吧
		do {
			out = s.top();
			mSec[out] = TNum;  //mSec是城市-->国家的映射
							   //printf("%d ", out);
			s.pop();
		} while (out != u);
		TNum++;
		//printf("\n");
	}
	path.reset(u);        //
}
int main() {
	int t; cin >> t;
	while (t--) {
		Init();
		cin >> N >> M;
		while (M--) {
			int s, e; scanf("%d%d", &s, &e);
			G[s].push_back(e);
		}

		for (int i = 1; i <= N; i++)   //Tarjan生成缩点
			if (!visited[i])     //每个入度为0的点都访问一遍
				Tarjan(i);

		int outdeg[MAX] = { 0 }, indeg[MAX] = { 0 };
		for (int i = 1; i <= N; i++) {  //遍历所有航线,记录各国出/入境航班总数
			int scan = G[i].size();
			for (int j = 0; j < scan; j++) {
				int dest = mSec[G[i][j]], from = mSec[i];
				if (from != mSec[dest]) {   //i->G[i][j]是国际航线
					outdeg[from]++;      //outdeg[i]记录i从国出境的航线数
					indeg[dest]++;
				}
			}
		}
		int sumCorner = 0, sumSource = 0;
		for (int i = 0; i < TNum; i++) {
			if (outdeg[i] == 0)
				sumCorner++;
			if (indeg[i] == 0)
				sumSource++;
		}
		if (sumCorner == 1 && sumSource == 1) cout << "Yes" << endl;
		else cout << "No" << endl;
		/*
		for (int i = 0; i <= 12; i++)
		cout << "mSec[" << i << "] = " << mSec[i] << endl;
		*/
	}
	return 0;
}