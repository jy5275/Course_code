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
	girl = str[i];      //�ҵ������к�Ů���ı�ʶ��
	for (i = 1; i < n - 1; i++) {   //���Ӻ���λ�������鹹������
		pre[i] = i - 1; suc[i] = i + 1;
	}
	if (n == 2) {       //���������ֻ�����ˣ�ֱ�����
		cout << 0 << " " << 1; 
		return 0;
	}
	pre[0] = n - 1; suc[0] = 1; pre[n - 1] = n - 2; suc[n - 1] = 1;
	while (suc[current] != pre[current]) {  //ֻҪ�������2�����ϣ��ͼ������ɣ�
		if (str[current] != str[suc[current]]) {   //ƥ�䣬���У�
			cout << current << " " << suc[current] << endl;
			suc[pre[current]] = suc[suc[current]];
			pre[suc[suc[current]]] = pre[current];
			current = 0;
			continue;
		}
		else {                //��ƥ�䣬�����Ұɣ�
			current = suc[current];
		}
	}
	cout << current << " " << suc[current];
	return 0;
}