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
int n, m, nNodesCnt = 0;
class CNode {
public:
	CNode * pChilds[LETTERS] = { NULL }, *pPrev = NULL;
	bool badNode = false;
}*pStart = NULL, *pRoot = NULL;

void Insert(char *s) {      //把模式串s插入trie树(pRoot)中
	CNode *p = pRoot;
	for (int i = 0; s[i]; i++) {      //i在s串上前进->new新树->p前进
		int index = s[i] - 'a';
		if (!p->pChilds[index]) 
			p->pChilds[index] = new CNode();
		p = p->pChilds[index];   //p前进(指向new出来的结点)
	}
	p->badNode = true;
}

void BuildDfa() {     //设置儿子的前缀指针与危险标识
	for (int i = 0; i < LETTERS; i++) pStart->pChilds[i] = pRoot;
	pStart->pPrev = NULL;
	pRoot->pPrev = pStart;     //tree[1]是root结点
	queue<CNode*> q;

	q.push(pRoot);             //把&root压入deque
	while (!q.empty()) {       //广搜设pPrev
		CNode *pCurrent = q.front();		//【1】取队首元素
		q.pop();							//【2】弹出队首元素
		for (int i = 0; i < LETTERS; i++) {	//【3】压入新元素p(current的儿子)
			CNode *p = pCurrent->pChilds[i];
			if (!p)	continue;					//跳过没儿子的位置
			CNode *pPrev = pCurrent->pPrev;
			while (pPrev->pChilds[i] == NULL)	//回溯,直到pPrev有i儿子
				pPrev = pPrev->pPrev;			//(回溯到p=pStart肯定有)
			p->pPrev = pPrev->pChilds[i];		//设置p-pPrev
			if (p -> pPrev->badNode)	//badNode？
				p->badNode = true;
			q.push(p);
		}
	}
}

bool SearchDfa(char *s) {
	CNode *p = pRoot;
	for (int i = 0; s[i] != '\0'; i++) {
		int index = s[i] - 'a';
		while (p->pChilds[index] == NULL)	//如果p没i儿子就沿前缀指针链回溯,
			p = p->pPrev;                   //..直到p有i儿子(回溯到p=pStart肯定有)
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