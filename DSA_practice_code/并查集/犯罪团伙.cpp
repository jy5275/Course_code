/* http://www.icourse163.org/learn/PKU-1002534001?tid=1003136008#/
 learn/ojhw?id=1004730180 -- 犯罪团伙*/
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<memory.h>
using namespace std;
const int MAX = 100010;
int M, N, parent[MAX], diff[MAX];
void Init() {
	for (int i = 0; i < N; i++) {
		diff[i] = 0;     // 1--不同，0--相同
		parent[i] = i;
	}
}
int GetRoot(int a) {
	if (a != parent[a]) {
		int t = GetRoot(parent[a]);
		diff[a] = diff[a] + diff[parent[a]];
		parent[a] = t;
	}
	return parent[a];
}
void Merge(int a, int b) {       // a的祖先赋给b
	int p1 = GetRoot(a), p2 = GetRoot(b);
	if (p1 == p2) return;
	parent[p2] = p1;
	diff[p2] = (diff[a] + diff[b] + 1) % 2;
}
bool Query(int a, int b) { return GetRoot(a) == GetRoot(b); }
int main() {
	char cmd;
	int T, a1, a2; scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &N, &M); cin.get();
		Init();
		char cmd;
		while (M--) {
			scanf("%c %d %d", &cmd, &a1, &a2);
			cin.get();
			if (cmd == 'D') 
				Merge(a1, a2);
			else if (cmd == 'A') {
				if (!Query(a1, a2))
					printf("Not sure yet.\n");
				else if (diff[a1] == diff[a2])
					printf("In the same gang.\n");
				else
					printf("In different gangs.\n");
			}
		}
	}
	return 0;
}