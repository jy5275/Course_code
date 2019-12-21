#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string.h>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<fstream>
/* dragon = 1, ninja = 2, iceman = 3, lion = 4, wolf = 5
 * 改进：define 5 warrior macros
 * make init lines in main more tolarable
 */
#define DRAGON 1
#define NINJA 2
#define ICEMAN 3
#define LION 4
#define WOLF 5

using namespace std;
int t = 0, warrior_num = 5;    //若需增加游戏角色数量，则需增加warrior_num
class CHeadquarter;
bool manu(CHeadquarter &head); //别忘了声明在前，否则设置不了友元
void PrintTime() {
	if (t < 10) cout << "00" << t << ' ';
	else if (t < 100) cout << "0" << t << ' ';
	else cout << t << ' ';
}
class CLion {
	static int ini_s;
	int strength = ini_s, id; //每个worrior都有个id，作为在head里的唯一身份标识
	char head[20];                   //head的名字，red or blue
	friend class CHeadquarter;
	friend bool manu(CHeadquarter &head);
public:
	static void get_strength(int n) { CLion::ini_s = n; }
};
class CDragon {
	static int ini_s;
	char head[20];
	int strength = ini_s, id;
	friend class CHeadquarter;
	friend bool manu(CHeadquarter &head);
public:
	static void get_strength(int n) { CDragon::ini_s = n;}
};
class CNinja {
	static int ini_s;
	char head[20];
	int strength = ini_s, id;
	friend class CHeadquarter;
	friend bool manu(CHeadquarter &head);
public:
	static void get_strength(int n) { CNinja::ini_s = n; }
};
class CWolf {
	static int ini_s;
	char head[20];
	int strength = ini_s, id;
	friend class CHeadquarter;
	friend bool manu(CHeadquarter &head);
public:
	static void get_strength(int n) { CWolf::ini_s = n; }
};
class CIceman {
	static int ini_s;
	char head[20];
	int strength = ini_s, id;
	friend class CHeadquarter;
	friend bool manu(CHeadquarter &head);
public:
	static void get_strength(int n) { CIceman::ini_s = n; }
};

int CLion::ini_s = 0, CIceman::ini_s = 0, CWolf::ini_s = 0,
CDragon::ini_s = 0, CNinja::ini_s = 0;

class CHeadquarter {       //司令部是个大部头
	const char *name;      //司令部正式名称
	int total_s, num = 0;  //剩余生命点、worrior个数
	int cnt[6] = { 0 };    //cnt计这个Headquarter里各worrior分别多少个,
public:                    //dragon=1, ninja=2, iceman=3, lion=4, wolf=5
	int sq[6], nowsq;
	CHeadquarter(int M, const char *str, const char *sqs, int startsq):
		total_s(M), name(str), nowsq(startsq) {
		sscanf(sqs, "%d%d%d%d%d", &sq[1], &sq[2], &sq[3], &sq[4], &sq[5]);
	}
	friend bool manu(CHeadquarter &head);
	void makeLion() {	//4号worrior
		PrintTime();
		CLion lion;		//生成一个新的lion
		cnt[LION]++; num++;		//cnt[4](计lion数)++
		strcpy(lion.head, name);
		lion.id = num;	//Head给这只lion一个专属id
		total_s -= CLion::ini_s;	//Head生命值减少
		nowsq = sq[nowsq];
		cout << name << " lion " << num << " born with strength " << CLion::ini_s
			<< ',' << cnt[LION] << " lion in " << name << " headquarter" << endl;
	}
	void makeDragon() {
		PrintTime();
		CDragon dragon;
		cnt[DRAGON]++; num++;
		strcpy(dragon.head, name);
		dragon.id = num;
		total_s -= CDragon::ini_s;
		nowsq = sq[nowsq];
		cout << name << " dragon " << num << " born with strength " << CDragon::ini_s
			<< ',' << cnt[1] << " dragon in " << name << " headquarter" << endl;
	}
	void makeNinja() {
		PrintTime();
		CNinja ninja;
		cnt[NINJA]++; num++;
		strcpy(ninja.head, name);
		ninja.id = num;
		total_s -= CNinja::ini_s;
		nowsq = sq[nowsq];
		cout << name << " ninja " << num << " born with strength " << CNinja::ini_s
			<< ',' << cnt[2] << " ninja in " << name << " headquarter" << endl;
	}
	void makeIceman() {
		PrintTime();
		CIceman iceman;
		cnt[ICEMAN]++; num++;
		strcpy(iceman.head, name);
		iceman.id = num;
		total_s -= CIceman::ini_s;
		nowsq = sq[nowsq];
		cout << name << " iceman " << num << " born with strength " << CIceman::ini_s
			<< ',' << cnt[3] << " iceman in " << name << " headquarter" << endl;
	}
	void makeWolf() {
		PrintTime();
		CWolf wolf;
		cnt[WOLF]++; num++;
		strcpy(wolf.head, name);
		wolf.id = num;
		total_s -= CWolf::ini_s;
		nowsq = sq[nowsq];
		cout << name << " wolf " << num << " born with strength " << CWolf::ini_s
			<< ',' << cnt[5] << " wolf in " << name << " headquarter" << endl;
	}
};
bool manu(CHeadquarter &head) {
	for (int k = 0; k < 5; k++) {   //如何得知该造哪种worrior？先尝试i号能不能造出来
		//如果Head生命不足，遍历NUM个没找到合适的，就凉了
		if (head.nowsq == 1) {
			if (head.total_s >= CDragon::ini_s) {
				head.makeDragon();
				return 1;
			}
		}
		else if (head.nowsq == 3) {
			if (head.total_s >= CIceman::ini_s) {
				head.makeIceman();
				return 1;
			}
		}
		else if (head.nowsq == 4) {
			if (head.total_s >= CLion::ini_s) {
				head.makeLion();
				return 1;
			}
		}
		else if (head.nowsq == 5) {
			if (head.total_s >= CWolf::ini_s) {
				head.makeWolf();
				return 1;
			}
		}
		else if (head.nowsq == 2) {
			if (head.total_s >= CNinja::ini_s) {
				head.makeNinja();
				return 1;
			}
		}
		head.nowsq = head.sq[head.nowsq];
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
		int  M, a1, a2, a3, a4, a5;
		bool redcont = 1, bluecont = 1;
		cin >> M >> a1 >> a2 >> a3 >> a4 >> a5;
		CDragon::get_strength(a1); CNinja::get_strength(a2);
		CIceman::get_strength(a3); CLion::get_strength(a4);
		CWolf::get_strength(a5);
		CHeadquarter head1(M, "red", "3 1 4 5 2", 3), head2(M, "blue", "2 3 5 1 4", 4);
		while (redcont || bluecont) {
			if (redcont) redcont = manu(head1);  //只要i不为0，就操纵head1
			if (bluecont) bluecont = manu(head2);  //只要j不为0，就操纵head2
			t++;
		}
	}
	return 0;
}