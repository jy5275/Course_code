#include<iostream>
#include<string.h>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;
const int Max = 101;
int max(const int a, const int b) {   //�ȴ�С����
	if (a > b)return a;
	else return b;
}
class Num {
	int  size = 0, num[2 * Max + 1] = { 0 }, minus = 0;
	char chNum[Max + 2];
public:
	friend ostream &operator<<(ostream &os, const Num &ans);
	void getSize() {            //��ȡ���鳤��
		int i;
		for (i = 2 * Max; num[i] == 0; i--) {
			if (i == 0) { size = 0; return; }
		}
		size = i + 1;
	}
	int numCmp(const Num &a, const Num &b) {   //����������Ĵ�С
		int i;
		for (i = Max + 1; a.num[i] == 0 && b.num[i] == 0; i--) {}
		for (; i >= 0; i--) {
			if (a.num[i] > b.num[i]) return 1;
			else if (a.num[i] < b.num[i])return -1;
		}
		return 0;
	}
	void getNum() {                   //�˹���ʼ������,ǰ������
		cin.getline(chNum, Max + 1);
		size = strlen(chNum);
		for (int i = 0, j = size - 1; j >= 0; j--, i++)
			num[i] = chNum[j] - '0';
	}
	
	Num &operator+(const Num a) {
		Num *tmp = new Num;
		for (int i = 0; i < max(a.size, size); i++) {
			tmp->num[i] += num[i] + a.num[i];
			tmp->num[i + 1] = tmp->num[i] / 10;
			tmp->num[i] = tmp->num[i] % 10;
		}
		tmp->getSize();
		return *tmp;
	}
	Num &operator+(const int a) {    //�ٴ�����+:Num+int(10����)
		Num *tmp = new Num;
		tmp->num[0] = a; tmp->size = 1;
		return (*tmp + *this);
	}
	Num &operator-(const Num c) {    //��������
		int i;
		Num *tmp = new Num;
		Num a = *this, b = c;        //a,b����ʱ��Num����,���޸�
		if (numCmp(*this, c) < 0) {  //���a<b...
			a = c, b = *this;        //�������,����a>b
			tmp->minus = 1; 
		}
		for (i = 0; i <= max(a.size, b.size); i++) {
			tmp->num[i] = a.num[i] - b.num[i];
			if (tmp->num[i] < 0) {
				a.num[i + 1]--;
				tmp->num[i] += 10;
			}
		}
		tmp->getSize();
		return *tmp;
	}
	Num &operator-(const int a) {    //�ٴ�����-:Num-int(10����)
		Num *tmp = new Num;
		tmp->num[0] = a; tmp->size = 1;
		return *this - *tmp;
	}
	Num &operator*(const Num &a) {    //�˷�����
		Num *tmp = new Num;
		for (int i = 0; i < this->size; i++) {
			for (int j = 0; j < a.size; j++)
				tmp->num[i + j] += a.num[j] * num[i];
		}
		for (int i = 0; i <= this->size + a.size; i++) {
			tmp->num[i + 1] = tmp->num[i + 1] + tmp->num[i] / 10;
			tmp->num[i] = tmp->num[i] % 10;
		}
		tmp->getSize();
		return *tmp;
	}
	Num &operator*(const int a) {   //�˷��ٴ�����:Num*int=Num
		Num *tmp = new Num;
		tmp->num[0] = a; tmp->size = 1;
		return (*this)*(*tmp);
	}
	Num &operator/(const Num &a) {
		Num *tmp = new Num, divider = a, *t = new Num;
		int i, j, Index = size - divider.size;           //Index��¼����λ��(����)�ڼ�λ
		if (numCmp(*this, divider) < 0) { tmp->size = 0; return *tmp; }
		for (i = size - 1,j = divider.size-1; i >= size - divider.size; i--,j--)  //ȡ��dividantǰdivider.sizeλ                   
				t->num[j] = num[i]; //��Ϊ��Num����t������
		t->getSize();
		for (; Index >= 0; Index--) {     //��ʽ������ʼ,����dividant����λ
			for (i = 1; i <= 10; i++) {
				if (numCmp(divider * i, *t) > 0) break;  //++��ͷ��!����һ��!д��������һλ!
			}
			tmp->num[Index] = i - 1;  //��i-1д���������һλ(��Indexλ)//
			tmp->getSize();
			Num substract = divider * (i - 1); substract.getSize();
			*t = (*t - substract);  //��������t,��ȥ����������
			if (Index == 0)break;     //����Ѿ�����dividant��λ,��������
			for (j = t->size; j > 0; j--)   //����t�Ｏ������
				t->num[j] = t->num[j - 1];      
			t->num[j] = num[Index-1];  //��this->num��һλ����t�����
			t->getSize();
		}
		tmp->getSize();
		return *tmp;
	}
};
ostream &operator<<(ostream &os, const Num &ans) {
	if (ans.size == 0) { cout << 0; return os; }
	if (ans.minus == 1)cout << '-';
	for (int i = ans.size - 1; i >= 0; i--) 
		cout << ans.num[i];
	return os;
}
int main() {
	Num a, b, ans;
	char mani;
	a.getNum(); cin >> mani; cin.get(); b.getNum();
	switch (mani) {
	case '+':ans = a + b; break;
	case '-':ans = a - b; break;
	case '*':ans = a * b; break;
	case '/':ans = a / b; break;
	default:cerr << "Error"; return 0;
	}
	cout << ans << endl;
	return 0;
}