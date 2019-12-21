#include <iostream>
#include<string.h>
using namespace std;
int main(){
	int n = 0, sum = 0;
	cin >> n;
	char str[41] = { 0 };
	for (int i = 0; i < n; i++){     //单词挨个读取，读一个判一个是否超出行限制，读n个
		cin >> str;                     
		if (sum + 1 + strlen(str) > 80) { //超出行限制
			cout << endl;
			sum = 0;
		}
		else if (i>0){   //未超出行限制
			cout << " ";
			sum++;
		}
		cout << str;
		sum += strlen(str);
	}
	return 0;
}