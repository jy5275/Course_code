#include <iostream>
#include<string.h>
using namespace std;
int main(){
	int n = 0, sum = 0;
	cin >> n;
	char str[41] = { 0 };
	for (int i = 0; i < n; i++){     //���ʰ�����ȡ����һ����һ���Ƿ񳬳������ƣ���n��
		cin >> str;                     
		if (sum + 1 + strlen(str) > 80) { //����������
			cout << endl;
			sum = 0;
		}
		else if (i>0){   //δ����������
			cout << " ";
			sum++;
		}
		cout << str;
		sum += strlen(str);
	}
	return 0;
}