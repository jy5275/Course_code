#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cmath>
#include<string>
#include<fstream>
using namespace std;
class CStudent {
protected:		//派生类成员函数可访问【当前对象】的基类protected！
	string name, id;		//基类中的private,派生类中不能访问！
	int age;
	char gender;
public:
	virtual void PrintInfo() {
		printf("Name:%s, ID:%s, Age:%d, Gender:%c\n", name.c_str(), id.c_str(), age, gender);
	}
	void SetInfo(const string &n_, const string &id_, int age_, char g_){
		name = n_; id = id_; age = age_; gender = g_;
	}
	string GetName() { return name; }
};

class CUndergraduate:public CStudent {
	string department;
public:
	void QualifiedForBaoyan() {
		cout << GetName() << " qualified for baoyan" << endl;
	}
	void PrintInfo() {	//【覆盖】派生类对基类方法的覆盖，同名同参数表
		CStudent::PrintInfo();	//告诉compiler：调用基类同名方法
		cout << "Department: " << department << endl;
	}
	void SetInfo(const string &n_, const string &id_, int age_, 
		char g_, const string &d_) {	//这不是覆盖！参数表不同
		CStudent::SetInfo(n_, id_, age_, g_);
		department = d_;
	}
};

class CProfessor;
class CGraduate :public CStudent {
	int nDepartment;
	CProfessor *mentor = NULL;
public:
	int countSalary(){}
};

class CProfessor {
	CGraduate *stu[10] = { NULL };
};

int main() {
	CStudent *p = new CUndergraduate();
	CUndergraduate *pu = (CUndergraduate*)p;
	pu->SetInfo("JY", "1600013239", 21, 'M', "Computer Science");
	pu->QualifiedForBaoyan();
	p->PrintInfo();
	cout << "main addr:" << (void*)main;
	// printf("%p\n", main);
	return 0;
}