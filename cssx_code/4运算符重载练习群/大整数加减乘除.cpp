#include<iostream>
#include<string.h>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;
const int Max = 101;
int max(const int a, const int b) {   //比大小函数
	if (a > b)return a;
	else return b;
}
class Num {
	int  size = 0, num[2 * Max + 1] = { 0 }, minus = 0;
	char chNum[Max + 2];
public:
	friend ostream &operator<<(ostream &os, const Num &ans);
	void getSize() {            //获取数组长度
		int i;
		for (i = 2 * Max; num[i] == 0; i--) {
			if (i == 0) { size = 0; return; }
		}
		size = i + 1;
	}
	int numCmp(const Num &a, const Num &b) {   //比两个数组的大小
		int i;
		for (i = Max + 1; a.num[i] == 0 && b.num[i] == 0; i--) {}
		for (; i >= 0; i--) {
			if (a.num[i] > b.num[i]) return 1;
			else if (a.num[i] < b.num[i])return -1;
		}
		return 0;
	}
	void getNum() {                   //人工初始化函数,前端输入
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
	Num &operator+(const int a) {    //再次重载+:Num+int(10以内)
		Num *tmp = new Num;
		tmp->num[0] = a; tmp->size = 1;
		return (*tmp + *this);
	}
	Num &operator-(const Num c) {    //减法重载
		int i;
		Num *tmp = new Num;
		Num a = *this, b = c;        //a,b是临时类Num对象,可修改
		if (numCmp(*this, c) < 0) {  //如果a<b...
			a = c, b = *this;        //无论如何,得令a>b
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
	Num &operator-(const int a) {    //再次重载-:Num-int(10以内)
		Num *tmp = new Num;
		tmp->num[0] = a; tmp->size = 1;
		return *this - *tmp;
	}
	Num &operator*(const Num &a) {    //乘法重载
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
	Num &operator*(const int a) {   //乘法再次重载:Num*int=Num
		Num *tmp = new Num;
		tmp->num[0] = a; tmp->size = 1;
		return (*this)*(*tmp);
	}
	Num &operator/(const Num &a) {
		Num *tmp = new Num, divider = a, *t = new Num;
		int i, j, Index = size - divider.size;           //Index记录商首位是(理想)第几位
		if (numCmp(*this, divider) < 0) { tmp->size = 0; return *tmp; }
		for (i = size - 1,j = divider.size-1; i >= size - divider.size; i--,j--)  //取出dividant前divider.size位                   
				t->num[j] = num[i]; //作为新Num对象t存起来
		t->getSize();
		for (; Index >= 0; Index--) {     //竖式除法开始,遍历dividant所有位
			for (i = 1; i <= 10; i++) {
				if (numCmp(divider * i, *t) > 0) break;  //++过头了!回来一个!写进商里新一位!
			}
			tmp->num[Index] = i - 1;  //把i-1写进商里边新一位(第Index位)//
			tmp->getSize();
			Num substract = divider * (i - 1); substract.getSize();
			*t = (*t - substract);  //更新余数t,减去可整除部分
			if (Index == 0)break;     //如果已经到了dividant个位,跳出来吧
			for (j = t->size; j > 0; j--)   //余数t里集体右移
				t->num[j] = t->num[j - 1];      
			t->num[j] = num[Index-1];  //把this->num新一位塞进t最左边
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