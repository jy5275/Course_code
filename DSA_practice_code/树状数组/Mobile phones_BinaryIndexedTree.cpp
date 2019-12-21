/* http://dapractise.openjudge.cn/2018wk2/2/ */
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
const int MAX = 1028;
int S, map[MAX][MAX] = { 0 }, C[MAX][MAX] = { 0 };
int lowbit(int x) { return x & (-x); }
void Add() {               //单点更新:(x, y)
	int x, y, A; scanf("%d %d %d", &x, &y, &A);
	x++, y++;
	map[x][y] += A;
	int i = x, j = y;
	while (i <= S) {
		j = y;
		while (j <= S) {
			C[i][j] += A;
			j = j + lowbit(j);
		}i = i + lowbit(i);
	}
}
int Sum(int x, int y) {    //求从(1,1)到(x,y)的所有元素总和
	int i = x, j = y, ans = 0;
	while (i > 0) {
		j = y;
		while (j > 0) {
			ans = ans + C[i][j];
			j = j - lowbit(j);
		}
		i = i - lowbit(i);
	}return ans;
}
void Query() {     //区间求和:(x_first, y_first)~(x_last, y_last)
	int x_first, x_last, y_first, y_last;
	scanf("%d %d %d %d", &x_first, &y_first, &x_last, &y_last);
	x_first++, x_last++, y_first++, y_last++;
	int ans = Sum(x_last, y_last) - Sum(x_last, y_first - 1) - Sum(x_first - 1, y_last)
		+ Sum(x_first - 1, y_first - 1);  //【BUG1】
	printf("%d\n", ans);
}
int main() {
	int Instr, cease = 0;
	while (1) {
		if (cease == 1) break;
		scanf("%d", &Instr);
		switch (Instr){
		case 0:scanf("%d", &S); break;
		case 1:Add(); break;
		case 2:Query(); break;
		case 3:cease++; break;
		}
	}
	return 0;
}/* Bugs:
 【BUG1】算法错误,二维数组(r_f, c_f)~(r_l, c_l)的计算要依据容斥法则！比一维求和复杂！
 */