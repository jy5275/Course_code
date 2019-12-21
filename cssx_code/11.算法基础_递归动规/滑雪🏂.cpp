/* http://noi.openjudge.cn/ch0206/90/ */
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<set>
#include<string>
#include<cstring>
#include<cmath>
#include<memory.h>
#include<algorithm>
using namespace std;
int terr[102][102], r, c, L[102][102];
class CPoint {
public:
	int r, c, h;
	CPoint(int r_, int c_, int h_) :r(r_), c(c_), h(h_) {}
};
bool operator<(const CPoint &p1, const CPoint &p2) {
	return p1.h < p2.h;
}
multiset<CPoint> s;   //凡是比大小会【判等】情形一律multiset

int calcL(int i, int j) {   //求以(i,j)为起点的最长滑行路径
							//不需要踩出脚印/退回脚步,因为terr已决定了什么地方不能走
	if (i<1 || i>r || j<1 || j>c) return 0;		//越界！
	if (L[i][j] != -1) return L[i][j];
	int R = 1;
	if (i >= 1 && terr[i - 1][j] < terr[i][j])  //可以滑向北边的方块
		R = max(R, calcL(i - 1, j) + 1);
	if (i <= r && terr[i + 1][j] < terr[i][j])  //可以滑向南边的方块
		R = max(R, calcL(i + 1, j) + 1);
	if (j >= 1 && terr[i][j - 1] < terr[i][j])  //可以滑向西边的方块
		R = max(R, calcL(i, j - 1) + 1);
	if (j <= c && terr[i][j + 1] < terr[i][j])  //可以滑向东边的方块
		R = max(R, calcL(i, j + 1) + 1);
	L[i][j] = R;
	return R;   //如果terr[i][j]是一块低地,就会返回R=1
}
void Init() {
	for (int i = 0; i < 102; i++) {
		for (int j = 0; j < 102; j++) {
			terr[i][j] = 10001;
			L[i][j] = 1;
		}
	}
}
/*滑雪问题告诉我们,
1.【边界条件】有可能不在几何边界或物理边界,甚至不能编译时确定,但递归运行时会
【自动确定】——走到发现【周围都是高墙的地方】就是边界条件
------------------------------------------------------------------
2.动规中不好确定【遍历顺序】怎么破?原则是计算"我"时"人人"都已算毕(我周围的点
L值都已算出,才能算哪条路径最长)。所以将所有点按高度排序,先算低的点,再算高的点
*/
int main() {
	//这道题与数字三角形相似,【局部最优性】体现得淋漓尽致。但边界条件不好找
	cin >> r >> c;
	int ans = 0;
	Init();
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			cin >> terr[i][j];
			s.insert(CPoint(i, j, terr[i][j]));  //动规才有用的操作
		}
	}
	//clock_t startTime = clock();

	//---------------递归方案------------------------------
	memset(L, -1, sizeof(L));
	for (int i = 1; i <= r; i++)	//以每个(i,j)点为起点算一遍,找出最长者
		for (int j = 1; j <= c; j++)
			ans = max(ans, calcL(i, j));

	//---------------动规方案------------------------------
	auto p = s.begin();
	//★★s向量列并不实际存在,但需用来动规！★★
	for (; p != s.end(); p++) {		//尽管无法确定实际路线,但从低到高总没毛病
		int ele = terr[p->r][p->c];
		int Nele = terr[p->r - 1][p->c], Sele = terr[p->r + 1][p->c],
			Wele = terr[p->r][p->c - 1], Eele = terr[p->r][p->c + 1];
		if (p->r > 1 && Nele < ele)		//北
			L[p->r][p->c] = max(L[p->r][p->c], L[p->r - 1][p->c] + 1);
		if (p->r < r && Sele < ele)		//南
			L[p->r][p->c] = max(L[p->r][p->c], L[p->r + 1][p->c] + 1);
		if (p->c > 1 && Wele < ele)		//西
			L[p->r][p->c] = max(L[p->r][p->c], L[p->r][p->c - 1] + 1);
		if (p->c < c && Eele < ele)		//东
			L[p->r][p->c] = max(L[p->r][p->c], L[p->r][p->c + 1] + 1);
		//第一次循环没有满足任何条件,因为 Xele<ele 都不成立
	}
	for (int i = 1; i <= r; i++)    //以每个(i,j)点为起点算一遍,找出最长者
		for (int j = 1; j <= c; j++)
			ans = max(ans, L[i][j]);

	cout << ans << endl;
	//------------------------------------------------------------

	//clock_t endTime = clock();
	//cout << "程序段运行时间:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	return 0;
}