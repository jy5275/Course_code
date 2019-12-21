#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
class myclass {
public:
	virtual void hello() { cout << "hello from myclass" << endl; }
	virtual void bye() { cout << "bye from myclass" << endl; }
	//virtual myclass(){cout<<"bye from myclass" }
};
class son :public myclass {
public:
	void hello() { cout << "hello from son" << endl; }
	void test() { cout << "test from son" << endl; }	//����virtual�����Ƕ�̬
	son() { hello(); }		//�ڹ���/���������е���virtual���Ƕ�̬��
	~son() { bye(); }		//�Լ�û��bye��������
};
class grandson :public son {
public:
	void hello() { cout << "hello from grandson" << endl; }		//�Զ���Ϊvirtual
	void bye() { cout << "bye from grandson" << endl; }
	void test() { cout << "test from grandson" << endl; }
	grandson() { cout << "constructing grandson" << endl; }
	~grandson() { cout << "destructing grandson" << endl; }
};
int main() {
	son *pson = new grandson();  //ͨ������ָ��delete����ʹָ�����������
	pson->hello();		//��̬��ִ������ʱ����(grandson)��virtual
	pson->test();		//���Ƕ�̬
	delete pson;               //ֻ�ܵ��û��������������������޷�������
	return 0;
}