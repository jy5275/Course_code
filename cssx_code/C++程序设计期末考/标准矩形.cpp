/*��Ŀ��
ƽ���ϵ�һ�����Σ�������ƽ���������ᣬ���Ǿͳ���Ϊ����׼���Ρ���
�������ظ��� n �����㣨�ᡢ�����궼�������ĵ㣩��
�����n��������ȡ4����Ϊ���������ɵ��ı����У��ж��ٸ��Ǳ�׼���Ρ�
O(n^4)*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Point {  //����
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
	//---�������������Խ����㼴��ȷ��һ������,���Ƕ������ѭ������--------
	/*
	sort(v.begin(), v.end());
	for( i = v.begin(); i < v.end() - 1;i ++ ){
	for(j = i+1; j < v.end(); j++){
	if(binary_search(v.begin(),v.end(),Point( j->x, i->y)) &&
	binary_search(v.begin(),v.end(),Point( i->x, j->y)) &&
	i->x != j->x && i->y != j->y )
	//ֱ��binary_search�Ƿ���ڷ���Ҫ������������Խǵ�
	nTotalNum ++;
	}}
	cout << nTotalNum/2;
	*/
	return 0;
}