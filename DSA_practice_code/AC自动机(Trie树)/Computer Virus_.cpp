/* http://dapractise.openjudge.cn/2018hw5/2/ */
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<string>
#include<queue>
#include<algorithm>
using namespace std;
const int MAX = 5100010, LETTERS = 26;
int n, m, cntVirus = 0;
class CNode {
public:
	CNode * pChilds[LETTERS] = { NULL }, *pPrev = NULL;
	int badNode = 0;
	bool safe = false;
}*pStart = NULL, *pRoot = NULL;

int calcBadNode(CNode *p) {  //【BUG4】只设置badNode无法对已访问病毒去重,递归大法好
	if (p->safe)             //【BUG5】为省时,设safe标志,表示已访问保证安全,
		return 0;            //..后续再沿前缀链寻访至此不用继续走,直接返回0
	int ans = p->badNode;
	p->badNode = 0, p->safe = true;   //访问后这个结点就安全了
	if (p->pPrev) ans += calcBadNode(p->pPrev);
	return ans;
}

void Insert(string s) {      //把模式串s插入trie树(pRoot)中
	CNode *p = pRoot;
	for (int i = 0; s[i]; i++) {      //i在s串上前进->new新树->p前进
		if (!p->pChilds[s[i] - 'A'])
			p->pChilds[s[i] - 'A'] = new CNode();
		p = p->pChilds[s[i] - 'A'];   //p前进(指向new出来的结点)
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
		CNode *pCurrent = q.front();       //1.取队首元素
		q.pop();                           //2.弹出队首元素
		for (int i = 0; i < LETTERS; i++) {    //3.准备压入新元素p
			CNode *p = pCurrent->pChilds[i];   //pRoot的i号指针
			if (!p)	continue;                  //如果pChild[i]为空,跳过这一步
			CNode *pPrev = pCurrent->pPrev;    //pPrev是p父的前缀指针指的结点
			while (pPrev->pChilds[i] == NULL)  //如果p没有i儿子就沿着前缀指针链回溯,
				pPrev = pPrev->pPrev;          //..直到p有i儿子(回溯到p=pStart肯定有)
			p->pPrev = pPrev->pChilds[i];      //终于可以设置p前缀指针了！
											   //if (p->pPrev->badNode)//设置危险节点
											   //p->badNode++;
			q.push(p);
			//不去重的话,这里要加入if(badNode)badNode=1
		}
	}
}

void SearchDfa(string s) {     //SearchDfa的效果是更新cntVirus  
	CNode *p = pRoot;
	for (int i = 0; s[i] != '\0'; i++) {
		while (p->pChilds[s[i] - 'A'] == NULL) //如果p没有i儿子就沿着前缀指针链回溯,
			p = p->pPrev;                      //..直到p有i儿子(回溯到p=pStart肯定有)
		p = p->pChilds[s[i] - 'A'];
		cntVirus += calcBadNode(p);
	}
}

void Process(string &str) {
	int p = 0;
	while (1) {
		if (str[p] == '\0') break;
		if (str[p] == '[') {
			int q = p;
			for (; str[q] != ']'; q++);
			string strNum = str.substr(p + 1, q - p - 2);  //取出[]中蕴含的int
			int rep = stoi(strNum);    //repCh重复次数
			char repCh = str[q - 1];
			str.replace(p, q - p + 1, rep, repCh);
			p = p + rep;
		}
		else p++;
	}
}

void DeleteDfa(CNode *root) {    //删除root的所有子树。【BUG3】new了要delete别忘
	for (int i = 0; i < LETTERS; i++)
		if (root->pChilds[i])
			DeleteDfa(root->pChilds[i]);
	delete root;
}

int main() {
	string str;
	int T; scanf("%d", &T);
	while (T--) {           // For each case
		pStart = new CNode, pRoot = new CNode, cntVirus = 0;  //【BUG1】访问NULL
		scanf("%d", &n);    //n种病毒(模式串)
		for (int i = 0; i < n; i++) {
			cin >> str;
			Insert(str);
		}
		BuildDfa();
		cin >> str;
		Process(str);       //"解压"母串str

		SearchDfa(str);
		reverse(str.begin(), str.end());
		SearchDfa(str);

		DeleteDfa(pRoot);   //【BUG2】pStart不能一块Delete,因为所有pChild指向同一对象！
		delete pStart;
		printf("%d\n", cntVirus);
	}
	return 0;
}/* 实际上很简单,但题目说不清楚ambiguous也没办法...
 印证了WA指导方针——使劲造数据测数据,重点找特殊值(一位测试工程师走进酒吧...)
 这套模板用着挺好,背下CNode类,BuildDfa(),Insert(s),SearchDfa(s),DeleteDfa(root)
 ..这道题特殊之处在于要对搜索历史【去重】,找到过的模式串之后就【不再找了】,
 ..所以将badNode设为0/1型int,并在SearchDfa时递归求badNode,
 还有设置safe安全位剪枝递归省时
 */