/*题目：
平面上的一个矩形，如果其边平行于坐标轴，我们就称其为“标准矩形”。
给定不重复的 n 个整点（横、纵坐标都是整数的点），
求从这n个点中任取4点作为顶点所构成的四边形中，有多少个是标准矩形。
O(n^4)*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Point {  //点类
	int x, y;
	Point(int x_, int y_) :x(x_), y(y_) { }
};
bool operator<(const Point & i, const Point & j) {
	if (i.y < j.y) return true;
	else if (i.y == j.y) return i.x < j.x;
	else return false;
}
int main() {
	int t, x, y;
	cin >> t;
	vector<Point> v;
	while (t--) {
		cin >> x >> y;
		v.push_back(Point(x, y));
	}
	vector<Point>::iterator i, j;
	int nTotalNum = 0;
	//------------------------------------
	vector<Point>::iterator h, k;
	i = v.begin(); j = v.begin(); k = v.begin(); h = v.begin();
	for (; i != v.end(); ++i) {
		j = i + 1;
		for (; j != v.end(); ++j) {
			h = j + 1;
			for (; h != v.end(); ++h) {
				k = h + 1;
				for (; k != v.end(); ++k) {
					int flag = 0;
					if (i->y == j->y && h->y == k->y && i->x == k->x && j->x == h->x) flag = 1;
					if (i->y == j->y && h->y == k->y && i->x == h->x && j->x == k->x) flag = 1;
					if (i->y == h->y && j->y == k->y && i->x == k->x && j->x == h->x) flag = 1;
					if (i->y == h->y && j->y == k->y && h->x == k->x && j->x == i->x) flag = 1;
					if (i->y == k->y && h->y == j->y && k->x == j->x && i->x == h->x) flag = 1;
					if (i->y == k->y && h->y == j->y && i->x == j->x && k->x == h->x) flag = 1;
					if (flag == 1)nTotalNum++;
				}
			}
		}
	}
	cout << nTotalNum;
	//---还可以这样：对角两点即可确定一个矩形,因此嵌套两个循环即可--------
	/*
	sort(v.begin(), v.end());
	for( i = v.begin(); i < v.end() - 1;i ++ ){
	for(j = i+1; j < v.end(); j++){
	if(binary_search(v.begin(),v.end(),Point( j->x, i->y)) &&
	binary_search(v.begin(),v.end(),Point( i->x, j->y)) &&
	i->x != j->x && i->y != j->y )
	//直接binary_search是否存在符合要求的另外两个对角点
	nTotalNum ++;
	}}
	cout << nTotalNum/2;
	*/
	return 0;
}