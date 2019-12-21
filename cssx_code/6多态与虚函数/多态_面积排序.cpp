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
public:		//��ʹ�Ǳ���ʱ����ΪCShape��ָ�룬����ʱ����Ϊ����Shape,���Ƕ�̬��
	void fun1() { PrintInfo(); }	//ִ���������PrintInfo��
	virtual double Area() { cout << "Never reach here!"; }
	virtual void PrintInfo() { cout << "Never reach here!"; };
};
class CRectangle :public CShape {
	int w, h;
public:
	CRectangle() { cin >> w >> h; }
	double Area() { return w * h; }  //���廯
	void PrintInfo() { cout << "Rectangle:" << Area() << endl; }    //���廯
};
class CCircle :public CShape {
	int r;
public:
	CCircle() { cin >> r; }
	double Area() { return 3.1416*r*r; }       //���廯
	void PrintInfo() { cout << "Circle:" << Area() << endl; }        //���廯
};
class CTriangle :public CShape {
	int a, b, c;
public:
	CTriangle() { cin >> a >> b >> c; }
	double Area() {         //���廯
		double p = (a + b + c) / 2.0;
		return sqrt(p*(p - a)*(p - b)*(p - c));
	}
	void PrintInfo() { cout << "Triangle:" << Area() << endl; }       //���廯
};
class CPentagon :public CShape {
	int a, b, c, d, e;
public:
	double Area() {          //���廯
		//...???
		return 0;
	}
	void PrintInfo() { cout << "Pentagon:" << Area() << endl; }     //���廯
};
int MyCompare(const void *s1, const void *s2) {		//s1,s2ָ����pShape������ĳ����Ԫ��
	CShape **p1 = (CShape**)s1;		//p1,s1����"ָ��ptr��ptr"
	CShape **p2 = (CShape**)s2;
	int a1 = (*p1)->Area();		//*p1ָ��һ��Shape,����ʱ������ȷ�����õ��ǻ���or��������麯��
	int a2 = (*p2)->Area();		//������������ȷ�����ⷴӳ�˶�̬�ĺ���"��̬����"
	if (a1 < a2)return -1;		//����-1����ԭ�򲻱�
	else if (a1 > a2)return 1;	//����1������Ԫ��
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
		case 'C':pC = new CCircle;   //��������󸳸���������������Զ�ʧ��
			pShapes[i] = pC; break;  //������ָ�븳������ָ�룬�������Ի��ڣ������������ˣ�ǿת�������
		case 'T':pT = new CTriangle;
			pShapes[i] = pT; break;
		case 'P':pP = new CPentagon;
			pShapes[i] = pP; break;
		}
	}
	qsort(pShapes, n, sizeof(CShape*), MyCompare);   //qsort(��ʼָ��,Ԫ�ظ���,��Ԫ�س���,������)
	for (i = 0; i < n; i++)
		pShapes[i]->PrintInfo();
	delete[]pShapes;
	return 0;
}