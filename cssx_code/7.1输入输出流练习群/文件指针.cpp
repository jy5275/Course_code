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
	fout.open("test.txt", ios::app); //���ļ�β���������
	if (!destFile) {
		cout << "Error opening destFile!" << endl;
		return 0;
	}

	int location = fout.tellp();
	fout.seekp(10);
	fout.seekp(10, ios::beg);
	fout.seekp(10, ios::cur);
	fout.seekp(-10, ios::end);

	ifstream fin("test.txt", ios::ate);	//��λ�ļ�ָ�뵽�ļ�β
	int location = fin.tellg();			//ȡ�ö�ָ��λ�ã��ļ����ȣ� 
	fin.seekg(10);              //����ָ���ƶ�����10���ֽڴ�
	fin.seekg(10, ios::beg);    //��ͷ��10
	fin.seekg(10, ios::cur);    //�ӵ�ǰλ���ƶ�10
	fin.seekg(-10, ios::end);
	
	return 0;
}