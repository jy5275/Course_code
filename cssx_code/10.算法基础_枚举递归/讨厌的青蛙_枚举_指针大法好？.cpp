#define _CRT_SECURE_NO_WARNINGS
//ö��֮���������
#include<iostream>
#include<vector>
#include<string>
#include<set>
#include<cmath>
#include<list>
#include<memory>
#include<map>
#include<stdexcept>
#include<algorithm>
#include<queue>
#include<iomanip>
#include<fstream>
#include<unordered_map>
#include<regex>
using namespace std;
int r, c, n, dx, dy, dxMax, dyMax;
class CPlant {
public:
	int x = 0, y = 0;
	CPlant() {}
	CPlant(int x_, int y_) :x(x_), y(y_) {}
	bool operator==(CPlant p) {
		if (x == p.x && y == p.y) return true;
		else return false;
	}
} *pPlants[5001], *pMaxStart;
bool operator<(CPlant *p1, CPlant *p2) {
	if (p1->x == p2->x)return p1->y < p2->y;
	else return p1->x < p2->x;
}
CPlant *formerPlant(CPlant *pNowP) {
	CPlant *pTmp = new CPlant(pNowP->x - dx, pNowP->y - dy);
	return pTmp;
}
CPlant *laterPlant(CPlant *pNowP) {
	CPlant *pTmp = new CPlant(pNowP->x + dx, pNowP->y + dy);
	return pTmp;
}
bool inField(CPlant *p) {       //����������ǲ�����������
	if (p->x <= 0 || p->x > r)return false;
	if (p->y <= 0 || p->y > c)return false;
	return true;
}
bool inPlantsList(CPlant *p) {  //����������ǲ����ڱ��ٵ�List���
	if (!binary_search(pPlants, pPlants + n, &p))return false;
	else return true;
}
int searchPath(CPlant *pStartPoint) {
	int step = 0;
	CPlant *pCurrentPoint = new CPlant(*pStartPoint);
	while (inField(pCurrentPoint)) {    //ֻҪ��һ�����������,�ͼ���ѭ��!
		if (!inPlantsList(pCurrentPoint)) { return 0; } //�ò�δ��,��!
		step++;  //��¼����++
		pCurrentPoint = laterPlant(pCurrentPoint); //����һ���òȴ�
	}
	return step;
}
int main() {
	int maxStep = 0;
	cin >> r >> c >> n;
	for (int i = 0; i < n; i++) {
		int x_, y_; cin >> x_ >> y_;
		pPlants[i]->x = x_;
		pPlants[i]->y = y_;
	}
	sort(pPlants, pPlants + n);
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (i == j) continue;   //����ͬһ���㣡
			dx = pPlants[j]->x - pPlants[i]->x;
			dy = pPlants[j]->y - pPlants[i]->y;
			if (inField(formerPlant(pPlants[i]))) continue; //ǰһ��������,��ȥ!
			if (pPlants[i]->x + (maxStep - 1)*dx > r) break;
			/*x�����Խ��!�������ǵڶ����㲻����,�����ֱ��i+1
			��һ��������±�,����������,��ȻԽx��,
			����Ӧ�ðѵ�һ�������µ�����break����һ����*/
			int py = pPlants[i]->y + (maxStep - 1)*dy;
			if (py > c || py < 1) continue;
			int step = searchPath(pPlants[i]);  //��plants[i]��ʼ���һ��,��ʼ��!
			if (step > maxStep) {
				maxStep = step;
				pMaxStart = pPlants[i];
				dxMax = dx; dyMax = dy;
			}
		}
	}
	if (maxStep > 2) {
		cout << maxStep << endl << "dxMax=" << dxMax << endl << "dyMax=" <<
			dyMax << endl << pMaxStart->x << "," << pMaxStart->y << endl;
	}
	else cout << "0" << endl;
	return 0;
}