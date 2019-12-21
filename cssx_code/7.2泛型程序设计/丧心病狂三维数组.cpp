#define _CRT_SECURE_NO_WARNINGS    
#include <iostream>
#include <iomanip> 
#include <cstring>
using namespace std;

template <class T>
class CArray3D{
	// 在此处补充你的代码
public:
	class CArray2D {
	public:
		int r, c;
		T *p;
		T *operator[](int x) {
			return p + x*c;
		}
		operator T*() {
			return p;
		}
	};

	CArray2D *p2 = NULL;

	int l, r, c;
	CArray3D(int l_, int r_, int c_) :l(l_), r(r_), c(c_){
		p2 = new CArray2D[l];
		for (int i = 0; i < l; i++) {
			p2[i].r = r; p2[i].c = c;
			p2[i].p = new T[r*c];
		}
	}

	CArray2D &operator[](int lin) {
		return p2[lin];
	}
};

CArray3D<int> a(3, 4, 5);
CArray3D<double> b(3, 2, 2);

void PrintA(){
	for (int i = 0; i < 3; ++i) {
		cout << "layer " << i << ":" << endl;
		for (int j = 0; j < 4; ++j) {
			for (int k = 0; k < 5; ++k)
				cout << a[i][j][k] << ",";
			cout << endl;
		}
	}
}
void PrintB(){
	for (int i = 0; i < 3; ++i) {
		cout << "layer " << i << ":" << endl;
		for (int j = 0; j < 2; ++j) {
			for (int k = 0; k < 2; ++k)
				cout << b[i][j][k] << ",";
			cout << endl;
		}
	}
}

int main(){
	int No = 0;
	for (int i = 0; i < 3; ++i) {
		a[i];
		for (int j = 0; j < 4; ++j) {
			a[j][i];
			for (int k = 0; k < 5; ++k)
				a[i][j][k] = No++;
			a[j][i][i];
		}
	}
	PrintA();
	memset(a[1], -1, 20 * sizeof(int));
	memset(a[1], -1, 20 * sizeof(int));
	PrintA();
	memset(a[1][1], 0, 5 * sizeof(int));
	PrintA();

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 2; ++j)
			for (int k = 0; k < 2; ++k)
				b[i][j][k] = 10.0 / (i + j + k + 1);
	PrintB();
	int n = a[0][1][2];
	double f = b[0][1][1];
	cout << "****" << endl;
	cout << n << "," << f << endl;
	return 0;
}