#include<iostream>
#include<string.h>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;
//一共最多有1000人
int succedent[1000]; //这个数组用于保存一个人后一人是谁，
					//比如“succedent[5]的值是7”就是说5号的下一位是7号，6号已经在之前退出了。
int precedent[1000];//这个数组用于保存一人前一位是谁，用法和上面的类似。
int main() {
	int n, m;
	while (true) {
		cin >> n >> m;
		if (n == 0 && m == 0)
			break;
		for (int i = 0; i < n - 1; i++) {
			succedent[i] = i + 1;
			precedent[i + 1] = i;
		}
		succedent[n - 1] = 0;
		precedent[0] = n - 1;

		int current = 0;
		while (true) {
			//如果一共要报m次号，那么取m-1次succedent之后就是需要退出的那个人
			for (int count = 0; count < m - 1; count++)
				current = succedent[current];
			cout << current << " ";
			int pre = precedent[current];
			int suc = succedent[current];
			//让current号退出很简单，就是把前一位的“下一位”指向current的下一位，下一位的“前一位”指向current的前一位就好了
			succedent[pre] = suc;
			precedent[suc] = pre;
			if (pre == suc) {
				//如果只剩下两人了，那么每个人的前位和后位就是同一个了。
				//current是退出的，那么另一个就是剩下的。
				cout << pre ;
				break;	
			}
			current = suc;
		}
	}
	return 0;
}