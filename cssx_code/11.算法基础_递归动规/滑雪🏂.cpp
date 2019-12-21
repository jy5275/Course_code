/* http://noi.openjudge.cn/ch0206/90/ */
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<set>
#include<string>
#include<cstring>
#include<cmath>
#include<memory.h>
#include<algorithm>
using namespace std;
int terr[102][102], r, c, L[102][102];
class CPoint {
public:
	int r, c, h;
	CPoint(int r_, int c_, int h_) :r(r_), c(c_), h(h_) {}
};
bool operator<(const CPoint &p1, const CPoint &p2) {
	return p1.h < p2.h;
}
multiset<CPoint> s;   //���Ǳȴ�С�᡾�еȡ�����һ��multiset

int calcL(int i, int j) {   //����(i,j)Ϊ���������·��
							//����Ҫ�ȳ���ӡ/�˻ؽŲ�,��Ϊterr�Ѿ�����ʲô�ط�������
	if (i<1 || i>r || j<1 || j>c) return 0;		//Խ�磡
	if (L[i][j] != -1) return L[i][j];
	int R = 1;
	if (i >= 1 && terr[i - 1][j] < terr[i][j])  //���Ի��򱱱ߵķ���
		R = max(R, calcL(i - 1, j) + 1);
	if (i <= r && terr[i + 1][j] < terr[i][j])  //���Ի����ϱߵķ���
		R = max(R, calcL(i + 1, j) + 1);
	if (j >= 1 && terr[i][j - 1] < terr[i][j])  //���Ի������ߵķ���
		R = max(R, calcL(i, j - 1) + 1);
	if (j <= c && terr[i][j + 1] < terr[i][j])  //���Ի��򶫱ߵķ���
		R = max(R, calcL(i, j + 1) + 1);
	L[i][j] = R;
	return R;   //���terr[i][j]��һ��͵�,�ͻ᷵��R=1
}
void Init() {
	for (int i = 0; i < 102; i++) {
		for (int j = 0; j < 102; j++) {
			terr[i][j] = 10001;
			L[i][j] = 1;
		}
	}
}
/*��ѩ�����������,
1.���߽��������п��ܲ��ڼ��α߽������߽�,�������ܱ���ʱȷ��,���ݹ�����ʱ��
���Զ�ȷ���������ߵ����֡���Χ���Ǹ�ǽ�ĵط������Ǳ߽�����
------------------------------------------------------------------
2.�����в���ȷ��������˳����ô��?ԭ���Ǽ���"��"ʱ"����"�������(����Χ�ĵ�
Lֵ�������,����������·���)�����Խ����е㰴�߶�����,����͵ĵ�,����ߵĵ�
*/
int main() {
	//���������������������,���ֲ������ԡ����ֵ����쾡�¡����߽�����������
	cin >> r >> c;
	int ans = 0;
	Init();
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			cin >> terr[i][j];
			s.insert(CPoint(i, j, terr[i][j]));  //��������õĲ���
		}
	}
	//clock_t startTime = clock();

	//---------------�ݹ鷽��------------------------------
	memset(L, -1, sizeof(L));
	for (int i = 1; i <= r; i++)	//��ÿ��(i,j)��Ϊ�����һ��,�ҳ����
		for (int j = 1; j <= c; j++)
			ans = max(ans, calcL(i, j));

	//---------------���淽��------------------------------
	auto p = s.begin();
	//���s�����в���ʵ�ʴ���,�����������棡���
	for (; p != s.end(); p++) {		//�����޷�ȷ��ʵ��·��,���ӵ͵�����ûë��
		int ele = terr[p->r][p->c];
		int Nele = terr[p->r - 1][p->c], Sele = terr[p->r + 1][p->c],
			Wele = terr[p->r][p->c - 1], Eele = terr[p->r][p->c + 1];
		if (p->r > 1 && Nele < ele)		//��
			L[p->r][p->c] = max(L[p->r][p->c], L[p->r - 1][p->c] + 1);
		if (p->r < r && Sele < ele)		//��
			L[p->r][p->c] = max(L[p->r][p->c], L[p->r + 1][p->c] + 1);
		if (p->c > 1 && Wele < ele)		//��
			L[p->r][p->c] = max(L[p->r][p->c], L[p->r][p->c - 1] + 1);
		if (p->c < c && Eele < ele)		//��
			L[p->r][p->c] = max(L[p->r][p->c], L[p->r][p->c + 1] + 1);
		//��һ��ѭ��û�������κ�����,��Ϊ Xele<ele ��������
	}
	for (int i = 1; i <= r; i++)    //��ÿ��(i,j)��Ϊ�����һ��,�ҳ����
		for (int j = 1; j <= c; j++)
			ans = max(ans, L[i][j]);

	cout << ans << endl;
	//------------------------------------------------------------

	//clock_t endTime = clock();
	//cout << "���������ʱ��:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	return 0;
}