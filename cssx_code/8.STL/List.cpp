#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<cmath>
#include<vector>
#include<list>
#include<deque>
#include<algorithm>
//List上的迭代器只支持双向迭代器，不支持>,<,[]与随机移动
using namespace std;
class A {
	int n;
	friend ostream &operator<<(ostream &os, const A &a);
	friend bool operator<(const A &a1, const A &a2);
	friend bool operator==(const A &a1, const A &a2);
public:
	A(int n_) :n(n_) {};
};
ostream &operator<<(ostream &os, const A &a) {  //重载流输出符号
	os << a.n;
	return os;
}
bool operator<(const A &a1, const A &a2) {   //重载'<',用于sort中比较大小
	return a1.n < a2.n;
}
bool operator==(const A &a1, const A &a2) {
	return a1.n == a2.n;
}
template<class T>
void PrintList(const list<T> &lst) {
	int tmp = lst.size();
	typename list<T>::const_iterator i;   //函数模板里的迭代器要加typename？
	for (i = lst.begin(); i != lst.end(); ++i)
		cout << *i << ",";
	cout << endl;
}
template<class T>
void setLst2(list<T> &lst2) {
	lst2.push_back(10); lst2.push_back(20); lst2.push_back(30); lst2.push_back(30);
	lst2.push_back(30); lst2.push_back(40); lst2.push_back(40);
}

int main() {
	list<A> lst1, lst2;
	lst1.push_back(1); lst1.push_back(3); lst1.push_back(2); lst1.push_back(4);
	lst1.push_back(2);  //lst1 = {1, 3, 2, 4, 2};
	setLst2(lst2);
	cout << "1)"; PrintList(lst1);
	cout << "2)"; PrintList(lst2);

	lst2.sort();  //lst2排序，用sort函数
	cout << "3)"; PrintList(lst2);

	lst2.pop_front();   //lst2删除首元素,首元素变成20 
	cout << "4)"; PrintList(lst2);

	lst1.remove(2); cout << "5)"; PrintList(lst1);  //删除所有A(2)元素
	lst2.unique(); cout << "6)"; PrintList(lst2);   //删除重复元素

	lst1.merge(lst2);   //合并lst2到lst1，lst2灭亡！
	cout << "7)"; PrintList(lst1);
	cout << "8)"; PrintList(lst2);

	lst1.reverse();     //lst1反了！       
	cout << "9)"; PrintList(lst1);

	setLst2(lst2);      //lst2卷土重来！
	list<A>::iterator p1, p2, p3;
	p1 = find(lst1.begin(), lst1.end(), 3);
	p2 = find(lst2.begin(), lst2.end(), 20);
	p3 = find(lst2.begin(), lst2.end(), 40);
	lst1.splice(p1, lst2, p2, p3);  //把[p2, p3)插入p1之前，并从lst2中删除[p2, p3)！

	cout << "11)"; PrintList(lst1);
	cout << "12)"; PrintList(lst2);
	return 0;
}
