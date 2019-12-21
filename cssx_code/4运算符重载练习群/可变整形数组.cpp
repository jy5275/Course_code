#include<iostream>
#include<string.h>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;
template<class T>
class CArray {
	T *ptr;
	int size = 0;       //首元素指针与长度
public:
	CArray(int s = 0) :size(s) {		//类型转换构造函数
		if (s == 0)ptr = NULL;
		else ptr = new T[s];
	}

	CArray(CArray &a) {       //复制构造函数【深复制】
		if (ptr)delete[]ptr;  //先清除ptr所占内存空间的原有信息，不过应该用不到
		if (a.size == 0) {    //模板的ptr为空
			ptr = NULL; size = 0;
		}
		else {
			ptr = new T[a.size];
			memcpy(ptr, a.ptr, sizeof(T)*a.size);
			size = a.size;
		}
	}

	CArray &operator=(const CArray &a) {	//'='重载,CArray相互赋值【深复制】
		if (ptr == a.ptr) return *this;	//防止自己给自己赋值
		if (!a.ptr) {
			if (ptr)delete[]ptr;
			ptr = NULL; size = 0;
			return *this;
		}
		if (size < a.size) {	//仅当原有空间不够大时,才分配新的空间
			if (ptr)delete[]ptr;
			ptr = new int[a.size];
		}
		size = a.size;
		memcpy(ptr, a.ptr, sizeof(T)*size);
		return *this;
	}

	void push_back(T v) {
		if (ptr) {		//若CArray里有元素
			T *tmpPtr = new T[size + 1];	//新开辟size+1空间
			memcpy(tmpPtr, ptr, sizeof(T)*size);
			delete[]ptr;	//释放旧空间
			ptr = tmpPtr;
		}
		else ptr = new T[1];	//若ptr没有元素
		ptr[size++] = v;		//把v给push到末尾
	}
	int length() { return size; }
	T &operator[](int i) {
		return ptr[i];
	}
	~CArray() {
		if (ptr)delete[]ptr;
	}
};
int main() {
	CArray<int> a;
	for (int i = 0; i < 5; ++i) 
		a.push_back(i);
	CArray<int> a2, a3;
	a2 = a;
	for (int i = 0; i < a.length(); ++i)
		cout << a2[i] << ' ';
	a2 = a3;
	for (int i = 0; i < a2.length(); ++i)
		cout << a2[i] << ' ';
	cout << endl;
	a[3] = 100;
	CArray<int> a4(a);
	for (int i = 0; i < a4.length(); ++i)
		cout << a4[i] << ' ';

	return 0;
}