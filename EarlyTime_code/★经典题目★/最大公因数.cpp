#include<iostream>
using namespace std;
int gys(int x, int y) {
	int tmp,d;
	if (x > y) { tmp = y; y = x; x = tmp; }
	d = y - x;
	if (d <= 0) return y;
	else if (d == x) return d;
	else return gys(d, x);

}
int main() {
	int x, y;
	while (1) {
		cin >> x >> y;
		cout << gys(x, y) << endl;
	}
	return 0;
}