#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stack>
#include<bitset>
#include<queue>
#include<set>
#include<vector>
#include<memory.h>
#include<algorithm>
#include<cmath>
using namespace std;
const int MAX = 1000;
int ub, N, M, Lsize = 0, ULsize = 0, Csize;
bitset<MAX> inC;
bool inL[MAX][MAX], inUL[MAX][MAX];
set<int> C,tmpC;
class Edge {
public:
	int s, e, w;
	Edge(int s_, int e_) :s(s_), e(e_), w(1) {}
};
set<Edge> L, UL;
typedef vector<int> edge;
vector<edge> G(MAX);
bool ChooseXchg(int &u, int &v) {
	return 0;
}
void Update() {

}
void Init() {
	tmpC = C;
	ub = C.size();
}
void Remove(int u) {		//从C删除u,把新增未覆盖Edge加进L
	C.erase(u);
	for (int i = 0; i < G[u].size(); i++) {	//遍历u发出的每条边
		int v = G[u][i];
		if (!inC[v]) {			// if (该边另一端点v不在L)
			inL[u][v] = true;	// ..那么该边移入L集合
			inL[v][u] = true;
			Lsize++;
		}
	}
}
void Insert(int v) {	//向C加入v,从L中删除新覆盖Edge
	C.insert(v);
	for (int i = 0; i < G[v].size(); i++) {	//遍历v发出的每条边
		int t = G[v][i];
		if (inL[v][t]) {			// if (该边另一端点t在L中)
			inL[v][t] = false;	// ..覆盖该边！移出
			inL[t][v] = false;
			Lsize--;
		}
	}
}
void Construct() {		//贪心地构建C
	while (Lsize > 0) {	//只要L非空,寻找dscore最大的结点
		int maxdscore = 0, maxID, dscore;
		for (int u = 1; u <= N; u++) {	//求每个非C中点的dscore
			dscore = 0;
			if (inC[u]) continue;
			for (int i = 0; i < G[u].size(); i++) {
				int v = G[u][i];
				if (inL[u][v]) dscore++;
			}
			if (dscore > maxdscore) {
				maxdscore = dscore;
				maxID = u;
			}
		}
		Insert(maxID);	//把dscore最大的点插入C
	}
	//C已是一组点覆盖集
}
void Removedelta(int delta) {	//若干个点移出C
	while (Csize > ub - delta) {	//继续移点,移dscore最大(abs最小)的点
		int mindscore = 0, minID, dscore;
		for (int u = 1; u <= N; u++) {	//求每个C中点的dscore
			dscore = 0;
			if (!inC[u]) continue;
			for (int i = 0; i < G[u].size(); i++) {
				int v = G[u][i];
				if (!inL[u][v]) dscore++;
			}
			if (dscore < mindscore) {
				mindscore = dscore;
				minID = u;
			}
		}
		Remove(minID);	//把dscore最大的点插入C
	}
}
void FindXchg(int &u, int &v) {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (i == j)continue;

		}
	}
}
void RandomStep() {		//更新边权之后随机挑两个点交换...
	int u, v;
	FindXchg(u, v);
}
void EWLS(int maxSteps, int delta) {
	int u, v, step = 0;
	Construct();
	Removedelta(delta);
	while (step < maxSteps) {
		if (ChooseXchg(u, v)) {
			Remove(u);
			Insert(v);
		}
		else {
			Update();
			RandomStep();
		}
		if (C.size() + L.size() < ub) {	//更新ub
			ub = C.size() + L.size();
			if (L.empty())		//如果L已是点覆盖,更新备选答案
				tmpC = C;
			else	//否则贪心扩充C为点覆盖
				Construct();
		}
		step++;
	}
}
int main() {
	while (scanf("%d %d", &N, &M) != EOF) {
		Init();
		while (M--) {
			int u, v;
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
			inL[u][v] = true; inL[v][u] = true;
			Lsize++;
		}
		EWLS(0,0);
	}

	return 0;
}