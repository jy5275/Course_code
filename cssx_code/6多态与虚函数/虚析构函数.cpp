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
	void test() { cout << "test from son" << endl; }	//不是virtual！不是多态
	son() { hello(); }		//在构造/析构函数中调用virtual不是多态！
	~son() { bye(); }		//自己没有bye，向上找
};
class grandson :public son {
public:
	void hello() { cout << "hello from grandson" << endl; }		//自动成为virtual
	void bye() { cout << "bye from grandson" << endl; }
	void test() { cout << "test from grandson" << endl; }
	grandson() { cout << "constructing grandson" << endl; }
	~grandson() { cout << "destructing grandson" << endl; }
};
int main() {
	son *pson = new grandson();  //通过基类指针delete（即使指向派生类对象）
	pson->hello();		//多态！执行运行时类型(grandson)的virtual
	pson->test();		//不是多态
	delete pson;               //只能调用基类析构函数，派生类无法析构！
	return 0;
}