/* 并查集:不直观,与物理结构相差较大,但能大大提升性能
N个不同的元素分布在若干个互不相交的集合中,需要多次进行以下3种操作:
1.合并a, b两个元素所在的集合 Merge(a, b)
2.查询一个元素在哪个集合
3.查询两个元素是否属于同一集合 Query(a, b) */
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<queue>
#include<vector>
#include<list>
#include<bitset>
#include<string>
#include<cstring>
#include<cmath>
#include<memory>
#include<stdexcept>
#include<time.h>
#include<algorithm>
#include<iomanip>
#include<fstream>
using namespace std;
const int MAX = 1 << 12;
void show_bytes(void *pv, int len) {  //只传入首地址与长度,不管基类型
	unsigned char *pStart = (unsigned char*)pv;
	char *ps = (char *)pv;
	for (int i = 0; i < len; i++)  //把ps+i(i=0:len-1)字节转为两位16进制码输出
		printf("%p  0x%.2x\n", pStart + i, pStart[i]); 
	printf("\n");
}
void show_int(int x) {
	show_bytes(&x, sizeof(int));
}
void show_double(double d) {
	show_bytes(&d, sizeof(double));
}
void show_pointer(void *x) {
	show_bytes(&x, sizeof(void *));
}
int main() {
	int k = (1 << 31) >> 31;
	unsigned h = (1 << 31) - 1;
	cout << h << endl;
	cout << k << endl;

	int aa = 15213;
	printf("int aa = 15213;\n");
	show_bytes(&aa, sizeof(int));
	printf("%x\n", aa);

	int a = -123, b = 123;
	cout << "a in hex is " << hex << a << endl;
	cout << "a in dec is " << dec << a << endl;
	cout << "b in hex is " << hex << b << endl;
	cout << "b in dec is " << dec << b << endl;

	unsigned int c = 0xFFFFFFFF;
	cout << "Largest unsigned int is " << dec << c << endl;
	cout << "Equal to " << pow(2, 32) << endl << endl;      //42亿

	int d = 0x7FFFFFFF;
	cout << "Largest signed int is " << dec << d << endl;
	cout << "Equal to " << pow(2, 31) << endl << endl;      //21亿

	cout << endl;
	cout << "sizeof(int):" << sizeof(int) << endl;
	cout << "sizeof(unsigned int):" << sizeof(unsigned int) << endl;
	cout << "sizeof(short):" << sizeof(short) << endl;
	cout << "sizeof(unsigned short):" << sizeof(unsigned short) << endl;
	cout << "sizeof(long):" << sizeof(long) << endl;
	cout << "sizeof(unsigned long):" << sizeof(unsigned long) << endl;
	cout << "sizeof(float):" << sizeof(float) << endl;
	cout << "sizeof(double):" << sizeof(double) << endl;
	cout << sizeof(int *) << "," << sizeof(char *) << "," << sizeof(void *) << endl;
	return 0;
}
