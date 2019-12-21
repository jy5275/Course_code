#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector> 
#include<string>
#include<iomanip>
#include<fstream> 
#include<algorithm>
using namespace std;
const int LEN = 500;
int MyCompare(const void *tp1, const void *tp2) {
	int *p1 = (int*)tp1, *p2 = (int*)tp2;
	return *p1 - *p2;
}
int main() {
	vector<int> v;
	ofstream srcFile("in.txt", ios::out);
	ofstream destFile("out.txt", ios::out);
	int x;
	for (int i = 0; i < LEN; i++) {
		x = rand() % 1000;
		v.push_back(x);
		srcFile << x << " ";
	}
	sort(v.begin(), v.end());

	for (int i = 0; i < v.size(); ++i)
		destFile << v[i] << " ";

	destFile.close();
	srcFile.close();
	return 0;
}
