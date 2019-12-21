//http://bailian.openjudge.cn/practice/4121/
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stack>
#include<vector>
#include<bitset>
#include<string>
#include<cstring>
#include<cmath>
#include<memory>
#include<stdexcept>
#include<time.h>
#include<algorithm>
#include<iomanip>
#include<fstream>
using namespace std;
/*深搜用栈实现,一条路走到死,再返回换条路走;
广搜用队列实现,所有路都一步一步走*/
const int MAX_COURSE = 16;
int T, N, ddl_time[2][MAX_COURSE], minLoss = 1 << 30;
string name[MAX_COURSE];
bitset<MAX_COURSE> finished;
stack<int> currentSq, minSq, coutSq;
int calcMinus() {
	int sum = 0;
	for (int i = 1; i <= N; ++i) {   //加和[F,L)中所有负数
		if (ddl_time[0][i] < 0) sum += (-ddl_time[0][i]);
	}
	return sum;
}
void calcMinLoss(int No, int n) {   //刚刚做完科目No,还有n门没完成！
	currentSq.push(No);    //先把科目No压入当前栈
	finished.set(No);
	if (n == 0) {
		int tmpt = calcMinus();
		if (tmpt < minLoss) {
			minLoss = tmpt;
			minSq = currentSq;
		}
		currentSq.pop();
		finished.reset(No);
		return;
	}
	for (int i = 1; i <= N; i++) {  //当前先做第i门作业,i=1:N,除去已做完的
		if (finished[i]) continue;
		int tmp[2][MAX_COURSE];
		memcpy(tmp, ddl_time, sizeof(ddl_time));  //把目前作业完成状态先存起来
		int alreadyLoss = 0;
		for (int j = 1; j <= N; j++) {      //其它没完成的科目作业ddl都顺延
			if (ddl_time[1][j] == 0) continue; //j科目已完成！不受影响！
			ddl_time[0][j] -= ddl_time[1][i];  //其它科目的ddl在逼近！
			if (ddl_time[0][j] < 0) alreadyLoss += (-ddl_time[0][j]);
		}  //循环完毕后,alreadyLoss记录当前已经损失的分数
		ddl_time[1][i] = 0;
		if (alreadyLoss <= minLoss)
			calcMinLoss(i, n - 1);
		memcpy(ddl_time, tmp, sizeof(ddl_time));
	}
	currentSq.pop();
	finished.reset(No);
}
int main() {
	cin >> T;
	while (T--) {
		cin >> N;
		for (int i = 1; i <= N; i++) {
			name[i].resize(52);
			scanf("%s%d%d", &name[i][0], &ddl_time[0][i], &ddl_time[1][i]);
		}
		clock_t startTime = clock();
		minLoss = 1 << 30;
		finished.reset();
		calcMinLoss(0, N);
		while (!minSq.empty()) {
			int t = minSq.top();
			coutSq.push(t);
			minSq.pop();
		}cout << minLoss;
		while (!coutSq.empty()) {
			cout << name[coutSq.top()] << endl;
			coutSq.pop();
		}
		clock_t endTime = clock();
		//cout << "程序段运行时间:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	}
	return 0;
}