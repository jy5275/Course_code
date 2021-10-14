#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<set>
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
int r, c, T, peanut[102][102], maxNut[102][102];
int calcMaxNut(int rth, int cth) {
	if (maxNut[rth][cth] != -1)return maxNut[rth][cth];
	int eccollect = 0, succollect = 0;
	if (rth < r) eccollect = calcMaxNut(rth + 1, cth);
	if (cth < c) succollect = calcMaxNut(rth, cth + 1);
	int tmpMax = max(eccollect, succollect) + peanut[rth][cth];
	maxNut[rth][cth] = tmpMax;
	return tmpMax;
}
int main() {
	cin >> T;
	while (T--) {
		memset(maxNut, -1, sizeof(maxNut));
		cin >> r >> c;
		for (int i = 1; i <= r; i++) {
			for (int j = 1; j <= c; j++) 
				cin >> peanut[i][j];
		}

		//----------递归方案--------------------------------------------------
		cout << calcMaxNut(1, 1) << endl;
		//----------动规方案--------------------------------------------------
		for (int i = r; i >= 1; i--) {
			for (int j = c; j > 0; j--) {
				maxNut[i][j] = peanut[i][j];
				if (i < r) maxNut[i][j] = max(maxNut[i][j], maxNut[i + 1][j] + peanut[i][j]);
				if (j < c) maxNut[i][j] = max(maxNut[i][j], maxNut[i][j + 1] + peanut[i][j]);
			}
		}
		cout << maxNut[1][1] << endl;
		//--------------------------------------------------------------------

	}
	clock_t startTime = clock();

	clock_t endTime = clock();
	//cout<< "程序段运行时间:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	return 0;
}