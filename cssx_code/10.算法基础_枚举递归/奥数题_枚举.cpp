#include<iostream>
#include<string.h>
#include<cstring>
#include<string>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;
const int LETTER_NUM = 5;
bool taken[10];            //记录数字是否被字母占用,每个case结束后清零！
int val[LETTER_NUM];       //记录各个字母代表的数字,01234代表ABCDE
int stint(string &s, int val[]) {     //给定字母数字对应表下,把string转成int
	int ans = 0, isMultipleZero = 1;
	int len = strlen(s.c_str());
	if (val[s[0] - 'A'] == 0 && len > 1) return -1;
	for (int i = 0; i < len; i++)
		ans = ans * 10 + val[s[i] - 'A'];
	return ans;
}
int main() {
	int n;
	string s1, s2, s3;
	cin >> n;
	while (n--) {   //共有n种情形
		int flag = 0;
		for (int i = 0; i < 10; i++) taken[i] = 0; //taken清零
		cin >> s1 >> s2 >> s3;
		for (val[0] = 0; val[0] <= 9; val[0]++) {
			taken[val[0]] = true;
			for (val[1] = 0; val[1] < 9; val[1]++) {
				if (taken[val[1]]) continue;
				taken[val[1]] = true;
				for (val[2] = 0; val[2] <= 9; val[2]++) {
					if (taken[val[2]]) continue;
					taken[val[2]] = true;
					for (val[3] = 0; val[3] < 9; val[3]++) {
						if (taken[val[3]]) continue;
						taken[val[3]] = true;
						for (val[4] = 0; val[4] < 9; val[4]++) {
							if (taken[val[4]]) continue;
							int n1 = stint(s1, val);
							int n2 = stint(s2, val);
							int n3 = stint(s3, val);
							if (n1 >= 0 && n2 >= 0 && n3 >= 0 && n1 + n2 == n3) {
								cout << n1 << '+' << n2 << '=' << n3 << endl;
								goto Found;
							}
						} taken[val[3]] = false;
					} taken[val[2]] = false;
				} taken[val[1]] = false;
			} taken[val[0]] = false;
		}
		if (flag == 0)
			cout << "No Solution!" << endl;
Found:
	}
	return 0;
}
/*Bugs：
1.No Solution放在了循环里边,导致多次输出！
2.val[]下标对应的不是ASCII值,要减去'A'！
3.flag、taken[]每次case前没有清零！
优化：
1.strlen少调用为好，用临时变量保存之
2.goto大法省去多重break
*/