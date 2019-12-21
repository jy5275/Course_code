#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<set>
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
typedef pair<int, int> status;
int al[1001], N, maxA[1001][2];
int myMax(int a, int b, int c) {
	if (a >= b && a >= c)return a;
	if (b >= a && b >= c)return b;
	if (c >= a && c >= b)return c;
}
int calcMaxA(int n, int descend) {    //��No.nΪ�յ�������·��
	int tmpMaxA = 1;
	//descend=1��ʾ��nʱһֱ������,descend=1��ʾ��nǰ�ѿ�ʼ�½�
	//tmpDescmaxAΪ���������½�·�ߵĻ�֮ǰ����ߵĲ���
	if (maxA[n][descend] != -1) return maxA[n][descend];
	for (int i = 1; i < n; i++) {
		if (descend == 0) {
			if (al[i] < al[n])    //Ӧ����������
				tmpMaxA = max(tmpMaxA, calcMaxA(i, 0) + 1);
		}
		else if (descend == 1) {
			if (al[i] > al[n])    //ֻ���½���
				tmpMaxA = myMax(tmpMaxA, calcMaxA(i, 0) + 1, calcMaxA(i, 1) + 1);
		}
	}
	maxA[n][descend] = tmpMaxA;
	return tmpMaxA;
}
int main() {
	int tmpMax = 1;
	cin >> N;
	for (int i = 1; i <= N; i++)
		cin >> al[i];
	clock_t startTime = clock();

	//-----------------���淽��-----------------------------------
	for (int i = 1; i <= N; i++) {	//��i������һ��
		//maxA[i][0]Ϊ��iΪ�յ�����½�·�߳���max
		//maxA[i][1]Ϊ��iΪ�յ�����½�·�߳���max
		maxA[i][0] = 1, maxA[i][1] = 1;
		for (int j = 1; j < i; j++) {
			if (al[j] < al[i])	//�ɴ�j�������ߵ�i,������iΪ�յ�������·�߳���
				maxA[i][0] = max(maxA[i][0], maxA[j][0] + 1);
			else if (al[j] > al[i])	//�ɴ�j�������ߵ�i,������iΪ�յ������½�·�߳���
				maxA[i][1] = myMax(maxA[i][1], maxA[j][0] + 1, maxA[j][1] + 1);
		}
		tmpMax = myMax(tmpMax, maxA[i][0], maxA[i][1]);
	}
	cout << tmpMax << endl;
	//-----------------�ݹ鷽��----------------------------------
	memset(maxA, -1, sizeof(maxA));
	for (int i = 1; i <= N; i++)
		tmpMax = myMax(tmpMax, calcMaxA(i, 0), calcMaxA(i, 1));
	cout << tmpMax << endl;
	//----------------------------------------------------------------

	clock_t endTime = clock();
	//cout<< "���������ʱ��:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	return 0;
}
/*�ݹ�return�����Ƚϸ��ӵ�,����֮,
���ʺ�Ҫ��������һ��������(��һ���Ƿ��½�),
��������һ��������(��һ���ĸ����)������
�е�ʱ��Ҫ��main����������iΪ��/�յ�����е��ҵ����Ž�
*/