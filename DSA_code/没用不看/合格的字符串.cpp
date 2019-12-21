#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
using namespace std;
const int MAX = 52;
string convert(string str) {   //转换成小写
	string ans;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] >= 'A'&&str[i] <= 'Z')
			ans.push_back(str[i] - 'A' + 'a');
		else ans.push_back(str[i]);
	}
	return ans;
}
string str[MAX], str_ini[MAX], standard;
bool subExit(string T, string P) {
	int pLen = P.size(), tLen = T.size();
	if (pLen == 0)return false;
	for (int i = 0; i <= tLen - pLen; i++) {
		if (T.substr(i, pLen) == P) return true;
	}
	return false;
}
int main() {
	int n; cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> str_ini[i];
		str[i] = convert(str_ini[i]);
	}   //从此开始str_ini只有在输出之时才派得上用场
	cin >> standard;
	standard = convert(standard);
	int start = standard.find('['), end = standard.rfind(']'), sdLen = standard.size();
	int headLen = start, tailLen = sdLen - end - 1, midLen = sdLen - headLen - tailLen - 2;
	string head(standard, 0, headLen), tail(standard, end + 1, tailLen);
	string mid(standard, start + 1, midLen);
	for (int i = 1; i <= n; i++) {
		int strLen = str[i].size();
		string strHead(str[i], 0, headLen), strTail(str[i], strLen - tailLen, tailLen);
		if (strHead != head || strTail != tail) continue;
		string strMid(str[i], start, strLen - headLen - tailLen);
		if (!subExit(mid, strMid)) continue;
		cout << i << " " << str_ini[i] << endl;
	}
	
	return 0;
}