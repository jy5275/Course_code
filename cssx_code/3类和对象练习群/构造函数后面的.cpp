#include<iostream>
#include<string.h>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;
class CTyre {
	int radius, width;
public:
	CTyre(int r,int w):radius(r),width(w){}  //初始化列表，风格更好
};
class CEngine {
};
class CDriver {
public:
	void ModifyCar(CCar *pCar) {
		pCar->price += 1000;
	}
	friend class CCar;  //相互免签
};
class CCar {
	int price;
	CTyre tyre;
	CEngine engine;   //CCar的部分成员变量是CTyre与CEngine的对象
public:
	CCar(int p, int tr, int w) :price(p), tyre(tr, w){};  //CCar的构造函数
	//用初始化列表，在构造函数参数表之后，使用冒号定义一系列成员变量
	//用每个成员变量后边的()里的参数表来初始化相应成员变量
	friend int MostExpensiveCar(CCar cars[], int total);  //声明友元函数
	//MostExpensiveCar函数不属于任何一类，相当于无国籍人士，对其给予免签
	//？为何不兼容？friend void CDriver::ModifyCar(CCar *pCar);
	friend class CDriver;    //声明友元函数，权限更大，
	                         //类如主权国家，友元类相当于免签
};  //汽车类成了封闭类
//先调用成员对象的构造函数，再调用封闭类的构造函数
//析构函数按照栈原则调用
//构造函数调用顺序遵循在封闭类中的声明顺序，而非封闭类构造函数的初始化顺序
int MostExpensiveCar(CCar cars[], int total) {
	int tmpMax = -1;
	for (int i = 0; i < total; ++i) {
		if (cars[i].price > tmpMax) tmpMax = cars[i].price;
	}
	return tmpMax;
}
int main() {
	CCar car(20000, 17, 225);   
	//封闭类不自己写构造函数会导致编译错误,编译器不知道该怎么初始化成员对象
	return 0;
}