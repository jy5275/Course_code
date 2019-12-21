#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<list>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;
union i_f {
	int i;
	float f;
};
float int2float(int x) {
	i_f tmp;
	tmp.i = x;
	return tmp.f;
}
int main() {
	for (int i = 0; i < 0xff; i++) {
		cout << i << ": " << (char)i << endl;
	}
	cout << int2float(255) << endl;
	return 0;
}