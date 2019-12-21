#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<stack>
#include<memory.h>
#include<queue>
#include<bitset>
using namespace std;
const int MAX = 1 << 12;
int n, No = 0;
class CNode {
public:
	int name, layer = 0;
	CNode *leftchild = NULL, *rightchild = NULL;
};
CNode *tree = new CNode[12];
int Depth() {
	queue<CNode*> q;
	int currentLayer = 0;
	tree[1].layer = 1;
	q.push(tree + 1);  //根结点地址入队
	while (!q.empty()) {
		CNode * now = q.front(); q.pop();
		currentLayer = now->layer;
		//if (!now->leftchild && !now->rightchild) return currentLayer;
		if (now->leftchild) {
			now->leftchild->layer = currentLayer + 1;
			q.push(now->leftchild);
		}
		if (now->rightchild) {
			now->rightchild->layer = currentLayer + 1;
			q.push(now->rightchild);
		}
	}
	return currentLayer;
}
int main() {
	cin >> n;
	int l, r;
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &l, &r);
		if (l != -1) tree[i].leftchild = tree + l;
		else tree[i].leftchild = NULL;
		if (r != -1) tree[i].rightchild = tree + r;
		else tree[i].rightchild = NULL;
	}
	cout << Depth() << endl;
	delete[]tree;
	return 0;
}