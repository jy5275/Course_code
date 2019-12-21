#include<iostream>
#include<string>
#include<cmath>
#include<iomanip>
#include<fstream>
#include<vector>
#include<list>
#include<numeric>
#include<algorithm>
#include<iterator>
using namespace std;
//4.变序算法：改变顺序，但不改变值，必须支持随机访问迭代器！
template<class InIt>
void PrintInterval(InIt first, InIt last) {
	for (; first != last; ++first)
		cout << *first << " ";
	cout << endl;
}
int main() {
	string str = "231";
	char szStr[] = "324";
	while (next_permutation(str.begin(), str.end()))
		cout << str << endl;
	sort(str.begin(), str.end());
	while (next_permutation(str.begin(), str.end()))
		cout << str << endl;
	int a[] = { 8,7,10 };
	list<int> *pList = new list<int>(a, a + 3);
	while (next_permutation(pList->begin(), pList->end())) {
		PrintInterval(pList->begin(), pList->end());
	}
	int b[] = { 2,8,1,50,3,100,8,9,4,21 };
	vector<int> vb(b, b + 10);
	sort(vb.begin(), vb.end());
	if (binary_search(vb.begin(), vb.end(), 9))
		cout << endl << "9 found";
	
	return 0;
}
