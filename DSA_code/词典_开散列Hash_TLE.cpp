/* http://dsa.openjudge.cn/final2018test/3/ */
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<memory.h>
#include<string>
#include<bitset>
#include<math.h>
#include<queue>
#include<vector>
#include<set>
using namespace std;
char book[100010][2][12];
class CNode {
public:
	char *pFor, *pEng;
	CNode *next = NULL;
	CNode(char *pf, char *pe) :pFor(pf), pEng(pe) {}
	CNode() {}
};
CNode *dict[20000] = { NULL }, *tail[20000] = { NULL };
void InsertList(char *pf, char *pe) {
	int index = pf[0] - 'a';
	CNode *p = dict[index];
	if (!p) {
		dict[index] = new CNode(pf, pe);
		tail[index] = dict[index];
	}
	else {
		p = tail[index];
		p->next = new CNode(pf, pe);
		tail[index] = p->next;
	}
}
bool SearchList(char str[], char* &ret) {
	int index = str[0] - 'a';
	CNode *p = dict[index];
	while (p) {
		if (strcmp(p->pFor, str) == 0) {
			ret = p->pEng;
			return true;
		}
		p = p->next;
	}
	return false;
}
void DeleteNode(CNode *p) {
	if (p) {
		DeleteNode(p->next);
		delete p;
	}
	else return;
}
void DeleteList() {
	for (int i = 0; i < 27; i++)
		DeleteNode(dict[i]);
}
int main() {
	char c, tmp[24], tmp1[12], tmp2[12];
	for (int j = 0;; j++) {
		fgets(tmp, 30, stdin);
		int len = strlen(tmp);
		if (len <= 1) break;
		int i;
		for (i = 0; i < len; i++)
			if (tmp[i] == ' ')break;
		memcpy(book[j][0], tmp, i); book[j][0][i] = '\0';
		memcpy(book[j][1], tmp + i + 1, len - i - 1); book[j][1][len - i - 2] = '\0';
		InsertList(book[j][1], book[j][0]);
	}
	while (scanf("%s", tmp) != EOF) {
		if (tmp[0] == '0')break;
		char *ans;
		if (SearchList(tmp, ans))
			printf("%s\n", ans);
		else printf("eh\n");
	}
	
	DeleteList();
	return 0;
}