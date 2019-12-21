#include<iostream>
#include<string.h>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<fstream>
#include<vector>
#include<list>
#include<deque>
#include<algorithm>
//List上的迭代器只支持双向迭代器，不支持>,<,[]与随机移动，
using namespace std;
int main() {
	int n, m;
	list<int> monkey;
	list<int>::iterator p;
	while (cin >> n >> m) {
		monkey.clear();
		for (int i = 1; i <= n; i++) monkey.push_back(i);   //挨个往后添加元素
		p = monkey.begin();                //每个case前初始化容器monkey与迭代器p
		while (monkey.size() > 1) {
			for (int j = 1; j < m; j++) {   //当前的猴报j,一旦发现j==2，跳出处死之！
				p++;
				if (p == monkey.end()) p = monkey.begin();
			}
			p = monkey.erase(p);           //erase返回被清除者的后一个元素
			if (p == monkey.end()) p = monkey.begin();
		}
		cout << monkey.front() << endl;
	}
	return 0;
}
