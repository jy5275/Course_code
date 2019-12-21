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
bool colFlags[9], rowFlags[9], leftWing[20], rightWing[20], board[9][9];
int numOfSln = 1;
class Pos {
public:
	int r, c;
	Pos(int r_, int c_) :r(r_), c(c_) {}
};
vector<Pos> blankPos;
void PrintBoard() {
	cout << "No." << numOfSln++ << endl;
	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 8; j++) {
			printf("%d ", board[i][j]);
		}cout << endl;
	}
}
void SetFlags(int r, int c, int f) {
	board[r][c] = f;
	colFlags[c] = f;
	rowFlags[r] = f;
	leftWing[r + c] = f;
	rightWing[8 + r -c] = f;
}
bool IsOk(int r, int c) {
	return !colFlags[c] && !rowFlags[r] && !leftWing[r + c] && !rightWing[8 + r - c];
}
void findSolutions(int x, int left) {  //前x个空位,放left个皇后
	if (left == 0 && x >= 0) {
		PrintBoard();
		return;
	}
	if (x < left) return ;
	if (IsOk(blankPos[x - 1].r, blankPos[x - 1].c)) { //这个皇后可以放在x位置
		SetFlags(blankPos[x - 1].r, blankPos[x - 1].c, 1);
		findSolutions(x - 1, left - 1);    //放上去继续！
		SetFlags(blankPos[x - 1].r, blankPos[x - 1].c, 0);
	}
	findSolutions(x - 1, left);   //前x-1个空位放left个皇后
	return ;
}
int main() {
	clock_t startTime = clock();
	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 8; j++) 
			blankPos.push_back(Pos(i, j));
	}
	findSolutions(blankPos.size(), 8);
	clock_t endTime = clock();
	cout << "程序段运行时间:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	
	return 0;
}