/* 并查集：
 * N个不同的元素分布在若干个互不相交的集合中,需要多次进行以下3种操作:
 *	1.合并a, b两个元素所在的集合 Merge(a, b)
 *	2.查询一个元素在哪个集合
 *	3.查询两个元素是否属于同一集合 Query(a, b) 
 */
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<memory.h>
#include<set>
#include<string>
#include<vector>
#include<queue>
#include<stack>
using namespace std;
const int MAXN = 2020;
int t, n, m, sus = 0;
int parent[MAXN], gender[MAXN];	//gender[i]记录i与parent[i]性别关系,0同1不同
int GetRoot(int x) {
	if (parent[x] != x) {
		int r = GetRoot(parent[x]);
		gender[x] = (gender[parent[x]] + gender[x]) % 2;
		parent[x] = r;
	}
	return parent[x];
}
void Merge(int x1, int x2) {
	int r1 = GetRoot(x1), r2 = GetRoot(x2);
	parent[r2] = r1;
	gender[r2] = (gender[x1] + gender[x2] + 1) % 2;
}
bool Test(int x1, int x2) {		// Return 1 if homosexual
	if (gender[x1] == gender[x2]) return 1; 
	else return 0;
}
void Init() {
	sus = 0;
	for (int i = 0; i <= n; i++) parent[i] = i;
	memset(gender, 0, sizeof(gender));
}
int main() {
	scanf("%d", &t);
	for (int c = 1; c <= t; c++) {
		scanf("%d %d", &n, &m);
		Init();
		printf("Scenario #%d:\n", c);
		int bug1, bug2;
		while (m--) {
			scanf("%d %d", &bug1, &bug2);
			if (GetRoot(bug1) != GetRoot(bug2))	//不在同一集合！
				Merge(bug1, bug2);
			else if(Test(bug1, bug2))	//两只bug在同一集合 && 性别相同！
				sus = 1;
		}
		if (!sus)
			printf("No suspicious bugs found!\n\n");
		else 
			printf("Suspicious bugs found!\n\n");
	}

	return 0;
}