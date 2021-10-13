
// you can use includes, for example:
// #include <algorithm>
#include <algorithm>
#include <iostream>
using namespace std;
// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;
long long Sum(vector<int> &A, int l, int r) {
    long long sum=0;
    for (int i=l; i<=r; i++) {
        sum += A[i];
    }
    return sum;
}

int Left(int x) { return 2 * x + 1; }
int Right(int x) { return 2 * x + 2; }
class CNode {
public:
    int L, R;
    long long sum = 0;
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
        tree[root].sum += v;
        return;
    }
    tree[root].sum += v;
    int mid = tree[root].Mid();
    if (node <= mid) 
        Set(tree, Left(root), node, v);
    else
        Set(tree, Right(root), node, v);
}

long long QSum(CNode *tree, int root, int a, int b) {
	if (tree[root].L == a && tree[root].R == b)
		return tree[root].sum;
    // printf("QSum root=%d, [%d, %d]\n",root, a, b);
	int mid = tree[root].Mid();
	if (b <= mid)
		return QSum(tree, Left(root), a, b);
	else if (a > mid)
		return QSum(tree, Right(root), a, b);
	else {
		return QSum(tree, Left(root), a, mid) +
			QSum(tree, Right(root), mid + 1, b);
	}
}

int solution(vector<int> &A, int K, int L) {
    // write your code in C++14 (g++ 6.2.0)
    long long tmpMax = 0;
    if (K+L>A.size()) return -1;
    CNode *ptree = new CNode[2 * A.size() + 10];
    BuildTree(ptree, 0, 1, A.size());
    for (int i=0; i<A.size(); i++) {
        Set(ptree, 0, i+1, A[i]);
    }
    
    // Alice pick first
    for (int i = 0; i+K-1 < A.size(); i++) {
        long long KSum = QSum(ptree, 0, i+1, i+K);
        // printf("Sum of K [%d, %d]=%ld\n", i+1, i+K, KSum);
        for (int j=i+K; j+L-1 < A.size(); j++) {
            long long LSum = QSum(ptree, 0, j+1, j+L);
            // printf("Sum of L [%d, %d]=%ld\n", j+1, j+L, LSum);
            tmpMax = max(tmpMax, LSum + KSum);
        }
    }
    
    // Bob pick first
    for (int i = 0; i+L-1 < A.size(); i++) {
        long long LSum = QSum(ptree, 0, i+1, i+L);
        // printf("Sum of K [%d, %d]=%ld\n", i+1, i+K, KSum);
        for (int j=i+L; j+K-1 < A.size(); j++) {
            long long KSum = QSum(ptree, 0, j+1, j+K);
            // printf("Sum of L [%d, %d]=%ld\n", j+1, j+L, LSum);
            tmpMax = max(tmpMax, LSum + KSum);
        }
    }
    delete []ptree;
    return tmpMax;
}