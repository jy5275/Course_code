#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
#include<memory.h>
#include<bitset>
#include<queue>
using namespace std;
const int INF = 1 << 29;
int N, M;
class Edge {
public:
	int s, e, w;
	Edge(int s_, int e_, int w_) :s(s_), e(e_), w(w_) { }
	Edge() {}
};
vector<Edge> G;
int dist[1000];
void Init() {
	G.clear();
	for (int i = 1; i <= N; i++)
		dist[i] = INF;
}
bool Bellman_ford(int v) {	//从v出发到各点最短路径
	dist[v] = 0;
	int size = G.size();
	for (int k = 1; k < N; k++) {			//N-1次【松弛】
		for (int i = 0; i < size; i++) {	//每次松弛都用所有边更新dist,O(M)
			int s = G[i].s, e = G[i].e;
			dist[e] = min(dist[e], dist[s] + G[i].w);
		}
	}
	for (int i = 0; i < size; i++) {	//【检查】检查开挂环是否存在,O(M)
		int s = G[i].s, e = G[i].e;
		if (dist[s] + G[i].w < dist[e])
			return true;
	}
	return false;
}
int main() {
	int s, e, t;
	scanf("%d%d", &N, &M);
	Init();
	for (int i = 0; i < M; i++) {
		scanf("%d%d%d", &s, &e, &t);
		G.push_back(Edge(s, e, t));
	}
	if (Bellman_ford(1))
		printf("Minus-weighed circle exits!\n");
	else printf("Normal.\n");
	

	return 0;
}