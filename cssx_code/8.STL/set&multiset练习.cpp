#define _CRT_SECURE_NO_WARNINGS    
#include<iostream>
#include<string>
#include<cmath>
#include<set>
#include<algorithm>
#include<map>
using namespace std;
//map/multimap容器(模板对象)里都放着pair模板类的对象！从大到小放的！
//set相对于multiset，insert可能不成功，多了返回值

template<class _T1, class _T2>
struct MyPair {     //模板类？
	typedef _T1 first_type;
	typedef _T2 second_type;
	_T1 first;
	_T2 second;
	MyPair() : first(), second() {}    //无参构造函数！
	MyPair(const _T1 &__a, const _T2 &__b) :first(__a), second(__b) {	}
	template<class _U1, class _U2>   //构造函数写成函数模板！复制构造函数？？？
	MyPair(const MyPair<_U1, _U2>&__p) : first(__p.first), second(__p.second) {}
};
template<class T>
void Print(T f, T l) {
	for (; f != l; ++f) cout << *f << " "; cout << endl;
}
class A {
	int n;
public:
	A(int n_) :n(n_) {}
	friend bool operator<(const A &a1, const A &a2);
	friend ostream &operator<<(ostream &os, const A &a2) { os << a2.n; return os; }
	friend bool Larger(const A &a1, const A &a2);
};
bool operator<(const A &a1, const A &a2) {	//自定义类型<必须重载为全局函数！
	return a1.n < a2.n;
}

class MyLess {		//【自定义函数对象】【int】按个位比大小
public:
	bool operator()(const int &a1, const int &a2)const {
		return (a1 % 10) < (a2 % 10);
	}
};

bool Larger(const A &a1, const A &a2) {
	return a1.n > a2.n;
}

int main() {
	typedef set<int>::iterator IT;
	int a[5] = { 31,37,41,43,47 };
	set<int, MyLess<int>> st(a, a + 5);
	multiset<int> ms(a, a + 5);
	ms.insert(37);
	ms.insert(49);
	pair<IT, bool> r = st.insert(37);
	//不一定插入成功！把结果用pair<set<int>::iterator,bool>类对象result保存,
	//把尝试插的元素的迭代器返回为first, true/false返回为second,

	if (r.second)
		cout << *(r.first) << " inserted" << endl;
	else
		cout << *(r.first) << " already exists" << endl;   //重复！输出first！

	cout << ms.count(37) << " 37 in m" << endl;
	Print(st.begin(), st.end());

	auto it = ms.find(41);	// ms = {31,37,37,41,43,47}
	if (it != ms.end()) cout << "found 41 in ms" << endl;
	cout << "ms = ";  Print(ms.begin(), ms.end());

	cout << "ms中37的下界 " << *ms.lower_bound(37) << ",上界" << *ms.upper_bound(37) << endl;
	it = ms.erase(ms.lower_bound(37), ms.upper_bound(37)); //删除[37, 37+Δ)
	cout << "删除ms所有22 "; Print(ms.begin(), ms.end());
	cout << "it指向删后的后一位 " << *it << endl;  //pp应指向删后的元素33

	pair<IT, IT> setBounds = st.equal_range(41);
	//用pair<IT,IT>类对象setBounds保存两个迭代器
	cout << *setBounds.first << "," << *setBounds.second;
	return 0;
}
