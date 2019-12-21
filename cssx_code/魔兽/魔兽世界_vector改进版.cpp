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
int t = 0, M, N, R, K, T, someoneWin = 0, gameOver = 0;//司令部初始生命M，城市数N，arrow攻击力R，Lion忠诚降K，时间上限T   
const int warrior_num = 5;  //若需增加武士种类数，则需增加warrior_num
void PrintWeaponName(int i) {    //方便起见，在CWarrior类内部用int代表weapon
	switch (i) {            //但cout时要把类别标识符int转成string
	case 0:cout << " a sword"; break;
	case 1:cout << " a bomb"; break;
	case 2:cout << " a arrow"; break;
	default:break;
	}
}
void PrintSortName(int i) {      //方便起见，在CWarrior类内部用int标记warrior类别
	switch (i) {               //但cout时要把类别标识符int转成string
	case 1:cout << " dragon "; break;
	case 2:cout << " ninja "; break;
	case 3:cout << " iceman "; break;
	case 4:cout << " lion "; break;
	case 5:cout << " wolf "; break;
	}
}
void PrintHeadName(int name) {     //方便起见，在CWarrior类内部用int标记所属Head
	switch (name) {              //但cout时要把Head标识符int转成string
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
void PrintTime() {               //时间输出函数！
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
	CCity(int l_) :locOfCity(l_) {}    //城市的构造函数
	CWarrior *pWarriorOfCity[2] = { NULL }; //pWarriorOfCity[0]指向red武士，pWarriorOfCity[1]指向blue武士
	CHeadquarter *pHeadOfCity = NULL;       //此城旗帜
	void yieldStrength() { strengthOfCity += 10; }   //城市生产生命元！
	void tryToGiveStrength();               //城市尝试给出自己生命元！
	int tryToBombCity();                    //38尝试在这座城扔炸弹！??
	void tryToWageWar();                    //40城市尝试开战?！
};
/////////////////武士类！//////////////////////////////////////////////武士类！//////////////////////////////////////////////////////////////////

class CWarrior {          //武士类！抽象类！
protected:
	bool shotDead = 0, reachEnemyHead = 0;  //sort:dragon=1, ninja=2, iceman=3, lion=4, wolf=5
	int cnt_weapon[3] = { 0 }, id;  //warrior的武器清单
	int forceOfWarrior;
	CCity *pLocOfWarrior = NULL;            //记录这个Warrior抵达的位置（城市）
	CHeadquarter *pHeadOfWarrior = NULL;        //阵营信息，red or blue (0 or 1)
	friend class CHeadquarter; friend class CWeapon;
	friend class CCity; friend void PrintMove(CWarrior *pRA, CWarrior *pBA);
public:
	int sort, strength;
	CWeapon *pWeapon[3] = { NULL , NULL  , NULL };          //warrior的武器库(地址)
	static int strength_ini[warrior_num + 1];     //各类warrior初始生命值
	static int forceOfWarriors[warrior_num + 1];  //各类warrior攻击力 
	CWarrior(int sort_, CHeadquarter *pHead_);    //warrior构造函数:武士类别、所属阵营、初始生命
	virtual ~CWarrior();                          //warrior死亡！注销户籍！
	static void setStrength() {                   //静态成员函数，把各类别warrior的生命值初始化，从屏幕输入
		for (int i = 1; i <= warrior_num; i++)
			cin >> strength_ini[i];
	}
	static void setForceWarrior() {
		for (int i = 1; i <= warrior_num; i++)    //静态成员函数，把各类别warrior的攻击力初始化，从屏幕输入
			cin >> forceOfWarriors[i];
	}
	void Shot() {                     //被弓箭射中是特殊的伤害！
		strength -= R;
		if (strength <= 0) { strength = 0; shotDead = 1; }  //中箭身亡！
	}
	void tryToUseArrow();             //35尝试射箭！没有弓箭也能调用！
	void holdWeapon(int i);           //持武器操作！
	int calcDamageOfSword();          //计算这个Warrior的sword的damage加成！
	int IwillDieHere();               //提前看看自己在这儿会不会被杀死！
	void Attack(CWarrior *pAttacked);
	void Hurted(int nPower) {        //Warrior受到伤害！
		strength -= nPower;
		if (strength < 0)strength = 0;
	}
	virtual void FightBack(CWarrior *pFighted) = 0;  //纯虚函数！每人都有！
	void PrintFightback(CWarrior *pFighted);
	virtual void winWar() = 0;        //取得战争胜利！
	void weaponReport_warrior();
};
int CWarrior::strength_ini[warrior_num + 1] = { 0 };
int CWarrior::forceOfWarriors[warrior_num + 1] = { 0 };

///////////////武士派生类！///////////////////////////////////////////武士派生类！///////////////////////////////////////////////////武士派生类！

class CDragon :public CWarrior {
	double morale;                          //Dragon才有士气！
	friend class CHeadquarter; friend class CCity;
public:
	CDragon(CHeadquarter *pHead_) : CWarrior(1, pHead_) {}   //Dragon构造函数！
	void FightBack(CWarrior *pFighted);
	void winWar();
	void yell();
};

class CLion :public CWarrior {
	int loyalty;                     //Lion才有忠诚度！
	friend class CHeadquarter;
public:
	CLion(CHeadquarter *pHead_) : CWarrior(4, pHead_) {}   //Lion构造函数！
	void FightBack(CWarrior *pFighted);
	void tryToEscape();                         //Lion尝试逃跑!
	void winWar();
	void loseLoy() { loyalty -= K; }
};

class CWolf :public CWarrior {
public:
	CWolf(CHeadquarter *pHead_) : CWarrior(5, pHead_) {}   //Dragon构造函数！
	void FightBack(CWarrior *pFighted);
	void winWar();
	void capWeapon(CWarrior* pDead);
};

class CNinja :public CWarrior {
public:
	CNinja(CHeadquarter *pHead_) : CWarrior(2, pHead_) {}   //Dragon构造函数！
	void FightBack(CWarrior *pFighted) {}    //Ninja忍气吞声，从不反击！
	void winWar();
};

class CIceman :public CWarrior {
	int cumPace = 0;
public:
	void icemanMove();
	CIceman(CHeadquarter *pHead_) : CWarrior(3, pHead_) {}   //冰人构造函数！
	void FightBack(CWarrior *pFighted);
	void winWar();
};

/////////////武器类！/////////////////////////////////////////////武器类！////////////////////////////////////////////////////////////////////////////////

class CWeapon {                 //武器类！抽象类！
	int sort;                   //sort: sword=0, bomb=1, arrow=2
	CWarrior *pMaster = NULL;   //武器持有人
	friend class CWolf;
public:
	CWeapon(int sort_, CWarrior *pMaster_) :sort(sort_), pMaster(pMaster_) {}
	virtual void wearOut() = 0;
	virtual ~CWeapon() {                      //武器类统一的析构函数
		pMaster->cnt_weapon[sort] -= 1;       //注销武器户籍！
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
		damage = floor(damage * 0.8);         //sword每用过一次要损坏！
		if (damage == 0) delete this;         //damage降为0就要报废！
	}
};
class CBomb :public CWeapon {
	friend class CWarrior;
	friend class CHeadquarter;
public:
	CBomb(CWarrior *pM_) :CWeapon(1, pM_) {}
	void wearOut() {}                         //Bomb一用，双方阵亡，不用再重复析构
};
class CArrow :public CWeapon {
	int left;
	friend class CWarrior;
	friend class CHeadquarter;
public:
	CArrow(CWarrior *pM_) :CWeapon(2, pM_), left(3) {}
	void wearOut() {                          //看看还剩多少支Arrow
		if (left > 1)left -= 1;               //多于1支Arrow
		else if (left <= 1) delete this;      //Arrow用光了！析构吧！
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

////////////////司令部类！/////////////////////////////////////////////////司令部类！////////////////////////////////////////

class CHeadquarter {                                    //司令部类！
	int total_s, buffer = 0, tot_warrior = 0, name, takeOver = 0;   //剩余生命点、warrior个数
	int sq[warrior_num + 1];    //记录顺序表里某warrior下个warrior类别编号,如sq[1]=2意为dragon过了轮到ninja
								//CWarrior *pWarrior[1000] = { NULL };      //在此设定每个Head最多有1000个warrior
	vector<CWarrior*> pWarrior;
	friend class CWarrior; friend class CLion; friend class CDragon; friend class CWolf; friend class CNinja;
	friend class CCity; friend class CIceman; friend class CWeapon;
	friend void PrintMove(CWarrior *pRA, CWarrior *pBA);
public:
	CHeadquarter * enemyHead = NULL;
	CHeadquarter(int M, int n_, int *psq) { //构造函数，把Head里总生命值、name编号、warrior制造顺序表都初始化
		total_s = M; name = n_;
		for (int i = 1; i <= warrior_num; i++)
			sq[i] = *(psq + i - 1);
		pWarrior.push_back(0);
	}
	CWarrior *headMove() {                       //10所有武士都前进一步！
		CWarrior *pArrive = NULL;
		for (int i = 1; i <= tot_warrior; i++) {
			if (pWarrior[i] == NULL || pWarrior[i]->reachEnemyHead == 1)continue;  //回去！
			if (name == 0) {                  //red和blue分开操作,先看看是不是red
				pWarrior[i]->pLocOfWarrior->numOfWarrior -= 1;              //注销户籍→到达新City→落户
				pWarrior[i]->pLocOfWarrior->pWarriorOfCity[0] = NULL;
				pWarrior[i]->pLocOfWarrior = pCity[pWarrior[i]->pLocOfWarrior->locOfCity + 1];
				pWarrior[i]->pLocOfWarrior->numOfWarrior += 1;
				if (pWarrior[i]->pLocOfWarrior->pWarriorOfCity[0] && pWarrior[i]->pLocOfWarrior->locOfCity != N + 1)
					cout << "Error:Red-overcrowded City！" << endl;
				pWarrior[i]->pLocOfWarrior->pWarriorOfCity[0] = pWarrior[i];
				if (pWarrior[i]->pLocOfWarrior->locOfCity == N + 1) {   //red武士到达blue司令部，不动了！
					pWarrior[i]->reachEnemyHead = 1;
					takeOver++; pArrive = pWarrior[i];
				}
			}
			else {             //再看看是不是blue
				pWarrior[i]->pLocOfWarrior->numOfWarrior -= 1;            //注销户籍→到达新City→落户
				pWarrior[i]->pLocOfWarrior->pWarriorOfCity[1] = NULL;
				pWarrior[i]->pLocOfWarrior = pCity[pWarrior[i]->pLocOfWarrior->locOfCity - 1];
				pWarrior[i]->pLocOfWarrior->numOfWarrior += 1;
				if (pWarrior[i]->pLocOfWarrior->pWarriorOfCity[1] && pWarrior[i]->pLocOfWarrior->locOfCity != 0)
					cout << "Error:Blue-overcrowded City！" << endl;
				pWarrior[i]->pLocOfWarrior->pWarriorOfCity[1] = pWarrior[i];
				if (pWarrior[i]->pLocOfWarrior->locOfCity == 0) {   //blue武士到达ted司令部，不动了！
					pWarrior[i]->reachEnemyHead = 1;
					takeOver++; pArrive = pWarrior[i];
				}
			}
			if (pWarrior[i]->sort == 3) ((CIceman*)pWarrior[i])->icemanMove();
		}
		return pArrive;
	}
	int make(int sort) {      //制造sort型worrior，返回按sq下一个该制造的sort编号
		if (total_s < CWarrior::strength_ini[sort])return sort; //司令部血不够了，滚回去吧！
		PrintTime();          //先输出时间
		tot_warrior++;   //注意：若++放的位置不对,pWarrior[i]指向空地址，很危险！
		total_s -= CWarrior::strength_ini[sort];         //Head生命值减少
		PrintHeadName(name); PrintSortName(sort);
		cout << tot_warrior << " born" << endl;
		if (sort == 1) {      // Dragon made!
			CDragon *pD = new CDragon(this);      //生成一个新的Dragon，把它的地址放在*pD里
			pD->id = tot_warrior;                 //Head给每只warrior一个专属id
			pD->morale = (double)total_s / (double)CWarrior::strength_ini[sort]; //设置Dragon士气！
			pD->holdWeapon(tot_warrior % 3);      //赋予Dragon武器！
			cout << "Its morale is " << fixed << setprecision(2) << pD->morale << endl;
			pWarrior.push_back(pD);             //把临时pD放进抽象类指针数组

		}
		if (sort == 2) {      // Ninja made!
			CNinja *pN = new CNinja(this);         //生成一个新的Dragon，把它的地址放在*pD里
			pN->id = tot_warrior;                  //Head给每只warrior一个专属id
			pN->holdWeapon(tot_warrior % 3);       //赋予Ninja武器！
			pN->holdWeapon((tot_warrior + 1) % 3); //再次赋予Ninja武器！
			pWarrior.push_back(pN);              //把临时pN放进抽象类指针数组
		}
		if (sort == 3) {      // Iceman made!
			CIceman *pI = new CIceman(this);       //生成一个新的Dragon，把它的地址放在*pD里
			pI->id = tot_warrior;
			pI->holdWeapon(tot_warrior % 3);       //赋予Iceman武器！
			pWarrior.push_back(pI);              //把临时pI放进抽象类指针数组
		}
		if (sort == 4) {      // Lion made!
			CLion *pL = new CLion(this);           //生成一个新的Dragon，把它的地址放在*pD里
			pL->id = tot_warrior;
			pL->loyalty = total_s;                 //设置Lion忠诚度！
			cout << "Its loyalty is " << pL->loyalty << endl;
			pWarrior.push_back(pL);            //把临时pL放进抽象类指针数组
		}
		if (sort == 5) {      // Wolf made!
			CWolf *pW = new CWolf(this);           //生成一个新的Dragon，把它的地址放在*pD里
			pW->id = tot_warrior;
			pWarrior.push_back(pW);            //把临时pL放进抽象类指针数组
		}
		return sq[sort];
	}
	void allocate() {
		if (name == 0) {    //Red！
			for (int i = N; i >= 1; i--) {
				if (pCity[i]->redRequest == 1) {   //在该城市发现生命元请求！
					pCity[i]->redRequest = 0;
					if (total_s >= 8) {            //司令部有生命元才奖励！
						total_s -= 8;
						pCity[i]->pWarriorOfCity[0]->strength += 8;
					}
				}
			}
		}
		else {              //Blue！
			for (int i = 1; i <= N; i++) {
				if (pCity[i]->blueRequest == 1) {   //在该城市发现生命元请求！
					pCity[i]->blueRequest = 0;
					if (total_s >= 8) {            //司令部有生命元才奖励！
						total_s -= 8;
						pCity[i]->pWarriorOfCity[1]->strength += 8;
					}
				}
			}
		}
	}
	void pushBuffer() {       //Push strength in buffer into total_s！
		total_s += buffer;
		buffer = 0;
	}
	void strengthReport() {   //14)司令部报告生命元数量！
		PrintTime(); cout << total_s << " elements in "; PrintHeadName(name); cout << " headquarter" << endl;
	}
	void weaponReport_head() {  //15)武士报告武器情况！
		for (int i = 0; i <= N + 1; i++) {  //自西向东遍历所有城市！到达敌方司令部也报告！
			if (pCity[i]->pWarriorOfCity[name]) {   //这座城市有我方Warrior！
				pCity[i]->pWarriorOfCity[name]->weaponReport_warrior();
			}
		}
	}
	~CHeadquarter();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////warrior持武器函数！/////////////////////////////////////////////warrior持武器函数！////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CWarrior::CWarrior(int sort_, CHeadquarter *pHead_) {    //warrior构造函数:武士类别、所属阵营、初始生命
	pHeadOfWarrior = pHead_;
	sort = sort_;
	strength = strength_ini[sort];
	forceOfWarrior = forceOfWarriors[sort];
	if (pHead_->name == 0) {
		pLocOfWarrior = pCity[0];
		pCity[0]->pWarriorOfCity[0] = this;
		pCity[0]->numOfWarrior++;
	} //red设定位置
	else {
		pLocOfWarrior = pCity[N + 1];
		pCity[N + 1]->pWarriorOfCity[1] = this;
		pCity[N + 1]->numOfWarrior++;
	}         //blue设定位置
}

void CWarrior::holdWeapon(int i) {   //持武器函数！主语是Warrior
	cnt_weapon[i]++;                 //更新武器清单
	if (i == 0) {
		pWeapon[0] = new CSword(this, floor(forceOfWarrior*0.2));  //造新武器
		if (((CSword*)pWeapon[0])->damage <= 0)delete pWeapon[0];  //一上来就拿了一把报废的Sword
	}
	else if (i == 1)
		pWeapon[1] = new CBomb(this);  //造新武器
	else if (i == 2)
		pWeapon[2] = new CArrow(this);  //造新武器
	else cerr << "Error 2" << endl;
}

void CLion::tryToEscape() {     //Lion尝试逃跑!
	if (loyalty > 0)return;
	if (pHeadOfWarrior->name == 0 && pLocOfWarrior->locOfCity == N + 1)return;
	else if (pHeadOfWarrior->name == 1 && pLocOfWarrior->locOfCity == 0)return;
	PrintTime(); PrintHeadName(pHeadOfWarrior->name); PrintSortName(sort);
	cout << ' ' << id << " ran away" << endl;
	delete this;
}

void PrintMove(CWarrior *pRA, CWarrior *pBA) {  //两个指针应为NULL，除非有Warrior到达敌方司令部
	if (pBA) {       //看看red司令部情况
		PrintTime(); PrintHeadName(1); PrintSortName(pBA->sort);
		cout << pBA->id << " reached red headquarter with " <<
			pBA->strength << " elements and force " << pBA->forceOfWarrior << endl;
		if (pBA->pHeadOfWarrior->takeOver == 2) {
			PrintTime(); PrintHeadName(0); cout << " headquarter was taken" << endl;
			gameOver = 1;
		}
	}
	for (int i = 1; i <= N; i++) {            //自西向东遍历所有City
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
	if (pRA) {       //看看blue司令部情况
		PrintTime(); PrintHeadName(0); PrintSortName(pRA->sort);
		cout << pRA->id << " reached blue headquarter with " <<
			pRA->strength << " elements and force " << pRA->forceOfWarrior << endl;
		if (pRA->pHeadOfWarrior->takeOver == 2) {
			PrintTime(); PrintHeadName(1); cout << " headquarter was taken" << endl;
			gameOver = 1;
		}
	}
}

void CCity::tryToGiveStrength() {              //城市尝试给出自己生命元！
	if (numOfWarrior == 1) {            //如果城里只有一个warrior    
		if (pWarriorOfCity[0]) {        //它效忠于red！
			PrintTime(); PrintHeadName(0); PrintSortName(pWarriorOfCity[0]->sort);
			cout << pWarriorOfCity[0]->id << " earned " << strengthOfCity << " elements for his headquarter" << endl;
			pWarriorOfCity[0]->pHeadOfWarrior->total_s += strengthOfCity;
			strengthOfCity = 0;
		}
		else if (pWarriorOfCity[1]) {   //它效忠于blue！
			PrintTime(); PrintHeadName(1); PrintSortName(pWarriorOfCity[1]->sort);
			cout << pWarriorOfCity[1]->id << " earned " << strengthOfCity << " elements for his headquarter" << endl;
			pWarriorOfCity[1]->pHeadOfWarrior->total_s += strengthOfCity;
			strengthOfCity = 0;
		}
		else cerr << "Error1" << endl;  //都不效忠！错了！
	}
}

void CWarrior::tryToUseArrow() {
	if (cnt_weapon[2] <= 0)return;    //没有弓箭，直接滚回去吧！
	if (pHeadOfWarrior->name == 0) {      //head是red
		if (pLocOfWarrior->locOfCity >= N)return;    //到blue家门口了！不能射箭了！
		if (pCity[pLocOfWarrior->locOfCity + 1]->pWarriorOfCity[1] == NULL)return;//下座城没blue武士，回！
		PrintTime(); PrintHeadName(pHeadOfWarrior->name); PrintSortName(sort); cout << id << " shot";
		if (pCity[pLocOfWarrior->locOfCity + 1]->pWarriorOfCity[1]->strength <= R) {  //提前判断能击毙！
			cout << " and killed "; PrintHeadName(pHeadOfWarrior->enemyHead->name);
			PrintSortName(pCity[pLocOfWarrior->locOfCity + 1]->pWarriorOfCity[1]->sort);
			cout << pCity[pLocOfWarrior->locOfCity + 1]->pWarriorOfCity[1]->id;
		}
		pCity[pLocOfWarrior->locOfCity + 1]->pWarriorOfCity[1]->Shot(); //下座城的blue武士被射中！但没死！
		pWeapon[2]->wearOut();   //箭减少！
		cout << endl;
	}
	else if (pHeadOfWarrior->name == 1) {  //head是blue
		if (pLocOfWarrior->locOfCity <= 1)return;    //到red家门口了！不能射箭了！
		if (pCity[pLocOfWarrior->locOfCity - 1]->pWarriorOfCity[0] == NULL)return;  //下座城没red武士,回！
		PrintTime(); PrintHeadName(pHeadOfWarrior->name); PrintSortName(sort); cout << id << " shot";
		if (pCity[pLocOfWarrior->locOfCity - 1]->pWarriorOfCity[0]->strength <= R) {  //提前判断能击毙！
			cout << " and killed "; PrintHeadName(pHeadOfWarrior->enemyHead->name);
			PrintSortName(pCity[pLocOfWarrior->locOfCity - 1]->pWarriorOfCity[0]->sort);
			cout << pCity[pLocOfWarrior->locOfCity - 1]->pWarriorOfCity[0]->id;
		}
		pCity[pLocOfWarrior->locOfCity - 1]->pWarriorOfCity[0]->Shot(); //下座城的red武士被射中！
		pWeapon[2]->wearOut();   //箭减少！
		cout << endl;
	}
}

int CCity::tryToBombCity() {                   //38尝试在这座城扔炸弹！??
	if (numOfWarrior < 2)return 0;      //这里没有敌人，不用扔炸弹！
	if ((pWarriorOfCity[0] && pWarriorOfCity[0]->strength <= 0) ||
		(pWarriorOfCity[1] && pWarriorOfCity[1]->strength <= 0))
		return 0;
	CWarrior *pBomber = NULL;
	if (pWarriorOfCity[1]->IwillDieHere() == 1 && pWarriorOfCity[1]->cnt_weapon[1] == 1) //blueTry
		pBomber = pWarriorOfCity[1];    //blue见势不妙赶紧UseBomb
	else if (pWarriorOfCity[0]->IwillDieHere() == 1 && pWarriorOfCity[0]->cnt_weapon[1] == 1)  //redTry
		pBomber = pWarriorOfCity[0];    //red见势不妙赶紧UseBomb
	else return 0;                      //没人能扔炸弹，回去厮杀吧
	int enemyHead = rival(pBomber->pHeadOfWarrior->name);
	PrintTime(); PrintHeadName(pBomber->pHeadOfWarrior->name); PrintSortName(pBomber->sort);
	cout << pBomber->id << " used a bomb and killed "; PrintHeadName(enemyHead);
	PrintSortName(pWarriorOfCity[enemyHead]->sort);
	cout << pWarriorOfCity[enemyHead]->id << endl;
	delete pWarriorOfCity[enemyHead];                        //你也死
	delete pWarriorOfCity[pBomber->pHeadOfWarrior->name];    //我也亡
	return 1;
}

int CWarrior::IwillDieHere() {              //提前看看自己在这儿会不会被杀死！
	pHeadOfWarrior->name;
	if ((pLocOfWarrior->pHeadOfCity == pHeadOfWarrior->enemyHead) || (pLocOfWarrior->pHeadOfCity == NULL &&
		pLocOfWarrior->locOfCity % 2 == pHeadOfWarrior->name % 2)) {             //不在自己地盘上！
		if (strength <= pLocOfWarrior->pWarriorOfCity[rival(pHeadOfWarrior->name)]->forceOfWarrior +
			pLocOfWarrior->pWarriorOfCity[rival(pHeadOfWarrior->name)]->calcDamageOfSword()) { //被打死路一条啊！
			return 1;
		}
		else return 0;    //不会被杀死！
	}
	else {                //在自己地盘上，会不会被反击死呢？
		if (pLocOfWarrior->pWarriorOfCity[rival(pHeadOfWarrior->name)]->strength <=
			forceOfWarrior + calcDamageOfSword()) return 0;    //对方已脆弱不堪！一击致死！
		if (pLocOfWarrior->pWarriorOfCity[rival(pHeadOfWarrior->name)]->sort == 2) return 0; //敌人是Ninjia
		if (strength <= (pLocOfWarrior->pWarriorOfCity[rival(pHeadOfWarrior->name)]->forceOfWarrior) / 2 +
			pLocOfWarrior->pWarriorOfCity[rival(pHeadOfWarrior->name)]->calcDamageOfSword()) { //被反击死路一条啊！
			return 1;
		}
		else return 0;
	}
}

void CCity::tryToWageWar() {        //40城市尝试开战?！
	if (numOfWarrior < 2)return;    //人数不够，无法开战(ˉ▽ˉ；)...
	someoneWin = 0;                 //胜利记录清零！
	CWarrior *pFighter = NULL, *pDead = NULL, *pWin = NULL;     //pDead记录战死Warrior！
	if (pHeadOfCity == NULL) {      //确定进攻方！
		if (locOfCity % 2 != 0) pFighter = pWarriorOfCity[0];
		else pFighter = pWarriorOfCity[1];
	}
	else if (pHeadOfCity->name == 0)  pFighter = pWarriorOfCity[0];
	else if (pHeadOfCity->name == 1)  pFighter = pWarriorOfCity[1];
	else cerr << "Error:Illigally Named City2!" << endl;
	CWarrior *pAttacked = pWarriorOfCity[rival(pFighter->pHeadOfWarrior->name)];  //确定反击方！
	int fighterStrength = pFighter->strength, attackedStrength = pAttacked->strength;
	if (pFighter->strength <= 0) {          //我方已被射死了！
		if (pAttacked->strength <= 0) {     //全被射死了！
			delete pFighter; delete pAttacked; pFighter = NULL; pAttacked = NULL; return;
		}
		else {                              //我方被射死，对方还活着！ 
			pDead = pFighter;
			if (pAttacked->sort == 5)((CWolf*)pAttacked)->capWeapon(pFighter); //Wolf缴获武器！
		}
	}
	else if (pAttacked->strength <= 0) {    //对方已被射死！我方存活！
		pDead = pAttacked;
		if (pFighter->sort == 5)((CWolf*)pFighter)->capWeapon(pAttacked);     //Wolf缴获武器！
	}
	else {             //双方都存活！恶战一触即发！?
		pFighter->Attack(pAttacked);           //攻方进攻！接下来：防方受伤！防方反击！攻方受伤！
		if (pFighter->strength <= 0) {         //如果反击胜利
			pDead = pFighter;
			if (pAttacked->sort == 5)((CWolf*)pAttacked)->capWeapon(pFighter); //Wolf缴获武器！
		}
		else if (pAttacked->strength <= 0) {   //如果进攻胜利
			pDead = pAttacked;
			if (pFighter->sort == 5)((CWolf*)pFighter)->capWeapon(pAttacked); //Wolf缴获武器！
		}
	}
	if (pDead) {
		pWin = pWarriorOfCity[rival(pDead->pHeadOfWarrior->name)];      //确定获胜方！
		pWin->winWar();
	}
	if (pDead && pDead->shotDead == 0) {                //8)被打死的，输出战死！
		PrintTime(); PrintHeadName(pDead->pHeadOfWarrior->name); PrintSortName(pDead->sort);
		cout << pDead->id << " was killed in city " << locOfCity << endl;
	}
	if (pFighter->sort == 1 && pAttacked->strength > 0)    //fighter的Dragon没赢，士气下降！
		((CDragon*)pFighter)->morale -= 0.2;      //士气下降！
	if (pAttacked->sort == 1 && pFighter->strength > 0)    //attacked的Dragon没赢，士气下降！
		((CDragon*)pAttacked)->morale -= 0.2;     //士气下降！
	if (pFighter->sort == 1 && pFighter->strength > 0 && ((CDragon*)pFighter)->morale > 0.8)
		((CDragon*)pFighter)->yell();             //9)欢呼吧Dragon！

	if (pFighter->sort == 4 && someoneWin == 0)((CLion*)pFighter)->loseLoy();   //攻方Lion降低忠诚度！
	if (pAttacked->sort == 4 && someoneWin == 0)((CLion*)pAttacked)->loseLoy(); //受方Lion降低忠诚度！

	if (pFighter->sort == 4 && pFighter->strength <= 0 && pAttacked->strength > 0)
		pAttacked->strength += fighterStrength;                          //受方取走Lion战前生命
	else if (pAttacked->sort == 4 && pAttacked->strength <= 0 && pFighter->strength > 0)
		pFighter->strength += attackedStrength;                          //攻方取走Lion战前生命

	if (someoneWin == 0) { changeFlagto[0] = 0; changeFlagto[1] = 0; }   //没人赢？城市changeFlag记录清零！
	else {                                          //有人赢了！
		if (strengthOfCity > 0) {                   //10)武士获取生命元！
			PrintTime(); PrintHeadName(pWin->pHeadOfWarrior->name); PrintSortName(pWin->sort);
			cout << pWin->id << " earned " << strengthOfCity << " elements for his headquarter" << endl;
			pWin->pHeadOfWarrior->buffer += strengthOfCity;    //先放入司令部的生命元缓冲区！
			strengthOfCity = 0;
		}
		if (pHeadOfCity != pWin->pHeadOfWarrior) {  //不是胜方旗帜！准备易帜！
			changeFlagto[pWin->pHeadOfWarrior->name]++;
			changeFlagto[pDead->pHeadOfWarrior->name] = 0;
			if (changeFlagto[pWin->pHeadOfWarrior->name] == 2) {    //敌方changeFlag达到2，11)易帜！
				pHeadOfCity = pWin->pHeadOfWarrior; changeFlagto[0] = 0, changeFlagto[1] = 0;
				PrintTime(); PrintHeadName(pHeadOfCity->name); cout << " flag raised in city " << locOfCity << endl;
			}
		}
		else {
			changeFlagto[pHeadOfCity->name] = 0;
			changeFlagto[pDead->pHeadOfWarrior->name] = 0;
		}   //是胜方旗帜！胜方战败记录清零！
	}

	delete pDead;
}

void CWarrior::Attack(CWarrior *pAttacked) {		//发起攻击！
	pAttacked->Hurted(forceOfWarrior + calcDamageOfSword());  //目标被击中，受伤！
	if (cnt_weapon[0])((CSword*)pWeapon[0])->wearOut();
	PrintTime(); PrintHeadName(pHeadOfWarrior->name); PrintSortName(sort); cout << id << " attacked ";
	PrintHeadName(pAttacked->pHeadOfWarrior->name); PrintSortName(pAttacked->sort);
	cout << pAttacked->id << " in city " << pLocOfWarrior->locOfCity << " with " << strength <<
		" elements and force " << forceOfWarrior << endl;
	if (pAttacked->strength > 0) { pAttacked->FightBack(this); }  //Warrior又被反击！
}

int CWarrior::calcDamageOfSword() {         //计算这个Warrior的sword的damage加成！
	if (cnt_weapon[0] == 0)return 0;
	else {
		CSword *pS = (CSword*)pWeapon[0];
		return pS->damage;
	}
}

void CDragon::FightBack(CWarrior *pFighted) {   //...龙进行反击！
	PrintFightback(pFighted);
	pFighted->Hurted(forceOfWarrior / 2 + calcDamageOfSword());
	if (cnt_weapon[0])((CSword*)pWeapon[0])->wearOut();
}

void CLion::FightBack(CWarrior *pFighted) {         //...狮子进行反击！
	PrintFightback(pFighted);
	pFighted->Hurted(forceOfWarrior / 2 + calcDamageOfSword());
	if (cnt_weapon[0])((CSword*)pWeapon[0])->wearOut();
}

void CWolf::FightBack(CWarrior *pFighted) {		//...狼进行反击！
	PrintFightback(pFighted);
	pFighted->Hurted(forceOfWarrior / 2 + calcDamageOfSword());
	if (cnt_weapon[0])((CSword*)pWeapon[0])->wearOut();
}

void CIceman::FightBack(CWarrior *pFighted) {		//...冰人进行反击！
	PrintFightback(pFighted);
	pFighted->Hurted(forceOfWarrior / 2 + calcDamageOfSword());
	if (cnt_weapon[0])((CSword*)pWeapon[0])->wearOut();
}

void CWarrior::PrintFightback(CWarrior *pFighted) {
	PrintTime(); PrintHeadName(pHeadOfWarrior->name); PrintSortName(sort); cout << id << " fought back against ";
	PrintHeadName(pFighted->pHeadOfWarrior->name); PrintSortName(pFighted->sort);
	cout << pFighted->id << " in city " << pLocOfWarrior->locOfCity << endl;
}

CWarrior::~CWarrior() {                             //warrior死亡！（虚函数）
	pHeadOfWarrior->pWarrior[id] = NULL;            //从司令部注销户籍！
	pLocOfWarrior->numOfWarrior -= 1;               //从所在城市注销户籍！
	pLocOfWarrior->pWarriorOfCity[pHeadOfWarrior->name] = NULL;  //从所在城市注销户籍！
	for (int i = 0; i < 3; i++) delete pWeapon[i];  //delete掉所持武器！释放内存！
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

void CWolf::capWeapon(CWarrior* pDead) {        //Wolf去缴获武器！
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

void CWarrior::weaponReport_warrior() {     //15)Warrior报告武器情况！
	int firstOutput = 1;
	PrintTime(); PrintHeadName(pHeadOfWarrior->name); PrintSortName(sort); cout << id << " has ";
	if (cnt_weapon[2] == 1) {  //Arrow！
		cout << "arrow(" << ((CArrow*)pWeapon[2])->left << ")";
		firstOutput = 0;
	}
	if (cnt_weapon[1] == 1) {  //Bomb！
		if (firstOutput == 0)cout << ",";
		cout << "bomb";
		firstOutput = 0;
	}
	if (cnt_weapon[0] == 1) {  //Sowrd！
		if (firstOutput == 0)cout << ",";
		cout << "sword(" << ((CSword*)pWeapon[0])->damage << ")";
		firstOutput = 0;
	}
	if (firstOutput == 1)   //没有输出过！没有武器！
		cout << "no weapon";
	cout << endl;
}

CHeadquarter::~CHeadquarter() {
	for (int i = 0; i < tot_warrior; i++) delete pWarrior[i];
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////开始游戏！///////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
	int n, all;
	cin >> n; all = n;
	while (n--) {
		t = 0;     //注意：每次游戏前时间归零！
		cout << "Case:" << all - n << endl;
		auto sqi = 3, sqj = 4;    //i和j记录head下一个该制造哪种warrior
		cin >> M >> N >> R >> K >> T;
		int sq[][warrior_num] = { { 3,1,4,5,2 },{ 2,3,5,1,4 } };
		CWarrior::setStrength();   //为CWarrior获取初始生命值
		CWarrior::setForceWarrior();
		CHeadquarter *pHead[2] = { NULL };
		pHead[0] = new CHeadquarter(M, 0, sq[0]), pHead[1] = new CHeadquarter(M, 1, sq[1]);    //建立2个Head
		pHead[0]->enemyHead = pHead[1]; pHead[1]->enemyHead = pHead[0];
		for (auto i = 0; i <= N + 1; i++) pCity[i] = new CCity(i);
		auto hour = 0, min = 0;

		t = 0;
		//计时开始！
		for (hour = 0; t <= T; hour++) {

			min = 0;             //00武士诞生！
			sqi = pHead[0]->make(sqi);
			sqj = pHead[1]->make(sqj);

			t += 5; min = 5; if (t > T)break;     //05Lion逃跑ε=ε=ε=┏(゜ロ゜;)┛
			for (int i = 0; i <= N + 1; i++) {
				if (pCity[i]->pWarriorOfCity[0] && pCity[i]->pWarriorOfCity[0]->sort == 4 && i != N + 1)  //red尝试逃跑
					((CLion*)pCity[i]->pWarriorOfCity[0])->tryToEscape();
				if (pCity[i]->pWarriorOfCity[1] && pCity[i]->pWarriorOfCity[1]->sort == 4 && i != 0)      //blue尝试逃跑
					((CLion*)pCity[i]->pWarriorOfCity[1])->tryToEscape();
			}

			t += 5; min = 10; if (t > T)break;    //10双方武士前进
			CWarrior *pRedArrive = pHead[0]->headMove(), *pBlueArrive = pHead[1]->headMove();
			PrintMove(pRedArrive, pBlueArrive);   //输出前进信息
			if (gameOver == 1)break;  //一方司令部被占领，游戏结束

			t += 10; min = 20; if (t > T)break;   //20每个城市生产生命元
			for (int i = 1; i <= N; i++)
				pCity[i]->yieldStrength();

			t += 10; min = 30; if (t > T)break;   //30武士可取走城中生命元
			for (int i = 1; i <= N; i++)
				pCity[i]->tryToGiveStrength();

			t += 5; min = 35; if (t > T)break;    //35放箭
			for (int i = 0; i <= N + 1; i++) {     //挨个尝试射箭
				if (pCity[i]->pWarriorOfCity[0])pCity[i]->pWarriorOfCity[0]->tryToUseArrow();
				if (pCity[i]->pWarriorOfCity[1])pCity[i]->pWarriorOfCity[1]->tryToUseArrow();
			}

			t += 3; min = 38; if (t > T)break;    //38扔炸弹炸弹(╯‵□′)╯??～*···
			for (int i = 1; i <= N; i++)      //挨个尝试扔炸弹！
				pCity[i]->tryToBombCity();

			t += 2; min = 40; if (t > T)break;    //40开战
			for (int i = 1; i <= N; i++)
				pCity[i]->tryToWageWar();
			pHead[0]->allocate(); pHead[1]->allocate();
			pHead[0]->pushBuffer(); pHead[1]->pushBuffer();

			for (int i = 0; i <= N + 1; i++) {    //清理僵尸
				if (pCity[i]->pWarriorOfCity[0] && pCity[i]->pWarriorOfCity[0]->strength <= 0)
					delete pCity[i]->pWarriorOfCity[0];
				if (pCity[i]->pWarriorOfCity[1] && pCity[i]->pWarriorOfCity[1]->strength <= 0)
					delete pCity[i]->pWarriorOfCity[1];
			}

			t += 10; min = 50; if (t > T)break;   //50回合结束，司令部报告剩余生命元
			pHead[0]->strengthReport();
			pHead[1]->strengthReport();

			t += 5; min = 55; if (t > T)break;    //55武士报告武器情况
			pHead[0]->weaponReport_head();
			pHead[1]->weaponReport_head();

			t += 5;
		}
		delete pHead[0]; delete pHead[1];
		for (auto i = 0; i <= N + 1; i++) delete pCity[i];
	}
	return 0;
}
