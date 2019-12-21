#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class CNode {
public:
	int val;
	CNode *leftchild = NULL, *rightchild = NULL, *parent = NULL;
	CNode(int v_) : val(v_), leftchild(NULL), rightchild(NULL) {}
};
CNode *root = NULL;
vector<int> mid, post;
vector<int>::iterator rt_dynamic;
void buildTree(CNode* &rt, vector<int> &m) {
	int rtVal = *rt_dynamic; 
	if (rt_dynamic != post.begin()) 
		rt_dynamic--;
	rt = new CNode(rtVal);
	auto it_m = find(m.begin(), m.end(), rtVal);
	if (it_m < m.end() - 1) {   //有右子树！
		vector<int> rightmid(it_m + 1, m.end());
		buildTree(rt->rightchild, rightmid);
	}
	if (it_m > m.begin()) {    //有左子树！
		vector<int> leftmid(m.begin(), it_m);
		buildTree(rt->leftchild, leftmid);
	}
}
void trav(CNode *rt) {
	bool first = 1;
	if (!first) printf(" ");
	printf("%d", rt->val); first = 0;
	if (rt->leftchild) trav(rt->leftchild);
	if (rt->rightchild) trav(rt->rightchild);
}
int main() {
	int tmp;
	while (cin>>tmp) {
		mid.push_back(tmp);
		if (cin.get() != ' ') break;
	}
	while (cin >> tmp) {
		post.push_back(tmp);
		if (cin.get() != ' ') break;
	}
	rt_dynamic = post.end() - 1;
	buildTree(root, mid);
	trav(root);
	printf("\n");
	return 0;
}