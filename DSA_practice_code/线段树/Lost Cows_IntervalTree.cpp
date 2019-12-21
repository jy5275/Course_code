/* http://dapractise.openjudge.cn/2018hw4/1/ */
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<limits.h>
#include<map>
#include<stack>
#include<bitset>
#include<memory.h>
#include<vector>
#include<algorithm>
#define Left(p) 2*(p)+1
#define Right(p) 2*(p)+2
using namespace std;
const int MAX = 100010;
stack<int> v;
stack<int> put_in;
int N;
class CNode {
public:
	int L, R, sum;
	int Mid() { return (L + R) / 2; }
	bool isLeaf() { return (L == R); }
}tree[4 * MAX + 10];         //【BUG1】注意二叉树顺序存储数组要开到4N大！

void BuildTree(int root, int L, int R) {
	tree[root].L = L; tree[root].R = R;
	tree[root].sum = R - L + 1;
	int mid = (L + R) / 2;
	if (L == R) return;
	BuildTree(Left(root), L, mid);
	BuildTree(Right(root), mid + 1, R);
}

void Search(int root, int n) {   //在root对应的树上搜第n小的元素压vector
	tree[root].sum--;
	if (tree[root].isLeaf()) {
		v.push(tree[root].L);
		return;
	}
	if (tree[Left(root)].sum < n)   //左子树不够搜！搜右子树！ 
		Search(Right(root), n - tree[Left(root)].sum);
	else
		Search(Left(root), n);
}

int main() {
	cin >> N;
	BuildTree(0, 1, N);
	put_in.push(0);
	for (int i = 2; i <= N; i++) {
		int tmp; scanf("%d", &tmp);
		put_in.push(tmp);
	}
	while (!put_in.empty()) {
		Search(0, put_in.top() + 1);
		put_in.pop();
	}
	while (!v.empty()) {
		printf("%d\n", v.top());
		v.pop();
	}
	return 0;
}/* 老是Wrong Answer怎么办,逻辑太复杂,不指望只通过读代码debug：
 1. 认真读题,检查边界条件(数组开小了？)和特殊参数(0,负数等)
 2. 自己造数据自己跑跑看,造特殊数据使劲跑...终于出错了？恭喜你
 */