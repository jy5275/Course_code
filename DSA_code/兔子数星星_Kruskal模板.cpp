#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<queue>
#include<vector>
#include<bitset>
#include<string>
#include<memory.h>
#include<algorithm>
using namespace std;
/* Kruskal算法核心:每次取权最小Edge,Query两端点,如果false则Merge两端点,并
   ..保留这条Edge,直到只剩1个等价类.用并查集实现
   存图数据结构灵活处理,Kruskal只按Edge一维保存即可
*/
class Edge {
public:
	char u, v;
	int weigh;
	Edge(char u_, char v_, int w_) :u(u_), v(v_), weigh(w_) {}
};
bool operator<(const Edge e1, const Edge e2) {
	return e1.weigh > e2.weigh;
}
priority_queue<Edge> G;
int n, m, parent[128], Isolate = 0, weighSum = 0;
void Init() {
	for (int i = 0; i < 128; i++) parent[i] = i;
}
int GetRoot(int a) {
	if (a != parent[a])
		parent[a] = GetRoot(parent[a]);
	return parent[a];
}
void Merge(int a, int b) {  //把b的根连上a的根
	int p1 = GetRoot(a), p2 = GetRoot(b);
	if (p1 == p2) return;
	parent[p2] = p1;        //把b的根(p2)连在a的根(p1)上
}
int main() {
	Init();
	cin >> n; Isolate = n;
	while (--n) {
		char s_; int num;
		scanf("\n%c %d ", &u_, &num);
		while (num--) {
			char v_; int w_;
			scanf(" %c %d", &v_, &w_);
			G.push(Edge(u_, v_, w_));    //建图,只需保存所有边即可
		}
	}
	while (Isolate > 1) {				//只要等价类数目>1,就继续并查！
		Edge e = G.top(); G.pop();		//【1】取出最小
		if (GetRoot(e.v) != GetRoot(e.u)) {		//【2】Query
			Merge(e.v, e.u);			//【3】合并
			Isolate--;    //维护全局变量Isolate,记录当前还剩多少个等价类
			weighSum += e.weigh;		//【4】记录总长度
		}
	}
	printf("%d\n", weighSum);
	return 0;
}
