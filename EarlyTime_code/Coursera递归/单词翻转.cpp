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
		if (str[i] != ' ') {  //������ĸ��������ĸǰ���ǲ�����ĸ��һ��������pre_is_letter��Ϊ1
			if (pre_is_letter == 0) {  //ǰ���ǿո񣬿����´�
				id++;
				word[id][0] = str[i];
				num_of_letter = 1;
			}
			else {  //ǰ������ĸ�����������
				word[id][num_of_letter] = str[i];
				num_of_letter++;
			}
			pre_is_letter = 1;
		}
		else {   //�����˿ո�pre_is_letter��Ϊ0
			if (pre_is_letter == 0) {  //�ո�ǰ��Ҳ�ǿո�
				empty[id]++;
			}
			else {    //�ո�ǰ���ǵ��ʣ���ô���������
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