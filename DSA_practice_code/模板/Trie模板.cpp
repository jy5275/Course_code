/* http://dapractise.openjudge.cn/2018hw5/1/ 
模板题,背熟不解释 */
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<list>
#include<deque>
#include<queue>
#include<algorithm>
using namespace std;
const int MAX = 1000, LETTERS = 26;
char str[MAX];
int n, m;
class CNode {
public:
	CNode * pChilds[LETTERS] = { NULL }, *pPrev = NULL;
	bool badNode = false;
}*pStart = NULL, *pRoot = NULL;
// Start is above root, all its children are root

void BuildDfa() {     // set pPrev ptr
	for (int i = 0; i < LETTERS; i++) pStart->pChilds[i] = pRoot;
	pStart->pPrev = NULL;
	pRoot->pPrev = pStart;
	queue<CNode*> q;

	q.push(pRoot);
	while (!q.empty()) {       // Use BFS to set pPrev
		CNode *pCurrent = q.front();		// 1. Fetch queue front elem
		q.pop();							// 2. Pop it out
		for (int i = 0; i < LETTERS; i++) {	// 3. Push new elem (all pCurrent's children)
			CNode *p = pCurrent->pChilds[i];
			if (p == NULL)	continue;
			CNode *pPrev = pCurrent->pPrev;
			while (pPrev->pChilds[i] == NULL)	// Backtrack until pPrev has child[i]
				pPrev = pPrev->pPrev;			// (pStart must have so backtrack will finally stop)
			p->pPrev = pPrev->pChilds[i];		// Set p-pPrev!
			if (p->pPrev->badNode)	// badNode？--> should set!
				p->badNode = true;
			q.push(p);
		}
	}
}

void Insert(char *s) {      // Insert pattern string s into Trie tree (pRoot)
	CNode *p = pRoot;
	for (int i = 0; s[i]; i++) {      // Process through s -> new Node
		int index = s[i] - 'a';
		if (!p->pChilds[index]) 
			p->pChilds[index] = new CNode();
		p = p->pChilds[index];
	}
	p->badNode = true;
}

bool SearchDfa(char *s) {
	CNode *p = pRoot;
	for (int i = 0; s[i] != '\0'; i++) {
		int index = s[i] - 'a';
		while (p->pChilds[index] == NULL)	// Backtrack until p has child[idx]
			p = p->pPrev;                   // (must have when p=pStart)
		p = p->pChilds[index];
		if (p->badNode) return true;
	}
	return false;
}

int main() {
	pStart = new CNode, pRoot = new CNode;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%s", str);
		Insert(str);
	}
	BuildDfa();
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		scanf("%s", str);
		if (SearchDfa(str)) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}