#include<iostream>
#include<string.h>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;

int main() {
	char str[101], boy, girl;
	cin.getline(str, 101);
	int i, j, k, pre[101], suc[101], n = strlen(str), current = 0;
	boy = str[0];
	for (i = 1; str[i] == boy; i++) {}
	girl = str[i];      //找到代表男孩女孩的标识符
	for (i = 1; i < n - 1; i++) {   //连接好首位，用数组构建链表
		pre[i] = i - 1; suc[i] = i + 1;
	}
	if (n == 2) {       //特殊情况：只有两人，直接输出
		cout << 0 << " " << 1; 
		return 0;
	}
	pre[0] = n - 1; suc[0] = 1; pre[n - 1] = n - 2; suc[n - 1] = 1;
	while (suc[current] != pre[current]) {  //只要队伍存在2人以上，就继续挑吧！
		if (str[current] != str[suc[current]]) {   //匹配，出列！
			cout << current << " " << suc[current] << endl;
			suc[pre[current]] = suc[suc[current]];
			pre[suc[suc[current]]] = pre[current];
			current = 0;
			continue;
		}
		else {                //不匹配，继续找吧！
			current = suc[current];
		}
	}
	cout << current << " " << suc[current];
	return 0;
}