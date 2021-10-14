#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
using namespace std;
bool function(vector<int> &seq) {
	if (seq.size() <= 2) return true;
	auto it = seq.end() - 1;
	vector<int> sub1, sub2;
	int last = *it;
	while (*it >= last && it != seq.begin())  --it;
	if (*it<last) ++it;    //it到达了sub2起点,如果sub2,size()==0,则it仍在last处
	auto mid = it;   //mid是sub2起点
	for (; it != seq.end() - 1; ++it) {
		if (*it < last) return false;
		sub2.push_back(*it);
	}
	for (it = seq.begin(); it < mid; ++it) {
		if (*it > last) return false;
		sub1.push_back(*it);
	}
	return function(sub1) && function(sub2);
}
int main() {
	vector<int> v[] = { { 3,7,1,6,5,2,4 },{ 3,4,2,1 },{ 3,1,2,4 } };
	for (int i = 0; i < 3; i++) 
		cout << function(v[i]) << endl;
	return 0;
}