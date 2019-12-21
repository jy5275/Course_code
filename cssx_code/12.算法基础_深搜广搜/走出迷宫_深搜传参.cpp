//http://bailian.openjudge.cn/practice/1724/
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
int x_start, y_start, x_terminal, y_terminal, minStep = 1 << 30;
int cache[103][103];
bool visited[103][103] = { 0 };
char labyrinth[103][103];
void minStepToTermial(int x, int y, int currentSteps = 0) {    
	if (visited[x][y]) return;
	if (x == x_terminal && y == y_terminal) {     //如果到达了终点，顺利完成一条路线！
		minStep = min(minStep, currentSteps);
		return ;
	}
	if (currentSteps >= minStep)return;
	if (currentSteps >= cache[x][y])return;
	visited[x][y] = 1;
	if (labyrinth[x - 1][y] != '#'&&labyrinth[x - 1][y] != 'S') //如果往北走没撞墙
		minStepToTermial(x - 1, y, currentSteps + 1);           //就往北走一步吧！
	if (labyrinth[x + 1][y] != '#'&&labyrinth[x + 1][y] != 'S') //南
		minStepToTermial(x + 1, y, currentSteps + 1);           //这里不能使用接连成功!要找最优解
	if (labyrinth[x][y - 1] != '#'&&labyrinth[x][y - 1] != 'S') //西
		minStepToTermial(x, y - 1, currentSteps + 1);
	if (labyrinth[x][y + 1] != '#'&&labyrinth[x][y + 1] != 'S') //东
		minStepToTermial(x, y + 1, currentSteps + 1);
	visited[x][y] = 0;  //退回脚印
	cache[x][y] = currentSteps;    //从(x,y)到终点要走R步
}
int main() {
	int i, j, n, m;
	cin >> n >> m;
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= m; j++)
			cache[i][j] = 1 << 30;
	}
	for (i = 0; i <= m + 1; i++) labyrinth[0][i] = '#';            //修好上边外墙
	for (i = 1; i <= n; i++) {
		labyrinth[i][0] = '#';             //修好左侧外墙
		for (j = 1; j <= m; j++) {
			cin >> labyrinth[i][j];        //输入
			if (labyrinth[i][j] == 'S') x_start = i, y_start = j;  //记录起点位置
			else if (labyrinth[i][j] == 'T')	x_terminal = i, y_terminal = j; //记录终点位置
		}labyrinth[i][j] = '#';            //修好右侧外墙
	}
	for (j = 0; j <= m + 1; j++)  labyrinth[i][j] = '#';           //修好下边外墙
	minStepToTermial(x_start, y_start);
	cout << minStep << endl;
	return 0;
}