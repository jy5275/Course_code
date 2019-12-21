/* 并查集：
 * N个不同的元素分布在若干个互不相交的集合中,需要多次进行以下3个操作:
 * 1.合并a, b两个元素所在的集合 Merge(a, b)
 * 2.查询一个元素在哪个集合
 * 3.查询两个元素是否属于同一集合 Query(a, b)
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
//找集合:互相感染的人属于同一集合
const int MAX = 30010;
int n, m, parent[MAX];  //parent[i]记录i号学生的父节点
int total[MAX];         //total[i]记录学生i领导的团体总人数
int GetRoot(int a) {
	if (a != parent[a])
		parent[a] = GetRoot(parent[a]);
	return parent[a];
}
void Merge(int a, int b) {  //把b的根连上a的根
	int p1 = GetRoot(a), p2 = GetRoot(b);
	parent[p2] = p1;        //把b的根(p2)连在a的根(p1)上
	total[p1] += total[p2]; //total可以在Merge或GetRoot中维护
}
int main() {
	while (1) {
		scanf("%d%d", &n, &m);
		if (n == 0 && m == 0)break;
		for (int i = 0; i < n; i++) {
			parent[i] = i;
			total[i] = 1;
		}
		for (int i = 0; i < m; i++) {
			int num, f; 
			scanf("%d%d", &num, &f); //num是当前group人数,f是group首人
			for (int j = 1; j < num; j++) {
				int no; scanf("%d", &no);
				Merge(f, no);
			}
		}
		cout << total[GetRoot(0)] << endl;
	}
	return 0;
}
