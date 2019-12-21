#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string.h>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;
class CRectangle {
	int w, h;
	static int nTotalArea, nTotalNumber;
public:
	CRectangle() {}
	CRectangle(int w_, int h_) :w(w_), h(h_) {
		nTotalNumber++;
		nTotalArea += w * h;
	}
	CRectangle(const CRectangle &r) {
		w = r.w; h = r.h;
		nTotalArea += w * h;
		nTotalNumber++;
	}
	~CRectangle() {
		nTotalArea -= w * h;
		nTotalNumber--;
	}
	static void PrintTotal() { cout << nTotalArea << ", " << nTotalNumber << endl; }
	void Init(int w_, int h_) { w = w_; h = h_; }
	int Area() { return w * h; }
	int Perimeter() { return 2 * (w + h); }
};
int CRectangle::nTotalArea = 0;
int CRectangle::nTotalNumber = 0;
void printRectangle(CRectangle &r) {    //引用式形参，高级授权
	cout << r.Area() << ',' << r.Perimeter();
}
int main() {
	int w, h;
	CRectangle r1, r2;
	cin >> w >> h;
	r1.Init(w, h);
	cout << r1.Area() << endl << r1.Perimeter() << endl;
	CRectangle::PrintTotal();

	CRectangle *p1 = &r1, *p2 = &r2;
	p2->Init(3, 4);

	CRectangle &rr = r1;
	rr.Init(3, 4);
	printRectangle(rr);

	return 0;
}