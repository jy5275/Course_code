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
	for (i = 0; str[i] != '\0'; i++) {      //�ȶ���ÿ����ĸ���޸�cnt�ж�Ӧֵ++
		if (str[i] >= 'A'&&str[i] <= 'Z') {
			char tmpc = str[i] - 'A' + 'a';
			cnt[tmpc]++;
		}
		else if (str[i] >= 'a'&&str[i] <= 'z') {  //ע���Сд�ϲ�
			cnt[str[i]]++;
		}
	}
	for (i = 'a'; i <='z'; i++)      //�ȼ�¼���ֵ
		if (cnt[i] > max) 
			max = cnt[i];
	for (i = 'a'; i <= 'z'; i++) {   //��¼max��ʼ�ҵڶ����ֵ
		if (cnt[i] == max)continue;  //����max������
		if (cnt[i] > sec_max) sec_max = cnt[i];  //����ȥ��max������ֵ
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