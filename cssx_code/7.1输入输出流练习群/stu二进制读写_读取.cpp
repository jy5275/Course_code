#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;
/* �����ƴ洢���ŵ㣺
 * 1.��ʡ�ռ�,2147483647�ı�Ҫ��9B,������ֻ��4B
 * 2.���ҷ���,ÿ����¼�ù̶����ȱ���,������ֲ���
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
		//read�ܰ��ļ���sizeof(s)λbinary code�ŵ��ڴ�s��ַ��
		int readedBytes = inFile.gcount();	//�����ûɶ����
		cout << s.name << " " << s.score << endl;
	}
	inFile.close();

	return 0;
}