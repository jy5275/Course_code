#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<queue>
#include<vector>
#include<bitset>
#include<string>
#include<memory.h>
#include<algorithm>
using namespace std;
/* Prim和Dijkstra差不多,两点不同:
   1.Prim的堆中元素为Edge,所以要维护parent变量以便用(u,parent)更新weighSum.
     也是因此,Dijkstra进堆就更新,而Prim访问到才更新!
   2.Prim堆元素pathLen只是这条路的Len,而非从起点累积的Len
*/
typedef vector<int> Edges;
bitset<128> indone;
vector<Edges> G(128);
int n, m, weighSum = 0, weigh[128][128];
class CNode {
public:
	int index, pathLen;
	CNode(int i_, int path_) :
		index(i_), pathLen(path_) {}
};
bool operator<(const CNode n1, const CNode n2) {
	return n1.pathLen > n2.pathLen;
}
priority_queue<CNode> H;
int main() {
	cin >> n;
	while (--n) {
		char s_; int num;
		scanf("\n%c %d ", &s_, &num);
		while (num--) {
			char e_; int w_;
			scanf(" %c %d", &e_, &w_);
			G[s_].push_back(e_); 
			G[e_].push_back(s_);
			weigh[s_][e_] = weigh[e_][s_] = w_;
		}
	}

	H.push(CNode('A', 0));	//【1】压入起点
	CNode p = H.top();
	while (!H.empty()) {
		p = H.top(); H.pop();	//【2】取出最小
		int u = p.index;
		if (indone[u]) continue;//【2.5】跳过已访问过的点
		indone.set(u);			//【标志u已加入MST】
		weighSum += p.pathLen;  //Dijkstra进堆就更新,Prim访问才更新
		for (int i = 0; i < G[u].size(); i++) {		//【4】压入邻点
			int v = G[u][i];
			if (indone[v]) continue;
			H.push(CNode(v, weigh[u][v]));
		}
	}
	printf("%d\n", weighSum);
	return 0;
}
