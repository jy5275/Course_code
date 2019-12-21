#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stack>
#include<string>
using namespace std;

int main() {
	stack<string> test;
	char str[1000];
	cin.getline(str, 1000);
	string allstr(str);
	int p = 0, flag = 0, len = allstr.size();
	while (p < len) {
		if (allstr[p] == '<') {       //begin another tag!
			int start = 1;
			if (allstr[p + 1] == '/') {  //1 for <tag>, 0 for </tag>
				p++; start = 0;
				if (p >= len) { flag++; goto end; }
			}
			int begin = p + 1;
			while (allstr[p] != '>') {
				p++;
				if (p >= len) { flag++; goto end; }

			}
			string tmp(allstr, begin, p - begin);
			if (start) test.push(tmp);  // if <tag>
			else {    // if</tag>
				if (tmp != test.top()) {  //</tag>!=<tag>
					flag++; break;
				}
				test.pop();
			}
		}
		p++;
	}
end:
	if (flag || !test.empty()) cout << "False" << endl;
	else cout << "True" << endl;
	return 0;
}