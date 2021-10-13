
// you can use includes, for example:
// #include <algorithm>
#include <algorithm>
#include <iostream>
using namespace std;
// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

int Left(int x) { return 2 * x + 1; }
int Right(int x) { return 2 * x + 2; }
class CNode {
public:
    int L, R;
    int minN = (1 << 31) - 1;
    int Mid() { return (L+R)/2; }
};

void BuildTree(CNode *tree, int root, int a, int b) {
    tree[root].L = a, tree[root].R = b;
    if (a == b) return;
	int mid = (a + b) / 2;
	BuildTree(tree, Left(root), a, mid);
	BuildTree(tree, Right(root), mid + 1, b);
}

void Set(CNode *tree, int root, int node, int v) {
    if (tree[root].L == node && tree[root].R == node) {
        tree[root].minN = v;
        return;
    }
    tree[root].minN = min(tree[root].minN, v);
    int mid = tree[root].Mid();
    if (node <= mid) 
        Set(tree, Left(root), node, v);
    else
        Set(tree, Right(root), node, v);
}

int QMin(CNode *tree, int root, int a, int b) {
	if (tree[root].L == a && tree[root].R == b) {
		return tree[root].minN;
    }

	int mid = tree[root].Mid();
    int ret = -1;
	if (b <= mid)
		ret = QMin(tree, Left(root), a, b);
	else if (a > mid)
		ret = QMin(tree, Right(root), a, b);
	else 
		ret = QMin(tree, Left(root), a, mid) +
			QMin(tree, Right(root), mid + 1, b);
    return ret;
}

int solution(vector<int> &A) {
    // write your code in C++14 (g++ 6.2.0)
    CNode *ptree = new CNode[4 * A.size() + 10];
    BuildTree(ptree, 0, 1, A.size());
    for (int i=1; i<=A.size(); i++) {
        Set(ptree, 0, i, A[i-1]);
    }
    for (int i=1; i<=A.size(); i++)
        QMin(ptree, 0, i, i);

    int tmpMin = (1 << 31) - 1;
    for (int i=1; i<A.size(); i++) {
        int tmpCost = (1<<31)-1;
        if (i >= 4) {
            tmpCost = min(tmpCost, QMin(ptree, 0, 2, i-2));
        }
        if (i <= A.size() - 3) {
            tmpCost = min(tmpCost, QMin(ptree, 0, i+2, A.size()-1));
        }
        tmpMin = min(tmpMin, tmpCost + A[i-1]);
        // printf("Cut cost of %d is %d\n", i, tmpMin);
    }
    delete []ptree;
    return tmpMin;
}
