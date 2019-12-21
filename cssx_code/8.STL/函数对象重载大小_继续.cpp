#include<iostream>
#include<string.h>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<fstream>
#include<vector>
#include<list>
#include<deque>
#include<algorithm>
using namespace std;
class MyLess {
public:
	bool operator()(const int c1, const int c2) {
		//自定义：谁的个位数小,谁就“小”
		return (bool)((c1 % 10) < (c2 % 10));
	}
};

bool MyCompare(const int a1, const int a2) {
	if ((a1 % 10) < (a2 % 10)) return false;
	else return true;     //谁的个位数大，谁就算“小”
}

template<class InIt, class op>
InIt MyMax(InIt F, InIt L, op _op) {
	static InIt tmpMax = first;
	for (; F != L; ++F) {
		if (op(*tmpMax, *F))
			tmpMax = F;
	}
	return tmpMax;
}
int main() {
	const int SIZE = 5;
	int a[] = { 35,7,13,19,12 };
	cout << *MyMax(a, a + 5, MyLess()) << endl;  //MyLess是一个函数对象
	cout << *MyMax(a, a + 5, MyCompare) << endl; //MyCompare是一个函数指针
	return 0;
}
