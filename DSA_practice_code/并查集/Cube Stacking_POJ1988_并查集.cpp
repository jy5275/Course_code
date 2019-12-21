/* 并查集：
N个不同的元素分布在若干个互不相交的集合中,需要多次进行以下3种操作:
1.合并a, b两个元素所在的集合 Merge(a, b)
2.查询一个元素在哪个集合
3.查询两个元素是否属于同一集合 Query(a, b)
*/
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<queue>
#include<vector>
#include<bitset>
#include<string>
#include<cstring>
#include<cmath>
#include<memory>
#include<stdexcept>
#include<time.h>
#include<algorithm>
#include<iomanip>
#include<fstream>
using namespace std;
/*找集合:在同一堆的牌是一个集合
集合的要求:1)树根必须从一而终,不合并就不能变;2)只合并不拆分
多维护一个数组：under,不必使其实时保持最新,Query时再更新也可
*/
const int MAX = 30010;
int N, parent[MAX], under[MAX], sum[MAX];
int GetRoot(int a) {
	if (a != parent[a]) {
		int t = GetRoot(parent[a]);
		under[a] += under[parent[a]]; //★★这一步时parent[a]还没挖到最深
		parent[a] = t;
	}
	return parent[a];
}
void Merge(int a, int b) {  //a所在堆拿起放在b所在堆上
	int p1 = GetRoot(a);
	int p2 = GetRoot(b);
	if (p1 == p2)return;
	parent[p1] = p2;
	under[p1] += sum[p2];  //每次Merge只更新某堆牌"根"的under
	sum[p2] += sum[p1];
}
void Query(int a) {
	GetRoot(a);
	printf("%d\n", under[a]);
}
int main() {
	for (int i = 0; i < MAX; i++) {
		parent[i] = i;
		under[i] = 0;
		sum[i] = 1;
	}
	while (1){
		char cmd; scanf("%s", &cmd);
		switch (cmd) {
		case 'M':int a, b; 
			cin >> a >> b;
			Merge(a, b); 
			break;
		case 'C':int x; cin >> x;
			Query(x);
			break;
		}
	}
	return 0;
}
