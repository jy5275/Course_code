#include<iostream>
#include<string.h>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;
int main() {
	int digit, m, m_test,k, i, j, cnt = 0;
	cin >> m >> k;  m_test = m;
	while (m_test != 0) {
		digit = m_test % 10;
		if (digit == 3)cnt++;
		m_test /= 10;
	}
	if (cnt == k && m % 19 == 0)
		cout << "YES";
	else
		cout << "NO";

	return 0;
}