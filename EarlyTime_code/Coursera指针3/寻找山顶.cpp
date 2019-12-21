#include<iostream>
#include<string.h>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;
int main() {
	int m, n, i, j, a[22][22];
	cin >> m >> n;
	for (i = 0; i <= 21; i++) {
		for (j = 0; j <= 21; j++) {
			a[i][j] = -99999;
		}
	}
	for (i = 1; i <= m; i++) {
		for (j = 1; j <= n; j++) {
			cin >> a[i][j];
		}
	}
	for (i = 1; i <= m; i++) {
		for (j = 1; j <= n; j++) {
			if (a[i][j] >= a[i - 1][j] && a[i][j] >= a[i + 1][j] && a[i][j] >= a[i][j + 1]
				&& a[i][j] >= a[i][j - 1]) {
				cout << i - 1 << ' ' << j - 1 << endl;
			}
		}
	}

	return 0;
}