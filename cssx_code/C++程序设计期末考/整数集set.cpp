#include<iostream>
#include<vector>
#include<string>
#include<set>
#include<algorithm>
using namespace std;
set<int> logSet;    //set的insert更省时，insert失败就无时间成本
multiset<int> MySet;
void MyAdd() {
	int x; cin >> x;
	MySet.insert(x);
	logSet.insert(x);
	cout << MySet.count(x) << endl;
}
void MyDel() {
	int x; cin >> x;
	cout << MySet.erase(x) << endl;
}
void MyAsk() {
	int x; cin >> x;
	if (logSet.count(x))cout << "1 ";
	else cout << "0 ";
	cout << MySet.count(x) << endl;
}
int main() {
	int n;	cin >> n;
	string cmd;
	while (n--) {
		cin >> cmd;
		if (cmd == "add") MyAdd();
		else if (cmd == "del") MyDel();
		else if (cmd == "ask") MyAsk();
		else cerr << "Illegal Input! " << endl;
	}
	return 0;
}