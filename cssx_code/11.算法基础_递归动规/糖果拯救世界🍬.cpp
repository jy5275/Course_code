//http://noi.openjudge.cn/ch0206/2989/
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
int N, K, sugarPack[102], mostSugar[102][102];
const int MIN = -1000000 * 100;
int calcMostSugar(int n, int rem) {  //����ֻ��ǰN���ǹ����������ȡK*k+rem���ǹ����ȡ��
	if (mostSugar[n][rem] != -1) return mostSugar[n][rem];
	if (n == 0) {
		if (rem != 0) return 1 << 31;
		else return 0;
	}
	int noPick = calcMostSugar(n - 1, rem);
	int doPick = calcMostSugar(n - 1, (rem + K - sugarPack[n] % K) % K) + sugarPack[n];
	mostSugar[n][rem] = max(noPick, doPick);
	return mostSugar[n][rem];
}
int main() {
	cin >> N >> K;
	for (int i = 1; i <= N; i++)
		cin >> sugarPack[i];
	//clock_t startTime = clock();

	//-----------------���淽��-----------------------------------
	for (int i = 1; i < K; i++)   //�߽�����1:��0���ǹ���ȡʹ����%K��������Ϊrem,ֱ��ʧ�ܣ� 
		mostSugar[0][i] = 1 << 31;
	mostSugar[0][0] = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < K; j++) {
			mostSugar[i][j] = max(mostSugar[i - 1][j],
				mostSugar[i - 1][(j + K - sugarPack[i] % K) % K] + sugarPack[i]);
		}
	}
	cout << mostSugar[N][0] << endl;
	//-----------------�ݹ鷽��----------------------------------
	memset(mostSugar, -1, sizeof(mostSugar));
	cout << calcMostSugar(N, 0) << endl;
	//----------------------------------------------------------------

	//clock_t endTime = clock();
	//cout<< "���������ʱ��:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	return 0;
}/*
 ���⣡��ά���鿴���Ƕ�ά�߽�,ʵ���һά�߽�
 �ǹ����ɲ�ҩ��������϶�������pick������,����ץס"����ĳԪ�ض�pool��������Ӱ��",
 ��������"��ǰn-1��Ԫ������ȡ����,�ܺ���������k-1"
 ÿ���ݹ黷���н���pick or not����ѡ��,��Ӧ��һ�������״̬
 */