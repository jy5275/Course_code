//递归搜索之连连看小游戏
#include<iostream>
#include<fstream>
#include<cstring>
#include<cmath>
#include<memory>
#include<algorithm>
#include<iomanip>
#include<time.h>
using namespace std;
int maxStep, w, h, dirc = 0;
char map[103][103];
int cache[103][103][5];       //从dirc方向走到(x,y),到T还需要的转弯数
//ifstream fin("in.txt", ios::in);
int minCmp(int a, int b) {
	if (a > b) return b;
	else return a;
}
bool ableToGo(int y, int x) {  //看看点(x,y)能不能踩
	if (map[y][x] == 'X' || map[y][x] == 'S')return false;
	if (y < 0 || x < 0)return false;
	return true;
}
int minSegToTerminal(int y, int x, int dirc) {  //此函数调用时已到(x,y),返回其到终点最少拐弯数
	if (map[y][x] == 'T')      //如果到达了终点，顺利完成一条路线！
		return 0;
	if (cache[y][x][dirc] != -1) return cache[y][x][dirc];  //从dirc方向走到(x,y)有存储!
	int R = maxStep;
	map[y][x] = 'S';           //踩出脚印：把a中(x,y)标为'S'
	if (ableToGo(y - 1, x)) {  //如果往北走：没撞墙&&没走回头路
		if (dirc != 1)         //前一步不是往北！拐弯！
			R = minCmp(R, 1 + minSegToTerminal(y - 1, x, 1));
		else
			R = minCmp(R, minSegToTerminal(y - 1, x, 1));
	}
	if (ableToGo(y + 1, x)) {  //南2
		if (dirc != 2)
			R = minCmp(R, 1 + minSegToTerminal(y + 1, x, 2));
		else
			R = minCmp(R, minSegToTerminal(y + 1, x, 2));
	}
	if (ableToGo(y, x - 1)) {  //西3
		if (dirc != 3)
			R = minCmp(R, 1 + minSegToTerminal(y, x - 1, 3));
		else
			R = minCmp(R, minSegToTerminal(y, x - 1, 3));
	}
	if (ableToGo(y, x + 1)) {  //东4
		if (dirc != 4)
			R = minCmp(R, 1 + minSegToTerminal(y, x + 1, 4));
		else
			R = minCmp(R, minSegToTerminal(y, x + 1, 4));
	}
	cache[y][x][dirc] = R;
	map[y][x] = ' ';  //退回脚印
	return R;         //返回R
}
int buildMap() {
	int i, j;
	cin >> w >> h;
	if (w == 0)return 0;
	for (j = 0; j <= w + 1; j++) map[0][j] = ' ';  //修好上边过道
	map[0][j] = 'X';  //堵上右上角
	for (i = 1; i <= h; i++) {
		cin.get();
		map[i][0] = ' ';              //修好左侧过道
		for (j = 1; j <= w; j++) 
			map[i][j] = cin.get();    //输入
		map[i][j] = ' ', map[i][++j] = 'X';       //修好右侧过道
	}
	for (j = 0; j <= w; j++)
		map[i][j] = ' ';
	map[i][j] = 'X';
	for (j = 0; j <= w + 2; j++)
		map[i + 1][j] = 'X';   //修好下边过道
	return 1;
}
int main() {
	clock_t startTime, endTime;
	int numBoard = 1;
	while (buildMap()) {
		int m = 0;
		maxStep = w * h;
		cout << "Board #" << numBoard << ":" << endl;
		while (++m) {     //每对始末位置输入即一次深搜,cache要清零！
			int x1, x2, y1, y2, k = 0;
			cin >> x1 >> y1 >> x2 >> y2;
			startTime = clock();
			memset(cache, -1, sizeof(cache));
			if (x1 == 0 && x2 == 0 && y1 == 0 && y2 == 0) break;
			//cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
			map[y1][x1] = 'S', map[y2][x2] = 'T';  //这一对始末位置ST标记在map上
			k = minSegToTerminal(y1, x1, 0);       //主要功夫都在这儿
			map[y1][x1] = 'X', map[y2][x2] = 'X';  //将ST重置为X
			cout << "Pair " << m << ": ";
			if (k == maxStep) cout << "impossible." << endl;
			else cout << k << " segments." << endl;
			endTime = clock();
			cout << "Total Time: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
		}
		numBoard++;
	}
	return 0;
}