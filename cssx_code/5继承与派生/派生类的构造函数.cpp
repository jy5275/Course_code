#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string.h>
#include<cstring>
#include<string>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;
class Skill {               //��ΪFlyBug�ĳ�Ա����
	int buff;
public:
	Skill(int b_) :buff(b_) {}
};

class Bug {
	int nLegs, nColor;
public:
	int nType = 0;
	//����������ĳ�ʼ���ӿ�
	Bug(int l_, int c_) :nLegs(l_), nColor(c_) {}
	void PrintBug() { cout << "Print from Bug" << endl; }
};

class FlyBug :public Bug {
	int nWings;
	Skill sk1, sk2;	//Skill��û���޲�Constructor,���ɶ���ʱҪ�ֶ���ʼ��
public:
	FlyBug(int l_, int c_, int w_) :
		Bug(l_, c_), nWings(w_), sk1(l_), sk2(c_) {}
	//�ó�ʼ���ĳ�Ա,���б��б���ȫ����ʼ������
	//������˳�򡿻���-->��Ա����-->������
	//������˳��������-->��Ա����-->����
};

int main() {
	Bug b1(1, 1), *pb1 = NULL;
	FlyBug fb1(2, 3, 4), *pfb1 = NULL;
	Bug &rfb1 = fb1, &rb1 = b1;
	pb1 = &fb1;		//���ϸ�ֵû����
	pfb1 = &fb1;	//���ϸ�ֵ
	b1.PrintBug();
	return 0;
}