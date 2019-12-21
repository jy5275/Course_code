#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stack>
#include<bitset>
#include<queue>
#include<vector>
#include<memory.h>
#include<time.h>
#include<algorithm>
#include<thread>
using namespace std;
const int MAX = 760;
int N, M, G[MAX][MAX], tmax = 0;
//typedef vector<int> Edge;
//vector<Edge> G(MAX);
bitset<MAX> inClique;
vector<int> curClique, tans;
bool pushOK(int x, vector<int> &v) {
	int size = v.size();
	for (int i = 0; i < size; i++) 
		if (!G[v[i]][x])return false;
	return true;
}
void Dfs(int l, int temp) {
	if (l == N+1) {		//到达最深层！回溯！
		if (temp > tmax) {		//尝试更新tmax与tans
			tmax = temp;
			tans = curClique;
		}
		return;
	}
	if (temp + (N - l) + 1 < tmax)return;
	if (pushOK(l, curClique)) {		//l可以入团！
		curClique.push_back(l);		//入团试试
		Dfs(l + 1, temp + 1);		//继续搜
		curClique.pop_back();		//l结点出团,试试不含l的团有多大
	}
	Dfs(l + 1, temp);
}
void Init() {
	tans.clear();
	curClique.clear();
	tmax = 0;
	memset(G, 0, sizeof(G));
}
int main() {
	while (scanf("%d %d", &N, &M) != EOF) {
		Init();
		while (M--) {
			int u, v;
			scanf("%d%d", &u, &v);
			G[u][v]++;
			G[v][u]++;
		}
		if(N<=750)
			Dfs(1, 0);
		printf("%d\n", tmax);
		for (int i = 0; i < tans.size(); i++)
			printf("%d ", tans[i]);
		printf("\n");
		
	}
	return 0;
}