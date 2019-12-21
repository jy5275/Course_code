//数字三角形
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<cmath>
#include<memory.h>
#include<algorithm>
#include<stack>
const int MAX = 101;
using namespace std;
int D[MAX][MAX], n, cache[MAX][MAX];
int maxSum(int i, int j) {         //返回从第i行第j列到底边的最大和
	if (i == n) return D[i][j];
	if (cache[i][j] != -1) return cache[i][j];
	cache[i][j] = max(maxSum(i + 1, j), maxSum(i + 1, j + 1)) + D[i][j];
	return cache[i][j];
}
/*递归到动归的一般方法:
1.递归函数有n个参数==数组dim=n,
2.数组下标==递归函数参数取值范围,
3.数组元素==递归函数返回值, cache[i][j] = maxSum(i, j);
如此可以从边界值开始逐步填充数组,相当于计算递归函数值的逆过程
从程序逻辑来看，递归是从上到下，动归是自下而上
*/
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= i; j++) 
			cin >> D[i][j];
	
	//------------递归方案----------------------------------------
	memset(cache, -1, sizeof(cache));
	cout << maxSum(1, 1) << endl;

	//------------动规方案----------------------------------------
	for (int i = n - 1; i >= 1; i--) 
		//从边界值开始逐行向上scan,置为maxSum下边两个大者+自身
		for (int j = 1; j <= i; ++j)
			D[i][j] = max(D[i + 1][j], D[i + 1][j + 1]) + D[i][j];

	cout << D[1][1] << endl;
	//------------------------------------------------------------
	return 0;
}