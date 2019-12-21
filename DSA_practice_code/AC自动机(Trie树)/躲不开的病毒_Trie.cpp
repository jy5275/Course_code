/* http://dapractise.openjudge.cn/2018hw5/3/ */
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<string>
#include<queue>
#include<algorithm>
#include<stack>
using namespace std;
const int MAX = 5100010, LETTERS = 2;
/* 妙！Trie图上不含badNode的圈 == 不含病毒的01串，Dfs出一个圈即
 * 还比较好做，看到输入模式大概能想到用Trie图吧。。。
 */
int n, m;
class CNode {
public:
	CNode * pChilds[LETTERS] = { NULL }, *pPrev = NULL;
	int badNode = 0;
	bool visited = 0;
}*pStart = NULL, *pRoot = NULL;

void Insert(string s) {      //把模式串s插入trie树(pRoot)中
	CNode *p = pRoot;
	for (int i = 0; s[i]; i++) {      //i在s串上前进->new新树->p前进
		int index = s[i] - '0';
		if (!p->pChilds[index])
			p->pChilds[index] = new CNode();
		p = p->pChilds[index];   //p前进(指向new出来的结点)
	}
	p->badNode = 1;  //Insert时肯定无重,b++和b=1效果一样
}

void BuildDfa() {     //设置前缀指针与危险标识
	for (int i = 0; i < LETTERS; i++) pStart->pChilds[i] = pRoot;
	pStart->pPrev = NULL;
	pRoot->pPrev = pStart;     //tree[1]是root结点
	queue<CNode*> q;

	q.push(pRoot);             //把&root压入deque
	while (!q.empty()) {       //广搜设pPrev
		CNode *pCurrent = q.front();       //【1】取队首元素
		q.pop();                           //【2】弹出队首
		for (int i = 0; i < LETTERS; i++) {    //【3】准备压入新元素p
			CNode *p = pCurrent->pChilds[i];
			if (!p)	continue;
			CNode *pPrev = pCurrent->pPrev;
			while (pPrev->pChilds[i] == NULL)  //如果p没i儿子,沿前缀指针链回溯
				pPrev = pPrev->pPrev;          //..直到p有i儿子(回溯到p=pStart肯定有)
			p->pPrev = pPrev->pChilds[i];      //终于可以设置p前缀指针了！
			q.push(p);

			//不去重的话,这里要加入if(badNode)badNode=1
			if (p->pPrev->badNode) p->badNode = 1;
		}
	}
}

bool Dfs(CNode *pCurrent) {
	if (pCurrent->visited) return true;   //找到圈，成功！
	if (pCurrent->badNode) return false;  //踩到禁止点，失败！
	pCurrent->visited = true;
	CNode *pNext = NULL;
	for (int i = 0; i < LETTERS; i++) {
		if (pCurrent->pChilds[i]) pNext = pCurrent->pChilds[i];
		else {
			CNode *pPrev = pCurrent->pPrev;
			while (pPrev->pChilds[i] == NULL)
				pPrev = pPrev->pPrev;
			pNext = pPrev->pChilds[i];
		}
		if (Dfs(pNext)) return true;	//成功找到！
		else continue;		//失败了，换个子结点继续试...
	}
	pCurrent->visited = false;   //试尽所有子结点无路可走,退回去吧
	return false;
}

void DeleteDfa(CNode *root) {    //删除root的所有子树
	for (int i = 0; i < LETTERS; i++)
		if (root->pChilds[i])
			DeleteDfa(root->pChilds[i]);
	delete root;
}

int main() {
	string str;
	pStart = new CNode, pRoot = new CNode;  
	scanf("%d", &n);    //n种病毒(模式串)
	for (int i = 0; i < n; i++) {
		cin >> str;
		Insert(str);
	}
	
	BuildDfa();
	if (Dfs(pRoot)) printf("TAK\n");
	else printf("NIE\n");

	DeleteDfa(pRoot);   
	delete pStart;
	return 0;
}