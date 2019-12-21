#include<iostream>
#include<vector>
#include<string>
#include<set>
#include<cmath>
#include<list>
#include<memory>
#include<map>
#include<algorithm>
#include<queue>
#include<iomanip>
#include<fstream>
using namespace std;
class CHeadquarter; class CWarrior; class CWeapon; class CCity;
CCity *pCity[22] = { NULL };
int t = 0, M, N, R, K, T, someoneWin = 0, gameOver = 0;//˾���ʼ����M��������N��arrow������R��Lion�ҳϽ�K��ʱ������T   
const int warrior_num = 5;  //����������ʿ����������������warrior_num
void PrintWeaponName(int i) {    //�����������CWarrior���ڲ���int����weapon
	switch (i) {            //��coutʱҪ������ʶ��intת��string
	case 0:cout << " a sword"; break;
	case 1:cout << " a bomb"; break;
	case 2:cout << " a arrow"; break;
	default:break;
	}
}
void PrintSortName(int i) {      //�����������CWarrior���ڲ���int���warrior���
	switch (i) {               //��coutʱҪ������ʶ��intת��string
	case 1:cout << " dragon "; break;
	case 2:cout << " ninja "; break;
	case 3:cout << " iceman "; break;
	case 4:cout << " lion "; break;
	case 5:cout << " wolf "; break;
	}
}
void PrintHeadName(int name) {     //�����������CWarrior���ڲ���int�������Head
	switch (name) {              //��coutʱҪ��Head��ʶ��intת��string
	case 0:cout << "red"; break;    //0---red
	case 1:cout << "blue"; break;   //1---blue
	}
}
int rival(int n) {
	if (n == 1)return 0;
	else if (n == 0)return 1;
	else {
		cerr << "Error:Head get wrong name!" << endl;
		return 0;
	}
}
void PrintTime() {               //ʱ�����������
	int hour = t / 60, min = t - hour * 60;
	if (hour < 10) cout << "00" << hour << ':';
	else if (hour < 100) cout << "0" << hour << ':';
	else cout << hour << ':';
	if (min == 0)cout << "00 ";
	else if (min < 10)cout << "0" << min << " ";
	else cout << min << " ";
}
class CCity {
	int locOfCity, numOfWarrior = 0, strengthOfCity = 0, changeFlagto[2] = { 0 }, strengthOfCity_buffer = 0;
	int redRequest = 0, blueRequest = 0;
	friend class CHeadquarter; friend class CWolf; friend class CIceman; friend class CNinja;
	friend class CWarrior; friend class CLion; friend class CDragon;
public:
	CCity(int l_) :locOfCity(l_) {}    //���еĹ��캯��
	CWarrior *pWarriorOfCity[2] = { NULL }; //pWarriorOfCity[0]ָ��red��ʿ��pWarriorOfCity[1]ָ��blue��ʿ
	CHeadquarter *pHeadOfCity = NULL;       //�˳�����
	void yieldStrength() { strengthOfCity += 10; }   //������������Ԫ��
	void tryToGiveStrength();               //���г��Ը����Լ�����Ԫ��
	int tryToBombCity();                    //38��������������ը����??
	void tryToWageWar();                    //40���г��Կ�ս?��
};
/////////////////��ʿ�࣡//////////////////////////////////////////////��ʿ�࣡//////////////////////////////////////////////////////////////////

class CWarrior {          //��ʿ�࣡�����࣡
protected:
	bool shotDead = 0, reachEnemyHead = 0;  //sort:dragon=1, ninja=2, iceman=3, lion=4, wolf=5
	int cnt_weapon[3] = { 0 }, id;  //warrior�������嵥
	int forceOfWarrior;
	CCity *pLocOfWarrior = NULL;            //��¼���Warrior�ִ��λ�ã����У�
	CHeadquarter *pHeadOfWarrior = NULL;        //��Ӫ��Ϣ��red or blue (0 or 1)
	friend class CHeadquarter; friend class CWeapon;
	friend class CCity; friend void PrintMove(CWarrior *pRA, CWarrior *pBA);
public:
	int sort, strength;
	CWeapon *pWeapon[3] = { NULL , NULL  , NULL };          //warrior��������(��ַ)
	static int strength_ini[warrior_num + 1];     //����warrior��ʼ����ֵ
	static int forceOfWarriors[warrior_num + 1];  //����warrior������ 
	CWarrior(int sort_, CHeadquarter *pHead_);    //warrior���캯��:��ʿ���������Ӫ����ʼ����
	virtual ~CWarrior();                          //warrior������ע��������
	static void setStrength() {                   //��̬��Ա�������Ѹ����warrior������ֵ��ʼ��������Ļ����
		for (int i = 1; i <= warrior_num; i++)
			cin >> strength_ini[i];
	}
	static void setForceWarrior() {
		for (int i = 1; i <= warrior_num; i++)    //��̬��Ա�������Ѹ����warrior�Ĺ�������ʼ��������Ļ����
			cin >> forceOfWarriors[i];
	}
	void Shot() {                     //������������������˺���
		strength -= R;
		if (strength <= 0) { strength = 0; shotDead = 1; }  //�м�������
	}
	void tryToUseArrow();             //35���������û�й���Ҳ�ܵ��ã�
	void holdWeapon(int i);           //������������
	int calcDamageOfSword();          //�������Warrior��sword��damage�ӳɣ�
	int IwillDieHere();               //��ǰ�����Լ�������᲻�ᱻɱ����
	void Attack(CWarrior *pAttacked);
	void Hurted(int nPower) {        //Warrior�ܵ��˺���
		strength -= nPower;
		if (strength < 0)strength = 0;
	}
	virtual void FightBack(CWarrior *pFighted) = 0;  //���麯����ÿ�˶��У�
	void PrintFightback(CWarrior *pFighted);
	virtual void winWar() = 0;        //ȡ��ս��ʤ����
	void weaponReport_warrior();
};
int CWarrior::strength_ini[warrior_num + 1] = { 0 };
int CWarrior::forceOfWarriors[warrior_num + 1] = { 0 };

///////////////��ʿ�����࣡///////////////////////////////////////////��ʿ�����࣡///////////////////////////////////////////////////��ʿ�����࣡

class CDragon :public CWarrior {
	double morale;                          //Dragon����ʿ����
	friend class CHeadquarter; friend class CCity;
public:
	CDragon(CHeadquarter *pHead_) : CWarrior(1, pHead_) {}   //Dragon���캯����
	void FightBack(CWarrior *pFighted);
	void winWar();
	void yell();
};

class CLion :public CWarrior {
	int loyalty;                     //Lion�����ҳ϶ȣ�
	friend class CHeadquarter;
public:
	CLion(CHeadquarter *pHead_) : CWarrior(4, pHead_) {}   //Lion���캯����
	void FightBack(CWarrior *pFighted);
	void tryToEscape();                         //Lion��������!
	void winWar();
	void loseLoy() { loyalty -= K; }
};

class CWolf :public CWarrior {
public:
	CWolf(CHeadquarter *pHead_) : CWarrior(5, pHead_) {}   //Dragon���캯����
	void FightBack(CWarrior *pFighted);
	void winWar();
	void capWeapon(CWarrior* pDead);
};

class CNinja :public CWarrior {
public:
	CNinja(CHeadquarter *pHead_) : CWarrior(2, pHead_) {}   //Dragon���캯����
	void FightBack(CWarrior *pFighted) {}    //Ninja�����������Ӳ�������
	void winWar();
};

class CIceman :public CWarrior {
	int cumPace = 0;
public:
	void icemanMove();
	CIceman(CHeadquarter *pHead_) : CWarrior(3, pHead_) {}   //���˹��캯����
	void FightBack(CWarrior *pFighted);
	void winWar();
};

/////////////�����࣡/////////////////////////////////////////////�����࣡////////////////////////////////////////////////////////////////////////////////

class CWeapon {                 //�����࣡�����࣡
	int sort;                   //sort: sword=0, bomb=1, arrow=2
	CWarrior *pMaster = NULL;   //����������
	friend class CWolf;
public:
	CWeapon(int sort_, CWarrior *pMaster_) :sort(sort_), pMaster(pMaster_) {}
	virtual void wearOut() = 0;
	virtual ~CWeapon() {                      //������ͳһ����������
		pMaster->cnt_weapon[sort] -= 1;       //ע������������
		pMaster->pWeapon[sort] = NULL;
	}
};
class CSword :public CWeapon {
	int damage;
	friend class CWarrior;
	friend class CHeadquarter;
public:
	CSword(CWarrior *pM_, int damage_) :CWeapon(0, pM_), damage(damage_) {}
	void wearOut() {
		damage = floor(damage * 0.8);         //swordÿ�ù�һ��Ҫ�𻵣�
		if (damage == 0) delete this;         //damage��Ϊ0��Ҫ���ϣ�
	}
};
class CBomb :public CWeapon {
	friend class CWarrior;
	friend class CHeadquarter;
public:
	CBomb(CWarrior *pM_) :CWeapon(1, pM_) {}
	void wearOut() {}                         //Bombһ�ã�˫���������������ظ�����
};
class CArrow :public CWeapon {
	int left;
	friend class CWarrior;
	friend class CHeadquarter;
public:
	CArrow(CWarrior *pM_) :CWeapon(2, pM_), left(3) {}
	void wearOut() {                          //������ʣ����֧Arrow
		if (left > 1)left -= 1;               //����1֧Arrow
		else if (left <= 1) delete this;      //Arrow�ù��ˣ������ɣ�
	}
};

void CIceman::icemanMove() {
	cumPace++;
	if (cumPace >= 2) {
		strength -= 9;
		if (strength <= 0)strength = 1;
		forceOfWarrior += 20;
		cumPace = 0;
	}
}

////////////////˾��࣡/////////////////////////////////////////////////˾��࣡////////////////////////////////////////

class CHeadquarter {                                    //˾��࣡
	int total_s, buffer = 0, tot_warrior = 0, name, takeOver = 0;   //ʣ�������㡢warrior����
	int sq[warrior_num + 1];    //��¼˳�����ĳwarrior�¸�warrior�����,��sq[1]=2��Ϊdragon�����ֵ�ninja
								//CWarrior *pWarrior[1000] = { NULL };      //�ڴ��趨ÿ��Head�����1000��warrior
	vector<CWarrior*> pWarrior;
	friend class CWarrior; friend class CLion; friend class CDragon; friend class CWolf; friend class CNinja;
	friend class CCity; friend class CIceman; friend class CWeapon;
	friend void PrintMove(CWarrior *pRA, CWarrior *pBA);
public:
	CHeadquarter * enemyHead = NULL;
	CHeadquarter(int M, int n_, int *psq) { //���캯������Head��������ֵ��name��š�warrior����˳�����ʼ��
		total_s = M; name = n_;
		for (int i = 1; i <= warrior_num; i++)
			sq[i] = *(psq + i - 1);
		pWarrior.push_back(0);
	}
	CWarrior *headMove() {                       //10������ʿ��ǰ��һ����
		CWarrior *pArrive = NULL;
		for (int i = 1; i <= tot_warrior; i++) {
			if (pWarrior[i] == NULL || pWarrior[i]->reachEnemyHead == 1)continue;  //��ȥ��
			if (name == 0) {                  //red��blue�ֿ�����,�ȿ����ǲ���red
				pWarrior[i]->pLocOfWarrior->numOfWarrior -= 1;              //ע��������������City���仧
				pWarrior[i]->pLocOfWarrior->pWarriorOfCity[0] = NULL;
				pWarrior[i]->pLocOfWarrior = pCity[pWarrior[i]->pLocOfWarrior->locOfCity + 1];
				pWarrior[i]->pLocOfWarrior->numOfWarrior += 1;
				if (pWarrior[i]->pLocOfWarrior->pWarriorOfCity[0] && pWarrior[i]->pLocOfWarrior->locOfCity != N + 1)
					cout << "Error:Red-overcrowded City��" << endl;
				pWarrior[i]->pLocOfWarrior->pWarriorOfCity[0] = pWarrior[i];
				if (pWarrior[i]->pLocOfWarrior->locOfCity == N + 1) {   //red��ʿ����blue˾��������ˣ�
					pWarrior[i]->reachEnemyHead = 1;
					takeOver++; pArrive = pWarrior[i];
				}
			}
			else {             //�ٿ����ǲ���blue
				pWarrior[i]->pLocOfWarrior->numOfWarrior -= 1;            //ע��������������City���仧
				pWarrior[i]->pLocOfWarrior->pWarriorOfCity[1] = NULL;
				pWarrior[i]->pLocOfWarrior = pCity[pWarrior[i]->pLocOfWarrior->locOfCity - 1];
				pWarrior[i]->pLocOfWarrior->numOfWarrior += 1;
				if (pWarrior[i]->pLocOfWarrior->pWarriorOfCity[1] && pWarrior[i]->pLocOfWarrior->locOfCity != 0)
					cout << "Error:Blue-overcrowded City��" << endl;
				pWarrior[i]->pLocOfWarrior->pWarriorOfCity[1] = pWarrior[i];
				if (pWarrior[i]->pLocOfWarrior->locOfCity == 0) {   //blue��ʿ����ted˾��������ˣ�
					pWarrior[i]->reachEnemyHead = 1;
					takeOver++; pArrive = pWarrior[i];
				}
			}
			if (pWarrior[i]->sort == 3) ((CIceman*)pWarrior[i])->icemanMove();
		}
		return pArrive;
	}
	int make(int sort) {      //����sort��worrior�����ذ�sq��һ���������sort���
		if (total_s < CWarrior::strength_ini[sort])return sort; //˾�Ѫ�����ˣ�����ȥ�ɣ�
		PrintTime();          //�����ʱ��
		tot_warrior++;   //ע�⣺��++�ŵ�λ�ò���,pWarrior[i]ָ��յ�ַ����Σ�գ�
		total_s -= CWarrior::strength_ini[sort];         //Head����ֵ����
		PrintHeadName(name); PrintSortName(sort);
		cout << tot_warrior << " born" << endl;
		if (sort == 1) {      // Dragon made!
			CDragon *pD = new CDragon(this);      //����һ���µ�Dragon�������ĵ�ַ����*pD��
			pD->id = tot_warrior;                 //Head��ÿֻwarriorһ��ר��id
			pD->morale = (double)total_s / (double)CWarrior::strength_ini[sort]; //����Dragonʿ����
			pD->holdWeapon(tot_warrior % 3);      //����Dragon������
			cout << "Its morale is " << fixed << setprecision(2) << pD->morale << endl;
			pWarrior.push_back(pD);             //����ʱpD�Ž�������ָ������

		}
		if (sort == 2) {      // Ninja made!
			CNinja *pN = new CNinja(this);         //����һ���µ�Dragon�������ĵ�ַ����*pD��
			pN->id = tot_warrior;                  //Head��ÿֻwarriorһ��ר��id
			pN->holdWeapon(tot_warrior % 3);       //����Ninja������
			pN->holdWeapon((tot_warrior + 1) % 3); //�ٴθ���Ninja������
			pWarrior.push_back(pN);              //����ʱpN�Ž�������ָ������
		}
		if (sort == 3) {      // Iceman made!
			CIceman *pI = new CIceman(this);       //����һ���µ�Dragon�������ĵ�ַ����*pD��
			pI->id = tot_warrior;
			pI->holdWeapon(tot_warrior % 3);       //����Iceman������
			pWarrior.push_back(pI);              //����ʱpI�Ž�������ָ������
		}
		if (sort == 4) {      // Lion made!
			CLion *pL = new CLion(this);           //����һ���µ�Dragon�������ĵ�ַ����*pD��
			pL->id = tot_warrior;
			pL->loyalty = total_s;                 //����Lion�ҳ϶ȣ�
			cout << "Its loyalty is " << pL->loyalty << endl;
			pWarrior.push_back(pL);            //����ʱpL�Ž�������ָ������
		}
		if (sort == 5) {      // Wolf made!
			CWolf *pW = new CWolf(this);           //����һ���µ�Dragon�������ĵ�ַ����*pD��
			pW->id = tot_warrior;
			pWarrior.push_back(pW);            //����ʱpL�Ž�������ָ������
		}
		return sq[sort];
	}
	void allocate() {
		if (name == 0) {    //Red��
			for (int i = N; i >= 1; i--) {
				if (pCity[i]->redRequest == 1) {   //�ڸó��з�������Ԫ����
					pCity[i]->redRequest = 0;
					if (total_s >= 8) {            //˾�������Ԫ�Ž�����
						total_s -= 8;
						pCity[i]->pWarriorOfCity[0]->strength += 8;
					}
				}
			}
		}
		else {              //Blue��
			for (int i = 1; i <= N; i++) {
				if (pCity[i]->blueRequest == 1) {   //�ڸó��з�������Ԫ����
					pCity[i]->blueRequest = 0;
					if (total_s >= 8) {            //˾�������Ԫ�Ž�����
						total_s -= 8;
						pCity[i]->pWarriorOfCity[1]->strength += 8;
					}
				}
			}
		}
	}
	void pushBuffer() {       //Push strength in buffer into total_s��
		total_s += buffer;
		buffer = 0;
	}
	void strengthReport() {   //14)˾���������Ԫ������
		PrintTime(); cout << total_s << " elements in "; PrintHeadName(name); cout << " headquarter" << endl;
	}
	void weaponReport_head() {  //15)��ʿ�������������
		for (int i = 0; i <= N + 1; i++) {  //�����򶫱������г��У�����з�˾�Ҳ���棡
			if (pCity[i]->pWarriorOfCity[name]) {   //�����������ҷ�Warrior��
				pCity[i]->pWarriorOfCity[name]->weaponReport_warrior();
			}
		}
	}
	~CHeadquarter();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////warrior������������/////////////////////////////////////////////warrior������������////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CWarrior::CWarrior(int sort_, CHeadquarter *pHead_) {    //warrior���캯��:��ʿ���������Ӫ����ʼ����
	pHeadOfWarrior = pHead_;
	sort = sort_;
	strength = strength_ini[sort];
	forceOfWarrior = forceOfWarriors[sort];
	if (pHead_->name == 0) {
		pLocOfWarrior = pCity[0];
		pCity[0]->pWarriorOfCity[0] = this;
		pCity[0]->numOfWarrior++;
	} //red�趨λ��
	else {
		pLocOfWarrior = pCity[N + 1];
		pCity[N + 1]->pWarriorOfCity[1] = this;
		pCity[N + 1]->numOfWarrior++;
	}         //blue�趨λ��
}

void CWarrior::holdWeapon(int i) {   //������������������Warrior
	cnt_weapon[i]++;                 //���������嵥
	if (i == 0) {
		pWeapon[0] = new CSword(this, floor(forceOfWarrior*0.2));  //��������
		if (((CSword*)pWeapon[0])->damage <= 0)delete pWeapon[0];  //һ����������һ�ѱ��ϵ�Sword
	}
	else if (i == 1)
		pWeapon[1] = new CBomb(this);  //��������
	else if (i == 2)
		pWeapon[2] = new CArrow(this);  //��������
	else cerr << "Error 2" << endl;
}

void CLion::tryToEscape() {     //Lion��������!
	if (loyalty > 0)return;
	if (pHeadOfWarrior->name == 0 && pLocOfWarrior->locOfCity == N + 1)return;
	else if (pHeadOfWarrior->name == 1 && pLocOfWarrior->locOfCity == 0)return;
	PrintTime(); PrintHeadName(pHeadOfWarrior->name); PrintSortName(sort);
	cout << ' ' << id << " ran away" << endl;
	delete this;
}

void PrintMove(CWarrior *pRA, CWarrior *pBA) {  //����ָ��ӦΪNULL��������Warrior����з�˾�
	if (pBA) {       //����red˾����
		PrintTime(); PrintHeadName(1); PrintSortName(pBA->sort);
		cout << pBA->id << " reached red headquarter with " <<
			pBA->strength << " elements and force " << pBA->forceOfWarrior << endl;
		if (pBA->pHeadOfWarrior->takeOver == 2) {
			PrintTime(); PrintHeadName(0); cout << " headquarter was taken" << endl;
			gameOver = 1;
		}
	}
	for (int i = 1; i <= N; i++) {            //�����򶫱�������City
		if (pCity[i]->pWarriorOfCity[0]) {    //red
			PrintTime(); PrintHeadName(0); PrintSortName(pCity[i]->pWarriorOfCity[0]->sort);
			cout << pCity[i]->pWarriorOfCity[0]->id << " marched to city " << i << " with " <<
				pCity[i]->pWarriorOfCity[0]->strength << " elements and force " <<
				pCity[i]->pWarriorOfCity[0]->forceOfWarrior << endl;
		}
		if (pCity[i]->pWarriorOfCity[1]) {      //blue
			PrintTime(); PrintHeadName(1); PrintSortName(pCity[i]->pWarriorOfCity[1]->sort);
			cout << pCity[i]->pWarriorOfCity[1]->id << " marched to city " << i << " with " <<
				pCity[i]->pWarriorOfCity[1]->strength << " elements and force " <<
				pCity[i]->pWarriorOfCity[1]->forceOfWarrior << endl;
		}
	}
	if (pRA) {       //����blue˾����
		PrintTime(); PrintHeadName(0); PrintSortName(pRA->sort);
		cout << pRA->id << " reached blue headquarter with " <<
			pRA->strength << " elements and force " << pRA->forceOfWarrior << endl;
		if (pRA->pHeadOfWarrior->takeOver == 2) {
			PrintTime(); PrintHeadName(1); cout << " headquarter was taken" << endl;
			gameOver = 1;
		}
	}
}

void CCity::tryToGiveStrength() {              //���г��Ը����Լ�����Ԫ��
	if (numOfWarrior == 1) {            //�������ֻ��һ��warrior    
		if (pWarriorOfCity[0]) {        //��Ч����red��
			PrintTime(); PrintHeadName(0); PrintSortName(pWarriorOfCity[0]->sort);
			cout << pWarriorOfCity[0]->id << " earned " << strengthOfCity << " elements for his headquarter" << endl;
			pWarriorOfCity[0]->pHeadOfWarrior->total_s += strengthOfCity;
			strengthOfCity = 0;
		}
		else if (pWarriorOfCity[1]) {   //��Ч����blue��
			PrintTime(); PrintHeadName(1); PrintSortName(pWarriorOfCity[1]->sort);
			cout << pWarriorOfCity[1]->id << " earned " << strengthOfCity << " elements for his headquarter" << endl;
			pWarriorOfCity[1]->pHeadOfWarrior->total_s += strengthOfCity;
			strengthOfCity = 0;
		}
		else cerr << "Error1" << endl;  //����Ч�ң����ˣ�
	}
}

void CWarrior::tryToUseArrow() {
	if (cnt_weapon[2] <= 0)return;    //û�й�����ֱ�ӹ���ȥ�ɣ�
	if (pHeadOfWarrior->name == 0) {      //head��red
		if (pLocOfWarrior->locOfCity >= N)return;    //��blue���ſ��ˣ���������ˣ�
		if (pCity[pLocOfWarrior->locOfCity + 1]->pWarriorOfCity[1] == NULL)return;//������ûblue��ʿ���أ�
		PrintTime(); PrintHeadName(pHeadOfWarrior->name); PrintSortName(sort); cout << id << " shot";
		if (pCity[pLocOfWarrior->locOfCity + 1]->pWarriorOfCity[1]->strength <= R) {  //��ǰ�ж��ܻ��У�
			cout << " and killed "; PrintHeadName(pHeadOfWarrior->enemyHead->name);
			PrintSortName(pCity[pLocOfWarrior->locOfCity + 1]->pWarriorOfCity[1]->sort);
			cout << pCity[pLocOfWarrior->locOfCity + 1]->pWarriorOfCity[1]->id;
		}
		pCity[pLocOfWarrior->locOfCity + 1]->pWarriorOfCity[1]->Shot(); //�����ǵ�blue��ʿ�����У���û����
		pWeapon[2]->wearOut();   //�����٣�
		cout << endl;
	}
	else if (pHeadOfWarrior->name == 1) {  //head��blue
		if (pLocOfWarrior->locOfCity <= 1)return;    //��red���ſ��ˣ���������ˣ�
		if (pCity[pLocOfWarrior->locOfCity - 1]->pWarriorOfCity[0] == NULL)return;  //������ûred��ʿ,�أ�
		PrintTime(); PrintHeadName(pHeadOfWarrior->name); PrintSortName(sort); cout << id << " shot";
		if (pCity[pLocOfWarrior->locOfCity - 1]->pWarriorOfCity[0]->strength <= R) {  //��ǰ�ж��ܻ��У�
			cout << " and killed "; PrintHeadName(pHeadOfWarrior->enemyHead->name);
			PrintSortName(pCity[pLocOfWarrior->locOfCity - 1]->pWarriorOfCity[0]->sort);
			cout << pCity[pLocOfWarrior->locOfCity - 1]->pWarriorOfCity[0]->id;
		}
		pCity[pLocOfWarrior->locOfCity - 1]->pWarriorOfCity[0]->Shot(); //�����ǵ�red��ʿ�����У�
		pWeapon[2]->wearOut();   //�����٣�
		cout << endl;
	}
}

int CCity::tryToBombCity() {                   //38��������������ը����??
	if (numOfWarrior < 2)return 0;      //����û�е��ˣ�������ը����
	if ((pWarriorOfCity[0] && pWarriorOfCity[0]->strength <= 0) ||
		(pWarriorOfCity[1] && pWarriorOfCity[1]->strength <= 0))
		return 0;
	CWarrior *pBomber = NULL;
	if (pWarriorOfCity[1]->IwillDieHere() == 1 && pWarriorOfCity[1]->cnt_weapon[1] == 1) //blueTry
		pBomber = pWarriorOfCity[1];    //blue���Ʋ���Ͻ�UseBomb
	else if (pWarriorOfCity[0]->IwillDieHere() == 1 && pWarriorOfCity[0]->cnt_weapon[1] == 1)  //redTry
		pBomber = pWarriorOfCity[0];    //red���Ʋ���Ͻ�UseBomb
	else return 0;                      //û������ը������ȥ��ɱ��
	int enemyHead = rival(pBomber->pHeadOfWarrior->name);
	PrintTime(); PrintHeadName(pBomber->pHeadOfWarrior->name); PrintSortName(pBomber->sort);
	cout << pBomber->id << " used a bomb and killed "; PrintHeadName(enemyHead);
	PrintSortName(pWarriorOfCity[enemyHead]->sort);
	cout << pWarriorOfCity[enemyHead]->id << endl;
	delete pWarriorOfCity[enemyHead];                        //��Ҳ��
	delete pWarriorOfCity[pBomber->pHeadOfWarrior->name];    //��Ҳ��
	return 1;
}

int CWarrior::IwillDieHere() {              //��ǰ�����Լ�������᲻�ᱻɱ����
	pHeadOfWarrior->name;
	if ((pLocOfWarrior->pHeadOfCity == pHeadOfWarrior->enemyHead) || (pLocOfWarrior->pHeadOfCity == NULL &&
		pLocOfWarrior->locOfCity % 2 == pHeadOfWarrior->name % 2)) {             //�����Լ������ϣ�
		if (strength <= pLocOfWarrior->pWarriorOfCity[rival(pHeadOfWarrior->name)]->forceOfWarrior +
			pLocOfWarrior->pWarriorOfCity[rival(pHeadOfWarrior->name)]->calcDamageOfSword()) { //������·һ������
			return 1;
		}
		else return 0;    //���ᱻɱ����
	}
	else {                //���Լ������ϣ��᲻�ᱻ�������أ�
		if (pLocOfWarrior->pWarriorOfCity[rival(pHeadOfWarrior->name)]->strength <=
			forceOfWarrior + calcDamageOfSword()) return 0;    //�Է��Ѵ���������һ��������
		if (pLocOfWarrior->pWarriorOfCity[rival(pHeadOfWarrior->name)]->sort == 2) return 0; //������Ninjia
		if (strength <= (pLocOfWarrior->pWarriorOfCity[rival(pHeadOfWarrior->name)]->forceOfWarrior) / 2 +
			pLocOfWarrior->pWarriorOfCity[rival(pHeadOfWarrior->name)]->calcDamageOfSword()) { //��������·һ������
			return 1;
		}
		else return 0;
	}
}

void CCity::tryToWageWar() {        //40���г��Կ�ս?��
	if (numOfWarrior < 2)return;    //�����������޷���ս(��������)...
	someoneWin = 0;                 //ʤ����¼���㣡
	CWarrior *pFighter = NULL, *pDead = NULL, *pWin = NULL;     //pDead��¼ս��Warrior��
	if (pHeadOfCity == NULL) {      //ȷ����������
		if (locOfCity % 2 != 0) pFighter = pWarriorOfCity[0];
		else pFighter = pWarriorOfCity[1];
	}
	else if (pHeadOfCity->name == 0)  pFighter = pWarriorOfCity[0];
	else if (pHeadOfCity->name == 1)  pFighter = pWarriorOfCity[1];
	else cerr << "Error:Illigally Named City2!" << endl;
	CWarrior *pAttacked = pWarriorOfCity[rival(pFighter->pHeadOfWarrior->name)];  //ȷ����������
	int fighterStrength = pFighter->strength, attackedStrength = pAttacked->strength;
	if (pFighter->strength <= 0) {          //�ҷ��ѱ������ˣ�
		if (pAttacked->strength <= 0) {     //ȫ�������ˣ�
			delete pFighter; delete pAttacked; pFighter = NULL; pAttacked = NULL; return;
		}
		else {                              //�ҷ����������Է������ţ� 
			pDead = pFighter;
			if (pAttacked->sort == 5)((CWolf*)pAttacked)->capWeapon(pFighter); //Wolf�ɻ�������
		}
	}
	else if (pAttacked->strength <= 0) {    //�Է��ѱ��������ҷ���
		pDead = pAttacked;
		if (pFighter->sort == 5)((CWolf*)pFighter)->capWeapon(pAttacked);     //Wolf�ɻ�������
	}
	else {             //˫��������սһ��������?
		pFighter->Attack(pAttacked);           //�������������������������ˣ������������������ˣ�
		if (pFighter->strength <= 0) {         //�������ʤ��
			pDead = pFighter;
			if (pAttacked->sort == 5)((CWolf*)pAttacked)->capWeapon(pFighter); //Wolf�ɻ�������
		}
		else if (pAttacked->strength <= 0) {   //�������ʤ��
			pDead = pAttacked;
			if (pFighter->sort == 5)((CWolf*)pFighter)->capWeapon(pAttacked); //Wolf�ɻ�������
		}
	}
	if (pDead) {
		pWin = pWarriorOfCity[rival(pDead->pHeadOfWarrior->name)];      //ȷ����ʤ����
		pWin->winWar();
	}
	if (pDead && pDead->shotDead == 0) {                //8)�������ģ����ս����
		PrintTime(); PrintHeadName(pDead->pHeadOfWarrior->name); PrintSortName(pDead->sort);
		cout << pDead->id << " was killed in city " << locOfCity << endl;
	}
	if (pFighter->sort == 1 && pAttacked->strength > 0)    //fighter��DragonûӮ��ʿ���½���
		((CDragon*)pFighter)->morale -= 0.2;      //ʿ���½���
	if (pAttacked->sort == 1 && pFighter->strength > 0)    //attacked��DragonûӮ��ʿ���½���
		((CDragon*)pAttacked)->morale -= 0.2;     //ʿ���½���
	if (pFighter->sort == 1 && pFighter->strength > 0 && ((CDragon*)pFighter)->morale > 0.8)
		((CDragon*)pFighter)->yell();             //9)������Dragon��

	if (pFighter->sort == 4 && someoneWin == 0)((CLion*)pFighter)->loseLoy();   //����Lion�����ҳ϶ȣ�
	if (pAttacked->sort == 4 && someoneWin == 0)((CLion*)pAttacked)->loseLoy(); //�ܷ�Lion�����ҳ϶ȣ�

	if (pFighter->sort == 4 && pFighter->strength <= 0 && pAttacked->strength > 0)
		pAttacked->strength += fighterStrength;                          //�ܷ�ȡ��Lionսǰ����
	else if (pAttacked->sort == 4 && pAttacked->strength <= 0 && pFighter->strength > 0)
		pFighter->strength += attackedStrength;                          //����ȡ��Lionսǰ����

	if (someoneWin == 0) { changeFlagto[0] = 0; changeFlagto[1] = 0; }   //û��Ӯ������changeFlag��¼���㣡
	else {                                          //����Ӯ�ˣ�
		if (strengthOfCity > 0) {                   //10)��ʿ��ȡ����Ԫ��
			PrintTime(); PrintHeadName(pWin->pHeadOfWarrior->name); PrintSortName(pWin->sort);
			cout << pWin->id << " earned " << strengthOfCity << " elements for his headquarter" << endl;
			pWin->pHeadOfWarrior->buffer += strengthOfCity;    //�ȷ���˾�������Ԫ��������
			strengthOfCity = 0;
		}
		if (pHeadOfCity != pWin->pHeadOfWarrior) {  //����ʤ�����ģ�׼�����ģ�
			changeFlagto[pWin->pHeadOfWarrior->name]++;
			changeFlagto[pDead->pHeadOfWarrior->name] = 0;
			if (changeFlagto[pWin->pHeadOfWarrior->name] == 2) {    //�з�changeFlag�ﵽ2��11)���ģ�
				pHeadOfCity = pWin->pHeadOfWarrior; changeFlagto[0] = 0, changeFlagto[1] = 0;
				PrintTime(); PrintHeadName(pHeadOfCity->name); cout << " flag raised in city " << locOfCity << endl;
			}
		}
		else {
			changeFlagto[pHeadOfCity->name] = 0;
			changeFlagto[pDead->pHeadOfWarrior->name] = 0;
		}   //��ʤ�����ģ�ʤ��ս�ܼ�¼���㣡
	}

	delete pDead;
}

void CWarrior::Attack(CWarrior *pAttacked) {		//���𹥻���
	pAttacked->Hurted(forceOfWarrior + calcDamageOfSword());  //Ŀ�걻���У����ˣ�
	if (cnt_weapon[0])((CSword*)pWeapon[0])->wearOut();
	PrintTime(); PrintHeadName(pHeadOfWarrior->name); PrintSortName(sort); cout << id << " attacked ";
	PrintHeadName(pAttacked->pHeadOfWarrior->name); PrintSortName(pAttacked->sort);
	cout << pAttacked->id << " in city " << pLocOfWarrior->locOfCity << " with " << strength <<
		" elements and force " << forceOfWarrior << endl;
	if (pAttacked->strength > 0) { pAttacked->FightBack(this); }  //Warrior�ֱ�������
}

int CWarrior::calcDamageOfSword() {         //�������Warrior��sword��damage�ӳɣ�
	if (cnt_weapon[0] == 0)return 0;
	else {
		CSword *pS = (CSword*)pWeapon[0];
		return pS->damage;
	}
}

void CDragon::FightBack(CWarrior *pFighted) {   //...�����з�����
	PrintFightback(pFighted);
	pFighted->Hurted(forceOfWarrior / 2 + calcDamageOfSword());
	if (cnt_weapon[0])((CSword*)pWeapon[0])->wearOut();
}

void CLion::FightBack(CWarrior *pFighted) {         //...ʨ�ӽ��з�����
	PrintFightback(pFighted);
	pFighted->Hurted(forceOfWarrior / 2 + calcDamageOfSword());
	if (cnt_weapon[0])((CSword*)pWeapon[0])->wearOut();
}

void CWolf::FightBack(CWarrior *pFighted) {		//...�ǽ��з�����
	PrintFightback(pFighted);
	pFighted->Hurted(forceOfWarrior / 2 + calcDamageOfSword());
	if (cnt_weapon[0])((CSword*)pWeapon[0])->wearOut();
}

void CIceman::FightBack(CWarrior *pFighted) {		//...���˽��з�����
	PrintFightback(pFighted);
	pFighted->Hurted(forceOfWarrior / 2 + calcDamageOfSword());
	if (cnt_weapon[0])((CSword*)pWeapon[0])->wearOut();
}

void CWarrior::PrintFightback(CWarrior *pFighted) {
	PrintTime(); PrintHeadName(pHeadOfWarrior->name); PrintSortName(sort); cout << id << " fought back against ";
	PrintHeadName(pFighted->pHeadOfWarrior->name); PrintSortName(pFighted->sort);
	cout << pFighted->id << " in city " << pLocOfWarrior->locOfCity << endl;
}

CWarrior::~CWarrior() {                             //warrior���������麯����
	pHeadOfWarrior->pWarrior[id] = NULL;            //��˾�ע��������
	pLocOfWarrior->numOfWarrior -= 1;               //�����ڳ���ע��������
	pLocOfWarrior->pWarriorOfCity[pHeadOfWarrior->name] = NULL;  //�����ڳ���ע��������
	for (int i = 0; i < 3; i++) delete pWeapon[i];  //delete�������������ͷ��ڴ棡
}

void CDragon::winWar() {
	someoneWin = 1;
	morale += 0.2;
	if (pHeadOfWarrior->name == 0)pLocOfWarrior->redRequest = 1;
	else pLocOfWarrior->blueRequest = 1;
}

void CDragon::yell() {
	PrintTime(); PrintHeadName(pHeadOfWarrior->name); PrintSortName(1);
	cout << id << " yelled in city " << pLocOfWarrior->locOfCity << endl;
}

void CLion::winWar() {
	someoneWin = 1;
	if (pHeadOfWarrior->name == 0)pLocOfWarrior->redRequest = 1;
	else pLocOfWarrior->blueRequest = 1;
}

void CWolf::winWar() {
	someoneWin = 1;
	if (pHeadOfWarrior->name == 0)pLocOfWarrior->redRequest = 1;
	else pLocOfWarrior->blueRequest = 1;
}

void CNinja::winWar() {
	someoneWin = 1;
	if (pHeadOfWarrior->name == 0)pLocOfWarrior->redRequest = 1;
	else pLocOfWarrior->blueRequest = 1;
}

void CIceman::winWar() {
	someoneWin = 1;
	if (pHeadOfWarrior->name == 0)pLocOfWarrior->redRequest = 1;
	else pLocOfWarrior->blueRequest = 1;
}

void CWolf::capWeapon(CWarrior* pDead) {        //Wolfȥ�ɻ�������
	if (pDead->pWeapon[0] && !pWeapon[0]) {
		pWeapon[0] = pDead->pWeapon[0];
		cnt_weapon[0]++;
		pWeapon[0]->pMaster = this;
		pDead->pWeapon[0] = NULL;
	}
	if (pDead->pWeapon[1] && !pWeapon[1]) {
		pWeapon[1] = pDead->pWeapon[1];
		cnt_weapon[1]++;
		pWeapon[1]->pMaster = this;
		pDead->pWeapon[1] = NULL;
	}
	if (pDead->pWeapon[2] && !pWeapon[2]) {
		pWeapon[2] = pDead->pWeapon[2];
		cnt_weapon[2]++;
		pWeapon[2]->pMaster = this;
		pDead->pWeapon[2] = NULL;
	}
}

void CWarrior::weaponReport_warrior() {     //15)Warrior�������������
	int firstOutput = 1;
	PrintTime(); PrintHeadName(pHeadOfWarrior->name); PrintSortName(sort); cout << id << " has ";
	if (cnt_weapon[2] == 1) {  //Arrow��
		cout << "arrow(" << ((CArrow*)pWeapon[2])->left << ")";
		firstOutput = 0;
	}
	if (cnt_weapon[1] == 1) {  //Bomb��
		if (firstOutput == 0)cout << ",";
		cout << "bomb";
		firstOutput = 0;
	}
	if (cnt_weapon[0] == 1) {  //Sowrd��
		if (firstOutput == 0)cout << ",";
		cout << "sword(" << ((CSword*)pWeapon[0])->damage << ")";
		firstOutput = 0;
	}
	if (firstOutput == 1)   //û���������û��������
		cout << "no weapon";
	cout << endl;
}

CHeadquarter::~CHeadquarter() {
	for (int i = 0; i < tot_warrior; i++) delete pWarrior[i];
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////��ʼ��Ϸ��///////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
	int n, all;
	cin >> n; all = n;
	while (n--) {
		t = 0;     //ע�⣺ÿ����Ϸǰʱ����㣡
		cout << "Case:" << all - n << endl;
		auto sqi = 3, sqj = 4;    //i��j��¼head��һ������������warrior
		cin >> M >> N >> R >> K >> T;
		int sq[][warrior_num] = { { 3,1,4,5,2 },{ 2,3,5,1,4 } };
		CWarrior::setStrength();   //ΪCWarrior��ȡ��ʼ����ֵ
		CWarrior::setForceWarrior();
		CHeadquarter *pHead[2] = { NULL };
		pHead[0] = new CHeadquarter(M, 0, sq[0]), pHead[1] = new CHeadquarter(M, 1, sq[1]);    //����2��Head
		pHead[0]->enemyHead = pHead[1]; pHead[1]->enemyHead = pHead[0];
		for (auto i = 0; i <= N + 1; i++) pCity[i] = new CCity(i);
		auto hour = 0, min = 0;

		t = 0;
		//��ʱ��ʼ��
		for (hour = 0; t <= T; hour++) {

			min = 0;             //00��ʿ������
			sqi = pHead[0]->make(sqi);
			sqj = pHead[1]->make(sqj);

			t += 5; min = 5; if (t > T)break;     //05Lion���ܦ�=��=��=��(�b��b;)��
			for (int i = 0; i <= N + 1; i++) {
				if (pCity[i]->pWarriorOfCity[0] && pCity[i]->pWarriorOfCity[0]->sort == 4 && i != N + 1)  //red��������
					((CLion*)pCity[i]->pWarriorOfCity[0])->tryToEscape();
				if (pCity[i]->pWarriorOfCity[1] && pCity[i]->pWarriorOfCity[1]->sort == 4 && i != 0)      //blue��������
					((CLion*)pCity[i]->pWarriorOfCity[1])->tryToEscape();
			}

			t += 5; min = 10; if (t > T)break;    //10˫����ʿǰ��
			CWarrior *pRedArrive = pHead[0]->headMove(), *pBlueArrive = pHead[1]->headMove();
			PrintMove(pRedArrive, pBlueArrive);   //���ǰ����Ϣ
			if (gameOver == 1)break;  //һ��˾���ռ�죬��Ϸ����

			t += 10; min = 20; if (t > T)break;   //20ÿ��������������Ԫ
			for (int i = 1; i <= N; i++)
				pCity[i]->yieldStrength();

			t += 10; min = 30; if (t > T)break;   //30��ʿ��ȡ�߳�������Ԫ
			for (int i = 1; i <= N; i++)
				pCity[i]->tryToGiveStrength();

			t += 5; min = 35; if (t > T)break;    //35�ż�
			for (int i = 0; i <= N + 1; i++) {     //�����������
				if (pCity[i]->pWarriorOfCity[0])pCity[i]->pWarriorOfCity[0]->tryToUseArrow();
				if (pCity[i]->pWarriorOfCity[1])pCity[i]->pWarriorOfCity[1]->tryToUseArrow();
			}

			t += 3; min = 38; if (t > T)break;    //38��ը��ը��(�s�F����)�s??��*������
			for (int i = 1; i <= N; i++)      //����������ը����
				pCity[i]->tryToBombCity();

			t += 2; min = 40; if (t > T)break;    //40��ս
			for (int i = 1; i <= N; i++)
				pCity[i]->tryToWageWar();
			pHead[0]->allocate(); pHead[1]->allocate();
			pHead[0]->pushBuffer(); pHead[1]->pushBuffer();

			for (int i = 0; i <= N + 1; i++) {    //����ʬ
				if (pCity[i]->pWarriorOfCity[0] && pCity[i]->pWarriorOfCity[0]->strength <= 0)
					delete pCity[i]->pWarriorOfCity[0];
				if (pCity[i]->pWarriorOfCity[1] && pCity[i]->pWarriorOfCity[1]->strength <= 0)
					delete pCity[i]->pWarriorOfCity[1];
			}

			t += 10; min = 50; if (t > T)break;   //50�غϽ�����˾�����ʣ������Ԫ
			pHead[0]->strengthReport();
			pHead[1]->strengthReport();

			t += 5; min = 55; if (t > T)break;    //55��ʿ�����������
			pHead[0]->weaponReport_head();
			pHead[1]->weaponReport_head();

			t += 5;
		}
		delete pHead[0]; delete pHead[1];
		for (auto i = 0; i <= N + 1; i++) delete pCity[i];
	}
	return 0;
}
