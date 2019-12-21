/* http://dapractise.openjudge.cn/hw11/2/ */
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<memory.h>
#include<string.h>
#include<bitset>
#include<math.h>
#define CPoint CVector
using namespace std;
/* 这题都能反复调试，你真TM是bug maker */
double PI = acos(-1), INF = 1e20, EPS = 1e-6;
bool IsZero(double x) {	return -EPS < x && x < EPS;}
bool FLarger(double a, double b) { return a - b > EPS; }
bool FLess(double a, double b) { return b - a > EPS; }
class CVector {
public:
	double x, y;
	CVector(double x_, double y_) :x(x_), y(y_) {}
	CVector() {}
};
class CLine {
public:
	CPoint A, B;
	CLine(CPoint A_, CPoint B_) :A(A_), B(B_) {}
};
CVector operator+(CVector p, CVector q) { return CVector(p.x + q.x, p.y + q.y); }
CVector operator-(CVector p, CVector q) { return CVector(p.x - q.x, p.y - q.y); }
CVector operator*(double k, CVector p) { return CVector(k*p.x, k*p.y); }
double operator*(CVector p, CVector q) { return p.x*q.x + p.y*q.y; }
double length(CVector p) { return sqrt(p*p); }
double operator^(CVector p, CVector q) {	// |p x q| = p * q * sin<p,q>
	return p.x*q.y - q.x*p.y;
}
double area(CVector p, CVector q) {	return fabs((p ^ q) / 2);}	//【无向面积】
double dist(CPoint p, CPoint q) { return length(p - q); }
double dist(CPoint p, CLine l) {		// 点到直线距离
	double S = area(p - l.A, p - l.B);	//先求三角形面积
	return 2 * S / length(l.B - l.A);	// 2*面积 / 底 = 高(距离)
}
CPoint rotate(CPoint B, CPoint A, double alpha) {	//将AB旋转alpha到AC,返回C
	CVector p = B - A;
	return CPoint(A.x + (p.x*cos(alpha) - p.y*sin(alpha)),
		A.y + (p.x*sin(alpha) + p.y*cos(alpha)));
}
int sideOfLine(CPoint P, CPoint A, CPoint B) {	// P在AB左侧否?
	double dirArea = (B - A)^(P - A);			//用有叉积判断之
	if (IsZero(dirArea)) return 0;
	else if (dirArea > 0) return 1;
	else return -1;
}
CLine Vertical(CPoint P, CLine l) {		//求P到l的垂线
	CVector vec = rotate(l.B, l.A, PI / 2) - l.A;
	return CLine(P, P + vec);
}
CVector unit(CVector p) {		// p方向单位向量
	return 1 / length(p) * p; 
}
double project(CVector p, CVector n) {		//p在n上的投影,|p|*cos<p,n>
	return p * unit(n);
}
CVector Project(CVector p, CVector n) {		//p在n上的投影,|p|*cos<p,n>
	return project(p, n) * n;
}
CPoint Foot(CPoint P, CLine l) {		//求P到l的垂足
	return l.A + Project(P - l.A, l.B - l.A);
}
class CTriangle {
public:
	int v1, v2, v3;
	CTriangle(int v1_, int v2_, int v3_) :v1(v1_), v2(v2_), v3(v3_) {}
	CTriangle(){}
}maxTriangle;
CPoint p[16];
int main() {
	int n, tx, ty;
	char tag;
	while (scanf("%d", &n)) {
		memset(p, 0, sizeof(p));
		if (!n) break;
		cin.get();
		for (int i = 0; i < n; i++) {
			scanf("%c %d %d", &tag, &tx, &ty);
			cin.get();
			p[i] = CPoint(tx, ty);
		}
		int v1, v2, v3;
		double maxArea = 0, tarea;
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				for (int k = j + 1; k < n; k++) {	// A triangle has emerged
					bool empty = 1;
					for (int h = 0; h < n; h++) {	// Enumerate each point
						if (h == i || h == j || h == k)continue; //【bug1】未除重
						int e1 = sideOfLine(p[h], p[i], p[j]);
						int e2 = sideOfLine(p[h], p[j], p[k]);
						int e3 = sideOfLine(p[h], p[k], p[i]);
						if ((e1 == e2 && e2 == e3) ||		//【bug2】未考虑点在线上
							(e1*e2*e3 == 0 && e1 + e2 + e3 != 0)) {
							//p[h] fall in triangle!
							empty = 0; break;
						}
					}
					if (!empty)continue;	// Not an empty triangle!
					tarea = area(p[i] - p[j], p[k] - p[j]);
					if (tarea > maxArea) {
						maxArea = tarea;
						maxTriangle = CTriangle(i, j, k);
					}
				}
			}
		}
		printf("%c%c%c\n", maxTriangle.v1 + 'A', maxTriangle.v2 + 'A',
			maxTriangle.v3 + 'A');			//【bug3】输出错误 (x - 'A')
	}
	return 0;
}