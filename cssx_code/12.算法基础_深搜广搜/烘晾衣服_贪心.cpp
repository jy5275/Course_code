#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<queue>
#include<vector>
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
int main() {
	int n, k, level = 0;
	cin >> n;
	priority_queue<int> clothes;
	for (int i = 0; i < n; i++) {
		int tmp; cin >> tmp;
		clothes.push(tmp);
	}
	cin >> k;
	clock_t startTime = clock();
	while (clothes.top() >= level) {  //目前水还剩a[i]-level
		int tmp = clothes.top();     //每次都烘最湿润的衣服！
		clothes.pop();
		clothes.push(tmp - k + 1);
		level++;
	}
	cout << level << endl;
	clock_t endTime = clock();
	//cout << "程序段运行时间:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	return 0;
}