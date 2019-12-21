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
	static int strength_ini[6];      //在strength_ini[6]数组里记录所有类别warrior的初始生命值
	int strength = strength_ini[sort], id; //每个worrior都有个id，作为在head里的唯一身份标识
	char head[20];                   //head的名字，red or blue
	friend class CHeadquarter;
	friend int manu(CHeadquarter &head, int i);
public:
	CWarrior(int sort_, int strength_):sort(sort_), strength(strength_) {}  //初始化列表
	static void set_strength(int i, int n) {
		CWarrior::strength_ini[i] = n;
	}
};
int CWarrior::strength_ini[6] = { 0 };
//int CLion::strength_ini = 0, CIceman::strength_ini = 0, CWolf::strength_ini = 0,
//CDragon::strength_ini = 0, CNinja::strength_ini = 0;

class CHeadquarter {       //司令部是个大部头
	char *name;            //司令部得有一个正式名称，不能只是head1,head2
	int total_s, tot_head = 0;  //剩余生命点、worrior个数
	CWarrior *pwarrior[1000]; //在此设定每个Head最多有1000个warrior
	int cnt_head[6] = { 0 };    //cnt是计数器,计算这个Headquarter里边各worrior分别有多少个，
public:                    //dragon=1, ninja=2, iceman=3, lion=4, wolf=5
	int sq[6];
	CHeadquarter(int M, char *str) : total_s(M), name(str) {} //Get:总生命值、是红是蓝
	friend int manu(CHeadquarter &head, int i);
	void make(int sort) {     //制造sort型worrior
		PrintTime();       //先输出时间
		pwarrior[tot_head] = new CWarrior(sort, CWarrior::strength_ini[sort]);  //生成一个新的warrior
		cnt_head[sort]++; tot_head++;   //cnt[4](计lion数)+1
		strcpy_s(pwarrior[tot_head]->head, name);  //给这只warrior指定司令
		pwarrior[tot_head]->id = tot_head;     //Head给每只warrior一个专属id
		total_s -= CWarrior::strength_ini[sort];   //Head生命值减少
		cout << name; getSortName(sort);
		cout << pwarrior[tot_head]->id << " born with strength " << CWarrior::strength_ini[sort]
			<< ',' << cnt_head[sort]; getSortName(sort);	
		cout << "in " << name << " headquarter" << endl;;
	}
};
int manu(CHeadquarter &head, int i) {
	for (int k = 0; k < warrior_num; k++) {   //如何得知该造哪种worrior？先尝试i号能不能造出来
		if (k) { i = head.sq[i]; }  //如果Head生命不足，遍历NUM个没找到合适的，就凉了
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
		t = 0;     //注意：每次游戏前时间归零！
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
			if (i) i = manu(head1, i);  //只要i不为0，就操纵head1
			if (j) j = manu(head2, j);  //只要j不为0，就操纵head2
			t++;
		}
	}
	return 0;
}