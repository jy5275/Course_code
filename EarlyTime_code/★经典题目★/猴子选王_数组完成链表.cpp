#include<iostream>
#include<string.h>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;
//һ�������1000��
int succedent[1000]; //����������ڱ���һ���˺�һ����˭��
					//���硰succedent[5]��ֵ��7������˵5�ŵ���һλ��7�ţ�6���Ѿ���֮ǰ�˳��ˡ�
int precedent[1000];//����������ڱ���һ��ǰһλ��˭���÷�����������ơ�
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
			//���һ��Ҫ��m�κţ���ôȡm-1��succedent֮�������Ҫ�˳����Ǹ���
			for (int count = 0; count < m - 1; count++)
				current = succedent[current];
			cout << current << " ";
			int pre = precedent[current];
			int suc = succedent[current];
			//��current���˳��ܼ򵥣����ǰ�ǰһλ�ġ���һλ��ָ��current����һλ����һλ�ġ�ǰһλ��ָ��current��ǰһλ�ͺ���
			succedent[pre] = suc;
			precedent[suc] = pre;
			if (pre == suc) {
				//���ֻʣ�������ˣ���ôÿ���˵�ǰλ�ͺ�λ����ͬһ���ˡ�
				//current���˳��ģ���ô��һ������ʣ�µġ�
				cout << pre ;
				break;	
			}
			current = suc;
		}
	}
	return 0;
}