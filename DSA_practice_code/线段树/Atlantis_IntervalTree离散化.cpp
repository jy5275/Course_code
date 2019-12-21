/*【未提交】这题太难了，遇上这种就放弃吧*/
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<list>
#include<algorithm>
using namespace std;
/* 本以为是贴海报的问题翻版,但没想到几个不一样：
1.离散化方式更难,大型int可直接正向映射 newTree: { Large int } ---> { Small int },
  这里只能反向映射 y[i]: { Large double } <---- { Small int },使得线段树区间更新
  时求取L与R需bin_search.但如果贴海报要求出露长度就也必须反向映射了.
2.这里不光要维护Len还要维护Covers,使得不能像贴海报一样遇见Covered区间就返回0,层级
  之间变量关系非常复杂.
*/
const int MAX = 200;
enum dir { Left, Right };
int nNodeCnt = 0;
double y[2 * MAX];    //y[i]是第i段离散化区间的起始地址, { MAX } ---y---> { N }
class CNode {
public:
	int L, R, Covers = 0;
	double Len = 0;   //Len是该扫描线落在当前矩形中的长度
	CNode *pLeft = NULL, *pRight = NULL;
	CNode(int L_, int R_, int C_, int Len_) :L(L_), R(R_), Covers(C_), Len(Len_) {}
	int Mid() { return (L + R) / 2; }
}Tree[4 * MAX + 4];

class CLine {
public:
	double x, y1, y2;
	dir edge;
	CLine(double x_, double y1_, double y2_, dir e_) :
		x(x_), y1(y1_), y2(y2_), edge(e_) {}
}lines[MAX * 2 + 3];
bool operator<(const CLine &l1, const CLine &l2) {   //给lines排序时要比较
	return l1.x < l2.x;
}

void Insert(CNode *pRoot, int L, int R) {
	if (pRoot->L == L && pRoot->R == R) {  //Insert恰覆盖区间,更新Cover与Len
		pRoot->Len = y[R + 1] - y[L];
		pRoot->Covers++;
		return;
	}
	if (R <= pRoot->Mid()) Insert(pRoot->pLeft, L, R);
	else if (L >= pRoot->Mid() + 1) Insert(pRoot->pRight, L, R);
	else {
		Insert(pRoot->pLeft, L, pRoot->Mid());
		Insert(pRoot->pRight, pRoot->Mid() + 1, R);
	}
	if (pRoot->Covers == 0)    //若目前还有出露,我覆盖=左覆盖+右覆盖
		pRoot->Len = pRoot->pLeft->Len + pRoot->pRight->Len;
}

void Delete(CNode *pRoot, int L, int R) { 
	if (pRoot->L == L && pRoot->R == R) {  //恰Delete区间[L,R],更新Cover与Len
		pRoot->Covers--;                   //更新Covers
		if (pRoot->Covers == 0) {          //更新Len
			if (pRoot->L == pRoot->R) pRoot->Len = 0;  //是叶子节点的话,Len=0
			else pRoot->Len = pRoot->pLeft->Len + pRoot->pRight->Len;
		}
		return;
	}
	if (R <= pRoot->Mid()) Delete(pRoot->pLeft, L, R);
	else if (L >= pRoot->Mid() + 1) Delete(pRoot->pRight, L, R);
	else {
		Delete(pRoot->pLeft, L, pRoot->Mid());
		Delete(pRoot->pRight, pRoot->Mid() + 1, R);
	}
	if (pRoot->Covers == 0)             //若目前还有出露,我覆盖=左覆盖+右覆盖
		pRoot->Len = pRoot->pLeft->Len + pRoot->pRight->Len;
}
void BuildTree(CNode *pRoot, int L, int R) {
	pRoot = new CNode(L, R, 0, 0);
	if (L == R) return;
	BuildTree(pRoot->pLeft, L, (L + R) / 2);
	BuildTree(pRoot->pRight, (L + R) / 2 + 1, R);
}

int main() {
	int n, i, j, k, yc, lc, nCnt = 0, t = 0;
	double x1, y1, x2, y2;
	while (1) {
		scanf("%d", &n); if (n == 0) break;
		t++; yc = 0, lc = 0;              //一共yc个纵坐标,lc条纵线(分左右)
		
		for (int i = 0; i < n; i++) {     //把矩形拆成一条条边,存进lines
			scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
			y[yc++] = y1; y[yc++] = y2;   //保存y坐标信息
			lines[lc++] = CLine(x1, y1, y2, Left);    //保存纵线信息
			lines[lc++] = CLine(x2, y1, y2, Right);
		} 

		sort(y, y + yc);              //排序所有y坐标作Hash Table
		sort(lines, lines + lc);      //按x(遍历先后顺序)排序纵线
		yc = unique(y, y + yc) - y;   //y要去重！图像横向划分为yc-1个区间
		BuildTree(Tree, 0, yc - 2);

		double Area = 0;
		for (int i = 0; i < lc - 1; i++){     //逐条遍历纵线
			int L = find(y, y + yc, lines[i].y1) - y;  //lines[i]起点子区间No
			int R = find(y, y + yc, lines[i].y2) - y;  //lines[i]终点子区间No+1
			if (lines[i].edge == Left) Insert(Tree, L, R - 1);
			else Delete(Tree, L, R - 1);
			Area = Area + Tree[0].Len * (lines[i + 1].x - lines[i].x);
		}
		printf("Test case #%d\n", t);
		printf("Total explored area: %.2lf\n", Area);
	}
	return 0;
}