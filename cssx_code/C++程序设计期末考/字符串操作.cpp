/*����
����n���ַ�������1��ʼ��ţ���ÿ���ַ����е��ַ�λ�ô�0��ʼ��ţ�����Ϊ1 - 500�������������ɲ�����
copy N X L��ȡ����N���ַ�����X���ַ���ʼ�ĳ���ΪL���ַ�����
add S1 S2:�ж�S1,S2�Ƿ�Ϊ0-99999����������������ת��Ϊ�������ӷ�,�����������ַ����ӷ�,����һ�ַ���
find S N���ڵ�N���ַ����д���ʼ��ѰS�ַ������������һ�γ��ֵ�λ�ã���û���ҵ��������ַ����ĳ���
rfind S N���ڵ�N���ַ����д��ҿ�ʼ��ѰS�ַ������������һ�γ��ֵ�λ�ã���û���ҵ��������ַ����ĳ���
insert S N X���ڵ�N���ַ����ĵ�X���ַ�λ���в���S�ַ�����
reset S N������N���ַ�����ΪS��
print N����ӡ�����N���ַ�����
printall����ӡ��������ַ�����
over������������

����N��X��L����find��rfind�������ʽ���ɣ�S��S1��S2����copy��add�������ʽ���ɡ�
����
��һ��Ϊһ������n��n��1 - 20֮�䣩
������n��Ϊn���ַ������ַ����������ո񼰲�������ȡ�
������������Ϊһϵ�в�����ֱ��over������

���
���ݲ�����ʾ�����Ӧ�ַ�����*/

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
	cin >> S; S = strProcess(S);   //��S����string��������,����һ��string
	cin >> N; n = intProcess(N);   //��N����int��������,����һ��int
	str[n] = S;     //ֱ�Ӵֱ��ذ�nth�ַ���resetΪS
}
void MyInsert() {
	string S, N, X; int n, x;
	cin >> S; S = strProcess(S);   //��S����string��������,����һ��string
	cin >> N; n = intProcess(N);   //��N����int��������,����һ��int
	cin >> X; x = intProcess(X);   //��X����int��������,����һ��int
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