/* http://bailian.openjudge.cn/practice/3438/
给定N个数A1,A2 … AN, Q次求任一区间[Ai, Aj]中最大数和最小数的差
*/
//有空用树状数组试试
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<limits.h>
#include<algorithm>
#define Left(p) 2*(p)+1
#define Right(p) 2*(p)+2
using namespace std;
const int MAX = 800010;
int maxValue = INT_MIN, minValue = INT_MAX;
class CNode {       //一个不足在于只适用于静态数组,否则结点区间改起来复杂度感人
public:
	int L, R, maxV = INT_MIN, minV = INT_MAX;
	int Mid() { return (L + R) / 2; }  //Mid求该节点对应区间中值
}tree[MAX];
void BuildTree(int root, int L, int R) {   //建树
	tree[root].L = L;
	tree[root].R = R;
	if (L == R)return;
	int mid = (L + R) / 2;
	BuildTree(Left(root), L, mid);
	BuildTree(Right(root), mid + 1, R);
}
void Insert(int root, int i, int v) {     //将值为v的第i个数插入以root为根的线段树
	if (tree[root].L == tree[root].R) {   //到达叶子结点,可以赋值了
		tree[root].minV = tree[root].maxV = v; return;
	}
	tree[root].minV = min(tree[root].minV, v);  //更新了tree[root]的值,
	tree[root].maxV = max(tree[root].maxV, v);  //没完！还要继续往下更新
	if (i <= tree[root].Mid()) Insert(Left(root), i, v);  //第i个结点v插到左子树中
	else Insert(Right(root), i, v);    //第i个结点v插到右子树中
}
void Query(int root, int s, int e) {   //查询区间[s, e]的最大最小值,记录在全局变量里
	if (tree[root].minV >= minValue && tree[root].maxV <= maxValue) return;  //剪枝
	if (tree[root].L == s && tree[root].R == e) {
		maxValue = max(maxValue, tree[root].maxV);
		minValue = min(minValue, tree[root].minV);
		return;
	}
	if (e <= tree[root].Mid()) Query(Left(root), s, e);
	else if (s >= tree[root].Mid() + 1) Query(Right(root), s, e);
	else {
		Query(Left(root), s, tree[root].Mid());
		Query(Right(root), tree[root].Mid() + 1, e);
	}
}
int main() {
	int Q, N, h;
	scanf("%d %d", &N, &Q);
	BuildTree(0, 1, N);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &h);
		Insert(0, i, h);
	}
	for (int i = 1; i <= Q; i++) {
		int s, e;
		scanf("%d %d", &s, &e);
		minValue = INT_MAX; maxValue = INT_MIN;
		Query(0, s, e);
		printf("%d\n", maxValue - minValue);
	}
	return 0;
}