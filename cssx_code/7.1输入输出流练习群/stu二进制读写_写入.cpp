#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<ostream>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;
class CStudent {
public:
	char name[20];
	int score;
};
int main() {
	CStudent s;
	ofstream outFile("student.dat", ios::app | ios::binary);
	if (!outFile) { cout << "error" << endl; return 0; }

	while (cin >> s.name >> s.score)
		outFile.write((char*)(&s), sizeof(s));	//每次写入sizeof(s)字节

	outFile.close();

	return 0;
}