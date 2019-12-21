#include<iostream>
#include<string.h>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;
void jg(int n) {
	if (n == 1) { cout << "End" << endl; }
	else if (n % 2 != 0) {  //ÆæÊý
		cout << n << "*3+1=" << n * 3 + 1 << endl;
		jg(n * 3 + 1);
	}
	else {  //Å¼Êý
		cout << n << "/2=" << n / 2 << endl;
		jg(n / 2);
	}
}
int main() {
	int n;
	cin >> n;
	jg(n);

	return 0;
}