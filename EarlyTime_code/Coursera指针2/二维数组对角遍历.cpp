#include<iostream>
#include<string.h>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;
int main() {
	int row, col, i, j, a[201][201],array_type,last;
	cin >> row >> col;
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			cin >> a[i][j];
		}
	}i = 0; j = 0;
	while (1) {
		if (j < 0) {   //һб���Ƿ������
			j = i;
			i = 0;
		}
		if (i < row&&j < col) 
			cout << a[i][j] << endl;
		if (i == row - 1 && j == col - 1) {   //�Ƿ�������
			break;
		}
		i++; j--;
	}
	return 0;
}