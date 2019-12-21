#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<stack>
#include<memory.h>
#include<string.h>
#include<string>
using namespace std;
// 注意:多个case的程序,每个case清零global！
const int MAX = 15;
string record[1000];
int main() {
	string R;
	int n, No = 0, i = 0, layer = 0;
	char tmp[MAX], line[MAX], ch;
	cin >> n;
	cin.get();
	while (1) {
		memset(tmp, 0, sizeof(tmp));
		memset(line, 0, sizeof(line));
		layer = 0; i = 0; No = 0; ch = 0;
		cin >> ch;
		if (ch == '!') break;
		else cin.putback(ch);
		do {
			cin.getline(line, 100, '\n');
			sscanf(line, "%s", tmp);
			if (tmp[0] == '{') layer++;
			else if (tmp[0] == '}') layer--;
			record[No++] = tmp;
			int len = strlen(line);
			if (len == 0) break;
		} while (1);
		cin >> R; layer = 0; i = 0;
		while (i < No && record[i] != R) i++;
		if (i == No) { cout << "No" << endl; continue; }  //未检出物质R
		while (1) {
			i++;
			if (layer < 0 || i >= No) break;
			if (record[i][0] == '{') layer++;
			else if (record[i][0] == '}') layer--;
			else if (layer > 0) continue;
			else {
				cout << record[i];
			}
		}
		cout << endl;
	}

	return 0;
}