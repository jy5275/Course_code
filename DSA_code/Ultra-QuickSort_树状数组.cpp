//http://bailian.openjudge.cn/practice/solution/16575378/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<memory.h>
/* 树状数组：单点更新，区间求和！ */
using namespace std;
const int MAX = 500010;
int n = 0;
long long a[MAX], ans, c[MAX];
int lowbit(int x) { return x & (-x); }
class CNode {
public:
	int val, sum;
}arr[MAX];
void BuildTree(int val) {
	while (val <= n) {
		c[val]++;
		val += lowbit(val);
	}
}
/* 树状数组初始化C 
 * C[i] = a[i - lowbit(i) + 1] + a[i - lowbit(i) + 2]... + a[i]
 * C[14] = a13 + a14
 * C[21] = a21 + a20 + a16
 */
void Init() {
	for (int i = 1; i <= n; i++) {
		c[i] = 0;
		for (int j = i; j > i - lowbit(i); j--)
			c[i] += a[j];
	}
}

/* 树状数组求和sum(val)：
 * iterator i follows a binary decrease sequence：
 * sum(val) = C[i1] + C[i2] + ... + C[im]
 * i：(from val to 0) i = i - lowbit(i)
 * sum(6) = C6 + C4;
 * sum(14) = C14 + C12 + C8;
 * sum(29) = C29 + C28 + C24 + C16;
 */
int Query(int k) {	//区间前val求和：二进制螺旋下降
	int sum = 0;
	for (int i = k; i >= 1; i = i - lowbit(i))
		sum += c[i];
	return sum;
}

/* 树状数组单点更新a[val]：
* i螺旋上升：需要更新C[i1], C[i2], ... C[im]
* i：(from 0 to N) i = i + lowbit(i)
* a[4]：C[4], C[8], C[16]...
* a[7]：C[7], C[8], C[16]... 
* a[9]：C[9], C[10], C[12], C[16], C[32]...
*/
void Renew(int k, int delta) {	//区间更新：二进制螺旋上升
	for (int i = k; i <= n; i = i + lowbit(i))
		c[i] = c[i] + delta;
}
bool cmp(CNode n1, CNode n2) {
	return n1.val < n2.val;
}
int main() {
	scanf("%d", &n);
	while (n) {
		ans = 0;
		memset(c, 0, sizeof(c));
		for (int i = 1; i <= n; i++) {
			scanf("%d", &arr[i].val);
			arr[i].sum = i;
		}
		sort(arr, arr + n + 1,cmp);

		for (int i = 1; i <= n; i++) 
			a[arr[i].sum] = i;
		for (int i = 1; i <= n; i++) {
			BuildTree(a[i]);
			ans += i - Query(a[i]);
		}
		printf("%lld\n", ans);
		scanf("%d", &n);
	}

	return 0;
}