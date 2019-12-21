/* http://dapractise.openjudge.cn/2018hw6/001/ */
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
#include<bitset>
#include<map>
using namespace std;
/* 算是模板题吧…好久没有一次性AC了
* 1.先Tarjan求出强连通分量,每个分量【缩】成一个结点,得到新图
* 2.遍历旧图所有边,旧图点==城市,新图点==国家,边==航线,sum[i]==国家i的城市数
*   在新图上寻找出度为0的结点==寻找没有出境航班的国家
* 3.新图恰有1国无出境航班==>输出sum[i]; 多于1国==>0; 不可能一国都没有
* 教训:有了算法思想就自己动手实现,先不看郭炜PPT或CSDN,不得已才看
* 看别人家代码时注意【抓大放小】,了解总体架构,着眼自己遇到的问题
*/
const int MAX = 10010;
typedef vector<int> Edge;    //邻接表存图,每个节点编号i~N
vector<Edge> G(MAX);         //G[i][0]~G[i][j]是i号结点出发到达的所有终点
map<int, int> mSec;           //城市到国家的映射
bitset<MAX> visited, instack;
int dfn[MAX], low[MAX], nTime = 0;
int N, M, TNum = 0, sum[MAX] = { 0 };
stack<int> s;
void Tarjan(int u) {
	dfn[u] = low[u] = nTime++;
	int size = G[u].size(), out = 0;
	s.push(u);
	instack.set(u);
	visited.set(u);
	for (int i = 0; i < size; i++) {    //逐条扫描u的所有出边
		int v = G[u][i];
		if (!visited[v]) {     //如果v没被访问过,就访问一下v
			Tarjan(v);
			low[u] = min(low[u], low[v]);
		}
		else if (instack[v])      //v没被访问过且在当前路径上==>更新low[u]
			low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u]) {    //回到u时,如果从u到不了更早点,pop吧
		do {
			sum[TNum]++;       //sum记录TNum这国家有多少城市
			out = s.top();
			instack.reset(out);
			mSec[out] = TNum;  //mSec是城市-->国家的映射
			s.pop();
		} while (out != u);
		TNum++;
	}
}
int main() {
	cin >> N >> M;
	while (M--) {
		int s, e; scanf("%d%d", &s, &e);
		G[s].push_back(e);
	}

	for (int i = 1; i <= N; i++)
		if (!visited[i])     //每个入度为0的点都访问一遍
			Tarjan(i);

	int outdeg[MAX] = { 0 };
	for (int i = 1; i <= N; i++) {
		int scan = G[i].size();
		for (int j = 0; j < scan; j++) {
			int dest = G[i][j], from = mSec[i];
			if (from != mSec[dest])   //i->G[i][j]是国际航线
				outdeg[mSec[i]]++;    //outdeg[i]记录i从国出境的航线数
		}
	}
	int sumCorner = 0, No;
	for (int i = 0; i < TNum; i++) {
		if (outdeg[i] == 0) {
			sumCorner++;
			No = i;
		}
	}
	if (sumCorner == 1) cout << sum[No] << endl;
	else cout << 0 << endl;
	return 0;
}