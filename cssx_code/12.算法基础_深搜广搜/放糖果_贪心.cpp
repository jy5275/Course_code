//棋盘问题,有点类似数独
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stack>
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
/*深搜用栈实现,一条路走到死,再返回换条路走;
广搜用队列实现,所有路都一步一步走*/
const int MAX = 10000;
class CBox {
public:
	int v, w, density;
} boxes[MAX];
int N, W;
double totV, totW;
bool operator<(const CBox &b1, const CBox &b2) {
	return b1.density < b2.density;
}
int main() {
	cin >> N >> W;
	for (int i = 0; i < N; i++) {
		cin >> boxes[i].v >> boxes[i].w;
		boxes[i].density = 1.0 * boxes[i].v / boxes[i].w;
	}
	totV = totW = 0;
	clock_t startTime = clock();
	sort(boxes, boxes + N);
	for (int i = N - 1; i >= 0; i--) {
		if (totW + boxes[i].w <= W) {  //把这箱糖果全放进去
			totW += boxes[i].w;
			totW += boxes[i].v;
		}
		else {  //不够放一箱糖果了,放满再说
			totV += boxes[i].density * (W - totW);
			totW = W;
			break;
		}
	}
	cout << totV << endl;
	clock_t endTime = clock();
	//cout << "程序段运行时间:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	
	return 0;
}