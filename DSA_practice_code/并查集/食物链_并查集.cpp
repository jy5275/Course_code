/* 并查集：
N个不同的元素分布在若干个互不相交的集合中,需要多次进行以下3种操作:
1.合并a, b两个元素所在的集合 Merge(a, b)
2.查询一个元素在哪个集合
3.查询两个元素是否属于同一集合 Query(a, b) */
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<memory.h>
#include<algorithm>
using namespace std;
/*找集合:已知相互关系的动物们各自抱团
与物理世界不同之处:1)集合不形象
                   2)现实动物群体中个体平等,不存在root,需要在自己找一个
                   3)relation不实时更至最新,直接读取不能得到确切值,读之前要GetRoot
*/
const int MAX = 50010;
int N, K, parent[MAX], relation[MAX]; //relation表与父节点关系,0同级,1吃父,2被父吃
int AddRln(int r1, int r2) {  //两段关系加和
	if (r1 == 0 && r2 == 0)return 0;
	else if (r1 == 0 || r2 == 0)return max(r1, r2);
	else if (r1 == r2)return 3 - r1;
	else return 0;
}
int ReverseRln(int a) {   //计算a的"逆关系"
	if (a == 0)return 0;
	else return 3 - a;
}
int GetRoot(int a) {      //对a获取Root同时简化树结构,同时更新relation表
	if (a != parent[a]) { 
		int t = GetRoot(parent[a]);
		relation[a] = AddRln(relation[a], relation[parent[a]]);//计算与新parent关系
		parent[a] = t;
	}
	return parent[a];
}
void Merge(int a, int b, int f) {   //把b归入a类动物,f用于更新relation
	int p1 = GetRoot(a), p2 = GetRoot(b);
	if (p1 == p2) return;
	parent[p2] = p1;
	//接下来更新p2与父节点p1的关系
	if (f == 1)
		relation[p2] = AddRln(AddRln(relation[a], 0), ReverseRln(relation[b]));
	else if (f == 2)
		relation[p2] = AddRln(AddRln(relation[a], 2), ReverseRln(relation[b]));
}
int main() {
	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		parent[i] = i;
		relation[i] = 0;
	}
	int cntFalse = 0;
	while (K--) {
		int cmd, animal1, animal2;
		scanf("%d%d%d", &cmd, &animal1, &animal2);
		if (animal1 > N || animal2 > N) {  //越界！错误！
			cntFalse++;
			continue;
		}
		if (cmd == 2 && animal1 == animal2) {  //吃自己,错误！①
			cntFalse++;
			continue;
		}
		if (GetRoot(animal1) != GetRoot(animal2))  //不在同一集合,肯定真话!
			Merge(animal1, animal2, cmd);
		else if (cmd == 1) {    //两只动物在同一集合,看是否同类
			if (relation[animal1] != relation[animal2]) cntFalse++;
		}
		else {   //1吃2
			if (AddRln(relation[animal2], ReverseRln(relation[animal1])) != 2)
				cntFalse++;
		}
	}
	cout << cntFalse << endl;
	return 0;
}
/* Bugs:
①判断条件错,animal12相等不一定是error,要cmd==2才是
②
*/