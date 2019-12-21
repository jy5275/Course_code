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
	int size = 0;       //��Ԫ��ָ���볤��
public:
	CArray(int s = 0) :size(s) {		//����ת�����캯��
		if (s == 0)ptr = NULL;
		else ptr = new T[s];
	}

	CArray(CArray &a) {       //���ƹ��캯������ơ�
		if (ptr)delete[]ptr;  //�����ptr��ռ�ڴ�ռ��ԭ����Ϣ������Ӧ���ò���
		if (a.size == 0) {    //ģ���ptrΪ��
			ptr = NULL; size = 0;
		}
		else {
			ptr = new T[a.size];
			memcpy(ptr, a.ptr, sizeof(T)*a.size);
			size = a.size;
		}
	}

	CArray &operator=(const CArray &a) {	//'='����,CArray�໥��ֵ����ơ�
		if (ptr == a.ptr) return *this;	//��ֹ�Լ����Լ���ֵ
		if (!a.ptr) {
			if (ptr)delete[]ptr;
			ptr = NULL; size = 0;
			return *this;
		}
		if (size < a.size) {	//����ԭ�пռ䲻����ʱ,�ŷ����µĿռ�
			if (ptr)delete[]ptr;
			ptr = new int[a.size];
		}
		size = a.size;
		memcpy(ptr, a.ptr, sizeof(T)*size);
		return *this;
	}

	void push_back(T v) {
		if (ptr) {		//��CArray����Ԫ��
			T *tmpPtr = new T[size + 1];	//�¿���size+1�ռ�
			memcpy(tmpPtr, ptr, sizeof(T)*size);
			delete[]ptr;	//�ͷžɿռ�
			ptr = tmpPtr;
		}
		else ptr = new T[1];	//��ptrû��Ԫ��
		ptr[size++] = v;		//��v��push��ĩβ
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