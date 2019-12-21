//棋盘问题,有点类似数独
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
const int MAX = 10000;
int n, d, T, x, y;
class CNode {
public:
	double left, right;
}s[MAX];
bool operator<(const CNode &n1, const CNode &n2) {
	return n1.left < n2.left;
}
int Solve(){
	int ans;
	double now;
	sort(s, s + n);
	ans = 1; now = s[0].right;    //按照左端起始位置排序
	for (int i = 1; i < n; i++) { //很奇妙的算法,姑且算贪心吧
		if (s[i].left <= now)     //该线段左端小于公共段的右端,
			now = min(now, s[i].right);  //可以共享已有雷达！
		else {                    //否则要不得不新开一个雷达  
			ans++;
			now = s[i].right;
		}
	}
	return ans;
}
int main() {
	while (1) {
		cin >> n >> d;
		if (n == 0)break;
		for (int i = 0; i < n; i++) {
			scanf("%d%d", &x, &y);
			if (y > d) {
				cout << -1 << endl; return 0;
			}
			s[i].left = x - sqrt(d*d - y * y);
			s[i].right = x + sqrt(d*d - y * y);
		}
		clock_t startTime = clock();
		Solve();

		clock_t endTime = clock();
		//cout << "程序段运行时间:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	}
	return 0;
}