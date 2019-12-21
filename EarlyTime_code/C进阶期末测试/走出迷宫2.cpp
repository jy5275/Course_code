#include<iostream>
#include<string.h>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;
int min_step, tmp_step, x_start, y_start, x_terminal, y_terminal;
char a[103][103];
int go(int x, int y, int k) {   //开始调用这个函数时，已经成功走了k步，到达(x,y)
	if (k > min_step)  return 0;               //如果已经比最小值还大了，那就回去歇息吧
	if (x == x_terminal && y == y_terminal) {  //如果第k步到达了终点...
		if (k < min_step) min_step = k;        //判定是不是当前最短路径
		return 0;                              //顺利完工！一条路线完毕
	}
	a[x][y] = 'S';              //踩出脚印：把a中第k步坐标(x,y)标为'S'
	if (a[x - 1][y] != '#'&&a[x - 1][y] != 'S')   //如果往北走没撞墙...
		go(x - 1, y, k + 1);    //就把往北这一步作为第k+1步吧！
	if (a[x + 1][y] != '#'&&a[x + 1][y] != 'S')   //南
		go(x + 1, y, k + 1);
	if (a[x][y - 1] != '#'&&a[x][y - 1] != 'S')   //西
		go(x, y - 1, k + 1);
	if (a[x][y + 1] != '#'&&a[x][y + 1] != 'S')   //东
		go(x, y + 1, k + 1);
	a[x][y] = '.';    //退回脚印
	return 0;
}
int main() {
	int i, j, n, m;
	cin >> n >> m;
	for (i = 0; i <= m + 1; i++)
		a[0][i] = '#';             //修好外墙
	min_step = n * m;
	for (i = 1; i <= n; i++) {
		a[i][0] = '#';             //修好外墙
		for (j = 1; j <= m; j++) {
			cin >> a[i][j];        //输入
			if (a[i][j] == 'S')
				x_start = i, y_start = j;
			else if (a[i][j] == 'T')
				x_terminal = i, y_terminal = j;
		}a[i][j] = '#';            //修好外墙
	}
	for (j = 0; j <= m + 1; j++)
		a[i][j] = '#';             //修好外墙
	go(x_start, y_start, 0);
	cout << min_step;
	return 0;
}