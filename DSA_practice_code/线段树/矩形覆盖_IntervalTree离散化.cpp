#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<list>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;
/* 本以为是贴海报的问题翻版,但没想到几个不一样：
1.离散化方式更难,大型int可直接正向映射 newTree: { Large int } ---> { Small int },
这里只能反向映射 y[i]: { Large int } <---- { Small int },使得线段树区间更新
时求取L与R需bin_search.但如果贴海报要求出露长度就也必须反向映射了.
2.这里不光要维护Len还要维护Covers,使得不能像贴海报一样遇见Covered区间就返回0,层级
之间变量关系非常复杂.
*/
int Left(int n) { return 2 * n + 1; }
int Right(int n) { return 2 * n + 2; }
const int MAX = 5000; //Number of Rectangles 
enum dir { l, r };
int y[2 * MAX + 3];   //y[i]是第i段离散化区间的起始地址, { MAX } ---y---> { N }
class CNode {         //纵向排序,保存若干个横行
public:
	int L, R, Covers = 0, Len = 0;       //Len是该扫描线落在当前矩形中的长度
	CNode(int L_, int R_, int C_, int Len_) :L(L_), R(R_), Covers(C_), Len(Len_) {}
	CNode() {}
	int Mid() { return (L + R) / 2; }
}tree[4 * MAX + 4];

class CLine {         //挨个保存纵边
public:
	int x, y1, y2;
	dir edge;
	CLine(int x_, int y1_, int y2_, dir e_) :
		x(x_), y1(y1_), y2(y2_), edge(e_) {}
	CLine(){}
}lines[MAX * 2 + 3];
bool operator<(const CLine &l1, const CLine &l2) {   //给lines排序时要比较x
	return l1.x < l2.x;
}

void Insert(int root, int L, int R) {
	if (tree[root].L == L && tree[root].R == R) {  //Insert恰覆盖区间,更新Cover与Len
		tree[root].Len = y[R + 1] - y[L];
		tree[root].Covers++;
		return;
	}
	if (R <= tree[root].Mid()) Insert(Left(root), L, R);
	else if (L >= tree[root].Mid() + 1) Insert(Right(root), L, R);
	else {
		Insert(Left(root), L, tree[root].Mid());
		Insert(Right(root), tree[root].Mid() + 1, R);
	}
	if (tree[root].Covers == 0)    //若目前还有出露,我覆盖=左覆盖+右覆盖
		tree[root].Len = tree[Left(root)].Len + tree[Right(root)].Len;
}

void Delete(int root, int L, int R) {
	if (tree[root].L == L && tree[root].R == R) {  //恰Delete区间[L,R],更新Cover与Len
		tree[root].Covers--;                   //更新Covers
		if (tree[root].Covers == 0) {          //更新Len
			if (tree[root].L == tree[root].R) tree[root].Len = 0;  //是叶子节点的话,Len=0
			else tree[root].Len = tree[Left(root)].Len + tree[Right(root)].Len;
		}
		return;
	}
	if (R <= tree[root].Mid()) Delete(Left(root), L, R);
	else if (L >= tree[root].Mid() + 1) Delete(Right(root), L, R);
	else {
		Delete(Left(root), L, tree[root].Mid());
		Delete(Right(root), tree[root].Mid() + 1, R);
	}
	if (tree[root].Covers == 0)             //若目前还有出露,我覆盖=左覆盖+右覆盖
		tree[root].Len = tree[Left(root)].Len + tree[Right(root)].Len;
}
void BuildTree(int root, int L, int R) {
	tree[root] = CNode(L, R, 0, 0);
	if (L == R) return;
	BuildTree(Left(root), L, (L + R) / 2);
	BuildTree(Right(root), (L + R) / 2 + 1, R);
}

int main() {
	int N, yc, lc;
	int x1, y1, x2, y2;
	scanf("%d", &N); 
	yc = 0, lc = 0;              //一共yc个纵坐标,lc条纵线(分左右)
	map<int, int> m;

	for (int i = 0; i < N; i++) {     //把矩形拆成一条条边,存进lines
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		y[yc++] = y1; y[yc++] = y2;   //保存y坐标信息
		lines[lc++] = CLine(x1, y1, y2, l);    //保存纵线信息
		lines[lc++] = CLine(x2, y1, y2, r);
		m[y1] = i;
	}

	sort(y, y + yc);              //排序所有y坐标作Hash Table
	sort(lines, lines + lc);      //按x(遍历先后顺序)排序纵线
	yc = unique(y, y + yc) - y;   //y坐标要去重！图像横向划分为yc-1个区间
	BuildTree(0, 0, yc - 2);

	for (int i = 0, *p = y; p < y + yc; p++, i++) 
		m[y[i]] = i;              //m[k]表示值为k的y坐标从是小到大第几个

	int Area = 0;
	for (int i = 0; i < lc - 1; i++) {     //逐条遍历纵线
		int L = m[lines[i].y1];   //lines[i]起点子区间No
		int R = m[lines[i].y2] - 1;  //lines[i]终点子区间No
		if (lines[i].edge == l) Insert(0, L, R);
		else Delete(0, L, R);
		Area = Area + tree[0].Len * (lines[i + 1].x - lines[i].x);
	}
	printf("%d\n", Area);
	return 0;
}