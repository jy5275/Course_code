#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;
/* 二进制存储的优点：
 * 1.节省空间,2147483647文本要存9B,二进制只需4B
 * 2.查找方便,每条记录用固定长度保存,方便二分查找
 */
class CStudent {
public:
	char name[20];
	int score;
};
int main() {
	CStudent s;
	ifstream inFile("student.dat", ios::in | ios::binary);
	if (!inFile) { cout << "error" << endl; return 0; }

	while (inFile.read((char*)(&s), sizeof(s))) {
		//read能把文件中sizeof(s)位binary code放到内存s地址中
		int readedBytes = inFile.gcount();	//在这儿没啥卵用
		cout << s.name << " " << s.score << endl;
	}
	inFile.close();

	return 0;
}