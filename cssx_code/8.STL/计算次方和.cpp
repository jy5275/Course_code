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
int sumSquares(int total, int value) {   //把参数2的平方加到参数1上
	return total + value * value;
}
template<class T>
void PrintInterval(T first, T last) {  //输入未知类型迭代器始末，输出之间的元素
	for (; first != last; ++first) cout << *first << " ";
	cout << endl;
}
template<class T>
class sumPowers {
	int power;
public:
	sumPowers(int p_) :power(p_) {}
	const T operator()(const T &total, const T &value) { //把参数2的power次方加到参数1上
		T v = value;
		for (int i = 0; i < power - 1; ++i) v = v * value;  //如果power=0还真没法搞！
		return total + v;
	}
};
template<class _Tp, class _InputIterator, class _op>
_Tp accumulate(_InputIterator __first, _InputIterator __last, _Tp __init, _op __op) {
	for (; __first != __last; __first++)
		__init = __op(__init, *__first);    //调用op函数,算*first的x次方,加在init上
	return __init;
}
using namespace std;
int main() {
	const int SIZE = 10;
	int a1[] = { 1,2,3,4,5,6,7,8,9,10 };
	vector<int> v(a1, a1 + SIZE);
	cout << "1)"; PrintInterval(v.begin(), v.end());
	int result = accumulate(v.begin(), v.end(), 0, sumSquares);
	cout << "2)平方和：" << result << endl;
	result = accumulate(v.begin(), v.end(), 0, sumPowers<int>(3));
	cout << "3)立方和：" << result << endl;
	result = accumulate(v.begin(), v.end(), 0, sumPowers<int>(4));
	cout << "4)四次方和：" << result << endl;
	return 0;
}
