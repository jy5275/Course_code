#include<iostream>
#include<string.h>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;
int main() {
	char str[501];
	cin.getline(str, 501);
	int i, j, cnt[257] = { 0 }, max = 0, sec_max = 0;
	for (i = 0; str[i] != '\0'; i++) {      //先读入每个字母，修改cnt中对应值++
		if (str[i] >= 'A'&&str[i] <= 'Z') {
			char tmpc = str[i] - 'A' + 'a';
			cnt[tmpc]++;
		}
		else if (str[i] >= 'a'&&str[i] <= 'z') {  //注意大小写合并
			cnt[str[i]]++;
		}
	}
	for (i = 'a'; i <='z'; i++)      //先记录最大值
		if (cnt[i] > max) 
			max = cnt[i];
	for (i = 'a'; i <= 'z'; i++) {   //记录max后开始找第二大的值
		if (cnt[i] == max)continue;  //碰到max就跳过
		if (cnt[i] > sec_max) sec_max = cnt[i];  //即找去除max后最大的值
	}
	for (i = 0; str[i] != '\0'; i++) {
		if (cnt[str[i]] == sec_max) {
			if (str[i] >= 'A'&&str[i] <= 'Z') 
				cout << str[i] << '+' << (char)(str[i] - 'A' + 'a');
			else 
				cout << (char)(str[i] - 'a' + 'A') << '+' << str[i];
			cout << ':' << sec_max;
			break;
		}
	}

	return 0;
}