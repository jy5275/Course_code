#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stack>
#include<string>
using namespace std;
int main() {
	int N; cin >> N;
	cin.get();
	while (N--) {
		char str[10000];
		cin.getline(str, 10001);
		string allstr(str);
		int p = 0, len = allstr.size();
		for (; p < len; p++) {
			if (allstr[p] >= 'a'&&allstr[p] < 'z')
				allstr[p] = allstr[p] + 1;
			else if (allstr[p] >= 'A'&&allstr[p] < 'Z')
				allstr[p] = allstr[p] + 1;
			else if (allstr[p] == 'z')
				allstr[p] = 'a';
			else if (allstr[p] == 'Z')
				allstr[p] = 'A';
		}
		cout << allstr << endl;
	}
	return 0;
}