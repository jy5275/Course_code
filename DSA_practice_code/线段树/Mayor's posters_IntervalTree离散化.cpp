/* http://dapractise.openjudge.cn/2018hw4/1/ */
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<limits.h>
#include<set>
#include<stack>
#include<bitset>
#include<memory.h>
#include<vector>
#include<algorithm>
using namespace std;
/* 这是个人认为比较难的一道题
【离散化】最多N张海报,共计2N个端点,这些端点把墙最多分成2N-1个单位区间,加上
端点本身一共最多可分成4N个单位区间。由于：
1. 每个单位区间要么【全被覆盖】,要么【全部露出】;
2. 没有哪个端点会落在一个单位区间内部;
3. 每张海报一定完整覆盖若干个连续单位区间。
所以我们对单位区间(而非瓷砖本身)建立线段树,这样就减少了二叉树深度,大大提升效率

离散化之后,这实质上是一个简单的区间更新(贴海报相当于每个结点减去exposure),区间
求和(把海报占用区间exposure加起来,0为完全覆盖,非0反之)。

Query和Change同时进行,所以对这两个操作可只写一个函数,但需注意顺序保证求和在减去
exposure之前进行。Query和Change分成两个函数可以用传统方法解决但不知会不会TLE
*/
const int MAX = 10000010, MAX_POST = 10010;
int newTree[MAX];      //第i块瓷砖是第newTree[i]个子区间的起始地址
bitset<MAX> visited;
class CNode {
public:
	int L, R, exposure;
	int Mid() { return (L + R) / 2; }
}Wall[4 * MAX_POST + 4];
int Left(int n) { return 2 * n + 1; }
int Right(int n) { return 2 * n + 2; }

void BuildTree(int root, int L, int R) {
	Wall[root].L = L, Wall[root].R = R, Wall[root].exposure = R - L + 1;
	if (L == R)return;         //叶子结点 (Wall[root].R == Wall[root].L == R == L)
	BuildTree(Left(root), L, (L + R) / 2);
	BuildTree(Right(root), (L + R) / 2 + 1, R);
}

int Paste(int root, int s, int e) {    //把poster[s, e]贴在root对应区间expose的格数
	if (Wall[root].exposure <= 0) return 0;   //剪枝
	if (Wall[root].L == s && Wall[root].R == e) {
		int ret = Wall[root].exposure; //一旦match,就把这段的exposure减光,
		Wall[root].exposure = 0;       //..它的低级结点全部自动作废,46行返回
		return ret;
	}
	int exposure_sub;
	if (e <= Wall[root].Mid()) exposure_sub = Paste(Left(root), s, e);
	else if (s >= Wall[root].Mid() + 1) exposure_sub = Paste(Right(root), s, e);
	else exposure_sub = Paste(Left(root), s, Wall[root].Mid()) +
		Paste(Right(root), Wall[root].Mid() + 1, e);
	Wall[root].exposure -= exposure_sub;   //【Bug2】别减全部s~e,只减子结点exposure部分
	return exposure_sub;
}

int main() {
	int C;	cin >> C;
	while (C--) {
		memset(newTree, 0, sizeof(newTree));  //【BUG0】注意每次case初始化全局变量
		visited.reset();
		int cnt = 0, N;
		vector<int> v;
		int s[MAX_POST], e[MAX_POST];
		cin >> N;

		//记录插入的海报,反向插入
		for (int i = 1; i <= N; i++) {
			int s_, e_;
			scanf("%d %d", &s_, &e_);
			s[N + 1 - i] = s_, e[N + 1 - i] = e_;  //先输入的放se后边,后输入的放se前边
			v.push_back(s_); v.push_back(e_);
		}

		//进行离散化,用newTree将区间{ MAX }元素映射到区间{ 4N }上,减少树的深度
		sort(v.begin(), v.end());
		auto it = v.begin();
		for (int i = -1; it != v.end(); ++it) { //【BUG1】注意相邻/重合端点对区间分配的要求
			if (visited[*it]) {  }              //newTree[*it]已经被访问过了,啥也不用做
			else if (visited[(*it) - 1] || i == -1) {  //newTree中第*it-1号已被访问过
				i++;
				newTree[*it] = i;
				visited.set(*it);
			}
			else {    //newTree中*it前一个元素还没有被访问过
				i = i + 2;
				newTree[*it] = i;
				visited.set(*it);
			}
		}         //     { MAX } ---newTree--> { 4*N } (哈希表？)
		BuildTree(0, 0, 4 * N);

		//贴海报
		for (int i = 1; i <= N; i++) {
			int expose = Paste(0, newTree[s[i]], newTree[e[i]]);
			if (expose) cnt++;
		}
		cout << cnt << endl;
	}
	return 0;
}/* 老是Wrong Answer怎么办,逻辑太复杂,不指望只通过读代码debug：
 1. 认真读题,检查边界条件(数组开小了？)和特殊参数(0,负数等)
 2. 自己造数据自己跑跑看,造特殊数据使劲跑...终于出错了？恭喜你
 */