//�ݹ�����֮������С��Ϸ
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
int cache[103][103][5];       //��dirc�����ߵ�(x,y),��T����Ҫ��ת����
//ifstream fin("in.txt", ios::in);
int minCmp(int a, int b) {
	if (a > b) return b;
	else return a;
}
bool ableToGo(int y, int x) {  //������(x,y)�ܲ��ܲ�
	if (map[y][x] == 'X' || map[y][x] == 'S')return false;
	if (y < 0 || x < 0)return false;
	return true;
}
int minSegToTerminal(int y, int x, int dirc) {  //�˺�������ʱ�ѵ�(x,y),�����䵽�յ����ٹ�����
	if (map[y][x] == 'T')      //����������յ㣬˳�����һ��·�ߣ�
		return 0;
	if (cache[y][x][dirc] != -1) return cache[y][x][dirc];  //��dirc�����ߵ�(x,y)�д洢!
	int R = maxStep;
	map[y][x] = 'S';           //�ȳ���ӡ����a��(x,y)��Ϊ'S'
	if (ableToGo(y - 1, x)) {  //��������ߣ�ûײǽ&&û�߻�ͷ·
		if (dirc != 1)         //ǰһ���������������䣡
			R = minCmp(R, 1 + minSegToTerminal(y - 1, x, 1));
		else
			R = minCmp(R, minSegToTerminal(y - 1, x, 1));
	}
	if (ableToGo(y + 1, x)) {  //��2
		if (dirc != 2)
			R = minCmp(R, 1 + minSegToTerminal(y + 1, x, 2));
		else
			R = minCmp(R, minSegToTerminal(y + 1, x, 2));
	}
	if (ableToGo(y, x - 1)) {  //��3
		if (dirc != 3)
			R = minCmp(R, 1 + minSegToTerminal(y, x - 1, 3));
		else
			R = minCmp(R, minSegToTerminal(y, x - 1, 3));
	}
	if (ableToGo(y, x + 1)) {  //��4
		if (dirc != 4)
			R = minCmp(R, 1 + minSegToTerminal(y, x + 1, 4));
		else
			R = minCmp(R, minSegToTerminal(y, x + 1, 4));
	}
	cache[y][x][dirc] = R;
	map[y][x] = ' ';  //�˻ؽ�ӡ
	return R;         //����R
}
int buildMap() {
	int i, j;
	cin >> w >> h;
	if (w == 0)return 0;
	for (j = 0; j <= w + 1; j++) map[0][j] = ' ';  //�޺��ϱ߹���
	map[0][j] = 'X';  //�������Ͻ�
	for (i = 1; i <= h; i++) {
		cin.get();
		map[i][0] = ' ';              //�޺�������
		for (j = 1; j <= w; j++) 
			map[i][j] = cin.get();    //����
		map[i][j] = ' ', map[i][++j] = 'X';       //�޺��Ҳ����
	}
	for (j = 0; j <= w; j++)
		map[i][j] = ' ';
	map[i][j] = 'X';
	for (j = 0; j <= w + 2; j++)
		map[i + 1][j] = 'X';   //�޺��±߹���
	return 1;
}
int main() {
	clock_t startTime, endTime;
	int numBoard = 1;
	while (buildMap()) {
		int m = 0;
		maxStep = w * h;
		cout << "Board #" << numBoard << ":" << endl;
		while (++m) {     //ÿ��ʼĩλ�����뼴һ������,cacheҪ���㣡
			int x1, x2, y1, y2, k = 0;
			cin >> x1 >> y1 >> x2 >> y2;
			startTime = clock();
			memset(cache, -1, sizeof(cache));
			if (x1 == 0 && x2 == 0 && y1 == 0 && y2 == 0) break;
			//cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
			map[y1][x1] = 'S', map[y2][x2] = 'T';  //��һ��ʼĩλ��ST�����map��
			k = minSegToTerminal(y1, x1, 0);       //��Ҫ���������
			map[y1][x1] = 'X', map[y2][x2] = 'X';  //��ST����ΪX
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