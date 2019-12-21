/* http://dapractise.openjudge.cn/2018hw5/4/ */
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<queue>
#include<string>
#include<cstring>
#include<map>
#include<algorithm>
using namespace std;
const int LETTERS = 4, MAX = 1000;
int N, dp[MAX + 10][MAX + 10], cntNode = 2;

class CNode {
public:
	CNode * pChilds[LETTERS] = { NULL }, *pPrev = NULL;
	bool badNode = false;
	int No = 0;
	CNode(int No_) :No(No_) {}
}*pStart = NULL, *pRoot = NULL;
map<int, CNode*> m;

void Insert(string s) {
	CNode *p = pRoot;
	for (int i = 0; s[i] != '\0'; i++) {
		if (p->pChilds[s[i]-'0'] == NULL) {
			p->pChilds[s[i]-'0'] = new CNode(cntNode);
			m[cntNode] = p->pChilds[s[i] - '0'];
			cntNode++;
		}
		p = p->pChilds[s[i]-'0'];
	}
	p->badNode = true;
}

void Process(string &str) {
	for (int i = 0; str[i] != '\0'; i++) {
		switch (str[i]){
		case 'A':str[i] = '0'; break;
		case 'T':str[i] = '1'; break;
		case 'C':str[i] = '2'; break;
		case 'G':str[i] = '3'; break;
		default:cerr << "Input Error!" << endl;
			break;
		}
	}
}

void BuildDfa() {    //设置pPrev
	for (int i = 0; i < LETTERS; i++) pStart->pChilds[i] = pRoot;
	pRoot->pPrev = pStart;
	
	queue<CNode*> q;

	q.push(pRoot);
	while (!q.empty()) {
		CNode *pCurrent = q.front();
		q.pop();
		for (int i = 0; i < LETTERS; i++) {
			CNode *p = pCurrent->pChilds[i], *pPrev = pCurrent->pPrev;
			if (!p) continue;
			while (pPrev->pChilds[i] == NULL)
				pPrev = pPrev->pPrev;
			p->pPrev = pPrev->pChilds[i];    //【BUG2】"->pChilds[i]"写漏了,
			q.push(p);                       //..BuildDfa后仔细检查pPrev!
			if (p->pPrev->badNode) p->badNode = true;
		}
	}
}

void DeleteDfa(CNode *p) {
	for (int i = 0; i < LETTERS; i++) 
		if (p->pChilds[i])
			DeleteDfa(p->pChilds[i]);
	delete p;
}

int main() {
	int cnt = 1;
	while (1) {
		scanf("%d", &N);
		if (N == 0) break;
		pStart = new CNode(0), pRoot = new CNode(1);
		m[0] = pStart; m[1] = pRoot;
		cntNode = 2;
		string s, str;
		while (N--) {
			cin >> s;
			Process(s);
			Insert(s);
		}

		cin >> str; int len = str.length();
		Process(str);
		for (int i = 0; i <= len; i++) {
			for (int j = 0; j < cntNode; j++)
				dp[i][j] = (1 << 30) - 1;    //【BUG1】1<<31太大,+1导致正溢出！
		}
		BuildDfa();

		dp[0][1] = 0;
		CNode *pCurrent = pRoot, *p = NULL;
		int son = 0;

		for (int i = 0; i < len; i++) {
			for (int j = 0; j < cntNode; j++) {
				pCurrent = m[j];
				if (pCurrent->badNode)continue;
				for (int k = 0; k < LETTERS; k++) {   //遍历son(j)
					bool amend = 0;
 					if (pCurrent->pChilds[k]) {
						p = pCurrent->pChilds[k];
						son = p->No;
					}
					else {
						CNode *pPrev = pCurrent->pPrev;
						while (pPrev->pChilds[k] == NULL)
							pPrev = pPrev->pPrev;
						p = pPrev->pChilds[k];
						son = p->No;
					}
					if (p->badNode) continue;
					bool plus1 = (k != (str[i] - '0'));
					dp[i + 1][son] = min(dp[i + 1][son], dp[i][j] + plus1);
				}
			}
		}

		int ans = (1 << 30) - 1;
		for (int i = 0; i < cntNode; i++) 
			ans = min(ans, dp[len][i]);

		if (ans == (1 << 30) - 1) ans = -1;
		printf("Case %d: %d\n", cnt++, ans);
		DeleteDfa(pRoot);
		delete pStart;
	}
	return 0;
}