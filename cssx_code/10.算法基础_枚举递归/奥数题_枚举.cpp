#include<iostream>
#include<string.h>
#include<cstring>
#include<string>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;
const int LETTER_NUM = 5;
bool taken[10];            //��¼�����Ƿ���ĸռ��,ÿ��case���������㣡
int val[LETTER_NUM];       //��¼������ĸ���������,01234����ABCDE
int stint(string &s, int val[]) {     //������ĸ���ֶ�Ӧ����,��stringת��int
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
	while (n--) {   //����n������
		int flag = 0;
		for (int i = 0; i < 10; i++) taken[i] = 0; //taken����
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
/*Bugs��
1.No Solution������ѭ�����,���¶�������
2.val[]�±��Ӧ�Ĳ���ASCIIֵ,Ҫ��ȥ'A'��
3.flag��taken[]ÿ��caseǰû�����㣡
�Ż���
1.strlen�ٵ���Ϊ�ã�����ʱ��������֮
2.goto��ʡȥ����break
*/