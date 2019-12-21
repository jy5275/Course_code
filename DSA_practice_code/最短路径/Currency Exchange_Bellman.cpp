#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
#include<memory.h>
#include<bitset>
#include<queue>
using namespace std;
/* word天!要不是做Bellman_ford练习,怎能想到用这种算法!本是求【最短路径】,
 * 被本题抽象为求【某种最优属性】,看有没能无穷优化下去的【开挂环】存在
 * 图的存储用一维vector
 * 深入理解Bellman_ford算法!!!
 0.一维Edge数组存图,dist记录最短路径
 【1】松弛：N-1次,更新dist
 【2】检查(看开挂环专属)：试试再次优化是否有效
 */
const int MAX = 110;
class Edge {
public:
	int s, e;
	double R, C;
	Edge(int a_, int b_, double r_, double c_) : s(a_), e(b_), R(r_), C(c_) {}
};
vector<Edge> G;			//G是整图邻接表.按边存图时边的index不重要,反正要遍历所有边
int N, M, S;
double V, dist[110];   //dist[i]是到达i结点后最多可持有的i现金额
void Init() {
	memset(dist, 0, sizeof(dist));
	G.clear();
}

bool Bellman_ford() {  //★★核心思想:每次松弛时,每条路径都尝试从s到e更新一次★★
	for (int i = 1; i <= N; i++) dist[i] = 0;
	dist[S] = V;
	int size = G.size();
	for (int k = 1; k < N; k++) {     //【1】松弛:dist存放走k步骤可得【最优属性】
		for (int i = 0; i < size; i++) {
			int s = G[i].s, e = G[i].e;
			dist[e] = max(dist[e], (dist[s] - G[i].C)*G[i].R);  //★尝试更新dist[e]★
		}
	}
	for (int i = 0; i < size; i++) {	//【2】检查：遍历每条边,检查属性
		int s = G[i].s, e = G[i].e;		
		if ((dist[s] - G[i].C)*G[i].R > dist[e])	//还有优化空间,则肯定有【开挂环】 
			return true; 
	}
	return false;
}

int main() {
	Init();
	scanf("%d %d %d %lf", &N, &M, &S, &V);
	while (M--) {
		double r1, r2, c1, c2;
		int s, d; scanf("%d %d %lf %lf %lf %lf", &s, &d, &r1, &c1, &r2, &c2);
		G.push_back(Edge(s, d, r1, c1));
		G.push_back(Edge(d, s, r2, c2));
	}
	if (Bellman_ford())cout << "YES" << endl;
	else cout << "NO" << endl;

	return 0;
}