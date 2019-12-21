#include<iostream>
#include<string.h>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;
int main() {
	char str[501], word[501][501] = { '\0' };
	cin.getline(str, 501);
	int i, j, pre_is_letter = 1, id = 0, num_of_letter = 0, empty[500] = { 0 };
	for (i = 0; str[i] != '\0'; i++) {
		if (str[i] != ' ') {  //碰到字母！看这字母前边是不是字母，一番操作后，pre_is_letter置为1
			if (pre_is_letter == 0) {  //前边是空格，开启新词
				id++;
				word[id][0] = str[i];
				num_of_letter = 1;
			}
			else {  //前边是字母，继续这个词
				word[id][num_of_letter] = str[i];
				num_of_letter++;
			}
			pre_is_letter = 1;
		}
		else {   //碰到了空格，pre_is_letter置为0
			if (pre_is_letter == 0) {  //空格前边也是空格
				empty[id]++;
			}
			else {    //空格前边是单词，那么结束这个词
				word[id][num_of_letter] = '\0';
				empty[id]++;
			}
			pre_is_letter = 0;
		}
	}
	word[id][num_of_letter] = '\0';
	for (i = 0; word[i][0] != '\0'; i++) {
		int len = strlen(word[i]);
		for (j = len - 1; j >= 0; j--) {
			cout << word[i][j];
		}
		for (j = 0; j < empty[i]; j++) {
			cout << ' ';
		}
	}

	return 0;
}