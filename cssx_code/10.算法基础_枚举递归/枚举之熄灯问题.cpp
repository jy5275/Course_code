//ö��֮Ϩ������
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
	//û��Ҫ����ά�����¼�м�״̬,��Ϊ�м�״̬���Ա�press��puzzleȷ����
	for (r = 1; r < 5; r++) {
		for (c = 1; c < 7; c++) {
			press[r + 1][c] = (puzzle[r][c] + press[r][c] + press[r - 1][c] +
				press[r][c - 1] + press[r][c + 1]) % 2;
		} //�ȸ���r��r-1�в���ȷ��puzzle[r][c]״̬,��ȷ��press[r+1][c]����
	}     //ѭ������ʱ,ȫ5��6�еĲ�������ȷ��
	for (c = 1; c < 7; c++)   //��֤���һ���Ƿ�ȫ��,һ���������̷���false
		if ((press[5][c - 1] + press[5][c] + press[5][c + 1] +
			press[4][c] != puzzle[5][c])) return false;
	return true;
}
void enumerate() {     //ö�ٺ���
	int c;
	for (c = 1; c < 7; c++) press[1][c] = 0;
	while (guess() == false) {   //������press[1]�ܷ���������
		press[1][1]++;
		c = 1;
		while (press[1][c] > 1) {
			press[1][c] = 0;
			c++;          //��������ڷ��������Ĳ���,����һ����Խ��(c>6)��
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
		enumerate();   //ö�����е�һ�в�����		
		for (int i = 1; i <= 5; i++) {
			for (int j = 1; j <= 6; j++)
				cout << press[i][j] << " ";
			cout << endl;
		}
	}
	return 0;
}