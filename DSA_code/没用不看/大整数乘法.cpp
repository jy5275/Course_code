#include "include.h"
using namespace std;
const int MAX = 202;
class CLarge {
public:
	int val[MAX] = { 0 }, len = 0;
	CLarge() {}
	void SetLen();
	void Exp(const int n);
};
void CLarge::SetLen() {   //更新val位数
	int p = MAX - 1;
	while (val[p] == 0) { p--; }
	len = p + 1;
}
void CLarge::Exp(const int n) {   //大数*10^n
	for (int p = len + n; p >= 0; p--) {
		if (p - n < 0) val[p] = 0;
		else val[p] = val[p - n];
	} SetLen();
}
CLarge operator*(const CLarge large, const int small) {  //大数*个位数
	CLarge ans;
	int adv_prev = 0;
	for (int i = 0; i <= large.len; i++) {
		int val_tmp = large.val[i] * small + adv_prev;
		ans.val[i] = val_tmp % 10;
		adv_prev = val_tmp / 10;
	} ans.SetLen();
	return ans;
}
CLarge operator+(const CLarge l1, const CLarge l2) {   //大数+大数
	CLarge ans; 
	int newLen = max(l1.len, l2.len) + 1, adv_prev = 0;
	for (int i = 0; i < newLen; i++) {
		int val_tmp = l1.val[i] + l2.val[i] + adv_prev;
		ans.val[i] = val_tmp % 10;
		adv_prev = val_tmp / 10;
	} ans.SetLen();
	return ans;
}
CLarge operator*(const CLarge l1, const CLarge l2) {  //大数*大数
	CLarge ans;
	for (int i = 0; i < l2.len; i++) {
		CLarge tmp = l1 * l2.val[i];
		tmp.Exp(i);
		ans = ans + tmp;
		ans.SetLen();
	}
	return ans;
}
istream &operator>>(istream &i, CLarge &l) {
	char tmp[MAX]; i >> tmp;
	l.len = strlen(tmp);
	for (int i = l.len - 1, j = 0; i >= 0; i--, j++) {
		l.val[j] = tmp[i] - '0';
	}
	return i;
}
ostream &operator<<(ostream &o, const CLarge &l) {
	for (int i = l.len - 1; i >= 0; i--) {
		o << l.val[i];
	}
	return o;
}
int main() {
	CLarge m1, m2;
	cin >> m1 >> m2;
	cout << m1 * m2 << endl;
	return 0;
}
