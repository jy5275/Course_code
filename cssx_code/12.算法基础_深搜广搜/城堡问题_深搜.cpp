#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stack>
#include<bitset>
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
int roomWallIndex[52][52], n, m, cntRoom = 0, maxSize = 0;
int visited[52][52] = { 0 };
bool northWall[52][52], southWall[52][52], westWall[52][52], eastWall[52][52];
bool eastWallExist(int x) {
	if (x >= 8) x -= 8;
	if (x >= 4) return true;
	else return false;
}
int calcSize(int r, int c) {
	if (visited[r][c]) return 0;
	visited[r][c] = cntRoom;
	int tmpSize = 1;
	if (!northWall[r][c] && !visited[r - 1][c])   //北有路！
		tmpSize += calcSize(r - 1, c);
	if (!southWall[r][c] && !visited[r + 1][c])   //南有路！
		tmpSize += calcSize(r + 1, c);
	if (!westWall[r][c] && !visited[r][c - 1])    //西有路！
		tmpSize += calcSize(r, c - 1);
	if (!eastWall[r][c] && !visited[r][c + 1])    //东有路！
		tmpSize += calcSize(r, c + 1);
	return tmpSize;
}
/*深搜用栈实现,一条路走到死,再返回换条路走;
广搜用队列实现,所有路都一步一步走*/
int main() {
	cin >> n >> m;    //n行m列
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> roomWallIndex[i][j];
			if (roomWallIndex[i][j] % 2 == 1) westWall[i][j] = true;
			else westWall[i][j] = false;
			if (roomWallIndex[i][j] % 4 == 2 || roomWallIndex[i][j] % 4 == 3)
				northWall[i][j] = true;
			else northWall[i][j] = false;
			if (roomWallIndex[i][j] >= 8) southWall[i][j] = true;
			else southWall[i][j] = false;
			if (eastWallExist(roomWallIndex[i][j])) eastWall[i][j] = true;
			else eastWall[i][j] = false;
		}
	}
	clock_t startTime = clock();
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (!visited[i][j]) {    //如果这时visited[i][j]还是未被染指
				cntRoom++;
				int tmpSize = calcSize(i, j);
				maxSize = max(maxSize, tmpSize);
			}
		}
	}cout << cntRoom << endl << maxSize << endl;
	clock_t endTime = clock();
	//cout << "程序段运行时间:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	return 0;
}