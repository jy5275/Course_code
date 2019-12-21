#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;
int main() {
	ofstream fout("some.dat", ios::out | ios::binary);
	int x = 120;
	fout.write((const char*)(&x), sizeof(int));	//把x的二进制码写入文件!
	//用char方式写入占3byte,而bin方式占4byte！
	//文本方式写入用fout<<x;
	fout.close();

	ifstream fin("some.dat", ios::in | ios::binary);
	int y;
	fin.read((char*)(&y), sizeof(int));		//读取二进制数据,读字符串用fin>>y
	fin.close();
	return 0;
}