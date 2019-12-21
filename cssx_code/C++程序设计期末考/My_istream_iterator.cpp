#include <iostream>
#include <string>
using namespace std;
template<class T>
class CMyistream_iterator {
	typedef CMyistream_iterator MYIS_IT;
	istream &is;
	T *pVal = NULL;   //��ǰָ��pVal
public:
	CMyistream_iterator(istream &i) :is(i) {}
	void operator++(int k) { pVal = NULL; }
	T operator*() {
		if (pVal != NULL)
			return *pVal;  //�Ѿ��ж�ȡֵ�ˣ����ػ�ȥ��
		else {
			pVal = new T;
			is >> *pVal;
			return *pVal;
		}
	}
};

//------------���ϵĴ𰸣�------------
template <class T>
class CMyistream_iterator_2{
	T a;
	istream& is;
public:
	CMyistream_iterator(istream &input) :is(input) { is >> a;}
	T operator*(){ return a; }
	void operator++(int){ is >> a;}
};
//-------------����----------------

int main() {
	CMyistream_iterator<int> inputInt(cin);
	int n1, n2, n3;
	n1 = *inputInt; //���� n1
	int tmp = *inputInt;
	cout << tmp << endl;
	inputInt++;
	n2 = *inputInt; //���� n2
	inputInt++;
	n3 = *inputInt; //���� n3
	cout << n1 << "," << n2 << "," << n3 << endl;
	CMyistream_iterator<string> inputStr(cin);
	string s1, s2;
	s1 = *inputStr;
	inputStr++;
	s2 = *inputStr;
	cout << s1 << "," << s2 << endl;
	return 0;
}