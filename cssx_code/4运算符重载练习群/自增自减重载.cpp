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
	CDemo(int i=0):n(i){}    //���캯��
	CDemo &operator++() {    //����ǰ��++ΪCDemo��Ա����
		n++;
		return *this;
	}
	CDemo &operator++(int k) {  //���غ���++ΪCDemo��Ա����
		CDemo tmp(*this);
		n++;
		return tmp;
	}
	operator int(){ return n; }  //ǿת,��д����ֵ����,ʵ���ϵķ���ֵ���ͼ�ǿת�����������
	friend CDemo &operator--(CDemo &);
	friend CDemo &operator--(CDemo &, int);
};
CDemo &operator--(CDemo &d) {   //����ǰ��--Ϊȫ�ֺ���
	d.n--; 
	return d;
}
CDemo &operator--(CDemo &d, int) {  //���غ���--Ϊȫ�ֺ���,����Ǹ�int��ɶ����Ҫ,
	CDemo tmp(d);                  //������ǣ�ʹ�ú���������ǰ��--���غ���
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