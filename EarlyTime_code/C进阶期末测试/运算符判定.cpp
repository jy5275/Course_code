#include<iostream>
#include<string.h>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;
int main() {
	int a, b, c;
	char d1, d2;
	cin >> a >> d1 >> b >> d2 >> c;
	if (a + b == c)cout << '+';
	else if (a - b == c)cout << '-';
	else if (a*b == c)cout << '*';
	else if (a / b == c)cout << '/';
	else if (a%b == c)cout << '%';
	else cout << "error";


	return 0;
}