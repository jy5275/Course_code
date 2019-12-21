//棋盘问题,有点类似数独http://bailian.openjudge.cn/practice/1321/
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
int n, k;
bool colFlags[8], rowFlags[8];
char board[9][9];
class Pos {
public:
	int r, c;
	Pos(int r_, int c_) :r(r_), c(c_) {}
};
vector<Pos> blankPos;
void SetFlags(int r, int c, int f) {
	colFlags[c] = f;
	rowFlags[r] = f;
}
bool IsOk(int r, int c) {
	return !colFlags[c] && !rowFlags[r];
}
//(x空位,left个子) = (x-1个空位,left个子) + (x-1个空位,left-1个子)
int calcSolutions(int x, int left) {  //前x个空位,放left个棋子
	if (left == 0 && x >= 0) return 1;
	if (x < left) return 0;
	int ans = 0;
	if (IsOk(blankPos[x-1].r, blankPos[x-1].c)) {
		SetFlags(blankPos[x - 1].r, blankPos[x - 1].c, 1); //迈进！
		ans += calcSolutions(x - 1, left - 1);             //递归！
		SetFlags(blankPos[x - 1].r, blankPos[x - 1].c, 0); //撤回！
	}
	ans += calcSolutions(x - 1, left);
	return ans;
}
int main() {
	while (1) {
		memset(rowFlags, 0, sizeof(rowFlags));
		memset(colFlags, 0, sizeof(colFlags));
		blankPos.clear();
		cin >> n >> k;
		if (n == -1) break;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> board[i][j];
				if(board[i][j]=='#')
					blankPos.push_back(Pos(i, j));
			}
		}
		clock_t startTime = clock();
		cout << calcSolutions(blankPos.size(), k) << endl;
		clock_t endTime = clock();
		//cout << "程序段运行时间:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	}
	return 0;
}