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
	for (i = 0; str[i] != '\0'; i++) {  //�Ȱѵ���һ��һ�ηŽ�word��ά�ַ�������
		if (str[i]!=' ') {              //��������ַ�...
			if (pre_is_letter == 1) {   //���ǰ��Ҳ���ַ�����������
				word[id][num_of_word] = str[i];
				num_of_word++;
				pre_is_letter = 1;
			}
			else {                      //���ǰ���ǿո񣬿������ַ�
				id++; pre_is_letter = 1;
				word[id][0] = str[i];
				num_of_word = 1;
			}
		}
		else {                          //��������ո�...
			if (pre_is_letter == 1) {   //���ǰ�����ַ����������ַ�'\0'
				word[id][num_of_word] = '\0';
				pre_is_letter = 0;
			}
			else                        //���ǰ���ǿո��ǾͲ�������
				pre_is_letter = 0;
		}
	}
	word[id][num_of_word] = '\0';       //�����һ��������β
	int row = 0, in_row[101];
	for (i = 0; i < n;) {   //�������е���
		if (letter_of_row[row] + strlen(word[i]) <= 80) {  //����row�У�û�г���
			in_row[i] = row; 
			letter_of_row[row] += strlen(word[i]) + 1;
			i++;
		}
		else {              //��i���ʼ���row�У�������row��80��letter��
			row++;
			in_row[i] = row;
			letter_of_row[row] += strlen(word[i]) + 1;
			i++;
		}
	}cout << word[0];
	for (i = 1; i < n; i++) {
		if (in_row[i - 1] == in_row[i])   //������
			cout << " " << word[i];
		else     //����
			cout << endl << word[i];
	}
	return 0;
}