#include<iostream>
#include<ostream>
#include<string.h>
#include<string>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;
int main() {
	ofstream fout;
	fout.open("test.txt", ios::app); //在文件尾部添加数据
	if (!destFile) {
		cout << "Error opening destFile!" << endl;
		return 0;
	}

	int location = fout.tellp();
	fout.seekp(10);
	fout.seekp(10, ios::beg);
	fout.seekp(10, ios::cur);
	fout.seekp(-10, ios::end);

	ifstream fin("test.txt", ios::ate);	//定位文件指针到文件尾
	int location = fin.tellg();			//取得读指针位置（文件长度） 
	fin.seekg(10);              //将读指针移动至第10个字节处
	fin.seekg(10, ios::beg);    //从头数10
	fin.seekg(10, ios::cur);    //从当前位置移动10
	fin.seekg(-10, ios::end);
	
	return 0;
}