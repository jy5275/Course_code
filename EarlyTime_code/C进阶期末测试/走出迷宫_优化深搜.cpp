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
int minStepToTermial(int x, int y) {    //�˺�������ʱ����k��������(x,y),����(x,y)���յ�����ٲ���
	if (cnt[x][y] != -1)  return cnt[x][y];            //�����������ط�֮ǰ������ֱ�ӷ��ؼ���ֵ
	if (x == x_terminal && y == y_terminal) {          //����������յ㣬˳�����һ��·�ߣ�
		cnt[x][y] = 0;	return 0;
	}
	int R = 10010;
	map[x][y] = 'S';  //�ȳ���ӡ����a��(x,y)��Ϊ'S'
	if (map[x - 1][y] != '#'&&map[x - 1][y] != 'S')    //��������ߣ�ûײǽ&&û�߻�ͷ·
		R = minCmp(R, 1 + minStepToTermial(x - 1, y)); //��������һ���ɣ�
	if (map[x + 1][y] != '#'&&map[x + 1][y] != 'S')    //��
		R = minCmp(R, 1 + minStepToTermial(x + 1, y));
	if (map[x][y - 1] != '#'&&map[x][y - 1] != 'S')    //��
		R = minCmp(R, 1 + minStepToTermial(x, y - 1));
	if (map[x][y + 1] != '#'&&map[x][y + 1] != 'S')    //��
		R = minCmp(R, 1 + minStepToTermial(x, y + 1));
	map[x][y] = '.';  //�˻ؽ�ӡ
	cnt[x][y] = R;    //��(x,y)���յ�Ҫ��R��
	return R;         //����R
}
int main() {
	int i, j, n, m;
	cin >> n >> m;
	for (i = 0; i <= n; i++) {
		for (j = 0; j <= m; j++)
			cnt[i][j] = -1;
	}
	for (i = 0; i <= m + 1; i++) map[0][i] = '#';            //�޺��ϱ���ǽ
	maxStep = n * m;
	for (i = 1; i <= n; i++) {
		map[i][0] = '#';             //�޺������ǽ
		for (j = 1; j <= m; j++) {
			cin >> map[i][j];        //����
			if (map[i][j] == 'S') x_start = i, y_start = j;  //��¼���λ��
			else if (map[i][j] == 'T')	x_terminal = i, y_terminal = j;  //��¼�յ�λ��
		}map[i][j] = '#';            //�޺��Ҳ���ǽ
	}
	for (j = 0; j <= m + 1; j++)  map[i][j] = '#';           //�޺��±���ǽ
	cout << minStepToTermial(x_start, y_start);
	return 0;
}