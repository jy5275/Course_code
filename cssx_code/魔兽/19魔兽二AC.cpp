#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string.h>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;
enum weapon { sword, bomb, arrow };
enum warrior { dragon=1, ninja, iceman, lion, wolf };
enum head { red, blue };
int t = 0;
const int warrior_num = 5;
class CHeadquarter;
class CWarrior;
class CWeapon;
bool manu(CHeadquarter &head);
const char *weaponName(weapon w) {
	switch (w) {
	case 0:return "sword";
	case 1:return "bomb";
	case 2:return "arrow";
	default:perror("error036");
	}
}
const char *sortName(warrior s) {
	switch (s) {
	case 1:return "dragon";
	case 2:return "ninja";
	case 3:return "iceman";
	case 4:return "lion";
	case 5:return "wolf";
	default:perror("error055");
	}
}
const char *headName(head h) {
	switch (h) {
	case 0:return "red";    //0---red
	case 1:return "blue";   //1---blue
	default:perror("error066");
	}
}
void PrintTime() {            //时间输出函数！
	if (t < 10) printf("00%d ", t); 
	else if (t < 100) printf("0%d ", t);
	else printf("%d ", t);
}

class CWarrior {               //武士类！
	int strength, id;    //dragon=1, ninja=2, iceman=3, lion=4, wolf=5
	warrior wa;
	static int ini_s[warrior_num + 1];   //各类warrior初始生命值
	CHeadquarter *pHeadOfWarrior = NULL;        //阵营信息，red or blue (0 or 1)
	double morale = -1;        //士气，dragon专属
	int loyalty = -1;          //忠诚度，lion专属
	int cnt_weapon[3] = { 0 }, tot_weapon = 0;  //warrior的武器清单
	CWeapon *pWeapon[3][2] = { { NULL } ,{ NULL } ,{ NULL } };   //warrior的武器库(地址)
	friend class CHeadquarter;
	friend class CWeapon;
	friend bool manu(CHeadquarter &head);
public:
	CWarrior(warrior wa_, CHeadquarter *head_) {  //warrior构造函数:武士类别、所属阵营、初始生命
		pHeadOfWarrior = head_;
		wa = wa_;
		strength = ini_s[wa];
	}
	static void setStrength() {          //静态成员函数，把各类别warrior的生命值初始化，从屏幕输入
		for (int i = 1; i <= warrior_num; i++)
			scanf("%d", &ini_s[i]);
	}
	void holdWeapon(weapon w);              //持武器操作！
};
int CWarrior::ini_s[warrior_num + 1] = { 0 };


class CWeapon {                 //武器类！
	weapon wp;
	int damage;           //sort: sword=0, bomb=1, arrow=2
	CWarrior *pMaster = NULL;   //武器持有人
	CHeadquarter *pHeadOfWeapon = NULL;  //武器所属阵营
public:
	CWeapon(weapon wp_, CWarrior *pMaster_) {   //武器构造函数，初始化武器类别、持有人、所属阵营
		wp = wp_;
		pMaster = pMaster_;
		pHeadOfWeapon = pMaster->pHeadOfWarrior;
	}
	friend class CWarrior;
	friend class CHeadquarter;
};


class CHeadquarter {       //司令部类！
	head h;
	int tot_s, tot_wa = 0;         //剩余生命点、warrior个数
	CWarrior *pWarrior[1000] = { NULL };  //设定Head最多1k个warrior
	int cnt_wa[warrior_num + 1] = { 0 }; //计该Head里各warrior分别多少个
	warrior sq[warrior_num + 1], nowsq;
public:
	CHeadquarter(int M, head h_, const char *sqs, warrior sta) {
		tot_s = M; h = h_; nowsq = sta;
		sscanf(sqs, "%d %d %d %d %d", &sq[1], &sq[2], &sq[3], &sq[4], &sq[5]);
	}
	friend bool manu(CHeadquarter &head);

	void make(warrior w) {     //制造sort型warrior
		PrintTime();          //先输出时间
		cnt_wa[w]++; tot_wa++;   //注意：若++放的位置不对,pWarrior[i]指向一个还是空的地址，很危险！
		pWarrior[tot_wa] = new CWarrior(w, this);  //生成一个新的warrior
		pWarrior[tot_wa]->id = tot_wa;           //Head给每只warrior一个专属id
		tot_s -= CWarrior::ini_s[w];           //Head生命值减少
		printf("%s %s %d ", headName(h), sortName(w), pWarrior[tot_wa]->id);
		printf("born with strength %d,", CWarrior::ini_s[w]);
		printf("%d %s in %s headquarter\n", cnt_wa[w], sortName(w), headName(h));
		nowsq = sq[nowsq];

		if (w == dragon) {      // Dragon made!
			pWarrior[tot_wa]->holdWeapon((weapon)(tot_wa % 3));		//赋予Dragon武器
			printf("It has a %s", weaponName((weapon)(tot_wa % 3)));
			pWarrior[tot_wa]->morale = (double)tot_s / (double)CWarrior::ini_s[w]; //士气
			printf(",and it's morale is %.2lf\n", pWarrior[tot_wa]->morale);
		}
		else if (w == ninja) {      // Ninja made!
			pWarrior[tot_wa]->holdWeapon((weapon)(tot_wa % 3));		//赋予Ninja武器
			pWarrior[tot_wa]->holdWeapon((weapon)((tot_wa + 1) % 3));//再次赋予武器
			printf("It has a %s and a %s\n", weaponName((weapon)(tot_wa % 3)),
				weaponName((weapon)((tot_wa + 1) % 3)));
		}
		else if (w == iceman) {      // Iceman made!
			pWarrior[tot_wa]->holdWeapon((weapon)(tot_wa % 3));		//赋予Iceman武器
			printf("It has a %s\n", weaponName((weapon)(tot_wa % 3)));
		}
		else if (w == lion) {      // Lion made!
			pWarrior[tot_wa]->loyalty = tot_s;     //设置Lion忠诚度！
			printf("It's loyalty is %d\n", pWarrior[tot_wa]->loyalty);
		}
	}
};


bool manu(CHeadquarter &head) {        //Head操作函数！
	for (int k = 0; k < warrior_num; k++) {  
		if (head.tot_s >= CWarrior::ini_s[head.nowsq]) {
			head.make(head.nowsq); 
			return 1;
		}
		head.nowsq = head.sq[head.nowsq];
	}
	PrintTime();     //经历warrior_num个回合还没return走出来，说明这个Head彻底痿了
	printf("%s headquarter stops making warriors\n", headName(head.h));
	return 0;
}

void CWarrior::holdWeapon(weapon w) {   //持武器函数！主语是Warrior
	cnt_weapon[w]++; tot_weapon++;   //更新武器清单
	pWeapon[w][cnt_weapon[w]] = new CWeapon(w, this);  //造新武器
}

int main() {
	int n, all;
	scanf("%d", &n); all = n;
	while (n--) {
		t = 0;     //注意：每次游戏前时间归零
		printf("Case:%d\n", all - n);
		int M; scanf("%d", &M);
		bool redcont = 1, bluecont = 1;
		int sq0[warrior_num] = { 3,1,4,5,2 }, sq1[warrior_num] = { 2,3,5,1,4 };
		CWarrior::setStrength();   //为CWarrior获取初始生命值
		CHeadquarter head1(M, red, "3 1 4 5 2", iceman), 
			head2(M, blue, "2 3 5 1 4", lion);
		while (redcont || bluecont) {
			if (redcont) redcont = manu(head1);  //只要i不为0，就操纵head1
			if (bluecont) bluecont = manu(head2);  //只要j不为0，就操纵head2
			t++;
		}
	}
	return 0;
}