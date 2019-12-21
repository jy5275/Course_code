#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<string.h>
#include<queue>
#include<cmath>
#include<memory.h>
#include<algorithm>
using namespace std;
/* 我为人人动规，
 * 本题难点在于【休息】更新的不是下一行,而是跳好几行！因为一休息就必须满血复活再跑！
 * 【跑步】则正常更新,注意check体力值
 */
const int MIN = 1 << 31;
int N, M, D[10010], maxL[10010][510];
void Init() {
	memset(maxL, -1, sizeof(maxL));
}
int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++)
		scanf("%d", &D[i]);
	Init();
	maxL[0][M] = 0;
	for (int min = 0; min <= N; min++) {
		for (int s = 0; s <= M; s++) {
			if (maxL[min][s] == -1)continue;
			//【跑步】更新：第min分钟run,消耗体力1点/时间1点,增加成就D[min]点
			if (s > 0)
				maxL[min + 1][s - 1] = max(maxL[min + 1][s - 1], maxL[min][s] + D[min]);

			//【休息】更新：第min分钟rest,满血复活,消耗时间M-s点
			if (s != M && min + M - s <= N)
				maxL[min + M - s][M] = max(maxL[min + M - s][M], maxL[min][s]);
			else if (s == M)		//再休息也没用！s不能超过M！
				maxL[min + 1][s] = max(maxL[min + 1][s], maxL[min][s]);
		}
	}
	printf("%d\n", maxL[N][M]);

	return 0;
}