//数独,类似少林神棍,注意状态由参数与全局变量共同dictate,甚至全局变量占到主要地位
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
bool rowFlags[9][10], colFlags[9][10], blockFlags[9][10];
int board[9][9];
class Pos {
public:
	int r, c;
	Pos(int r_, int c_) :r(r_), c(c_) {}
};
vector<Pos> blankPos;   //所有空白格子的位置
void SetAllFlags(int i, int j, int num, int f) { //把num放在(i,j),设标记;或从(i,j)取走num,清除标记
	rowFlags[i][num] = f;
	colFlags[i][num] = f;
	blockFlags[(i / 3) * 3 + j / 3][num] = f;
	if(f==1) board[i][j] = num;
	else board[i][j] = 0;
}
bool IsOk(int i, int j, int num) {   //看看num能否放在(i,j)位置
	return !rowFlags[i][num] && !colFlags[i][num] && 
		!blockFlags[(i / 3) * 3 + j / 3][num];
}
bool Dfs(int n) {  //处理blankPos[n]前的所有空格.
	//这里board才能充分描述当前状态,甚至n都可以写成全局变量
	if (n < 0) return true;    //【立即成功】board保持原封不动返回
	int r = blankPos[n].r, c = blankPos[n].c; //从第n个格子开始处理
	for (int num = 1; num <= 9; num++) {      //从1~9挨个尝试放进blankPos[n]
		if (IsOk(r, c, num)) {  
			SetAllFlags(r, c, num, 1);   //修改全局！
			if (Dfs(n - 1, num)) return true; //如果放得进去,继续放第n-1个,如果追溯到底成功则返回true
			SetAllFlags(r, c, num, 0);   //否则清除第n个空格放的num,尝试放另一个num
		}
	}
	return false;
}
int main() {
	int t; cin >> t;
	while (t--) {   //每个case之前记得把全局变量们清零！
		memset(rowFlags, 0, sizeof(rowFlags));
		memset(colFlags, 0, sizeof(colFlags));
		memset(blockFlags, 0, sizeof(blockFlags));
		blankPos.clear();
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				int tmp; scanf("%d",&tmp);
				board[i][j] = tmp;
				if (board[i][j]) SetAllFlags(i, j, tmp, 1);
				else blankPos.push_back(Pos(i, j));
			}
		}
		clock_t startTime = clock();
		if (Dfs(blankPos.size())) {    //尝试一次就行,不像少林神棍,要枚举L挨个尝试
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					printf("%d", board[i][j]);
				}cout << endl;
			}
		}
		clock_t endTime = clock();
		//cout << "程序段运行时间:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	}
	return 0;
}