#include<iostream>
#include<vector>
#include<string>
#include<set>
#include<cmath>
#include<list>
#include<memory>
#include<map>
#include<stdexcept>
#include<algorithm>
#include<queue>
#include<iomanip>
#include<fstream>
#include<unordered_map>
#include<regex>
using namespace std;
int main() {
	double m, n;
	cin >> m >> n;
	try {
		cout << "before dividing" << endl;
		if (n == 0) throw - 1;  //抛出int类型异常，抛出后立即终止try块运行！
		else if (m == 0) throw - 1.0;  //抛出double型异常
		else cout << m / n << endl;
		cout << "after dividing" << endl;
	}
	catch (double d) {       //如果try块中没有抛出任何异常，所有catch块都不会被执行
		cout << "catch(double)" << d << endl;
	}
	catch (int e) {
		cout << "catch(int)" << e << endl;
	}
	catch (...) {
		cout << "catch(...)" << endl;   //可以捕获任何异常！
	}

	//bad_cast类型转换时会抛出此异常
	//bad_alloc内存不够分配失败
	try { char *p = new char[0x7fffffff]; }
	catch (bad_alloc &e) { cerr << e.what(); }

	//out_of_range容器越界时会抛出此异常
	vector<int> v(10);
	try { v.at(100) = 100; }
	catch (out_of_range &e) { cerr << e.what() << endl; }
	string s = "hello";
	try { char c = s.at(100); }
	catch (out_of_range &e) { cerr << e.what() << endl; }
	return 0;
}
