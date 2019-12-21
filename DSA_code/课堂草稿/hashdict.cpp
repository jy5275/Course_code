#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<queue>
#include<memory.h>
#include<stack>
#include<set>
#define EMPTY 0
#define TOMB -1
using namespace std;
template<class Key, class Elem>
Key getkey(Elem e) {    // arbitrary value(Elem) --> key
	//...
}
template<class Key, class Elem>
bool eq(Elem &e1, Elem &e2) {
	return e1 == e2;
}
template<class Key, class Elem>
class hashdict {
private:
	Elem *HT;        // 存放散列表,每个表项的值都是Elem类型
	int M, current;
	int p(Key k, int i) {};
	int h(Key k)const {};
public:
	hashdict(int sz, Elem e);
	~hashdict() { delete[]HT; }
	bool HashSearch(Elem &e)const;
	bool HashInsert(const Elem &e);
	bool HashDelete(const Elem &e);
	int size() { return current; }
};
//========================【Hash插入】===============================
template<class Key, class Elem>
bool hashdict::HashInsert(const Elem &e) {
	int home = h(getkey(e));     //1.home是基地址下标
	int pos = home, insplace = -1;            //e插入的位置
	while (HT[pos] != EMPTY)) {       //3.直到找到EMPTY位坐下...
		if (HT[pos] == e) return false;  //成功的查找 ==> 失败的插入
		if (HT[pos] == TOMB && insplace == -1)   // Find 1st TOMB！还要继续查找！
			insplace = pos;
		pos = (home + p(getkey(e), ++i)) % M;  //pos指向探查序列下一位
	}
	if (insplace == -1) insplace = pos;
	HT[insplace] = e;
	return true;
} 
//=======================【Hash查找】================================
template<class Key, class Elem>
bool hashdict::HashSearch(Elem &e) const { 
	Key k = getkey(e);
	int i = 0, home = h(k);			 //先去home位找有没有！
	int pos = home;
	while (HT[pos] != EMPTY) {	 //跳到空位还没找到就凉了
		if (HT[pos] == e)
			return true;
		pos = (home + p(k, ++i)) % M;  //沿着探查路径继续找！
	}
	return false;
}
//========================【Hash删除】================================
template<class Key, class Elem>
bool hashdict::HashDelete(const Elem &e) {
	Key k = getkey(e);
	int i = 0, home = h(k);
	while (HT[pos] != EMPTY) {	//先来一次成功的查找！
		if (HT[pos] == e)) {
			HT[pos] = TOMB;		//删除的位置设为TOMB
			return true;		//返回一个e,告诉你删除成功
		}
		pos = (home + p(k, ++i)) % M;
	}
	return false;
}
int main() {
	
	return 0;
}