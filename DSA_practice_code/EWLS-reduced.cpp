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
int ub, N, M, Lsize, Csize, CCsize, justrm = 0, justin = 0;
bool inC[MAX], inL[MAX][MAX], inCC[MAX];
set<int> C, CC;
typedef vector<int> edge;
vector<edge> G(MAX);
int Graph[MAX][MAX];
void Init() {
	G.clear(); G.resize(MAX);
	C.clear(); CC.clear();
	Lsize = 0, Csize = 0, justrm = 0, justin = 0, CCsize = 0;
	memset(inC, 0, sizeof(inC));
	memset(inL, 0, sizeof(inL));
	memset(inCC, 0, sizeof(inCC));
	memset(Graph, 0, sizeof(Graph));
}
void Remove(int u) {		//从C删除u,把新增未覆盖Edge加进L
	C.erase(u);	Csize--;
	inC[u] = false;
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
	C.insert(v); Csize++;
	inC[v] = true;
	for (int i = 0; i < G[v].size(); i++) {	//遍历v发出的每条边
		int t = G[v][i];
		if (inL[v][t]) {			// if (该边在L中)
			inL[v][t] = false;	// ..覆盖该边！移出
			inL[t][v] = false;
			Lsize--;
		}
	}
}
int Getdscore_inC(int u) {	//求C中结点的|dscore|
	int _dscore = 0;
	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (!inL[u][v]) _dscore++;
	}	return _dscore;
}
int Getdscore_outC(int u) {	//求C外结点的dscore
	int dscore = 0;
	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (!inL[u][v]) dscore++;
	}	return dscore;
}
void Construct() {		//贪心地构建C
	while (Lsize > 0) {	//只要L非空,就继续循环,寻找dscore最大的结点
		int maxdscore = 0, maxID, dscore;
		for (int u = 1; u <= N; u++) {	//求每个非C中点的dscore
			if (inC[u]) continue;
			dscore = Getdscore_outC(u);
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
	ub = Csize;
	CC = C;
	memcpy(inCC, inC, sizeof(inCC));
}
void RemoveMin() {		//移除C中|dscore|最小的点
	int _dscore = 0, minabs = 1 << 28, minID = 0;
	for (int u = 1; u <= N; u++) {	//求每个C中点的_dscore
		if (!inC[u] || u == justin) continue;
		_dscore = Getdscore_inC(u);
		if (_dscore < minabs) {
			minabs = _dscore;
			minID = u;
		}
	}
	Remove(minID);
	justrm = minID;
}
void InsertMax() {		//向C中插入dscore最大的点
	int dscore = 0, maxdscore = 0, maxID = 0;
	for (int u = 1; u <= N; u++) {	//求每个非C中点的dscore
		if (inC[u] || u == justrm) continue;
		dscore = Getdscore_outC(u);
		if (dscore > maxdscore) {
			maxdscore = dscore;
			maxID = u;
		}
	}
	Insert(maxID);
	justin = maxID;
}
void Minimize() {		//去掉C中|dscore|=0的点,即无关紧要的那些点
	while (1) {
		bool garbage = false;
		for (int u = 1; u <= N; u++) {
			if (!inC[u])continue;
			if (Getdscore_inC(u) == 0) {
				Remove(u); garbage = true;
				break;	//找到一个垃圾点==>移除后break再找一轮
			}
		}
		if (!garbage)break;		//找不到垃圾点==>已得局部最优,返回
	}
}
template<class It>
void Print(It f, It l) {
	for (; f != l; ++f)
		printf("%d ", *f);
	printf("\n");
}
void EWLS(int maxSteps, int delta) {
	int u, v, step = 0;
	Construct();	//已构建起一组点覆盖,存在C中
					//Print(CC.begin(), CC.end());
	RemoveMin();	//rm _dscore min
	while (step < maxSteps) {
		if (Lsize > 0) {	//只要还有L,就要继续insert点到C中
			InsertMax();	//insert dscore max
			RemoveMin();	//再删去不重要点
		}
		else {		//已构建点覆盖集！
			Minimize();	//将点覆盖集缩小至最优
			if (Csize < ub) {
				ub = Csize;
				CC = C;
				memcpy(inCC, inC, sizeof(inCC));
			}
			justin = justrm = 0;
		}
		step++;
	}
}
void PrintAns() {
	printf("%d\n", N - ub);
	for (int i = 1; i <= N; i++)
		if (!inCC[i])
			printf("%d ", i);
	printf("\n");
}
int main() {
	//FILE *in = fopen("in15.txt", "r");
	while (fscanf(stdin, "%d %d", &N, &M) != EOF) {
		Init();
		while (M--) {
			int u, v;
			fscanf(stdin, "%d%d", &u, &v);
			Graph[u][v] = 1;
			Graph[v][u] = 1;
		}
		for (int i = 1; i <= N; i++) {		//求Graph的补图G
			for (int j = i + 1; j <= N; j++) {
				if (Graph[i][j] == 0) {
					G[i].push_back(j);
					G[j].push_back(i);
					inL[i][j] = true; inL[j][i] = true;
					Lsize++;
				}
			}
		}

		EWLS(3000, 0);
		PrintAns();
	}
	//fclose(in);

	return 0;
}