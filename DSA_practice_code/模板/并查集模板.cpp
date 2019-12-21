/* http://bailian.openjudge.cn/practice/3243/ */
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
#include<memory.h>
#include<bitset>
#include<queue>
using namespace std;
const int MAX = 10010;
int parent[MAX], N;
void Init() {
	for (int i = 0; i < N; i++)
		parent[i] = i;
}
int GetRoot(int x) {
	if (parent[x] != x)
		parent[x] = GetRoot(parent[x]);
	return parent[x];
}
void Merge(int a, int b) {		//b挂在a上
	int r1 = GetRoot(a), r2 = GetRoot(b);
	parent[r2] = r1;
}
bool Query(int a, int b) {
	return GetRoot(a) == GetRoot(b);
}
int main() {

	return 0;
}