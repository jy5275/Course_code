#include<iostream>
#include<ostream>
#include<string.h>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;
class CDemo {
	int n;
public:
	CDemo(int i=0):n(i){}    //构造函数
	CDemo &operator++() {    //重载前置++为CDemo成员函数
		n++;
		return *this;
	}
	CDemo &operator++(int k) {  //重载后置++为CDemo成员函数
		CDemo tmp(*this);
		n++;
		return tmp;
	}
	operator int(){ return n; }  //强转,不写返回值类型,实际上的返回值类型即强转符代表的类型
	friend CDemo &operator--(CDemo &);
	friend CDemo &operator--(CDemo &, int);
};
CDemo &operator--(CDemo &d) {   //重载前置--为全局函数
	d.n--; 
	return d;
}
CDemo &operator--(CDemo &d, int) {  //重载后置--为全局函数,后边那个int是啥不重要,
	CDemo tmp(d);                  //仅做标记，使该函数区别于前置--重载函数
	d.n--; 
	return tmp;
}
int main() {
	CDemo d(5);
	cout << d++ << endl;
	cout << ++d << endl;
	int a=(int)d;
	return 0;
}