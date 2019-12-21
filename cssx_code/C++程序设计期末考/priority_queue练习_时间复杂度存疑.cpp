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
					if (i%j == 0) { //i�ɱ�j������i�Ǻ�����ֹͣ�������i��
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
for (; n != 1; attemptId++) {    //ֻҪn���Ǻ�������һֱ������ȥ��
int processed = 0;
if (primeList[attemptId] == primary)break;
while (n%primeList[attemptId] == 0 && n != 1) {
//ֻҪ���������������Ϊ��������һֱ����ȥ��
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
		if (a % i == 0) {      //��a/i = k��������
			k = a / i;
			if (i != k && isPrime(k))  //�˴���a�ֽ�Ϊa=k*i,�ֱ�k��i�ǲ���prime
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
	//findPrime();  //����֣���findPrime�ͻᳬʱ��Ϊʲô��
	int num, tmp;
	cin >> num;
	while (num--) {
		for (int i = 0; i < 10; i++) {
			cin >> tmp;
			numSet.insert(tmp);
		}
		pSet = numSet.begin();   //�������Ƶ���������Ԫ��
		cout << *pSet << " ";    //���������
		numSet.erase(pSet);      //ɾ��������
		pSet = numSet.end(); --pSet;  //�������Ƶ���ĩ����Ԫ��
		cout << *pSet << endl;   //���������
		numSet.erase(pSet);      //ɾ��������
	}
	return 0;
}