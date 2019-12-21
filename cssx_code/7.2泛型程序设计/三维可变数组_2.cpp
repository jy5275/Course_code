#include<iostream>
#include<string.h>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;
template<class T>
class CArray3D {
	T ***pArray;     //pArray指向整张二维表,相当于三维表名
	int r, c, l;
public:
	CArray3D(int r_, int c_, int l_) {
		r = r_; c = c_; l = l_;
		pArray = new T **[r];         //pArray是指向表的指针,给它分配r张表吧！
		for (int i = 0; i < r; i++)
			pArray[i] = new T *[c];   //pArray[i]是指向数组的指针,给它分配c个数组吧！
		for (int i = 0; i < r; i++)
			for (int j = 0; j < c; j++)
				pArray[i][j] = new T[l];  //pArray[i][j]指向元素,给它分配元素吧！
	}
	T **operator[] (int index) {   //？只能解释一级[],如果调用者是T**(表名)怎么搞？
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