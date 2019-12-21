/* http://dapractise.openjudge.cn/hw11/1/ */
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<memory.h>
#include<string.h>
#include<bitset>
#include<math.h>
#define CPoint CVector
using namespace std;
/* 切记浮点数不能用==,否则WA半天过不了！ */
double PI = acos(-1), INF = 1e20, EPS = 1e-4;
bool IsZero(double x) {	return -EPS < x && x < EPS;}
bool FLarger(double a, double b) { return a - b > EPS; }
bool FLess(double a, double b) { return b - a > EPS; }
class CVector {
public:
	double x, y;
	CVector(double x_, double y_) :x(x_), y(y_) {}
	CVector() {}
};
bool operator==(CVector v1, CVector v2) {
	return fabs(v1.x - v2.x) < EPS && fabs(v1.y - v2.y) < EPS;
}
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
double area(CVector p, CVector q) {	return (p ^ q) / 2;}	//【无向面积】
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
bool parallel(CLine l1, CLine l2) {
	return unit(l1.A - l1.B) == unit(l2.A - l2.B) ||
		unit(l1.A - l1.B) == unit(l2.B - l2.A);
}
CPoint intersect(CLine l, CLine m) {
	double x = area(m.A - l.A, l.B - l.A);
	double y = area(l.B - l.A, m.B - l.A);
	if (IsZero(x + y)) return CPoint(0, 0);
	return m.A + x / (x + y) * (m.B - m.A);
}
int main() {
	int N;
	double x1, y1, x2, y2, x3, y3, x4, y4;;
	printf("INTERSECTING LINES OUTPUT\n");
	scanf("%d", &N);
	while (N--) {
		scanf("%lf %lf %lf %lf %lf %lf %lf %lf", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);
		CPoint A1(x1, y1), A2(x2, y2), A3(x3, y3), A4(x4, y4);
		CLine l1(A1, A2), l2(A3, A4);
		if (parallel(l1, l2)){
			if (IsZero(area(A4 - A1, A3 - A1)))		//有面积，不重合
				printf("LINE\n");
			else printf("NONE\n");
			continue;
		}
		CPoint In(intersect(l1, l2));
		printf("POINT %.2lf %.2lf\n", In.x, In.y);
	}
	printf("END OF OUTPUT\n");
	return 0;
}