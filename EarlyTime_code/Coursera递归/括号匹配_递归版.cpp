#include<iostream>
#include<string.h>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;
bool b;
int f(char str[], int s) {
	if (strlen(str) == s) {
		b = 1;
		return -1;  //ƥ�䣡
	}
	else {
		if (str[s] == '(') {  //�����ж�����ǲ���һ�������ţ��������ȥƥ���������������Ķ���
			int n = f(str, s + 1);
			if (b == 0) {
				b = 0; return n;
			}
			else {
				if (str[n] == ')')  //ƥ������֮��������ƥ������������
					return f(str, n + 1);  //��������һ��
				else
				{
					b = 0; return n;  //����һ�������ⶼ�᷵��0
				}
			}
		}
		else {
			b = 1; return s;  //ƥ�䣡
		}
	}
}
int main() {
	char str[15]; cin >> str;
	int n = f(str, 0);
	if (b == 1 && n == -1)
		cout << "yes" << endl;
	else
		cout << "no";
	return 0;
}