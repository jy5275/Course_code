#include<iostream>
#include<string.h>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;
int t = 0, warrior_num = 5;    //����������Ϸ��ɫ��������������warrior_num
class CHeadquarter;
int manu(CHeadquarter &head, int i); //������������ǰ���������ò�����Ԫ
void PrintTime() {
	if (t < 10) cout << "00" << t << ' ';
	else if (t < 100) cout << "0" << t << ' ';
	else cout << t << ' ';
}
void getSortName(int i) {
	switch (i)
	{
	case 1:cout << " dragon "; break;
	case 2:cout << " ninja "; break;
	case 3:cout << " iceman "; break;
	case 4:cout << " lion "; break;
	case 5:cout << " wolf "; break;
	default:
		break;
	}
}
class CWarrior {
	int sort, strength = 0;                //dragon=1, ninja=2, iceman=3, lion=4, wolf=5
	static int strength_ini[6];      //��strength_ini[6]�������¼�������warrior�ĳ�ʼ����ֵ
	int strength = strength_ini[sort], id; //ÿ��worrior���и�id����Ϊ��head���Ψһ��ݱ�ʶ
	char head[20];                   //head�����֣�red or blue
	friend class CHeadquarter;
	friend int manu(CHeadquarter &head, int i);
public:
	CWarrior(int sort_, int strength_):sort(sort_), strength(strength_) {}  //��ʼ���б�
	static void set_strength(int i, int n) {
		CWarrior::strength_ini[i] = n;
	}
};
int CWarrior::strength_ini[6] = { 0 };
//int CLion::strength_ini = 0, CIceman::strength_ini = 0, CWolf::strength_ini = 0,
//CDragon::strength_ini = 0, CNinja::strength_ini = 0;

class CHeadquarter {       //˾��Ǹ���ͷ
	char *name;            //˾�����һ����ʽ���ƣ�����ֻ��head1,head2
	int total_s, tot_head = 0;  //ʣ�������㡢worrior����
	CWarrior *pwarrior[1000]; //�ڴ��趨ÿ��Head�����1000��warrior
	int cnt_head[6] = { 0 };    //cnt�Ǽ�����,�������Headquarter��߸�worrior�ֱ��ж��ٸ���
public:                    //dragon=1, ninja=2, iceman=3, lion=4, wolf=5
	int sq[6];
	CHeadquarter(int M, char *str) : total_s(M), name(str) {} //Get:������ֵ���Ǻ�����
	friend int manu(CHeadquarter &head, int i);
	void make(int sort) {     //����sort��worrior
		PrintTime();       //�����ʱ��
		pwarrior[tot_head] = new CWarrior(sort, CWarrior::strength_ini[sort]);  //����һ���µ�warrior
		cnt_head[sort]++; tot_head++;   //cnt[4](��lion��)+1
		strcpy_s(pwarrior[tot_head]->head, name);  //����ֻwarriorָ��˾��
		pwarrior[tot_head]->id = tot_head;     //Head��ÿֻwarriorһ��ר��id
		total_s -= CWarrior::strength_ini[sort];   //Head����ֵ����
		cout << name; getSortName(sort);
		cout << pwarrior[tot_head]->id << " born with strength " << CWarrior::strength_ini[sort]
			<< ',' << cnt_head[sort]; getSortName(sort);	
		cout << "in " << name << " headquarter" << endl;;
	}
};
int manu(CHeadquarter &head, int i) {
	for (int k = 0; k < warrior_num; k++) {   //��ε�֪��������worrior���ȳ���i���ܲ��������
		if (k) { i = head.sq[i]; }  //���Head�������㣬����NUM��û�ҵ����ʵģ�������
		if (head.total_s >= CWarrior::strength_ini[i]) { head.make(i); return head.sq[i]; }
	}
	PrintTime();
	cout << head.name << " headquarter stops making warriors" << endl;
	return 0;
}
int main() {
	int n, all;
	cin >> n; all = n;
	while (n--) {
		t = 0;     //ע�⣺ÿ����Ϸǰʱ����㣡
		cout << "Case:" << all - n << endl;
		int  M, a1, a2, a3, a4, a5, i = 3, j = 4;
		char r[20] = {}, b[20] = {}; strcpy_s(r, "red"); strcpy_s(b, "blue");
		cin >> M >> a1 >> a2 >> a3 >> a4 >> a5;
		CWarrior::set_strength(1, a1); CWarrior::set_strength(2, a2);
		CWarrior::set_strength(3, a3); CWarrior::set_strength(4, a4);
		CWarrior::set_strength(5, a5);
		CHeadquarter head1(M, r), head2(M, b);
		head1.sq[1] = 3; head1.sq[2] = 1; head1.sq[3] = 4; head1.sq[4] = 5; head1.sq[5] = 2;
		head2.sq[1] = 2; head2.sq[2] = 3; head2.sq[3] = 5; head2.sq[4] = 1; head2.sq[5] = 4;
		while (i || j) {
			if (i) i = manu(head1, i);  //ֻҪi��Ϊ0���Ͳ���head1
			if (j) j = manu(head2, j);  //ֻҪj��Ϊ0���Ͳ���head2
			t++;
		}
	}
	return 0;
}