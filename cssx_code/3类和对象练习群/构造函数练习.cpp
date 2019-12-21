#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string.h>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;
class Complex {
public:
	double real, imag;
	void get_num(int r_, int i_) {
		real = r_; imag = i_;
	}
	Complex(const Complex &c) {         //复制构造函数，故意乱写，使得复制出错
		real = -1; imag = -1;
	}
	Complex(int r_ = 0, int i_ = 0) {   //一般构造函数，允许参数缺省
		real = r_, imag = i_;
	}
};
void Func1(Complex c) {
	//经【复制构造函数】初始化的c(错误初始化)
	cout << "Func1: " << c.real << '+' << c.imag << 'i' << endl;
}
void Func2(Complex &c) {
	c.get_num(19, 19);
	cout << "Func2: " << c.real << '+' << c.imag << 'i' << endl;
}
int main() {
	Complex c1(1);
	Complex c2(c1);
	Func1(c1); Func2(c1);

	return 0;
}