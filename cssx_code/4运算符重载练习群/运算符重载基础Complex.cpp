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
	Complex operator-(const Complex &c) {		//һ������Ϊ��Ա����
		return Complex(real - c.real, imag - c.imag);
	}
	operator double() { return real; }			//��������ת�������,���践������
	Complex &operator++() {		// ++c,����ԭ���������
		real++; return *this;
	}
	Complex &operator++(int) {	// c++,���ص���tmp����,����ԭ��������ã�
		Complex tmp(*this);
		real++;
		return tmp;
	}
	Complex &operator--() {		// --c
		real--; return *this;
	}
	Complex &operator--(int) {	// c--,����tmp����
		Complex tmp(*this);
		real--;
		return tmp;
	}
};
Complex operator+(const Complex &a, const Complex &b) {		//����Ϊȫ��,������
	return Complex(a.real + b.real, a.imag + b.imag);
}
ostream &operator<<(ostream &os, const Complex &c) {	//��Complex����<<
	if (c.real == 0) {				//ֻ������Ϊȫ�ֺ���,��Ϊostream����д����
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
	double d = (double)a;	//��ʽ����ת����Complex-->double
	int i = a;			//��ʽ����ת��,�ó���int��Ѱ�Ұ�Complex����Ϊint�Ĺ���
	return 0;
}