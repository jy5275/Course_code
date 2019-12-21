//http://cxsjsx.openjudge.cn/2019hw3/7/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream> 
#include <cstring> 
#include <cstdlib> 
#include <cstdio> 
using namespace std;
const int MAX = 110;
class CHugeInt {
	// 在此处补充你的代码
public:
	char str[210];
	int num[210];
	void Init() { for (int i = 0; i < 210; i++) num[i] = 0; }
	void str2num() {
		int len = strlen(str);
		for (int i = len - 1, j = 0; i >= 0; i--, j++)
			num[j] = str[i] - '0';
	}
	CHugeInt(char *s) {
		Init();
		sscanf(s, "%s", str);
		str2num();
	}
	CHugeInt(int n) {
		Init();
		sprintf(str, "%d", n);
		str2num();
	}
	CHugeInt() { Init(); }
	friend CHugeInt operator+(const CHugeInt &h1, const CHugeInt &h2) {
		CHugeInt tmp;
		int inc = 0;
		for (int i = 0; i < 210; i++) {		//【Bug1】inc写在了%10外边可还行???
			tmp.num[i] = (h1.num[i] + h2.num[i]+ inc) % 10;
			inc = (h1.num[i] + h2.num[i]+inc) / 10;
		}
		return tmp;
	}
	friend ostream &operator<<(ostream &os, const CHugeInt &h) {
		int i = 209;
		for (; i>=0 && h.num[i] == 0; i--);	//【Bug2】条件语句执行从左到右！RE！
		if (i < 0) cout << 0;
		else for (; i >= 0; i--) cout << h.num[i];
		return os;
	}
	void operator+=(int n) {
		CHugeInt tmp(n), Ori(*this);
		int inc = 0;
		for (int i = 0; i < 210; i++) {
			num[i] = (Ori.num[i] + tmp.num[i] + inc) % 10;
			inc = (Ori.num[i] + tmp.num[i] + inc) / 10;
		}
	}
	CHugeInt &operator++() {
		*this += 1;
		return *this;
	}
	CHugeInt operator++(int) {
		CHugeInt tmp(*this);
		*this += 1;
		return tmp;
	}
};
int  main(){
	char s[210];
	int n;
	while (cin >> s >> n) {
		CHugeInt a(s);
		CHugeInt b(n);

		cout << a + b << endl;
		cout << n + a << endl;
		cout << a + n << endl;
		b += n;
		cout << ++b << endl;
		cout << b++ << endl;
		cout << b << endl;
		
	}
	return 0;
}