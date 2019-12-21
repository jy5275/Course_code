#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<queue>
#include<stack>
#include<vector>
#include<bitset>
#include<string>
#include<map>
#include<memory.h>
#include<algorithm>
using namespace std;
/* Dijkstra还要熟练一些!背熟:
   【0】存图数据结构:二维vector存边,weigh数组存权
   【0】堆中元素CNode记录index与pathLen
   【1】压入起点Node
   【2】取出最小,设访问位:最小未done的pathLen弹出,压入未done的Node
   【3】边界判断:到达终点break做后续
   【4】压入邻点
   这道题的边边角角有点多,首先要用映射m与反映射mr,使得int与string能自由切换
   其次要维护parent(最短是怎么走的),造成更新路径信息必须用if而不能用min公式
*/
map<string, int> m;
map<int, string> mr;
typedef vector<int> Edges;
vector<Edges> G(31);
bitset<31> done;
int P, Q, R, weigh[31][31], from, dest, Dist[31], parent[31];
class CNode {
public:
	int index, pathLen;
	CNode(int n_, int d_) :index(n_), pathLen(d_) {}
};
bool operator<(const CNode n1, const CNode n2) {
	return n1.pathLen > n2.pathLen;
}
void Init() {
	memset(parent, 0, sizeof(parent));
	for (int i = 0; i < 31; i++)Dist[i] = 1 << 29;
	done.reset();
}
void Dijkstra() {	//1234步骤与bfs有点像？
	priority_queue<CNode> H;
	H.push(CNode(from, 0));		//【1】压入起点
	CNode p = H.top();
	while (!H.empty()) {
		p = H.top(); 
		H.pop();				
		if (done[p.index]) 
			continue;
		done.set(p.index);		//【2】取出最小,设访问位
		if (p.index == dest) break;    //【3】边界判断
		int u = p.index;
		for (int i = 0; i < G[u].size(); i++) {		//【4】压入邻点
			int v = G[u][i];
			if (done[v]) continue;
			if (Dist[v] > p.pathLen + weigh[u][v]) {  //需要更新路径！
				Dist[v] = p.pathLen + weigh[u][v];
				H.push(CNode(v, Dist[v]));
				parent[v] = u;
			}
		}
	}
	stack<int> sInter, sDis;
	int p1 = dest;
	while (1) {
		sInter.push(p1);
		if (p1 != from) {
			sDis.push(weigh[parent[p1]][p1]);
			p1 = parent[p1];
		}
		else break;
	}
	p1 = sInter.top(); sInter.pop();
	cout << mr[p1];
	while (!sInter.empty()) {
		printf("->(%d)->", weigh[p1][sInter.top()]);
		p1 = sInter.top(); sInter.pop();
		cout << mr[p1];
	}
	cout << endl;
}
int main() {
	cin >> P;
	string str1, str2;
	for (int i = 0; i < P; i++) {
		cin >> str1;
		m[str1] = i;
		mr[i] = str1;
	}
	cin >> Q;
	while (Q--) {
		cin >> str1 >> str2;
		int s = m[str1], e = m[str2], w_; scanf("%d", &w_);
		G[s].push_back(e); G[e].push_back(s);
		weigh[s][e] = w_; weigh[e][s] = w_;
	}
	cin >> R;
	while (R--) {
		Init();
		cin >> str1 >> str2;
		from = m[str1]; dest = m[str2];
		Dijkstra();
	}

	return 0;
}
