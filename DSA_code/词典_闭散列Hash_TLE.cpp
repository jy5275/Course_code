/* http://dsa.openjudge.cn/final2018test/3/ */
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<memory.h>
#include<string>
#include<string.h>
#include<bitset>
#include<math.h>
#include<queue>
#include<vector>
#include<set>
#include<map>
using namespace std;
const int MAX = 100010;
class CNode {
public:
	string forg, eng;
	bool taken = 0;
	CNode(string f_, string e_) :forg(f_), eng(e_) {}
	CNode() {}
}HashTable[2 * MAX];
void HashInsert(string f, string e) {
	int home;
	if(f.size() > 1)
		home = 27 * (f[0] - 'a') + f[1] - 'a';
	else home = 26 * (f[0] - 'a');
	int pos = home;
	while (HashTable[pos].taken) {		//找到空位坐下为止
		pos = (pos + 2) % MAX;
	}
	HashTable[pos].taken = 1;
	HashTable[pos].eng = e;
	HashTable[pos].forg = f;
}
bool HashSearch(string f, string &ret) {
	int home;
	if (f.size() > 1) 
		home = 27 * (f[0] - 'a') + f[1] - 'a';
	else home = 26 * (f[0] - 'a');
	int pos = home;
	while (HashTable[pos].taken) {		//只要不是空位就还有找到的希望
		if (HashTable[pos].forg == f) {
			ret = HashTable[pos].eng;
			return true;
		}
		pos = (pos + 2) % MAX;
	}
	return false;
}
int main() {
	char tmp[24], tmp1[12], tmp2[12];
	string str1, str2;
	for (int j = 0;; j++) {
		fgets(tmp, 30, stdin);
		int len = strlen(tmp);
		if (len <= 1) break;
		int i;
		for (i = 0; i < len; i++)
			if (tmp[i] == ' ')break;
		memcpy(tmp1, tmp, i); tmp1[i] = '\0';
		memcpy(tmp2, tmp + i + 1, len - i - 1); tmp2[len - i - 2] = '\0';
		str1 = tmp1, str2 = tmp2;
		HashInsert(str2, str1);
	}
	while (scanf("%s", tmp) != EOF) {
		if (tmp[0] == '0')break;
		str1 = tmp;
		if (HashSearch(str1, str2))
			printf("%s\n", str2.c_str());
		else printf("eh\n");
	}
	return 0;
}