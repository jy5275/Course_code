/* http://dapractise.openjudge.cn/2018wk2/1/ */
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include<vector>
#include<algorithm>
#include<bitset>
const int MAX = 100010;
using namespace std;
vector<int> vson[MAX];  //i的子节点放在vson[i]里面(最简单粗暴,Dijkstra记得用)
bitset<MAX> visited;    //dfs使用
int t = 0, N, M, start[MAX], finish[MAX], a[MAX * 2], c[MAX * 2];
void dfs(int i) {       //初始化树状数组的母数组a
	//if (visited[i]) return;
	t++;
	//visited.set(i);
	start[i] = t;
	auto it = vson[i].begin();
	for (; it != vson[i].end(); ++it)
		dfs(*it);
	t++;
	finish[i] = t;
}
int lowbit(int x) { return x & (-x); }

/* iterator i follows a binary decrease sequence：
* i：(from val to 0) i = i - lowbit(i)
* 6, 4, 0;
* 14, 12, 8, 0;
* 29, 28, 24, 16, 0;
*/
int QueryTree(int val) {   //树状数组区间求和！
	int sum = 0;
	for (int i = val; i >= 1; i = i - lowbit(i)) 
		sum += c[i];
	return sum;
}

void SetC() {            //树状数组初始化！
	for (int i = 1; i <= N * 2; i++) {
		a[i] = 1;
		int beg = i - lowbit(i);
		c[i] = i - beg;
	}
}

void QuerySum(int k) {   //实际求和：[start[i], finish[i]] / 2
	int ans = (QueryTree(finish[k]) - QueryTree(start[k] - 1)) / 2;
	cout << ans << endl;
}

void ChangeTree(int val) {   //树状数组单点更新！
	int delta = (a[val] == 0) ? 1 : -1;
	a[n] += delta;
	for (int i = val; i <= N * 2; i = i + lowbit(i))
		c[i] = c[i] + delta;
}

void Change(int k) {       //实际单点(双点)更新
	ChangeTree(start[k]);
	ChangeTree(finish[k]);
}

int main() {
	cin >> N;
	char cmd;
	int tmpFa, tmpSon, cmdN;
	for (int i = 1; i <= N - 1; i++) {
		cin >> tmpFa >> tmpSon;
		vson[tmpFa].push_back(tmpSon);
	}SetC();
	dfs(1);
	cin >> M;
	while (M--) {
		cin >> cmd >> cmdN;
		switch (cmd){
		case 'C':Change(cmdN); break;
		case 'Q':QuerySum(cmdN); break;
		}
	}
	return 0;
}