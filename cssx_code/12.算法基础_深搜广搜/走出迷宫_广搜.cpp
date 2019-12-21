#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stack>
#include<queue>
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
char labyrinth[102][102];
int n, m, maxStep, rStart, cStart, rTerminal, cTerminal, succeed = 0;
bool visited[102][102] = { false };
class CStep {
public:
	int r, c, rFather, cFather, steps;
	CStep(int r_, int c_, int rf_, int cf_, int s_) :
		r(r_), c(c_), rFather(rf_), cFather(cf_), steps(s_) {
		visited[r_][c_] = true;
	}
};
queue<CStep> open;
stack<CStep> close, result;
int main() {
	cin >> n >> m;
	maxStep = n * m;
	int i, j, currentStep = 0;
	for (i = 0; i <= m + 1; i++) labyrinth[0][i] = '#';            //修好上边外墙
	for (i = 1; i <= n; i++) {
		labyrinth[i][0] = '#';             //修好左侧外墙
		for (j = 1; j <= m; j++) {
			cin >> labyrinth[i][j];        //输入
			if (labyrinth[i][j] == 'S') rStart = i, cStart = j;  //记录起点位置
			else if (labyrinth[i][j] == 'T')	rTerminal = i, cTerminal = j;  //记录终点位置
		}labyrinth[i][j] = '#';            //修好右侧外墙
	}
	for (j = 0; j <= m + 1; j++)  labyrinth[i][j] = '#';           //修好下边外墙
	clock_t startTime = clock();

	open.push(CStep(rStart, cStart, 0, 0, 0));
	CStep current = open.front();

	while (!open.empty()) {
		current = open.front();      //1.取出首节点
		close.push(current);
		currentStep = current.steps;

		if (current.c == cTerminal && current.r == rTerminal) {
			succeed = 1;             //2.判断目标状态
			break;
		}
		if ((labyrinth[current.r - 1][current.c] == '.' || 
			labyrinth[current.r - 1][current.c] == 'T') &&     //3.扩展新节点 
			!visited[current.r - 1][current.c])         //向北走一步
			open.push(CStep(current.r - 1, current.c, current.r, current.c, currentStep + 1));
		if ((labyrinth[current.r + 1][current.c] == '.' ||
			labyrinth[current.r + 1][current.c] == 'T') &&
			!visited[current.r + 1][current.c])         //向南走一步
			open.push(CStep(current.r + 1, current.c, current.r, current.c, currentStep + 1));
		if ((labyrinth[current.r][current.c - 1] == '.' ||
			labyrinth[current.r][current.c - 1] == 'T') &&
			!visited[current.r][current.c - 1])         //向西走一步
			open.push(CStep(current.r, current.c - 1, current.r, current.c, currentStep + 1));
		if ((labyrinth[current.r][current.c + 1] == '.' ||
			labyrinth[current.r][current.c + 1] == 'T') &&
			!visited[current.r][current.c + 1])         //向东走一步
			open.push(CStep(current.r, current.c + 1, current.r, current.c, currentStep + 1));
		open.pop();
	}
	if (succeed == 0) 
		cout << "Impossible!" << endl;
	else {
		cout << currentStep << endl;
		CStep tmp = close.top();
		result.push(tmp);
		while (!close.empty()) {
			if (close.top().r == tmp.rFather && close.top().c == tmp.cFather) {
				tmp = close.top();
				result.push(tmp);
			}
			close.pop();
		}
		while (!result.empty()) {
			cout << "(" << result.top().r << "," << result.top().c << ")";
			if (result.size() > 1) cout << " -> ";
			else cout << endl;
			result.pop();
		}
	}
	clock_t endTime = clock();
	cout<< "程序段运行时间:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	return 0;
}