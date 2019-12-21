//Wrong Answer
#include<iostream>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;
int maxStep, x_start, y_start, x_terminal, y_terminal;
int cnt[103][103];
char map[103][103];
int minCmp(int a, int b) {
	if (a > b) return b;
	else return a;
}
int minStepToTermial(int x, int y) {    //此函数调用时已走k步，到达(x,y),返回(x,y)到终点的最少步数
	if (cnt[x][y] != -1)  return cnt[x][y];            //如果发现这个地方之前来过，直接返回记忆值
	if (x == x_terminal && y == y_terminal) {          //如果到达了终点，顺利完成一条路线！
		cnt[x][y] = 0;	return 0;
	}
	int R = 10010;
	map[x][y] = 'S';  //踩出脚印：把a中(x,y)标为'S'
	if (map[x - 1][y] != '#'&&map[x - 1][y] != 'S')    //如果往北走：没撞墙&&没走回头路
		R = minCmp(R, 1 + minStepToTermial(x - 1, y)); //就往北走一步吧！
	if (map[x + 1][y] != '#'&&map[x + 1][y] != 'S')    //南
		R = minCmp(R, 1 + minStepToTermial(x + 1, y));
	if (map[x][y - 1] != '#'&&map[x][y - 1] != 'S')    //西
		R = minCmp(R, 1 + minStepToTermial(x, y - 1));
	if (map[x][y + 1] != '#'&&map[x][y + 1] != 'S')    //东
		R = minCmp(R, 1 + minStepToTermial(x, y + 1));
	map[x][y] = '.';  //退回脚印
	cnt[x][y] = R;    //从(x,y)到终点要走R步
	return R;         //返回R
}
int main() {
	int i, j, n, m;
	cin >> n >> m;
	for (i = 0; i <= n; i++) {
		for (j = 0; j <= m; j++)
			cnt[i][j] = -1;
	}
	for (i = 0; i <= m + 1; i++) map[0][i] = '#';            //修好上边外墙
	maxStep = n * m;
	for (i = 1; i <= n; i++) {
		map[i][0] = '#';             //修好左侧外墙
		for (j = 1; j <= m; j++) {
			cin >> map[i][j];        //输入
			if (map[i][j] == 'S') x_start = i, y_start = j;  //记录起点位置
			else if (map[i][j] == 'T')	x_terminal = i, y_terminal = j;  //记录终点位置
		}map[i][j] = '#';            //修好右侧外墙
	}
	for (j = 0; j <= m + 1; j++)  map[i][j] = '#';           //修好下边外墙
	cout << minStepToTermial(x_start, y_start);
	return 0;
}