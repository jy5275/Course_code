/* 无向图Dijkstra模板 */
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
#include<memory.h>
#include<bitset>
#include<queue>
using namespace std;
/* ★以后存图尽量往这种数据结构上靠:★
   图边用vector<vector<int> > G保存,G[i][0]~G[i][j]是i结点各出边的末梢结点编号
   权重另开一个weight数组存,无向图的weight是对称的
   ★代码实现遇到问题,纸上画数据结构逐步分析,各种细节都画出来!即可茅塞顿开!★
*/
const int MAX = 110;
class Edge {
public:
	int src, dest;
	double R, C;
	Edge(int a_, int b_, double r_, double c_) : src(a_), dest(b_), R(r_), C(c_) {}
};
bitset<MAX> done, visited;
typedef vector<Edge> Point;
vector<Point> G;    //G是整个图的邻接表
int N, M, S;
double maxCurrency[MAX] = { 0 }, V;

void Init() {
	memset(maxCurrency, 0, sizeof(maxCurrency));
	done.reset(); visited.reset();
	G.clear(); G.resize(MAX);
}

//深搜遍历No所有子结点(实质是遍历No的【所有出边】,所以从重复的也都遍历)
bool Dfs(int No, double Q) {
	if (!visited[No]) maxCurrency[No] = Q;   //以前还没来过No
	else if (Q > maxCurrency[No])  //以前来过No,且这次到时钱更多 ==> 成功了
		return true;
	else return false;          //以前来过No,这次来时钱更少 ===> 返回吧,白走了！
	bool succeed = false;
	visited.set(No);
	int scan = G[No].size();    //G总共有scan条出边
	double newQ = 0; 
	for (int i = 0; i < scan; i++) {
		Edge now = G[No][i];
		int u = G[No][i].dest;
		if (Q < now.C) continue;    //Commission都付不起,别去了
		newQ = (Q - now.C)*now.R;   //沿着G[No][i]走到u,手中还有newQ元
		succeed = succeed || Dfs(u, newQ);
	}
	return succeed;
}

int main() {
	Init();
	scanf("%d %d %d %lf", &N, &M, &S, &V);
	while (M--) {
		double r1, r2, c1, c2;
		int s, d; scanf("%d %d %lf %lf %lf %lf", &s, &d, &r1, &c1, &r2, &c2);
		G[s].push_back(Edge(s, d, r1, c1));
		G[d].push_back(Edge(d, s, r2, c2));
	}
	if (Dfs(S, V))cout << "YES" << endl;
	else cout << "NO" << endl;

	return 0;
}