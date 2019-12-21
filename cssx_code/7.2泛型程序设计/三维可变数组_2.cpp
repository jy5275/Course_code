#include<iostream>
#include<string.h>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;
template<class T>
class CArray3D {
	T ***pArray;     //pArrayָ�����Ŷ�ά��,�൱����ά����
	int r, c, l;
public:
	CArray3D(int r_, int c_, int l_) {
		r = r_; c = c_; l = l_;
		pArray = new T **[r];         //pArray��ָ����ָ��,��������r�ű�ɣ�
		for (int i = 0; i < r; i++)
			pArray[i] = new T *[c];   //pArray[i]��ָ�������ָ��,��������c������ɣ�
		for (int i = 0; i < r; i++)
			for (int j = 0; j < c; j++)
				pArray[i][j] = new T[l];  //pArray[i][j]ָ��Ԫ��,��������Ԫ�ذɣ�
	}
	T **operator[] (int index) {   //��ֻ�ܽ���һ��[],�����������T**(����)��ô�㣿
		return pArray[index];
	}
};

int main() {
	CArray3D<int> a(3, 4, 5);
	int No = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 4; j++)
			for (int k = 0; k < 5; k++)
				a[i][j][k] = No++;
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 4; ++j)
			for (int k = 0; k < 5; ++k)
				cout << a[i][j][k] << ",";
	return 0;
}