#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<queue>
#include<sys/stat.h>
#include<string>
#include<iomanip>	//流操纵算子
using namespace std;
ostream &tab(ostream &o) {	//用户自定义流操纵算子(就是一个函数)
	return o << '\t';
}
int main() {
	int n = 13238, n1 = 13239, n2 = 13240;
	cout << hex << n << endl
		<< oct << n << endl
		<< dec << n << endl;	//设一次流操纵算子,一直起作用
	double pi = 3.1415926536;
	cout << setprecision(4) << pi <<endl<< n << endl;	//非定点输出
	cout << setw(12) << left << setfill('*') << n
		<< setw(12) << left << setfill('_') << n1
		<< setw(12) << left << setfill('=') << n2 << endl;
	
	//设置输入域宽setw(w) or cin.width(w),一次性起作用
	char str[10];
	cin.width(5);
	while (cin >> str) {	//设置width(5)后,只从stdin中读5个字符
		cout.width(5);		//设置width(5)后,只向stdout输出5个字符
		cout << str << endl;
		cin.width(5);	//每次都要设置！只起作用1次！
	}
	return 0;
}
