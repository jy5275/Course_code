#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string.h>
#include<cstring>
#include<string>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;
class Skill {               //作为FlyBug的成员对象
	int buff;
public:
	Skill(int b_) :buff(b_) {}
};

class Bug {
	int nLegs, nColor;
public:
	int nType = 0;
	//留给派生类的初始化接口
	Bug(int l_, int c_) :nLegs(l_), nColor(c_) {}
	void PrintBug() { cout << "Print from Bug" << endl; }
};

class FlyBug :public Bug {
	int nWings;
	Skill sk1, sk2;	//Skill类没有无参Constructor,生成对象时要手动初始化
public:
	FlyBug(int l_, int c_, int w_) :
		Bug(l_, c_), nWings(w_), sk1(l_), sk2(c_) {}
	//该初始化的成员,在列表中必须全部初始化掉！
	//【构造顺序】基类-->成员对象-->派生类
	//【析构顺序】派生类-->成员对象-->基类
};

int main() {
	Bug b1(1, 1), *pb1 = NULL;
	FlyBug fb1(2, 3, 4), *pfb1 = NULL;
	Bug &rfb1 = fb1, &rb1 = b1;
	pb1 = &fb1;		//向上赋值没问题
	pfb1 = &fb1;	//向上赋值
	b1.PrintBug();
	return 0;
}