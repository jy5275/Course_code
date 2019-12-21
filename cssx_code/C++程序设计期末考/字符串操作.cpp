/*描述
给定n个字符串（从1开始编号），每个字符串中的字符位置从0开始编号，长度为1 - 500，现有如下若干操作：
copy N X L：取出第N个字符串第X个字符开始的长度为L的字符串。
add S1 S2:判断S1,S2是否为0-99999间整数，若是则将其转化为整数做加法,若不是则作字符串加法,返回一字符串
find S N：在第N个字符串中从左开始找寻S字符串，返回其第一次出现的位置，若没有找到，返回字符串的长度
rfind S N：在第N个字符串中从右开始找寻S字符串，返回其第一次出现的位置，若没有找到，返回字符串的长度
insert S N X：在第N个字符串的第X个字符位置中插入S字符串。
reset S N：将第N个字符串变为S。
print N：打印输出第N个字符串。
printall：打印输出所有字符串。
over：结束操作。

其中N，X，L可由find与rfind操作表达式构成，S，S1，S2可由copy与add操作表达式构成。
输入
第一行为一个整数n（n在1 - 20之间）
接下来n行为n个字符串，字符串不包含空格及操作命令等。
接下来若干行为一系列操作，直到over结束。

输出
根据操作提示输出对应字符串。*/

#include<iostream>
#include<vector>
#include<string>
#include<set>
#include<list>
#include<algorithm>
using namespace std;
string MyCopy();
int MyFind();
int MyRfind();
string MyAdd();
vector<string> str;
bool isDegital(string str) {
	if (str.size() > 5) return false;
	for (int i = 0; i < str.size(); i++) {
		if (str.at(i) > '9' || str.at(i) < '0')return false;
	}
	return true;
}
string strProcess(string str) {
	if (str == "copy") return MyCopy();
	else if (str == "add") return MyAdd();
	else return str;
}
int intProcess(string str) {
	if (str == "find") return MyFind();
	else if (str == "rfind") return MyRfind();
	else return atoi(str.c_str());
}
int MyFind() {
	string S, N; int n, flag;
	cin >> S; S = strProcess(S);
	cin >> N; n = intProcess(N);
	if ((flag = str[n].find(S)) != string::npos) return flag;
	else return str[n].size();
}
int MyRfind() {
	string S, N; int n, flag;
	cin >> S; S = strProcess(S);
	cin >> N; n = intProcess(N);
	if ((flag = str[n].rfind(S)) != string::npos) return flag;
	else return str[n].size();
}
string MyCopy() {
	string N, X, L; int n, x, l;
	cin >> N; n = intProcess(N);
	cin >> X; x = intProcess(X);
	cin >> L; l = intProcess(L);
	return str[n].substr(x, l);
}
string MyAdd() {
	string S1, S2, ANS; int s1, s2, ans;
	cin >> S1; S1 = strProcess(S1);
	cin >> S2; S2 = strProcess(S2);
	if (isDegital(S1) && isDegital(S2)) {
		ans = atoi(S1.c_str()) + atoi(S2.c_str());
		ANS = to_string(ans);
	}
	else ANS = S1 + S2;
	return ANS;
}
void MyPrint() {
	int n;
	cin >> n;
	cout << str[n] << endl;
}
void MyPrintall() {
	int sz = str.size();
	for (int i = 1; i != sz; i++)
		cout << str[i] << endl;
}
void MyReset() {
	string S, N;
	int n;
	cin >> S; S = strProcess(S);   //把S送往string处理中心,返回一个string
	cin >> N; n = intProcess(N);   //把N送往int处理中心,返回一个int
	str[n] = S;     //直接粗暴地把nth字符串reset为S
}
void MyInsert() {
	string S, N, X; int n, x;
	cin >> S; S = strProcess(S);   //把S送往string处理中心,返回一个string
	cin >> N; n = intProcess(N);   //把N送往int处理中心,返回一个int
	cin >> X; x = intProcess(X);   //把X送往int处理中心,返回一个int
	str[n].insert(x, S);
}
int main() {
	int n; cin >> n;
	string cmd;
	str.push_back(" ");
	for (int i = 1; i <= n; i++) {
		string tmp; cin >> tmp;
		str.push_back(tmp);
	}
	while (1) {
		cin >> cmd;
		if (cmd == "reset") MyReset();
		else if (cmd == "insert") MyInsert();
		else if (cmd == "print") MyPrint();
		else if (cmd == "printall") MyPrintall();
		else if (cmd == "over")break;
	}
	return 0;
}