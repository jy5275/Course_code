//枚举之熄灯问题
#include<iostream>
#include<vector>
#include<string>
#include<set>
#include<cmath>
#include<list>
#include<memory>
#include<map>
#include<stdexcept>
#include<algorithm>
#include<queue>
#include<iomanip>
#include<fstream>
#include<unordered_map>
#include<regex>
using namespace std;
int puzzle[7][8], press[7][8] = { 0 };
class binaryInt {
	vector<int> biInt{ 0 };
	void operator++(int k) {
		biInt[0]++;
		int c = 0;
		while (biInt[c] == 2) {
			if (biInt.size() == c) biInt.push_back(0);
			biInt[c] = 0;
			c++;
			biInt[c]++;
		}
	}
};
bool guess() {
	int c, r;
	//没必要另开二维数组记录中间状态,因为中间状态可以被press与puzzle确定！
	for (r = 1; r < 5; r++) {
		for (c = 1; c < 7; c++) {
			press[r + 1][c] = (puzzle[r][c] + press[r][c] + press[r - 1][c] +
				press[r][c - 1] + press[r][c + 1]) % 2;
		} //先根据r与r-1行操作确定puzzle[r][c]状态,再确定press[r+1][c]操作
	}     //循环结束时,全5行6列的操作都已确定
	for (c = 1; c < 7; c++)   //验证最后一行是否全灭,一旦不对立刻返回false
		if ((press[5][c - 1] + press[5][c] + press[5][c + 1] +
			press[4][c] != puzzle[5][c])) return false;
	return true;
}
void enumerate() {     //枚举函数
	int c;
	for (c = 1; c < 7; c++) press[1][c] = 0;
	while (guess() == false) {   //看这种press[1]能否满足条件
		press[1][1]++;
		c = 1;
		while (press[1][c] > 1) {
			press[1][c] = 0;
			c++;          //如果不存在符合条件的操作,则这一步会越界(c>6)！
			press[1][c]++;
		}
	}
	return;
}
int main() {
	int n; cin >> n;
	for (int c = 1; c <= n; c++) {
		cout << "case " << c << endl;
		for (int i = 1; i <= 5; i++) {
			for (int j = 6; j <= 6; j++) cin >> a[i][j];
		}
		enumerate();   //枚举所有第一行操作！		
		for (int i = 1; i <= 5; i++) {
			for (int j = 1; j <= 6; j++)
				cout << press[i][j] << " ";
			cout << endl;
		}
	}
	return 0;
}