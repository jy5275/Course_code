#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<list>
#include<vector>
#include<algorithm>
using namespace std;
int win = 0, DIV = 10, SCORE = 5;
double p, totalWin = 0, totalLose = 0, STOP = 1e-7;
void Test(int winOrNot, double prob) {
	win = win + winOrNot;  //0001 for 1,1111 for 0
	if (win >= SCORE) {
		totalWin += prob , win--;
		return;
	}
	else if (win <= -SCORE) {
		totalLose += prob , win++;
		return;
	}
	int winTester = p * DIV, loseTester = (1 - p) * DIV;
	if (prob*p / DIV > STOP) {
		for (int i = 0; i < winTester; i++)
			Test(1, prob / DIV);
	}
	if (prob*(1 - p) / DIV > STOP) {
		for (int i = 0; i < loseTester; i++)
			Test(-1, prob / DIV);
	}
	win = win - winOrNot;  //0001 for 1,1111 for 0
}
int main() {
	p = 0.4;
	Test(0, 1);
	cout << (double)totalWin / (double)(totalLose + totalWin) << endl;
	return 0;
}