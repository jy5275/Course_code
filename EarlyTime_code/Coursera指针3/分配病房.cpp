#include<iostream>
#include<string.h>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;
void sort(int *a, double *b, int n) {
	int i, j, tmpa ;
	double tmpb  ;
	for (i = 0; i < n - 1; i++) {
		for (j = 0; j < n - i - 1; j++) {
			if (b[j + 1] > b[j]) {
				tmpa = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmpa;
				tmpb = b[j];
				b[j] = b[j + 1];
				b[j + 1] = tmpb;
			}
		}
	}
}
int main() {
	int n, i, j, f = 0, num[51];
	double illness[51], line;
	cin >> n >> line;
	for (i = 0; i < n; i++) 
		cin >> num[i] >> illness[i];
	sort(num, illness, n);
	for (i = 0; i < n; i++) {
		if (illness[i] < line)break;
		if (num[i] < 10) cout << "00" << num[i] << " ";
		else if (num[i] < 100)cout << "0" << num[i] << " ";
		else cout << num[i] << " ";
		cout << fixed << setprecision(1) << illness[i] << endl;
		f = 1;
	}
	if (f == 0)cout << "None.";
	return 0;
}