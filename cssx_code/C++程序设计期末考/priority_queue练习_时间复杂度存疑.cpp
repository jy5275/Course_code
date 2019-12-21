#include<iostream>
#include<vector>
#include<string>
#include<set>
#include<cmath>
#include<list>
#include<map>
#include<algorithm>
#include<queue>
using namespace std;/*
					int notPrime[100001] = { 0 }, primeList[6001] = { 0 }, cnt = 0;
					void findPrime() {
					for (int i = 2; i < 100001; i++) {
					for (int j = 2; j < i; j++) {
					if (notPrime[j]) continue;
					if (i%j == 0) { //i可被j整除！i是合数！停止调查这个i！
					notPrime[i] = 1;
					break;
					}
					}
					if (notPrime[i] == 0)
					primeList[cnt++] = i;
					}
					}*/
bool isPrime(int iVal) {
	for (int i = 2; i <= sqrt((float)iVal); i++) {
		if (iVal % i == 0)
			return false;
	}
	return true;
}
/*
int findPrimeNum(int primary) {
int n = primary, ans = 0, attemptId = 0;
for (; n != 1; attemptId++) {    //只要n还是合数，就一直搜索下去！
int processed = 0;
if (primeList[attemptId] == primary)break;
while (n%primeList[attemptId] == 0 && n != 1) {
//只要还有这个质因数且为合数，就一直除下去！
n = n / primeList[attemptId];
if (processed == 0) {
ans++;
processed = 1;
//cout << primeList[attemptId] << " ";
}
}
}
return ans;
}*/
int findPrimeNum(int a) {
	int sum = 0, k = 0;
	for (int i = 2; i <= sqrt((float)a); i++) {
		if (a % i == 0) {      //即a/i = k，无余数
			k = a / i;
			if (i != k && isPrime(k))  //此处把a分解为a=k*i,分别看k和i是不是prime
				sum += 1;
			if (isPrime(i))
				sum += 1;
		}
	}
	return sum;
}
/*
class MyValue {
int val, primeNum;
friend ostream &operator<<(ostream &os, const MyValue v);
friend bool operator<(const MyValue &v1, const MyValue &v2);
friend class Larger;
public:
MyValue(int v_) :val(v_) {
primeNum = findPrimeNum(val);
}
};
bool operator<(const MyValue &v1, const MyValue &v2) {
if (v1.primeNum > v2.primeNum)return 1;
else if (v1.primeNum < v2.primeNum)return 0;
else return v1.val > v2.val;
}*/
class Larger {
public:
	bool operator()(int v1, int v2) {
		int a1 = findPrimeNum(v1), a2 = findPrimeNum(v2);
		if (a1 > a2)return 1;
		else if (a1 < a2)return 0;
		else return v1 > v2;
	}
};
class Less {
public:
	bool operator()(int v2, int v1) {
		int a1 = findPrimeNum(v1), a2 = findPrimeNum(v2);
		if (a1 > a2)return 1;
		else if (a1 < a2)return 0;
		else return v1 > v2;
	}
};
/*
ostream &operator<<(ostream &os, const MyValue v) {
os << v.val;
return os;
}*/
multiset<int, Larger> numSet;
multiset<int>::iterator pSet;
int main() {
	//findPrime();  //很奇怪，用findPrime就会超时，为什么？
	int num, tmp;
	cin >> num;
	while (num--) {
		for (int i = 0; i < 10; i++) {
			cin >> tmp;
			numSet.insert(tmp);
		}
		pSet = numSet.begin();   //迭代器移到队首最优元素
		cout << *pSet << " ";    //输出最优者
		numSet.erase(pSet);      //删除最优者
		pSet = numSet.end(); --pSet;  //迭代器移到队末最劣元素
		cout << *pSet << endl;   //输出最劣者
		numSet.erase(pSet);      //删除最劣者
	}
	return 0;
}