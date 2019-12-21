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
之间变量关系非常复杂.幸好有郭老师现成代码...
*/
int Left(int n) { return 2 * n + 1; }
int Right(int n) { return 2 * n + 2; }
const int MAX = 5000; //Number of Rectangles 
enum dir { l, r, u, d };
int y[2 * MAX + 3];   //y[i]是第i段离散化区间的起始地址, { MAX } ---y---> { N }
int x[2 * MAX + 3];   //x[i]是第i段离散化区间的起始地址, { MAX } ---x---> { N }
class CNode {         //纵向排序,保存若干个横/纵行
public:
	int L, R, Covers = 0, Len = 0;       //Len是该扫描线落在当前矩形中的长度
	CNode(int L_, int R_, int C_, int Len_) :L(L_), R(R_), Covers(C_), Len(Len_) {}
	CNode() {}
	int Mid() { return (L + R) / 2; }
}treey[4 * MAX + 4], treex[4 * MAX + 4];

class CVertLine {         //挨个保存纵边
public:
	int x, y1, y2;
	dir edge;
	CVertLine(int x_, int y1_, int y2_, dir e_) :
		x(x_), y1(y1_), y2(y2_), edge(e_) {}
	CVertLine() {}
}vert_lines[MAX * 2 + 3];
bool operator<(const CVertLine &v1, const CVertLine &v2) {   //给vert_lines排序时要比较x
	if (v1.x != v2.x)	return v1.x < v2.x;
	else return v1.edge == l && v2.edge == r;   //edge==l的排在前面(左边)
	return 1;  //无所谓了
}

class CHorizLine {         //挨个保存纵边
public:
	int x1, x2, y;
	dir edge;
	CHorizLine(int y_, int x1_, int x2_, dir e_) :
		y(y_), x1(x1_), x2(x2_), edge(e_) {}
	CHorizLine() {}
}horiz_lines[MAX * 2 + 3];
bool operator<(const CHorizLine &h1, const CHorizLine &h2) {   //给horiz_lines排序时要比较y
	if (h1.y != h2.y) return h1.y < h2.y;
	else return h1.edge == u && h2.edge == d;  //edge==u的排在前面(上边)
	return 1;
}

//---------------------------------For VertSect---------------------------------
void yInsert(int root, int L, int R) {
	if (treey[root].L == L && treey[root].R == R) {  //Insert恰覆盖区间,更新Cover与Len
		treey[root].Len = y[R + 1] - y[L];
		treey[root].Covers++;
		return;
	}
	if (R <= treey[root].Mid()) yInsert(Left(root), L, R);
	else if (L >= treey[root].Mid() + 1) yInsert(Right(root), L, R);
	else {
		yInsert(Left(root), L, treey[root].Mid());
		yInsert(Right(root), treey[root].Mid() + 1, R);
	}
	if (treey[root].Covers == 0)    //若目前还有出露,我覆盖=左覆盖+右覆盖
		treey[root].Len = treey[Left(root)].Len + treey[Right(root)].Len;
}

void yDelete(int root, int L, int R) {
	if (treey[root].L == L && treey[root].R == R) {  //恰Delete区间[L,R],更新Cover与Len
		treey[root].Covers--;                   //更新Covers
		if (treey[root].Covers == 0) {          //更新Len
			if (treey[root].L == treey[root].R) treey[root].Len = 0;  //是叶子节点的话,Len=0
			else treey[root].Len = treey[Left(root)].Len + treey[Right(root)].Len;
		}
		return;
	}
	if (R <= treey[root].Mid()) yDelete(Left(root), L, R);
	else if (L >= treey[root].Mid() + 1) yDelete(Right(root), L, R);
	else {
		yDelete(Left(root), L, treey[root].Mid());
		yDelete(Right(root), treey[root].Mid() + 1, R);
	}
	if (treey[root].Covers == 0)             //若目前还有出露,我覆盖=左覆盖+右覆盖
		treey[root].Len = treey[Left(root)].Len + treey[Right(root)].Len;
}
void yBuildTree(int root, int L, int R) {
	treey[root] = CNode(L, R, 0, 0);
	if (L == R) return;
	yBuildTree(Left(root), L, (L + R) / 2);
	yBuildTree(Right(root), (L + R) / 2 + 1, R);
}
//---------------------------------For VertSect---------------------------------

//---------------------------------For HorizSect---------------------------------
void xInsert(int root, int L, int R) {
	if (treex[root].L == L && treex[root].R == R) {  //Insert恰覆盖区间,更新Cover与Len
		treex[root].Len = x[R + 1] - x[L];
		treex[root].Covers++;
		return;
	}
	if (R <= treex[root].Mid()) xInsert(Left(root), L, R);
	else if (L >= treex[root].Mid() + 1) xInsert(Right(root), L, R);
	else {
		xInsert(Left(root), L, treex[root].Mid());
		xInsert(Right(root), treex[root].Mid() + 1, R);
	}
	if (treex[root].Covers == 0)    //若目前还有出露,我覆盖=左覆盖+右覆盖
		treex[root].Len = treex[Left(root)].Len + treex[Right(root)].Len;
}

void xDelete(int root, int L, int R) {
	if (treex[root].L == L && treex[root].R == R) {  //恰Delete区间[L,R],更新Cover与Len
		treex[root].Covers--;                   //更新Covers
		if (treex[root].Covers == 0) {          //更新Len
			if (treex[root].L == treex[root].R) treex[root].Len = 0;  //是叶子节点的话,Len=0
			else treex[root].Len = treex[Left(root)].Len + treex[Right(root)].Len;
		}
		return;
	}
	if (R <= treex[root].Mid()) xDelete(Left(root), L, R);
	else if (L >= treex[root].Mid() + 1) xDelete(Right(root), L, R);
	else {
		xDelete(Left(root), L, treex[root].Mid());
		xDelete(Right(root), treex[root].Mid() + 1, R);
	}
	if (treex[root].Covers == 0)             //若目前还有出露,我覆盖=左覆盖+右覆盖
		treex[root].Len = treex[Left(root)].Len + treex[Right(root)].Len;
}
void xBuildTree(int root, int L, int R) {
	treex[root] = CNode(L, R, 0, 0);
	if (L == R) return;
	xBuildTree(Left(root), L, (L + R) / 2);
	xBuildTree(Right(root), (L + R) / 2 + 1, R);
}
//---------------------------------For HorizSect---------------------------------

int main() {
	int N, yc = 0, ylc = 0, xc = 0, xlc = 0;    //一共yc个纵坐标,ylc条纵线(分左右)
	int x1, y1, x2, y2;
	scanf("%d", &N);
	map<int, int> mx, my;

	for (int i = 0; i < N; i++) {     //把矩形拆成一条条边,存进vert_lines
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		y[yc++] = y1; y[yc++] = y2;   //保存y坐标信息
		vert_lines[ylc++] = CVertLine(x1, y1, y2, l);    //保存纵线信息
		vert_lines[ylc++] = CVertLine(x2, y1, y2, r);

		x[xc++] = x1; x[xc++] = x2;   //保存x坐标信息
		horiz_lines[xlc++] = CHorizLine(y1, x1, x2, u);    //保存横线信息
		horiz_lines[xlc++] = CHorizLine(y2, x1, x2, d);
	}

	sort(y, y + yc);              //排序所有y坐标作Hash Table
	sort(vert_lines, vert_lines + ylc);      //按x(遍历先后顺序)排序纵线
	yc = unique(y, y + yc) - y;   //y坐标要去重！图像横向划分为yc-1个区间
	yBuildTree(0, 0, yc - 2);
	for (int i = 0, *p = y; p < y + yc; p++, i++)
		my[y[i]] = i;              //my[k]表示值为k的y坐标从是小到大第几个

	sort(x, x + xc);              //排序所有x坐标作Hash Table
	sort(horiz_lines, horiz_lines + xlc);      //按y(遍历先后顺序)排序纵线
	xc = unique(x, x + xc) - x;   //x坐标要去重！图像横向划分为xc-1个区间
	xBuildTree(0, 0, xc - 2);
	for (int i = 0, *p = x; p < x + xc; p++, i++)
		mx[x[i]] = i;              //mx[k]表示值为k的x坐标从是小到大第几个

	int prev = 0, perimeter = 0, delta = 0, i = 0;
	for (int i = 0; i < ylc - 1; i++) {    //逐条遍历纵线
		int L = my[vert_lines[i].y1];           //vert_lines[i]起点子区间No
		int R = my[vert_lines[i].y2] - 1;       //vert_lines[i]终点子区间No
		if (vert_lines[i].edge == l) yInsert(0, L, R);
		else yDelete(0, L, R);
		delta = (prev > treey[0].Len) ? prev - treey[0].Len : treey[0].Len - prev;
		perimeter += delta;
		prev = treey[0].Len;
	}
	if (prev != 0) {
		perimeter += prev;
		prev = 0;
	}

	i = 0;
	for (int i = 0; i < xlc - 1; i++) {    //逐条遍历横线
		int L = mx[horiz_lines[i].x1];           //vert_lines[i]起点子区间No
		int R = mx[horiz_lines[i].x2] - 1;       //vert_lines[i]终点子区间No
		if (horiz_lines[i].edge == u) xInsert(0, L, R);
		else xDelete(0, L, R);
		delta = (prev > treex[0].Len) ? prev - treex[0].Len : treex[0].Len - prev;
		perimeter += delta;
		prev = treex[0].Len;
	}
	if (prev != 0) {
		perimeter += prev;
		prev = 0;
	}


	printf("%d\n", perimeter);
	return 0;
}/*BUGs：
 一是Area和perimeter没分,开始白忙活了半天
 二是一开始没考虑右边界接左边界重合的情况,后来路子错了用do...while,事实上让重合处
 右矩形左边盖住左矩形右边Δ宽度就行,这可以在给vert_lines排序时实现
 在求覆盖面积基础上嫁接完成,其实xy写一个进行,代码体量可减半
 ★★★此题重点在Insert与Delete部分,看看Covers与Len是如何变化的！★★★
 */