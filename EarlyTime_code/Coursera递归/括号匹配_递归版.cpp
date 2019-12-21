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
		return -1;  //匹配！
	}
	else {
		if (str[s] == '(') {  //首先判断这个是不是一个左括号，如果是则去匹配这个左括号里面的东西
			int n = f(str, s + 1);
			if (b == 0) {
				b = 0; return n;
			}
			else {
				if (str[n] == ')')  //匹配完了之后我们再匹配后面的右括号
					return f(str, n + 1);  //继续找下一个
				else
				{
					b = 0; return n;  //任意一步出问题都会返回0
				}
			}
		}
		else {
			b = 1; return s;  //匹配！
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