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
	sort(test, n);  //先给所有点排序，按照x坐标从小到大顺序
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (i == j)continue;
			if (test[i].x <= test[j].x&&test[i].y <= test[j].y) //发现i被j支配，立即break
				break;
		}
		if (j >= n) {  //如果j>=n，则说明i不被任何点支配，输出它！
			if (f > 0)cout << ',';
			cout << '(' << test[i].x << ',' << test[i].y << ')';
			f = 1;     //标记已经cout过了
		}
	}
	return 0;
}
//Debug两次：第一次38行j=i+1，导致对每个i小于i的j都没考虑，从而每次验证不支配性时跳过了很多点，
//从而多输出了很多组，这个错在样例中看不出来【算法错误->少考虑了情况】
//第二次39行continue写成了break，【常见错误！！！】