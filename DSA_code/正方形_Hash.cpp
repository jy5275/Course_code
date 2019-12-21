#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<memory.h>
using namespace std;
/* 检索问题在日常算法题中大量存在！Hashtable大有用武之地！
 * 老是TLE怎么办：
	1.优化getkey函数，映射到HashTable中尽可能离散！
	2.优化探查函数p，避免Hash冲突！
 */
const int MAX = 1220;
int x[MAX], y[MAX];
class Point {
public:
	int x, y;
	bool taken = 0;
}Hashtable[2 * MAX];
int getkey(int x, int y) { return (x*x + y * y) % 1999; }//【TLE】整数映射到正数：平方！
int p(int d0, int i) { return abs(d0 + i * i); }   // Hash函数,大多数情况下无所谓
bool Insert(int x, int y) {
	int home = getkey(x, y);
	int pos = home, i = 0;
	while (Hashtable[pos].taken)     //一直找,直到找到空位坐下
		pos = (pos + 1) % 1999;    //沿着探查路径找下一个
	Hashtable[pos].taken = true;
	Hashtable[pos].x = x, Hashtable[pos].y = y;
	return true;
}
bool Search(int x, int y) {
	int home = getkey(x, y);
	int pos = home, i = 0;
	while (Hashtable[pos].taken) {     //一直找,直到找到 or 扑空
		if (Hashtable[pos].x == x && Hashtable[pos].y == y)
			return true;
		pos = (pos + 1) % 1999;  //沿着探查路径找下一个
	}
	return false;
}
void Init() {
	//memset(x, 0, sizeof(x));
	//memset(y, 0, sizeof(y));
	memset(Hashtable, 0, sizeof(Hashtable));
}
int main() {
	while (1) {
		int n, delx, dely, cnt = 0;
		scanf("%d", &n);
		Init();
		if (!n) break;
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &x[i], &y[i]);
			Insert(x[i], y[i]);
		}
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				delx = x[j] - x[i];
				dely = y[j] - y[i];
				if (Search(x[i] + dely, y[i] - delx) && Search(x[j] + dely, y[j] - delx))
					cnt++;
				if (Search(x[i] - dely, y[i] + delx) && Search(x[j] - dely, y[j] + delx))
					cnt++;
			}
		}
		printf("%d\n", cnt / 4);
	}
	return 0;
}