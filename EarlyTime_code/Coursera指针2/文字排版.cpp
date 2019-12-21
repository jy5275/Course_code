//Presentational Error
#include<iostream>
#include<string.h>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;
int main() {
	char word[101][41];
	int i, n, num_of_word = 0, id = 0, pre_is_letter = 1, letter_of_row[1001] = { 0 };
	cin >> n; cin.get();
	char str[10001]; cin.getline(str, 10001);
	for (i = 0; str[i] != '\0'; i++) {  //先把单词一段一段放进word二维字符数组中
		if (str[i]!=' ') {              //如果读到字符...
			if (pre_is_letter == 1) {   //如果前边也是字符，单词增长
				word[id][num_of_word] = str[i];
				num_of_word++;
				pre_is_letter = 1;
			}
			else {                      //如果前边是空格，开启新字符
				id++; pre_is_letter = 1;
				word[id][0] = str[i];
				num_of_word = 1;
			}
		}
		else {                          //如果读到空格...
			if (pre_is_letter == 1) {   //如果前边是字符，结束该字符'\0'
				word[id][num_of_word] = '\0';
				pre_is_letter = 0;
			}
			else                        //如果前边是空格，那就不搞事情
				pre_is_letter = 0;
		}
	}
	word[id][num_of_word] = '\0';       //把最后一个单词收尾
	int row = 0, in_row[101];
	for (i = 0; i < n;) {   //遍历所有单词
		if (letter_of_row[row] + strlen(word[i]) <= 80) {  //加入row行，没有超出
			in_row[i] = row; 
			letter_of_row[row] += strlen(word[i]) + 1;
			i++;
		}
		else {              //第i个词加入row行，超出了row行80个letter！
			row++;
			in_row[i] = row;
			letter_of_row[row] += strlen(word[i]) + 1;
			i++;
		}
	}cout << word[0];
	for (i = 1; i < n; i++) {
		if (in_row[i - 1] == in_row[i])   //不跳行
			cout << " " << word[i];
		else     //跳行
			cout << endl << word[i];
	}
	return 0;
}