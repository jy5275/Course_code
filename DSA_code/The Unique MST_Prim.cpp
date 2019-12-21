/* http://dsa.openjudge.cn/final2018test/2/ */
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<memory.h>
#include<string.h>
#include<bitset>
#include<math.h>
#include<queue>
#include<vector>
using namespace std;
/* 算法都设计不出来，会实现顶个鸟用，还是调试半天才调出来的
 * 需要一点理论分析：从一棵生成树到另一棵生成树的变换：
 *  对每条弦e = (u,v)：将它加入MST中,必然得含一个环的MST'，试图在e的基本回路上
 *  找到一条树枝e',使得weight(e)<=weight(e'),即e'可替代e建成MST，这就成功了
 */
typedef vector<int> Edge;
vector<Edge> G;
int weight[101][101];
bool valid[101][101];
bitset<101> done;
class Node {
public:
	int v, len, u;
	Node(int u_, int v_, int l_) :u(u_), v(v_), len(l_) {}
};
bool operator<(Node n1, Node n2) {
	return n1.len > n2.len;
}
priority_queue<Node> H;
void Init() {
	memset(valid, 0, sizeof(valid));
	memset(weight, 0, sizeof(weight));
	while (!H.empty())H.pop();
	done.reset();
	G.clear();
	G.resize(101);
}
bool Inspect(int start, int end, int weigh_limit) {	
	//找到一条start到end的通路,检查上边有无超额【大问题拆分成小问题】
	queue<int> q;
	bitset<101> visited(0);
	int parent[101];
	q.push(start);
	while (1) {		//在MST中找start-->end的通路，记录在parent中
		int u = q.front(); q.pop();
		visited.set(u);
		if (u == end)break;
		for (int i = 0; i < G[u].size(); i++) {
			int v = G[u][i];
			if (valid[u][v] && !visited[v]) {	//【bug2】一条边两端点来回走 
				q.push(v);
				parent[v] = u;
			}
		}
	}
	int it = end;
	while (it != start) {	//往回走，逐边检查
		if (weight[it][parent[it]] >= weigh_limit)
			return true;
		it = parent[it];	//【bug2】没有更新it，原地打转
	}
	return false;
}
int main() {
	int t; cin >> t;
	while (t--) {
		int n, m, u_, v_, w_, sum = 0, notunique = 0; 
		scanf("%d %d", &n, &m);
		Init();
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d", &u_, &v_, &w_);
			G[u_].push_back(v_); G[v_].push_back(u_);
			weight[u_][v_] = weight[v_][u_] = w_;
		}
		H.push(Node(0, 1, 0));
		while (!H.empty()) {
			Node p = H.top(); H.pop();
			int u = p.v;
			if (done[u]) continue;
			done.set(u);
			valid[p.u][u] = 1;	// Edge p is added into MST
			valid[u][p.u] = 1;
			sum += p.len;
			for (int i = 0; i < G[u].size(); i++) {
				int v = G[u][i];
				if (done[v])continue;
				H.push(Node(u, v, weight[u][v]));
			}
		}
		for (int u = 1; u <= n; u++) {
			for (int i = 0; i < G[u].size(); i++) {	//遍历所有弦
				int v = G[u][i];
				if (valid[u][v])continue; // Ignore valid edge
				if (Inspect(u, v, weight[u][v])) {
					printf("Not Unique!\n");
					notunique = 1;
					break;
				}
			}
			if (notunique)break;
		}
		if (!notunique)printf("%d\n", sum);
	}
	return 0;
}