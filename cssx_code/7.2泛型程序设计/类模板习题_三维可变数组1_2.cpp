#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<cmath>
using namespace std;
int column = 0, row = 0, stratum = 0;  //Q：new内存如何同时分配多个+初始化之？Impossible！

template<class T>
class CArray1D {
	T *pT = NULL;
public:
	CArray1D() { pT = new T[column]; }
	T &operator[](int i) { return pT[i]; }
};

template<class T>
class CArray2D {
	CArray1D<T> *pArray1D = NULL;
public:
	CArray2D() { pArray1D = new CArray1D<T>[row]; }
	CArray1D<T> operator[](int i) { return pArray1D[i]; }
};

template<class T>
class CArray3D {
	CArray2D<T> *pArray2D = NULL;
public:
	CArray3D(int s_, int r_, int c_) {
		stratum = s_, column = c_, row = r_;
		pArray2D = new CArray2D<T>[stratum];
	}
	CArray2D<T> operator[](int i) { return pArray2D[i]; }
};

//-----------------------------------------------------------------------
int main() {
	CArray3D<int> a(3, 4, 5);
	int No = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 4; j++)
			for (int k = 0; k < 5; k++)
				a[i][j][k] = No++;
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 4; ++j)
			for (int k = 0; k < 5; ++k)
				cout << a[i][j][k] << ",";
	return 0;
}