/* http://dapractise.openjudge.cn/2018hw4/2/ 
头疼题,换过算法,各种STL容器都上了
*/
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<algorithm>
using namespace std;
/* 一般枚举都是非常耗时的算法,能搜索就不枚举,但这道题反其道而行之,枚举(实际上相
   当于二分查找)直到 upper_bound(X) = k 且最小.
   主要是因为区间拼接太耗时.【枚举求小于X的数目】可用线段树分治完成,logN非常快,
   再嵌套上logN也比区间拼接好,另注意离散化操作.
   如何才能避开用val查Index？试试多用一个容器吧！
*/
int Left(int n) { return 2 * n + 1; }
int Right(int n) { return 2 * n + 2; }
const int MAX = 100000;
int N, Q, putin[MAX + 5];     //【BUG1】数组只开MAX不够,从putin[1]开始计数！
class CNode {
public:
	int L, R;
	vector<int> v;
	int Mid() { return (L + R) / 2; }
	bool isLeaf() { return L == R; }
} tree[4 * MAX + 5];
void DQ(vector<int> &dest, vector<int> &src1, vector<int> &src2) {     //归并！分治！
	auto it1 = src1.begin(), it2 = src2.begin();       //src1与src2归并排序,放入dest
	while (it1 != src1.end() || it2 != src2.end()) {   //指针逐个后移,直到俩都到头
		if (it1 == src1.end()) 
			dest.push_back(*it2), ++it2; 
		else if (it2 == src2.end())      //【BUG2】细节问题:sr2写成sr1,报fatal error
			dest.push_back(*it1), ++it1; 
		else {
			if (*it1 < *it2) dest.push_back(*it1), ++it1;
			else dest.push_back(*it2), ++it2;
		}
	}
}
void BuildTree(int root, int L, int R) {
	tree[root].L = L, tree[root].R = R;
	if (L == R) {
		tree[root].v.push_back(putin[L]);
		return;
	}
	BuildTree(Left(root), L, (L + R) / 2);
	BuildTree(Right(root), (L + R) / 2 + 1, R);
	DQ(tree[root].v, tree[Left(root)].v, tree[Right(root)].v); //Left,Right归并放进v
}
int Search(int root, int L, int R, int X) {   //返回[L,R]区间中不大于X的元素个数
	if (tree[root].L == L && tree[root].R == R) {
		int ans= upper_bound(tree[root].v.begin(), tree[root].v.end(), X)
			- tree[root].v.begin();
		return ans;                           //用库函数的多写一行ans方便设断点debug
	}
	if (R <= tree[root].Mid()) return Search(Left(root), L, R, X);
	else if (L >= tree[root].Mid() + 1) return Search(Right(root), L, R, X);
	else
		return Search(Left(root), L, tree[root].Mid(), X) +
		    Search(Right(root), tree[root].Mid() + 1, R, X);
}
int main() {
	scanf("%d%d", &N, &Q);
	map<int, int> m;
	vector<int> mRecord; mRecord.push_back(0); //离散化如何避开二分查找?多开一个数组
	for (int No = 1; No <= N; No++) {          //..把两边映射关系都记录上
		int tmp; scanf("%d", &tmp);
		m[tmp] = No;
	}        //输入完毕后才能获得每个结点大小顺序
	map<int, int>::iterator it = m.begin();
	for (int i = 1; i <= N; i++, ++it) {
		mRecord.push_back(it->first);
		putin[it->second] = i;    //建树优化:直接从左右子树拷贝v,避免一个个Insert耗时
	}
	BuildTree(0, 1, N);
	for (int i = 1; i <= Q; i++) {
		int s, e, k; scanf("%d%d%d", &s, &e, &k);
		int X = N / 2 + 1 , num, ntest, range = N;    //range是当前搜索空间大小
		while (X > 0) {      //反复尝试X
			int plus = max(range / 4, 1);
			num = Search(0, s, e, X);           //【BUG3】待分解区间是[s,e],不是[0,N]
			ntest = Search(0, s, e, X - 1);
			if (num == k && ntest == k - 1) {   //恰有一元素==X
				printf("%d\n", mRecord[X]); 
				break;
			}
			else if (num < k) X = X + plus;     //num太小,X需增大
			else X = X - plus;                  //num太大,X需二分减小
			range = max(range / 2, 1);          //【BUG4】二分参数错误
		}
	}
	return 0;
}