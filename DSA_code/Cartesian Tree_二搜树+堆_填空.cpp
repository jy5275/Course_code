#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<string.h>
#include<queue>
#include<cmath>
#include<memory.h>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
/* 代码填空,一般比较难(要不然就直接叫你编程了),考试的时候先跳过,走投无路再做
 * 先抓主体,明白算法总体框架,再考虑细节,不要一上来就考虑各种特殊情况……
 */
const int MAXN = 50005;
//Tkey为输入主键与辅键的结构体
struct Tkey {
	int key, aux, index;	//key主键,aux辅键,这是输入的第index个结点
} keys[MAXN];
bool operator<(const Tkey &a, const Tkey &b) {
	return a.key < b.key;
}

//Tnode是BST结点的结构体，key表示主键，aux表示辅键
struct Tnode {
	int key, aux, parent, leftchild, rightchild;
} node[MAXN];

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d", &keys[i].key, &keys[i].aux);
		keys[i].index = i;
	}
	sort(keys + 1, keys + n + 1);	//按key对结点排序

	//按key从小到大将结点插入BST
	//parent - 当前插入结点的父，leftchild - 当前插入结点的左儿子
	//rightMost - 每次插入前BST最右的结点
	int p, parent, leftchild, rightMost = 0;
	for (int i = 1; i <= n; ++i) {
		//寻找插入结点i的父亲与左儿子
		leftchild = 0; parent = rightMost;
		while (parent != 0 && node[parent].aux > keys[i].aux) {
			leftchild = parent;
			parent = node[parent].parent;
		}
		if (node[parent].aux > keys[i].aux) {
			printf("NO\n");
			return 0;
		}
		//将结点插入BST
		p = keys[i].index;
		node[p].key = keys[i].key;
		node[p].aux = keys[i].aux;
		node[p].parent = parent;
		node[p].leftchild = leftchild;
		node[p].rightchild = 0;
		if (parent != 0)
			node[parent].rightchild = p;
		if (leftchild != 0)
			node[leftchild].parent = p;
		rightMost = p;
	}

	//输出答案
	printf("YES\n");
	for (int i = 1; i <= n; ++i)
		printf("%d %d %d\n", node[i].parent, node[i].leftchild, node[i].rightchild);
	return 0;
}