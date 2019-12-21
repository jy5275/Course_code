#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int main() {
	char t1; 
	bool suspect = false, inAnno = false, inStr = false, zy = false;
	while ((t1 = cin.get()) != EOF) {
		if (zy) {
			zy = false;
			printf("%c", t1);
			continue;
		}
		if (inAnno == false) {     // Not in annotation currently
			if (t1 == '"') 	inStr = 1 - inStr;
			if (!inStr) {
				if (t1 == '/') {
					if (suspect == true) printf("/");
					suspect = true;
				}
				else if (t1 == '*' && suspect == true && !inStr) 
					inAnno = true, suspect = false;
				else if (suspect == true) {
					printf("/%c", t1);
					suspect = false;
				}
				else printf("%c", t1);
			}
			else {
				if (suspect == true) {
					printf("/");
					suspect = false;
				}
				if (t1 == '\\') 
					zy = true;
				printf("%c", t1);
			}
		}
		else {
			if (t1 == '*') suspect = true;
			else if (t1 == '/' && suspect == true) 
				inAnno = false, suspect = false;
			else if (t1 != '/' && suspect == true) 
				suspect = false;
		}

	}
	return 0;
}/* Bugs:
 1.!inAnno双引号里不管啥都原样保留,inAnno双引号里可以跳进!inAnno
 2.转义字符'\"'直接读会当成两个char,从而跳出inStr;遇到这种情况要zy特殊处理
 */