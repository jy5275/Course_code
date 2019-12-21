#include<iostream>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<fstream>
#include<vector>
#include<list>
#include<numeric>
#include<algorithm>
#include<iterator>
using namespace std;
class CLessThan9 {
public:
	bool operator()(int n) { return n < 9; }
};
bool CLessThan9(int n) {
	return n < 9;
}
void outputSquare(int value) { cout << value * value << " "; }
int calculateCube(int value) { return value * value * value; }
int main() {
	//1.不变序列算法，不修改算法作用的容器/对象，适用于顺序容器/关联容器，时间复杂度O(n)
	//2.变值算法,会修改目标区间元素的值，那个区间不能是关联容器（人家都排序好了）！！
	//3.删除算法

	const int SIZE = 10;
	int a1[] = { 1,2,3,4,5,6,7,8,9,10 };
	int a2[] = { 100,2,8,1,50,3,8,9,10,2 };
	vector<int> v(a1, a1 + SIZE);
	vector<int>::iterator p = v.begin();
	ostream_iterator<int>  output(cout, " "); //类模板，以int实例化，输出的东西都是int型
	random_shuffle(v.begin(), v.end());  //把区间内元素打乱
	cout << "1)";
	copy(v.begin(), v.end(), output); cout << endl;
	copy(a2, a2 + SIZE, v.begin());

	cout << "2)" << count(v.begin(), v.end(), 8);
	cout << "3)" << count_if(v.begin(), v.end(), CLessThan9); //数LessThan9的元素个数
	cout << "4)" << *min_element(v.begin(), v.end());  //返回指向min的迭代器
	cout << "5)" << *max_element(v.begin(), v.end());  //返回指向max的迭代器
													   //cout << "6)" << accumulate(v.begin, v.end(), 0);
	cout << "7)";
	for_each(v.begin(), v.end(), outputSquare);//对[begin,end)每个元素都执行outputSquare

	vector<int> cubes(SIZE);    //开辟一片空间，用来放a1给calcuCube的结果
	transform(a1, a1 + SIZE, cubes.begin(), calculateCube);
	cout << "8)";
	copy(cubes.begin(), cubes.end(), output); cout << endl;
	//------------------------------------------------------------------------------
	int a[5] = { 1,2,3,2,5 };
	int b[6] = { 1,2,3,2,5,6 };
	typedef vector<int> VINT;
	VINT va(a, a + 5);
	ostream_iterator<int> oit(cout, ",");
	VINT::iterator pa = remove(va.begin(), va.end(), 2); 
	        //remove返回有义数组末尾后边的迭代器，不改变容器的size
	cout << "1)";  copy(a, a + 5, oit);  cout << endl;
	cout << "2)" << pa - va.begin() << endl;
	VINT v2(b, b + 6);
	remove(v2.begin(), v2.end(), 2);
	cout << "3)"; copy(v2.begin(), v2.end(), oit); cout << endl;
	cout << "4)" << v2.size() << endl;

	return 0;
}
