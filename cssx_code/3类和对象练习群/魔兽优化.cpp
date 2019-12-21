#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string.h>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;
int t = 0;
const int warrior_num = 5;    //若需增加游戏角色数量，则需增加warrior_num
class CHeadquarter;
class CWarrior;
class CWeapon;
int manu(CHeadquarter &head, int i); //别忘了声明在前，否则设置不了友元
void getWeaponName(int i) {   //方便起见，在CWarrior类内部用int代表weapon
	switch (i){               //但cout时要把类别标识符int转成string
	case 0:cout << " a sword"; break;
	case 1:cout << " a bomb"; break;
	case 2:cout << " a arrow"; break;
	default:break;
	}
}
void getSortName(int i) {     //方便起见，在CWarrior类内部用int标记warrior类别
	switch (i){               //但cout时要把类别标识符int转成string
	case 1:cout << " dragon "; break;
	case 2:cout << " ninja "; break;
	case 3:cout << " iceman "; break;
	case 4:cout << " lion "; break;
	case 5:cout << " wolf "; break;
	}
}
void getHeadName(int name) {   //方便起见，在CWarrior类内部用int标记所属Head
	switch(name){              //但cout时要把Head标识符int转成string
	case 0:cout << "red"; break;    //0---red
	case 1:cout << "blue"; break;   //1---blue
	}
}
void PrintTime() {            //时间输出函数！
	if (t < 10) cout << "00" << t << ' ';
	else if (t < 100) cout << "0" << t << ' ';
	else cout << t << ' ';
}


class CWarrior {               //武士类！
	int sort, strength, id;    //sort:dragon=1, ninja=2, iceman=3, lion=4, wolf=5
	static int strength_ini[warrior_num + 1];   //各类warrior初始生命值
	CHeadquarter *pHeadOfWarrior = NULL;        //阵营信息，red or blue (0 or 1)
	double morale = -1;        //士气，dragon专属
	int loyalty = -1;          //忠诚度，lion专属
	int cnt_weapon[3] = { 0 }, tot_weapon = 0;  //warrior的武器清单
	CWeapon *pWeapon[3][2] = { { NULL } ,{ NULL } ,{ NULL } };          //warrior的武器库(地址)
	friend class CHeadquarter;
	friend class CWeapon;
	friend int manu(CHeadquarter &head, int i);
public:
	CWarrior(int sort_, CHeadquarter *head_) {  //warrior构造函数:武士类别、所属阵营、初始生命
		pHeadOfWarrior = head_;
		sort = sort_;
		strength = strength_ini[sort];
	}
	static void setStrength() {          //静态成员函数，把各类别warrior的生命值初始化，从屏幕输入
		for (int i = 1; i <= warrior_num; i++)
			cin >> strength_ini[i];
	}
	void holdWeapon(int i);              //持武器操作！
};
int CWarrior::strength_ini[warrior_num + 1] = { 0 };


class CWeapon {                 //武器类！
	int sort, damage;           //sort: sword=0, bomb=1, arrow=2
	CWarrior *pMaster = NULL;   //武器持有人
	CHeadquarter *pHeadOfWeapon = NULL;  //武器所属阵营
public:
	CWeapon(int sort_, CWarrior *pMaster_) {   //武器构造函数，初始化武器类别、持有人、所属阵营
		sort = sort_;
		pMaster = pMaster_;
		pHeadOfWeapon = pMaster->pHeadOfWarrior;
	}
	friend class CWarrior;
	friend class CHeadquarter;
};


class CHeadquarter {       //司令部类！
	int name;              //司令部正式编号，可用getHeadName转为char*
	int total_s, tot_warrior = 0;         //剩余生命点、warrior个数
	CWarrior *pWarrior[1000] = { NULL };  //在此设定每个Head最多有1000个warrior
	int cnt_warrior[warrior_num + 1] = { 0 }; //cnt是计数器,计该Headquarter里各warrior分别有多少个，dragon=1, ninja=2, iceman=3, lion=4, wolf=5
	int sq[warrior_num + 1];    //记录顺序表里某个warrior的下一个warrior类别编号,譬如sq[1]=2意为dragon过了轮到ninja
public:
	CHeadquarter(int M, int n_,int *psq){ //构造函数，把Head里的总生命值、name编号、warrior制造顺序表都初始化
		total_s = M; name = n_;
		for (int i = 1; i <= warrior_num; i++) 
			sq[i] = *(psq + i - 1);
	}
	friend int manu(CHeadquarter &head, int i);
	void make(int sort) {     //制造sort型worrior
		PrintTime();          //先输出时间
		cnt_warrior[sort]++; tot_warrior++;   //注意：若++放的位置不对,pWarrior[i]指向一个还是空的地址，很危险！
		pWarrior[tot_warrior] = new CWarrior(sort, this);  //生成一个新的warrior
		pWarrior[tot_warrior]->id = tot_warrior;           //Head给每只warrior一个专属id
		total_s -= CWarrior::strength_ini[sort];           //Head生命值减少
		getHeadName(name); getSortName(sort);
		cout << pWarrior[tot_warrior]->id << " born with strength " << CWarrior::strength_ini[sort]
			<< ',' << cnt_warrior[sort]; getSortName(sort);
		cout << "in "; getHeadName(name); cout << " headquarter" << endl;
		if (sort == 1) {      // Dragon made!
			pWarrior[tot_warrior]->holdWeapon(tot_warrior % 3);    //赋予Dragon武器！
			cout << "It has"; getWeaponName(tot_warrior % 3);
			pWarrior[tot_warrior]->morale = (double)total_s / (double)CWarrior::strength_ini[sort]; //设置Dragon士气！
			cout << ",and it's morale is " << fixed << setprecision(2) << pWarrior[tot_warrior]->morale << endl;
		}
		if (sort == 2) {      // Ninja made!
			pWarrior[tot_warrior]->holdWeapon(tot_warrior % 3);         //赋予Ninja武器！
			pWarrior[tot_warrior]->holdWeapon((tot_warrior + 1) % 3);   //再次赋予Ninja武器！
			cout << "It has"; getWeaponName(tot_warrior % 3); cout << " and";
			getWeaponName((tot_warrior + 1) % 3); cout << endl;
		}
		if (sort == 3) {      // Iceman made!
			pWarrior[tot_warrior]->holdWeapon(tot_warrior % 3);         //赋予Iceman武器！
			cout << "It has"; getWeaponName(tot_warrior % 3);cout << endl;
		}
		if (sort == 4) {      // Lion made!
			pWarrior[tot_warrior]->loyalty = total_s;     //设置Lion忠诚度！
			cout << "It's loyalty is " << pWarrior[tot_warrior]->loyalty << endl;
		}
	}
};


int manu(CHeadquarter &head, int i) {        //Head操作函数！
	for (int k = 0; k < warrior_num; k++) {   //如何得知该造哪种worrior？先尝试i号能不能造出来
		if (k) { i = head.sq[i]; }  //如果Head生命不足，遍历NUM个没找到合适的，就凉了
		if (head.total_s >= CWarrior::strength_ini[i]) { head.make(i); return head.sq[i]; }
	}
	PrintTime();     //经历warrior_num个回合还没return走出来，说明这个Head彻底痿了
	getHeadName(head.name);
	cout << " headquarter stops making warriors" << endl;
	return 0;
}

void CWarrior::holdWeapon(int i) {   //持武器函数！主语是Warrior
	cnt_weapon[i]++; tot_weapon++;   //更新武器清单
	pWeapon[i][cnt_weapon[i]] = new CWeapon(i, this);  //造新武器
}


int main() {
	int n, all;
	cin >> n; all = n;
	while (n--) {
		t = 0;     //注意：每次游戏前时间归零！
		cout << "Case:" << all - n << endl;
		int  M, i = 3, j = 4;    //i和j记录head下一个该制造哪种warrior
		cin >> M;
		int sq0[warrior_num] = { 3,1,4,5,2 }, sq1[warrior_num] = { 2,3,5,1,4 };
		CWarrior::setStrength();   //为CWarrior获取初始生命值
		CHeadquarter head1(M, 0, sq0), head2(M, 1, sq1);    //建立2个Head
		while (i || j) {   //i为0即司令部已无生命元了
			if (i) i = manu(head1, i);  //只要i不为0，就操纵head1
			if (j) j = manu(head2, j);  //只要j不为0，就操纵head2
			t++;
		}
	}
	return 0;
}