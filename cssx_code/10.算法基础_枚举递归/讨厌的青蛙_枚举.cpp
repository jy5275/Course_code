//枚举之讨厌的青蛙
#include<iostream>
#include<vector>
#include<string>
#include<set>
#include<cmath>
#include<list>
#include<memory>
#include<map>
#include<stdexcept>
#include<algorithm>
#include<queue>
#include<iomanip>
#include<time.h>
#include<fstream>
#include<unordered_map>
#include<regex>
using namespace std;
int r, c, n, dx, dy, dxMax, dyMax, a[5002][5002] = { 0 };
class CPlant {
public:
	int x = 0, y = 0;
	CPlant() {}
	CPlant(int x_, int y_) :x(x_), y(y_) {}
	bool operator==(CPlant p) {
		if (x == p.x && y == p.y) return true;
		else return false;
	}
} plants[5001], maxStart;
CPlant &formerPlant(CPlant &nowP) {
	CPlant tmp(nowP.x - dx, nowP.y - dy);
	return tmp;
}
CPlant &laterPlant(CPlant &nowP) {
	CPlant tmp(nowP.x + dx, nowP.y + dy);
	return tmp;
}
bool inField(CPlant &p) {       //看看这个点是不是在田地里边
	if (p.x <= 0 || p.x > r)return false;
	if (p.y <= 0 || p.y > c)return false;
	return true;
}
bool inPlantsList(CPlant &p) {  //看看这个点是不是在被毁的List里边
	if (a[p.x][p.y] == 0)return false; //这个效率可能更高一些？
	//if (!binary_search(plants, plants + n, p))return false;
	else return true;
}
bool operator<(CPlant p1, CPlant p2) {
	if (p1.x == p2.x)return p1.y < p2.y;
	else return p1.x < p2.x;
}
int searchPath(CPlant startPoint) {
	int step = 0;
	CPlant currentPoint(startPoint);
	while (inField(currentPoint)) {    //只要走一步还在田地里,就继续循环!
		if (!inPlantsList(currentPoint)) { return 0; } //该踩未踩,错!
		step++;  //记录步数++
		currentPoint = laterPlant(currentPoint); //看下一个该踩处
	}
	return step;
}
int main() {
	int maxStep = 0;
	cin >> r >> c >> n;
	for (int i = 0; i < n; i++) {
		int x_, y_; cin >> x_ >> y_;
		plants[i].x = x_;
		plants[i].y = y_;
		a[x_][y_] = 1;
	}
	clock_t startTime, endTime;
	startTime = clock();
	sort(plants, plants + n);
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (i == j) continue;   //这是同一个点！
			dx = plants[j].x - plants[i].x;
			dy = plants[j].y - plants[i].y;
			if (inField(formerPlant(plants[i]))) continue; //前一步在田里,回去!
			if (plants[i].x + (maxStep - 1)*dx > r) break;
			/*x方向会越界!表面上是第二个点不合适,但如果直接i+1
			下一个点更靠下边,步长不会变短,仍然越x界,
			所以应该把第一个点往下调整。break换第一个点*/
			int py = plants[i].y + (maxStep - 1)*dy;
			if (py > c || py < 1) continue;
			int step = searchPath(plants[i]);  //从plants[i]开始算第一步,开始走!
			if (step > maxStep) {
				maxStep = step;
				maxStart = plants[i];
				dxMax = dx; dyMax = dy;
			}
		}
	}
	if (maxStep > 2) {
		cout << maxStep << endl << "dxMax=" << dxMax << endl << "dyMax=" << dyMax
			<< endl << "起点位于(" << maxStart.x << "," << maxStart.y << ")" << endl;
	}
	else cout << "0" << endl;
	endTime = clock();
	cout << "程序段运行时间：" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	return 0;
}