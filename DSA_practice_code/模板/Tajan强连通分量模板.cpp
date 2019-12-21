/* http://dapractise.openjudge.cn/2018hw6/001/ */
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
#include<bitset>
using namespace std;
const int MAX = 10010;
typedef vector<int> Edge;    //邻接表存图,每个节点编号i~N
vector<Edge> G(MAX);         //G[i][0]~G[i][j]是i号结点出发到达的所有终点
bitset<MAX> visited, instack;
int dfn[MAX], low[MAX], nTime = 1, N, M;
stack<int> s;
void Tarjan(int u) {
	dfn[u] = low[u] = nTime++;
	int size = G[u].size(), out = 0;
	s.push(u);
	instack.set(u);
	visited.set(u);		//【1.进栈,设访问位】
	for (int i = 0; i < size; i++) {	//【逐条深搜,更新low值】
		int v = G[u][i];
		if (!visited[v]) {	
			Tarjan(v);
			low[u] = min(low[u], low[v]);
		}
		else if (instack[v])		//【若v已在栈中,检查low值】
			low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u]) {		//【3.强连通Root,弹栈】
		do {
			out = s.top();
			instack.reset(out);
			s.pop();
			printf("%d ", out);
		} while (out != u);
		printf("\n");
	}
}
int main() {
	cin >> N >> M;
	while (M--) {
		int s, e; scanf("%d%d", &s, &e);
		G[s].push_back(e);
	}
	printf("\n");
	for (int i = 1; i <= N; i++)
		if (!visited[i])     //每个入度为0的点都访问一遍
			Tarjan(i);
	return 0;
}