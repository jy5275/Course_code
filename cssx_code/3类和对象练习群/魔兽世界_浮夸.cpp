#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<string.h>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;
int t = 0, warrior_num = 5;    //若需增加游戏角色数量，则需增加warrior_num
class CHeadquarter;
int manu(CHeadquarter &head, int i); //别忘了声明在前，否则设置不了友元
void PrintTime() {
	if (t < 10) cout << "00" << t << ' ';
	else if (t < 100) cout << "0" << t << ' ';
	else cout << t << ' ';
}
class CLion {
	static int strength_ini;
	int strength = strength_ini, id; //每个worrior都有个id，作为在head里的唯一身份标识
	char head[20];                   //head的名字，red or blue
	friend class CHeadquarter;
	friend int manu(CHeadquarter &head, int i);
public:
	static void get_strength(int n) {
		CLion::strength_ini = n;
	}
};
class CDragon {
	static int strength_ini;
	char head[20];
	int strength = strength_ini, id;
	friend class CHeadquarter;
	friend int manu(CHeadquarter &head, int i);
public:
	static void get_strength(int n) {
		CDragon::strength_ini = n;
	}
};
class CNinja {
	static int strength_ini;
	char head[20];
	int strength = strength_ini, id;
	friend class CHeadquarter;
	friend int manu(CHeadquarter &head, int i);
public:
	static void get_strength(int n) {
		CNinja::strength_ini = n;
	}
};
class CWolf {
	static int strength_ini;
	char head[20];
	int strength = strength_ini, id;
	friend class CHeadquarter;
	friend int manu(CHeadquarter &head, int i);
public:
	static void get_strength(int n) {
		CWolf::strength_ini = n;
	}
};
class CIceman {
	static int strength_ini;
	char head[20];
	int strength = strength_ini, id;
	friend class CHeadquarter;
	friend int manu(CHeadquarter &head, int i);
public:
	static void get_strength(int n) {
		CIceman::strength_ini = n;
	}
};

int CLion::strength_ini = 0, CIceman::strength_ini = 0, CWolf::strength_ini = 0,
   CDragon::strength_ini = 0, CNinja::strength_ini = 0;

class CHeadquarter {       //司令部是个大部头
	char *name;            //司令部得有一个正式名称，不能只是head1,head2
	int total_s, num = 0;  //剩余生命点、worrior个数
	int cnt[6] = { 0 };    //cnt是计数器,计算这个Headquarter里边各worrior分别有多少个,
public:                    //dragon=1, ninja=2, iceman=3, lion=4, wolf=5
	int sq[6];
	CHeadquarter(int M, char *str) : total_s(M), name(str) {}
	friend int manu(CHeadquarter &head, int i);
	void make_lion() {     //4号worrior
		PrintTime();       //先输出时间
		CLion lion;        //生成一个新的lion
		cnt[4]++; num++;   //cnt[4](计lion数)+1
		strcpy(lion.head, name);
		lion.id = num;     //Head给这只lion一个专属id
		total_s -= CLion::strength_ini;   //Head生命值减少
		cout << name << " lion " << num << " born with strength " << CLion::strength_ini
			<< ',' << cnt[4] << " lion in " << name << " headquarter" << endl;
	}
	void make_dragon() {
		PrintTime();
		CDragon dragon;
		cnt[1]++; num++;
		strcpy(dragon.head, name);
		dragon.id = num;
		total_s -= CDragon::strength_ini;
		cout << name << " dragon " << num << " born with strength " << CDragon::strength_ini
			<< ',' << cnt[1] << " dragon in " << name << " headquarter" << endl;
	}
	void make_ninja() {
		PrintTime();
		CNinja ninja;
		cnt[2]++; num++;
		strcpy(ninja.head, name);
		ninja.id = num;
		total_s -= CNinja::strength_ini;
		cout << name << " ninja " << num << " born with strength " << CNinja::strength_ini
			<< ',' << cnt[2] << " ninja in " << name << " headquarter" << endl;
	}
	void make_iceman() {
		PrintTime();
		CIceman iceman;
		cnt[3]++; num++;
		strcpy(iceman.head, name);
		iceman.id = num;
		total_s -= CIceman::strength_ini;
		cout << name << " iceman " << num << " born with strength " << CIceman::strength_ini
			<< ',' << cnt[3] << " iceman in " << name << " headquarter" << endl;
	}
	void make_wolf() {
		CWolf wolf;
		cnt[5]++; num++;
		strcpy(wolf.head, name);
		wolf.id = num;
		total_s -= CWolf::strength_ini;
		PrintTime();
		cout << name << " wolf " << num << " born with strength " << CWolf::strength_ini
			<< ',' << cnt[5] << " wolf in " << name << " headquarter" << endl;
	}
};
int manu(CHeadquarter &head,int i) {
	for (int k = 0; k < warrior_num; k++) {   //如何得知该造哪种worrior？先尝试i号能不能造出来
		if (k) { i = head.sq[i]; }  //如果Head生命不足，遍历NUM个没找到合适的，就凉了
		if (i == 1) {
			if (head.total_s >= CDragon::strength_ini) { head.make_dragon(); return head.sq[i]; }
		}
		else if (i == 3) {
			if (head.total_s >= CIceman::strength_ini) { head.make_iceman(); return head.sq[i]; }
		}
		else if (i == 4) {
			if (head.total_s >= CLion::strength_ini) { head.make_lion(); return head.sq[i]; }
		}
		else if (i == 5) {
			if (head.total_s >= CWolf::strength_ini) { head.make_wolf(); return head.sq[i]; }
		}
		else if (i == 2) {
			if (head.total_s >= CNinja::strength_ini) { head.make_ninja(); return head.sq[i]; }
		}
	}
	PrintTime();
	cout << head.name << " headquarter stops making warriors" << endl;
	return 0;
}
int main() {
	int n, all;
	cin >> n; all = n;
	while (n--) {
		t = 0;     //注意：每次游戏前时间归零！
		cout << "Case:" << all - n << endl;
		int  M, a1, a2, a3, a4, a5, i = 3, j = 4;
		char r[20] = {}, b[20] = {}; strcpy(r, "red"); strcpy(b, "blue");
		cin >> M >> a1 >> a2 >> a3 >> a4 >> a5;
		CDragon::get_strength(a1);CNinja::get_strength(a2);
		CIceman::get_strength(a3);CLion::get_strength(a4);
		CWolf::get_strength(a5);
		CHeadquarter head1(M, r), head2(M, b);
		head1.sq[1] = 3; head1.sq[2] = 1; head1.sq[3] = 4; head1.sq[4] = 5; head1.sq[5] = 2;
		head2.sq[1] = 2; head2.sq[2] = 3; head2.sq[3] = 5; head2.sq[4] = 1; head2.sq[5] = 4;
		while (i||j) {
			if (i) i = manu(head1, i);  //只要i不为0，就操纵head1
			if (j) j = manu(head2, j);  //只要j不为0，就操纵head2
			t++;
		}
	}
	return 0;
}