//�ݹ�֮���̷ָ�
#include<iostream>
#include<string>
#include<cmath>
#include<memory>
#include<algorithm>
#include<iomanip>
using namespace std;
int chessBoard[10][10];        //ÿ�����ӵķ���
double cache[15][9][9][9][9];  //�洢�Ѿ���(x1,y1)-(x2,y2)��Ϊn�ݵ���Сƽ����
int sum[9][9] = { 0 };         //�����(1,1)��(i,j)�ķ���֮��
int calSum(int x1, int y1, int x2, int y2) {   //��(x1,y1)-(x2,y2)�����
	return sum[y2][x2] - sum[y2][x1 - 1] - sum[y1 - 1][x2] + sum[y1 - 1][x1 - 1];
}
int myMin(double a, double b) {
	if (floor(a) != a)return b;
	if (floor(b) != b)return a;
	if (a < b)return a;
	else return b;
}
double fun(int n, int x1, int y1, int x2, int y2) {   //��(x1,y1)-(x2,y2)�����n�ݵ���Сƽ����
	double sumSquare = 0;
	if (n == 1) {     //�������̿�
		if (cache[1][x1][y1][x2][y2] != -1) return cache[1][x1][y1][x2][y2];  //�д洢����
																			  //�޴洢����
		int tmp = calSum(x1, y1, x2, y2);
		sumSquare = tmp * tmp;
		cache[1][x1][y1][x2][y2] = sumSquare;
		return sumSquare;
	}
	//������̿�
	if (cache[n][x1][y1][x2][y2] != -1) return cache[n][x1][y1][x2][y2];      //�д洢
																			  //�޴洢->��������
	sumSquare = 0.111111;
	for (int i = x1; i < x2; i++)   //���з���
		sumSquare = myMin(sumSquare, fun(n - 1, x1, y1, i, y2) + fun(1, i + 1, y1, x2, y2));
	for (int i = x1; i < x2; i++)   //���з���
		sumSquare = myMin(sumSquare, fun(n - 1, i, y1, x2, y2) + fun(1, x1, y1, i + 1, y2));
	for (int i = y1; i < y2; i++)   //���з���
		sumSquare = myMin(sumSquare, fun(n - 1, x1, y1, x2, i) + fun(1, x1, i + 1, x2, y2));
	for (int i = x1; i < x2; i++)   //���з���
		sumSquare = myMin(sumSquare, fun(n - 1, x1, i, x2, y2) + fun(1, x1, y1, x2, i + 1));
	cache[n][x1][y1][x2][y2] = sumSquare;
	return sumSquare;
}
int main() {
	memset(cache, -1, sizeof(cache));
	int n; cin >> n;
	for (int i = 1; i <= 8; i++) {
		for (int j = 1, rowsum = 0; j <= 8; j++) {
			cin >> chessBoard[i][j];
			rowsum += chessBoard[i][j];
			sum[i][j] = sum[i - 1][j] + rowsum;
		}
	}
	double cacheult = n * fun(n, 1, 1, 8, 8) - sum[8][8] * sum[8][8];
	return 0;
}