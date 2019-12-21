#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
class Complex {
	double real, imag;
	friend ostream &operator<<(ostream &os, const Complex &c);
	friend istream &operator>>(istream &is, Complex &c);
	friend Complex operator+(const Complex &a, const Complex &b);
public:
	Complex(double r_ = 0, double i_ = 0) :real(r_), imag(i_) {};
	Complex operator-(const Complex &c) {		//一般重载为成员函数
		return Complex(real - c.real, imag - c.imag);
	}
	operator double() { return real; }			//重载类型转换运算符,不需返回类型
	Complex &operator++() {		// ++c,返回原对象的引用
		real++; return *this;
	}
	Complex &operator++(int) {	// c++,返回的是tmp对象,而非原对象的引用！
		Complex tmp(*this);
		real++;
		return tmp;
	}
	Complex &operator--() {		// --c
		real--; return *this;
	}
	Complex &operator--(int) {	// c--,返回tmp对象！
		Complex tmp(*this);
		real--;
		return tmp;
	}
};
Complex operator+(const Complex &a, const Complex &b) {		//重载为全局,不常用
	return Complex(a.real + b.real, a.imag + b.imag);
}
ostream &operator<<(ostream &os, const Complex &c) {	//对Complex重载<<
	if (c.real == 0) {				//只能重载为全局函数,因为ostream类已写好了
		if (c.imag == 0)os << 0;
		else os << c.imag << 'i';
	}
	else {
		if (c.imag == 0) cout << c.real;
		else cout << c.real << "+" << c.imag << "i";
	}
	return os;
}
istream &operator>>(istream &is, Complex &c) {
	char s[10];
	is >> s;
	sscanf(s, "%lf+%lfi", &(c.real), &(c.imag));
	return is;
}
int main() {
	Complex a(4, 4), b(1, 1), c;
	cout << a + b << endl;
	cin >> c;
	cout << c << endl;
	double d = (double)a;	//显式类型转换：Complex-->double
	int i = a;			//隐式类型转换,该出现int处寻找把Complex解释为int的工具
	return 0;
}