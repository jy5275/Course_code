#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<memory.h>
#include<set>
#include<vector>
using namespace std;
/* 能用set/map完成的检索任务,为何要用HashTable呢？
* 不要反复发明轮子！
* Revised closed HashTable = Accepted
* vector + sort + binary_search = Accepted
* set + s.find = Accepted
* set + binary_search = TLE？？？
*/
const int MAX = 1010;
int x[MAX], y[MAX];
class Point {
public:
	int x, y;
	Point() {}
	Point(int x_, int y_) :x(x_), y(y_) {}
};
void Init() {
	memset(x, 0, sizeof(x));
	memset(y, 0, sizeof(y));
}
vector<Point> s;
bool operator<(Point p1, Point p2) {
	if (p1.x != p2.x)return p1.x < p2.x;
	return p1.y < p2.y;
}
int main() {
	while (1) {
		s.clear();
		int n, delx, dely, cnt = 0;
		scanf("%d", &n);
		//Init();
		if (!n) break;
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &x[i], &y[i]);
			s.push_back(Point(x[i], y[i]));
		}
		sort(s.begin(), s.end());
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				delx = x[j] - x[i];
				dely = y[j] - y[i];
				Point p1(x[i] + dely, y[i] - delx);
				Point p2(x[j] + dely, y[j] - delx);
				if (binary_search(s.begin(), s.end(), p1) &&
					binary_search(s.begin(), s.end(), p2))
					cnt++;
				Point p3(x[i] - dely, y[i] + delx);
				Point p4(x[j] - dely, y[j] + delx);
				if (binary_search(s.begin(), s.end(), p3) &&
					binary_search(s.begin(), s.end(), p4))
					cnt++;
			}
		}
		printf("%d\n", cnt / 4);
	}
	return 0;
}