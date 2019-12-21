#include <iostream>
using namespace std;
class CStudent {
private:
	int nVal;
public:
	virtual void Fun() { cout << "Student::Fun" << endl; }
	virtual void Do() { cout << "Student::Do" << endl; }
};
class CGraduate :public CStudent{
public:
	virtual void Do() { cout << "Graduate::Do" << endl; }
	virtual void Fun() { cout << "Graduate::Fun" << endl; }
};
class CUndergraduate :public CStudent {
public:
	virtual void Do() { cout << "Undergraduate::Do" << endl; }
	virtual void Fun() { cout << "Undergraduate::Fun" << endl; }
};
class CFreshman :public CUndergraduate {
public:
	void Do() { cout << "Freshman::Do" << endl; }
	void Fun() { cout << "Freshman::Fun" << endl; }
};
void Call(CStudent *p) {
	p->Fun();  p->Do();   //ָ��ʽ���������������Լ��ģ�����virtual������Ҽ̳е�
}
int main() {
	CStudent *pS = new CFreshman;
	Call(pS);
	return 0;
}