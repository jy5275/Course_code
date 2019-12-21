#include<iostream>
#include<vector>
#include<string>
#include<set>
#include<cmath>
#include<list>
#include<memory>
#include<map>
#include<algorithm>
#include<queue>
#include<iomanip>
#include<fstream>
#include<unordered_map>
//哈希表用法跟map一样，但效率更高，插入与查找时间复杂度几乎为const,但耗内存
#include<regex>     //正则表达式
class MyLess {
public:
	bool operator()(int x, int y) { return x % 10 < y % 10; }
};
using namespace std;
int main() {
	unordered_map<string, int> turingWinner;
	turingWinner.insert(make_pair("Dijkstra", 1972));
	turingWinner.insert(make_pair("Wilkes", 1968));
	turingWinner["JiangYan"] = 2020;
	string name;
	cin >> name;
	auto p = turingWinner.find(name);
	if (p != turingWinner.end())
		cout << p->second;
	else
		cout << "Not Found" << endl;
	//------------------------------------------
	regex reg("b.?p.*k"); //b+任意字符(出现0/1次)+p+任意字符(出现0/任意多次)+k
	cout << regex_match("bopggk", reg) << endl;     //1,匹配！
	cout << regex_match("boopgggk", reg) << endl;   //0,不匹配！
	cout << regex_match("b pk", reg) << endl;       //1,匹配！
	regex reg2("\\d{3}([a-zA-Z]+).(\\d{2}|N/A)\\s\\1"); // \d(数字)出现三次

	int x = 100, y = 200, z = 300;
	cout << [](double a, double b) {return a + b; }(1.2, 2.5) << endl;
	auto ff = [=, &y, &z](int n) {
		cout << x << endl;
		y++; z++;
		return n * n;
	};
	cout << ff(15) << endl;

	vector<int> a{ 4,2,11,33 };
	int total = 0;
	sort(a.begin(), a.end(), [](int x, int y)->bool { return x % 10 < y % 10; });
	for_each(a.begin(), a.end(), [&](int &x) { total += x; x *= 2; });
	for_each(a.begin(), a.end(), [](int x) { cout << x << " "; });


	return 0;
}
