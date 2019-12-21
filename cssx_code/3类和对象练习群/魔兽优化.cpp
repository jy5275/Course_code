#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string.h>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;
int t = 0;
const int warrior_num = 5;    //����������Ϸ��ɫ��������������warrior_num
class CHeadquarter;
class CWarrior;
class CWeapon;
int manu(CHeadquarter &head, int i); //������������ǰ���������ò�����Ԫ
void getWeaponName(int i) {   //�����������CWarrior���ڲ���int����weapon
	switch (i){               //��coutʱҪ������ʶ��intת��string
	case 0:cout << " a sword"; break;
	case 1:cout << " a bomb"; break;
	case 2:cout << " a arrow"; break;
	default:break;
	}
}
void getSortName(int i) {     //�����������CWarrior���ڲ���int���warrior���
	switch (i){               //��coutʱҪ������ʶ��intת��string
	case 1:cout << " dragon "; break;
	case 2:cout << " ninja "; break;
	case 3:cout << " iceman "; break;
	case 4:cout << " lion "; break;
	case 5:cout << " wolf "; break;
	}
}
void getHeadName(int name) {   //�����������CWarrior���ڲ���int�������Head
	switch(name){              //��coutʱҪ��Head��ʶ��intת��string
	case 0:cout << "red"; break;    //0---red
	case 1:cout << "blue"; break;   //1---blue
	}
}
void PrintTime() {            //ʱ�����������
	if (t < 10) cout << "00" << t << ' ';
	else if (t < 100) cout << "0" << t << ' ';
	else cout << t << ' ';
}


class CWarrior {               //��ʿ�࣡
	int sort, strength, id;    //sort:dragon=1, ninja=2, iceman=3, lion=4, wolf=5
	static int strength_ini[warrior_num + 1];   //����warrior��ʼ����ֵ
	CHeadquarter *pHeadOfWarrior = NULL;        //��Ӫ��Ϣ��red or blue (0 or 1)
	double morale = -1;        //ʿ����dragonר��
	int loyalty = -1;          //�ҳ϶ȣ�lionר��
	int cnt_weapon[3] = { 0 }, tot_weapon = 0;  //warrior�������嵥
	CWeapon *pWeapon[3][2] = { { NULL } ,{ NULL } ,{ NULL } };          //warrior��������(��ַ)
	friend class CHeadquarter;
	friend class CWeapon;
	friend int manu(CHeadquarter &head, int i);
public:
	CWarrior(int sort_, CHeadquarter *head_) {  //warrior���캯��:��ʿ���������Ӫ����ʼ����
		pHeadOfWarrior = head_;
		sort = sort_;
		strength = strength_ini[sort];
	}
	static void setStrength() {          //��̬��Ա�������Ѹ����warrior������ֵ��ʼ��������Ļ����
		for (int i = 1; i <= warrior_num; i++)
			cin >> strength_ini[i];
	}
	void holdWeapon(int i);              //������������
};
int CWarrior::strength_ini[warrior_num + 1] = { 0 };


class CWeapon {                 //�����࣡
	int sort, damage;           //sort: sword=0, bomb=1, arrow=2
	CWarrior *pMaster = NULL;   //����������
	CHeadquarter *pHeadOfWeapon = NULL;  //����������Ӫ
public:
	CWeapon(int sort_, CWarrior *pMaster_) {   //�������캯������ʼ��������𡢳����ˡ�������Ӫ
		sort = sort_;
		pMaster = pMaster_;
		pHeadOfWeapon = pMaster->pHeadOfWarrior;
	}
	friend class CWarrior;
	friend class CHeadquarter;
};


class CHeadquarter {       //˾��࣡
	int name;              //˾���ʽ��ţ�����getHeadNameתΪchar*
	int total_s, tot_warrior = 0;         //ʣ�������㡢warrior����
	CWarrior *pWarrior[1000] = { NULL };  //�ڴ��趨ÿ��Head�����1000��warrior
	int cnt_warrior[warrior_num + 1] = { 0 }; //cnt�Ǽ�����,�Ƹ�Headquarter���warrior�ֱ��ж��ٸ���dragon=1, ninja=2, iceman=3, lion=4, wolf=5
	int sq[warrior_num + 1];    //��¼˳�����ĳ��warrior����һ��warrior�����,Ʃ��sq[1]=2��Ϊdragon�����ֵ�ninja
public:
	CHeadquarter(int M, int n_,int *psq){ //���캯������Head���������ֵ��name��š�warrior����˳�����ʼ��
		total_s = M; name = n_;
		for (int i = 1; i <= warrior_num; i++) 
			sq[i] = *(psq + i - 1);
	}
	friend int manu(CHeadquarter &head, int i);
	void make(int sort) {     //����sort��worrior
		PrintTime();          //�����ʱ��
		cnt_warrior[sort]++; tot_warrior++;   //ע�⣺��++�ŵ�λ�ò���,pWarrior[i]ָ��һ�����ǿյĵ�ַ����Σ�գ�
		pWarrior[tot_warrior] = new CWarrior(sort, this);  //����һ���µ�warrior
		pWarrior[tot_warrior]->id = tot_warrior;           //Head��ÿֻwarriorһ��ר��id
		total_s -= CWarrior::strength_ini[sort];           //Head����ֵ����
		getHeadName(name); getSortName(sort);
		cout << pWarrior[tot_warrior]->id << " born with strength " << CWarrior::strength_ini[sort]
			<< ',' << cnt_warrior[sort]; getSortName(sort);
		cout << "in "; getHeadName(name); cout << " headquarter" << endl;
		if (sort == 1) {      // Dragon made!
			pWarrior[tot_warrior]->holdWeapon(tot_warrior % 3);    //����Dragon������
			cout << "It has"; getWeaponName(tot_warrior % 3);
			pWarrior[tot_warrior]->morale = (double)total_s / (double)CWarrior::strength_ini[sort]; //����Dragonʿ����
			cout << ",and it's morale is " << fixed << setprecision(2) << pWarrior[tot_warrior]->morale << endl;
		}
		if (sort == 2) {      // Ninja made!
			pWarrior[tot_warrior]->holdWeapon(tot_warrior % 3);         //����Ninja������
			pWarrior[tot_warrior]->holdWeapon((tot_warrior + 1) % 3);   //�ٴθ���Ninja������
			cout << "It has"; getWeaponName(tot_warrior % 3); cout << " and";
			getWeaponName((tot_warrior + 1) % 3); cout << endl;
		}
		if (sort == 3) {      // Iceman made!
			pWarrior[tot_warrior]->holdWeapon(tot_warrior % 3);         //����Iceman������
			cout << "It has"; getWeaponName(tot_warrior % 3);cout << endl;
		}
		if (sort == 4) {      // Lion made!
			pWarrior[tot_warrior]->loyalty = total_s;     //����Lion�ҳ϶ȣ�
			cout << "It's loyalty is " << pWarrior[tot_warrior]->loyalty << endl;
		}
	}
};


int manu(CHeadquarter &head, int i) {        //Head����������
	for (int k = 0; k < warrior_num; k++) {   //��ε�֪��������worrior���ȳ���i���ܲ��������
		if (k) { i = head.sq[i]; }  //���Head�������㣬����NUM��û�ҵ����ʵģ�������
		if (head.total_s >= CWarrior::strength_ini[i]) { head.make(i); return head.sq[i]; }
	}
	PrintTime();     //����warrior_num���غϻ�ûreturn�߳�����˵�����Head��������
	getHeadName(head.name);
	cout << " headquarter stops making warriors" << endl;
	return 0;
}

void CWarrior::holdWeapon(int i) {   //������������������Warrior
	cnt_weapon[i]++; tot_weapon++;   //���������嵥
	pWeapon[i][cnt_weapon[i]] = new CWeapon(i, this);  //��������
}


int main() {
	int n, all;
	cin >> n; all = n;
	while (n--) {
		t = 0;     //ע�⣺ÿ����Ϸǰʱ����㣡
		cout << "Case:" << all - n << endl;
		int  M, i = 3, j = 4;    //i��j��¼head��һ������������warrior
		cin >> M;
		int sq0[warrior_num] = { 3,1,4,5,2 }, sq1[warrior_num] = { 2,3,5,1,4 };
		CWarrior::setStrength();   //ΪCWarrior��ȡ��ʼ����ֵ
		CHeadquarter head1(M, 0, sq0), head2(M, 1, sq1);    //����2��Head
		while (i || j) {   //iΪ0��˾���������Ԫ��
			if (i) i = manu(head1, i);  //ֻҪi��Ϊ0���Ͳ���head1
			if (j) j = manu(head2, j);  //ֻҪj��Ϊ0���Ͳ���head2
			t++;
		}
	}
	return 0;
}