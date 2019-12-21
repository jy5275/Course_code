#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string.h>
#include<cstring>
#include<string>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;
class CShape {
public:		//即使是编译时类型为CShape的指针，运行时类型为具体Shape,仍是多态！
	void fun1() { PrintInfo(); }	//执行派生类的PrintInfo！
	virtual double Area() { cout << "Never reach here!"; }
	virtual void PrintInfo() { cout << "Never reach here!"; };
};
class CRectangle :public CShape {
	int w, h;
public:
	CRectangle() { cin >> w >> h; }
	double Area() { return w * h; }  //具体化
	void PrintInfo() { cout << "Rectangle:" << Area() << endl; }    //具体化
};
class CCircle :public CShape {
	int r;
public:
	CCircle() { cin >> r; }
	double Area() { return 3.1416*r*r; }       //具体化
	void PrintInfo() { cout << "Circle:" << Area() << endl; }        //具体化
};
class CTriangle :public CShape {
	int a, b, c;
public:
	CTriangle() { cin >> a >> b >> c; }
	double Area() {         //具体化
		double p = (a + b + c) / 2.0;
		return sqrt(p*(p - a)*(p - b)*(p - c));
	}
	void PrintInfo() { cout << "Triangle:" << Area() << endl; }       //具体化
};
class CPentagon :public CShape {
	int a, b, c, d, e;
public:
	double Area() {          //具体化
		//...???
		return 0;
	}
	void PrintInfo() { cout << "Pentagon:" << Area() << endl; }     //具体化
};
int MyCompare(const void *s1, const void *s2) {		//s1,s2指向了pShape数组中某两个元素
	CShape **p1 = (CShape**)s1;		//p1,s1都是"指向ptr的ptr"
	CShape **p2 = (CShape**)s2;
	int a1 = (*p1)->Area();		//*p1指向一个Shape,编译时并不能确定调用的是基类or派生类的虚函数
	int a2 = (*p2)->Area();		//运行起来才能确定，这反映了多态的核心"动态联编"
	if (a1 < a2)return -1;		//返回-1保持原序不变
	else if (a1 > a2)return 1;	//返回1交换两元素
	else return 0;
}
int main() {
	CShape *pShapes[100];
	int n, i; cin >> n;
	CPentagon *pP = NULL; CRectangle *pR = NULL; CCircle *pC = NULL; CTriangle *pT = NULL;
	for (i = 0; i < n; i++) {
		char c; cin >> c;
		switch (c) {
		case 'R':pR = new CRectangle;
			pShapes[i] = pR; break;
		case 'C':pC = new CCircle;   //派生类对象赋给基类对象，派生属性丢失；
			pShapes[i] = pC; break;  //派生类指针赋给基类指针，派生属性还在！但隐藏起来了，强转后才能用
		case 'T':pT = new CTriangle;
			pShapes[i] = pT; break;
		case 'P':pP = new CPentagon;
			pShapes[i] = pP; break;
		}
	}
	qsort(pShapes, n, sizeof(CShape*), MyCompare);   //qsort(起始指针,元素个数,单元素长度,排序函数)
	for (i = 0; i < n; i++)
		pShapes[i]->PrintInfo();
	delete[]pShapes;
	return 0;
}