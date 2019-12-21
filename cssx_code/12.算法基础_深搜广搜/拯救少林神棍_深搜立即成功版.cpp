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
/*
剪枝1:anLength中长度相同的木棒只考虑一次
剪枝2:若对∃木棒不能作为某根棍子的首木棒,即有L长度不成立！否则这根木棒迟早要拼到以后某根棍子中
剪枝3:不要希望通过仅仅替换已经拼好棍子的最后一根木棒来挽回失败的局面！
      留下的空位用其它木棒来填充也是徒劳的
剪枝4:每拼接一根棍子的时候,确保已经拼好的部分长度是从长到短排序的
*/
const int MAX = 100;
int L, N, k, nLastStickNo;        //记录最近拼上去的木棒下标
vector<int> anLength;
bitset<MAX> used;
bool Dfs(int No, int R, int M) {   //【R和M不能充分描述Dfs的状态,配合used才能！】
	//当前有R根未用木棒,正在拼装的棍子长度还缺M,返回能否拼接成功
	if (No > 0) {
		if (used[No - 1] == false && anLength[No] == anLength[No - 1])   //跳过等长的木棍
			return false;
	}
	if (R == 0 && M == 0) return true;   //判断目标条件
	if (M == 0) M = L;               //开始新一根棍子的拼接
	nLastStickNo = No;  //剪枝4:如果不是新开棍子,则下一根木棒从最近拼接的No木棒开始尝试
	int nStartNo = (M == L) ? 0 : nLastStickNo + 1;
	for (int i = nStartNo; i < N; i++) {     //从长到短依次拿
		if (!used[i] && anLength[i] <= M) {
			if (i > 0) {
				if (used[i - 1] == false && anLength[i] == anLength[i - 1]) 
					continue;
			}
			used.set(i);
			if (Dfs(i, R - 1, M - anLength[i]))
				return true;    //如果用剩下(!used)R-1根木棒能拼出长M-anLength[i]的棍子
			                    //就返回true,意思是用这R根木棒能拼出长M的棍子
			else {
				used.reset(i);
				if (M == L)    //若第i根木棒不能成为某棍子的首根木棒
					return false;      //【接连失败】
				if (anLength[i] == M)  //若第i根木棒不能成为某棍子的最后一根木棒
					return false;      //【接连失败】
			} //剩下R-1根木棒不能拼出长M-anLength[i]的棍子！拿i+1号木棒试试
		}
	}
	return false;    //如果试完R根木棒还没有拼出长M的棍子,就拆下这跟木棒！
}
int main() {
	while (1) {
		cin >> N;
		if (N == 0)break;
		int nTotalLen = 0;
		anLength.clear();
		for (int i = 0; i < N; i++) {
			int n; cin >> n;
			anLength.push_back(n);
			nTotalLen += n;
		}
		clock_t startTime = clock();
		sort(anLength.begin(), anLength.end(), greater<int>()); //先试长的木棒
		for (L = anLength[0]; L <= nTotalLen / 2; L++) {   //枚举所有可能的棍长L
			//一旦L是正确的L,那么木棒放上去的顺序是无所谓的！从小到大
			if (nTotalLen % L != 0) continue;        //尝试的L必须是nTotalLen的因数
			used.reset();
			if (Dfs(0, N, L)) {
				cout << L << endl;
				break;
			}
		}
		if (L > nTotalLen / 2)cout << nTotalLen << endl;
		clock_t endTime = clock();
	}
	return 0;
}