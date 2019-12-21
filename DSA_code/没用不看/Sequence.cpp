#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<queue>
#include<memory.h>
#include<stack>
using namespace std;
/* 实在想不出来巧妙的算法，暴力+剪枝也可以完成的！ */
const int MAX = 2010;
priority_queue<int> H;
int main() {
	int t; scanf("%d", &t);
	while (t--) {
		int n, m, base[MAX], add[MAX];
		scanf("%d %d", &m, &n);
		for (int i = 0; i < n; i++) 
			scanf("%d", &base[i]);
		sort(base, base + n);
		m--;
		while (m--) {
			for (int i = 0; i < n; i++) 
				scanf("%d", &add[i]);
			sort(add, add + n);
			for (int i = 0; i < n; i++) 
				H.push(base[i] + add[0]);
			for (int id_add = 1; id_add < n; id_add++) {   // Push base[0:n-1]+add[i]
				int id_base = 0;
				for (id_base = 0; id_base < n; id_base++) {
					int test = base[id_base] + add[id_add];
					if (test < H.top()) {
						H.pop();
						H.push(test);
					}
					else break;
				}
				if (id_base == 0) break;
			}
			for (int i = n - 1; i >= 0; i--) {
				base[i] = H.top();
				H.pop();
			}
		}
		printf("%d", base[0]);
		for (int i = 1; i < n; i++) 
			printf(" %d", base[i]);
		printf("\n");
	}
	return 0;
}