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
   【0】存图数据结构:二维vector存边,weigh数组存权
   【0】堆中元素CNode记录index与pathLen
   【1】压入起点Node
   【2】取出最小,设访问位:最小未done的pathLen弹出,压入未done的Node
   【3】边界判断:到达终点break做后续
   【4】压入邻点
   ★代码实现遇到问题,纸上画数据结构逐步分析,各种细节都画出来!即可茅塞顿开!★
*/
const int MAX = 10010;
struct CNode {
	int index, pathLen;
	CNode(int i_, int w_) :index(i_), pathLen(w_) {}
};
bool operator<(const CNode &d1, const CNode &d2) {
	return d1.pathLen > d2.pathLen;  //priority_queue是"最大值堆",要把符号反过来
}
bitset<MAX> done;
typedef vector<int> Edges;
vector<Edges> G;   //G是整个图的邻接表(二维vector)
int N, M, weight[MAX][MAX];
void Init() {
	memset(weight, 0, sizeof(weight));
	done.reset();
	G.clear(); 
	G.resize(MAX);
}
void Dijkstra(int dest) {  //寻找从点1到dest的minPath.去掉break则是1到所有点的minPath
	priority_queue<CNode> H;
	H.push(CNode(1, 0));	//【1】压入起点
	CNode p = H.top();
	while (!H.empty()) {    //循环至堆空,如果没有break要求收敛于空堆状态！
		p = H.top(); H.pop();         //【2】取出最小,设访问位
		if (done[p.index]) continue;  //由于压堆不除重,故会遇到已done点,直接pop就行
		if (p.index == dest) break;   //【3】边界判断
		int u = p.index;   //Just for convenience
		done.set(u);
		for (int i = 0; i < G[u].size(); i++) {    //【4】压入邻点
			int v = G[u][i];          //考察边(u,v)
			if (done[v]) continue;    //已求出minPath的点不用push到堆中
			H.push(CNode(v, p.pathLen + weight[u][v]));
		}
	}
	printf("%d\n", p.pathLen);
}

int main() {
	scanf("%d%d", &N, &M);
	Init();
	while (M--) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		G[u].push_back(v);
		G[v].push_back(u);
		weight[u][v] = weight[v][u] = w;
	}
	int dest = 0;
	Dijkstra(dest);

	return 0;
}