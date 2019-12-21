#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string.h>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;
struct CCar {
public:
	int price = 0;
};
void SetPrice(struct CCar *pThis, int p) {
	pThis->price = p;
}
class Demo {
	int id;
public:
	Demo(int i) {
		id = i;
		cout << "id=" << id << " constructed" << endl;
	}
	~Demo() {
		cout << "id=" << id << " destructed" << endl;
	}
};
Demo d1(1);
void Func() {
	static Demo d2(2);
	Demo d3(3);
	cout << "func" << endl;
}
class Ctest {
public:
	~Ctest() { cout << "Destructor called" << endl; }
};
Ctest fun(Ctest sobj) {
	return sobj;	//函数执行完毕,形参对象消亡
}
int main() {
	Ctest *pTest = new Ctest[3];
	//delete[]pTest;
	Ctest obj;
	obj = fun(obj);	//返回值临时对象马上就消亡
	
	Demo d4(4);
	d4 = 6;			//左式执行类型转换构造函数,生成临时对象
	cout << "main" << endl;
	{ Demo d5(5); }
	Func();

	cout << "End main" << endl;

	return 0;
}