#include<iostream>
#include<string.h>
#include<cstring>
#include<string>
#include<cmath>
using namespace std;
bool Valid(int row, int pos[]) {     //开始摆第row行,看看与pos记录的前边行位置有无冲突
	for (int i = 0; i < row; i++) {
		if (pos[row] == pos[i] || abs(row - i) == abs(pos[row] - pos[i]))
			return false;
	}
	return true;
}
int main() {
	int pos[8];
	for (pos[0] = 0; pos[0] < 8; pos[0]++) {
		for (pos[1] = 0; pos[1] < 8; pos[1]++) {
			if (!Valid(1, pos)) continue;
			for (pos[2] = 0; pos[2] < 8; pos[2]++) {
				if (!Valid(2, pos)) continue;
				for (pos[3] = 0; pos[3] < 8; pos[3]++) {
					if (!Valid(3, pos)) continue;
					for (pos[4] = 0; pos[4] < 8; pos[4]++) {
						if (!Valid(4, pos)) continue;
						for (pos[5] = 0; pos[5] < 8; pos[5]++) {
							if (!Valid(5, pos)) continue;
							for (pos[6] = 0; pos[6] < 8; pos[6]++) {
								if (!Valid(6, pos)) continue;
								for (pos[7] = 0; pos[7] < 8; pos[7]++) {
									if (Valid(7, pos)) {
										for (int i = 0; i < 8; i++)
											cout << pos[i] << " ";
										cout << endl;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return 0;
}