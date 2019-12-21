#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string.h>
#include<cstring>
#include<cmath>
#include<xstring>
#include<iomanip>
#include<fstream>
using namespace std;
class String {
	char *str;
public:
	String() :str(NULL) {}
	const char *c_str() { return str; }   //外界对String类有效内容的唯一调用途径

	String(const char *s) {		//类型转换构造函数：用const char*初始化String
		if (str) delete[]str;
		str = new char[strlen(s) + 1];
		strcpy(str, s);
	}

	String(const String &s) {    //复制构造函数【深复制】
		if (!s.str) str = NULL;
		else {
			str = new char[strlen(s.str) + 1];
			strcpy(str, s.str);
		}
	}

	String &operator=(const char *s) {    //'='重载1,用于char*对String赋值
		if (str)delete[]str;
		if (!s)str = NULL;
		else {
			str = new char[strlen(s) + 1];
			strcpy(str, s);
		}
		cout << "'=' functions on " << str << endl;
		return *this;
	}

	String &operator=(const String &s) {	//'='重载2,用于String相互赋值【深复制】
		if (str == s.str) return *this;		//避免自己给自己赋值
		if (str)delete[]str;
		if (!s.str)str = NULL;
		else {
			str = new char[strlen(s.str) + 1];
			strcpy(str, s.str);         //str是char*,s是const char*
		}
		return *this;
	}

	~String() {                  //String析构函数,鸡肋
		if (str)delete[]str;
	}
};
int main() {
	String s1, s2, s3;
	s1 = "Good Luck,";
	s3 = s2 = s1;   //连续等号必须把'='重载函数返回类型设为String&,否则可设为void
	return 0;
}