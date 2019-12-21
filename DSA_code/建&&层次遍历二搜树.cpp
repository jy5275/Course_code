#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<stack>
#include<memory.h>
#include<queue>
#include<string>
using namespace std;
/* 注意两点:
   1.上层函数传入指针后想在修改指针变量的值,必须使指针引用作形参！
     树形数据结构初始化root时(给NULL赋值)用得上,这给偷懒不写Tree类提供了方便
   2.new之后还是要delete一下,要不然轻则内存泄漏,重则报半天找不出来的bug...
     想想cachelab中malloc后不free的惨痛教训!!!
*/
class CNode {
public:
	int val;
	CNode *leftchild = NULL, *rightchild = NULL;
	CNode(int v_) :val(v_), leftchild(NULL), rightchild(NULL){}
};
CNode *root = NULL;
void AddPoint(CNode *p, int v) { //【BUG1】指针的引用作形参,才能改传入的指针变量
	if (!p) p = new CNode(v);
	if (v > p->val) {
		if (p->leftchild == NULL)
			p->leftchild = new CNode(v);
		else AddPoint(p->leftchild, v);
	}
	else if (v < p->val) {
		if (p->rightchild == NULL)
			p->leftchild = new CNode(v);
		else AddPoint(p->rightchild, v);
	}
}
void DeleteTree(CNode* &p) {   //【BUG2】又忘记了delete!
	if (p->leftchild) DeleteTree(p->leftchild);
	if (p->rightchild) DeleteTree(p->rightchild);
	delete p;
}
int main() {
	int tmp, first = 1, index;
	scanf("%d", &tmp);
	root = new CNode(v);
	while (scanf("%d", &tmp) != EOF) 
		AddPoint(root, tmp);
	queue<CNode*> q;
	if(root)
		q.push(root);
	while (!q.empty()) {
		CNode *now = q.front(); q.pop();
		if (!first) printf(" ");
		printf("%d", now->val); 
		first = 0;
		if (now->leftchild) q.push(now->leftchild);
		if (now->rightchild) q.push(now->rightchild);
	}
	DeleteTree(root);
	return 0;
}