#include<iostream>
#include<string.h>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;
struct point {
	int x, y;
};
void sort(point *a, int n) {
	int i, j; point tmpp;
	for (i = 0; i < n - 1; i++) {
		for (j = 0; j < n - i - 1; j++) {
			if (a[j].x > a[j + 1].x) {
				tmpp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmpp;
			}
			else if (a[j].x == a[j + 1].x) {
				if (a[j].y > a[j + 1].y) {
					tmpp = a[j];
					a[j] = a[j + 1];
					a[j + 1] = tmpp;
				}
			}
		}
	}
}
int main() {
	point test[101];
	int n, i, j, f = 0;
	cin >> n;
	for (i = 0; i < n; i++) 
		cin >> test[i].x >> test[i].y;
	sort(test, n);  //�ȸ����е����򣬰���x�����С����˳��
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (i == j)continue;
			if (test[i].x <= test[j].x&&test[i].y <= test[j].y) //����i��j֧�䣬����break
				break;
		}
		if (j >= n) {  //���j>=n����˵��i�����κε�֧�䣬�������
			if (f > 0)cout << ',';
			cout << '(' << test[i].x << ',' << test[i].y << ')';
			f = 1;     //����Ѿ�cout����
		}
	}
	return 0;
}
//Debug���Σ���һ��38��j=i+1�����¶�ÿ��iС��i��j��û���ǣ��Ӷ�ÿ����֤��֧����ʱ�����˺ܶ�㣬
//�Ӷ�������˺ܶ��飬������������п����������㷨����->�ٿ����������
//�ڶ���39��continueд����break�����������󣡣�����