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
	CTyre(int r,int w):radius(r),width(w){}  //��ʼ���б�������
};
class CEngine {
};
class CDriver {
public:
	void ModifyCar(CCar *pCar) {
		pCar->price += 1000;
	}
	friend class CCar;  //�໥��ǩ
};
class CCar {
	int price;
	CTyre tyre;
	CEngine engine;   //CCar�Ĳ��ֳ�Ա������CTyre��CEngine�Ķ���
public:
	CCar(int p, int tr, int w) :price(p), tyre(tr, w){};  //CCar�Ĺ��캯��
	//�ó�ʼ���б��ڹ��캯��������֮��ʹ��ð�Ŷ���һϵ�г�Ա����
	//��ÿ����Ա������ߵ�()��Ĳ���������ʼ����Ӧ��Ա����
	friend int MostExpensiveCar(CCar cars[], int total);  //������Ԫ����
	//MostExpensiveCar�����������κ�һ�࣬�൱���޹�����ʿ�����������ǩ
	//��Ϊ�β����ݣ�friend void CDriver::ModifyCar(CCar *pCar);
	friend class CDriver;    //������Ԫ������Ȩ�޸���
	                         //������Ȩ���ң���Ԫ���൱����ǩ
};  //��������˷����
//�ȵ��ó�Ա����Ĺ��캯�����ٵ��÷����Ĺ��캯��
//������������ջԭ�����
//���캯������˳����ѭ�ڷ�����е�����˳�򣬶��Ƿ���๹�캯���ĳ�ʼ��˳��
int MostExpensiveCar(CCar cars[], int total) {
	int tmpMax = -1;
	for (int i = 0; i < total; ++i) {
		if (cars[i].price > tmpMax) tmpMax = cars[i].price;
	}
	return tmpMax;
}
int main() {
	CCar car(20000, 17, 225);   
	//����಻�Լ�д���캯���ᵼ�±������,��������֪������ô��ʼ����Ա����
	return 0;
}