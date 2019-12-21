#define _CRT_SECURE_NO_WARNINGS  
#include<iostream>
#include<string>
#include<cmath>
#include<map>
#include<algorithm>
using namespace std;
//map相对于multimap特别之处在于关键字(first成员变量)不能相同
//以及可以用mapCourse[key]返回对关键字为key的元素值的引用
//★★★map最符合数据库的定义，主键不能重复！★★★
template<class Key, class Value>
ostream &operator<<(ostream &os, const pair<Key, Value> &p) {
	os << "(" << p.first << "," << p.second << ")";
	return os;
}
template<class It>
void Print(It f, It e) {
	for (; f != e; ++f)cout << *f << " "; cout << endl;
}
int main() {
	typedef map<int, double, less<int> > mmid;
	mmid pairs;
	cout << "1)" << pairs.count(15) << endl;
	pairs.insert(pair<int, double>(15, 2.7));
	pair<mmid::iterator, bool> p;     //用于接收insert结果的pair
	p = pairs.insert(pair<int, double>(15, 99.3)); //Key重复！Insert failure
	cout << "2)" << pairs.count(15) << endl;	//set和map中也有count函数,然并卵

	pairs.insert(make_pair(10, 9.3));
	cout << "3)"; Print(pairs.begin(), pairs.end());
	int n = pairs[40];		//返回Key为40的记录的值的引用,如果没有则创建一个
	pairs[15] = 6.28;		//显然,multimap没有[]快捷Query/Insert/Modify
	cout << "4)"; Print(pairs.begin(), pairs.end());

	return 0;
}
