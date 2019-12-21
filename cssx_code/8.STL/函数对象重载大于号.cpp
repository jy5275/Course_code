#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<cmath>
#include<vector>
#include<list>
#include<deque>
#include<functional>
#include<algorithm>
using namespace std;
class MyLess {		//【自定义函数对象】【int】按个位比大小
public:
	bool operator()(const int c1, const int c2) {
		return (c1 % 10) < (c2 % 10);
	}
};
template<class T>
class Greater {		//【自定义函数对象】比谁大
public:
	bool operator()(const T &x, const T &y) {
		return x > y;
	}
};
bool MyLess(const int a1, const int a2) { return a1 % 10 < a2 % 10; }
template<class _It>
void Print(_It F, _It L) {
	for (; F != L; ++F) cout << *F << ","; cout << endl;
}
int main() {
	const int SIZE = 5;
	int a[SIZE] = { 5,21,14,2,3 };
	list<int> lst(a, a + SIZE);
	lst.sort(MyLess);	//以函数指针MyLess为参数, 返回true则为小
	Print(lst.begin(), lst.end());
	lst.sort(Greater<int>());  //以函数对象Greater<int>来比大小,看相反的绝对大小
	Print(lst.begin(), lst.end());
	return 0;
}
