//http://noi.openjudge.cn/ch0206/1775/
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
//�����״̬ת�Ʒ���:����ʵ��ʵ���з��룩��
//��MaxValue(m, t) = max(MaxValue(m - 1, t), MaxValue(m - 1, t - t[m]) + v[m]);��
int T, M, maxValue[102][1002], cost[102], value[102];
int calcMaxValue(int m, int t) {       //������ǰm�ֲ�ҩ�в�,tʱ���ڿɲɵ����valueֵ
	if (t == 0 || m == 0) return 0;
	if (maxValue[m][t] != -1) return maxValue[m][t];
	int nopick, dopick = 0;
	nopick = calcMaxValue(m - 1, t);	//��������ҩ�����value
	if (t >= cost[m])					//ʱ�乻��m�Ų�ҩ
		dopick = calcMaxValue(m - 1, t - cost[m]) + value[m];
	maxValue[m][t] = max(nopick, dopick);	//���ɻ��ǲ��ɣ�����һ�����⡿
	return maxValue[m][t];
}
int main() {
	cin >> T >> M;
	for (int i = 1; i <= M; i++)
		cin >> cost[i] >> value[i];
	//clock_t startTime = clock();

	//-----------�ݹ鷽��---------------------------------
	memset(maxValue, -1, sizeof(maxValue));
	cout << calcMaxValue(M, T) << endl;
	//-----------���淽��---------------------------------
	for (int i = 1; i <= M; i++) maxValue[i][0] = 0;
	for (int i = 0; i <= T; i++) maxValue[0][i] = 0;
	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= T; j++) {
			int nopick = maxValue[i - 1][j];	//����i�Ų�ҩ,maxValueͬ��i��ҩʱ
			int dopick;
			if (j >= cost[i])
				dopick = maxValue[i - 1][j - cost[i]] + value[i];	//�����״̬ת�Ʒ��̡�
			maxValue[i][j] = max(dopick, nopick);	// To pick or not to pick��That's a Q
		}
	}
	cout << maxValue[M][T] << endl;
	//----------------------------------------------------
	//clock_t endTime = clock();
	//cout<< "���������ʱ��:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	return 0;
}/*
 ע��ͼ�����Ʃ��a[i]<=jд��a[i]<=i,a[n_case]д��a[n]���־ͱ�����,����ִ�а���ŷ��ֵ���...
 ����WA��RE,���ԡ����⡿���ݡ����ִ��������ִ�С�debug,
 ����㷨˼·������Կ����ڵݹ�/�����ֻ�һ��
 */