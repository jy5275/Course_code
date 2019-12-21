#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;
/* 文件操作好累...还是内存操作舒服
 * Linux/Unix下换行='\n'; Windows下'\r\n', endl = '\n'
 * 导致Linux下的文本文件在Windows记事本中打开时不换行
 * 因此,Unix/Linux下打开文件，用不用ios::binary没区别; 但Windows遇到'\r\n'会出事
 */
class CStudent {
public:
	char name[20];
	int score;
};
int main() {
	CStudent s;
	fstream ioFile("student.dat", ios::in | ios::out | ios::binary);
	if (!ioFile) { cout << "error" << endl; return 0; }

	ioFile.seekp(2 * sizeof(s), ios::beg);	//定位指针到第三条记录
	ioFile.write("Taotao", strlen("Taotao") + 1);
	ioFile.seekg(0, ios::beg);
	while (ioFile.read((char*)(&s), sizeof(s)))
		cout << s.name << " " << s.score << endl;

	ioFile.close();

	return 0;
}