#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
#include<bitset>
#include<memory.h>
#include<stack>
using namespace std;
const int MAX = 450;
int wa[MAX], wb[MAX], wv[MAX], Ws[MAX], sa[MAX];
void BuildSA(const char *s, int *sa, int n, int m) {
	int *pm = wa, *k2sa = wb, *t;
	for (int i = 0; i < m; i++) Ws[i] = 0;
	for (int i = 0; i < n; i++) Ws[pm[i] = s[i]]++;

	for (int i = 0; i < m; i++) Ws[i] += Ws[i - 1];
	for (int i = n - 1; i >= 0; i--) sa[--Ws[pm[i]]] = i;
	int i;
	for (int j = 1, p = 1; p < n; j <<= 1, m = p) {
		for (p = 0, i = n - j; i < n; i++) k2sa[p++] = i;
		for (i = 0; i < n; i++)
			if (sa[i] >= j) k2sa[p++] = sa[i] - j;
		for (int i = 0; i < m; i++) Ws[i] = 0;
		for (int i = 0; i < n; i++) Ws[wv[i] = pm[k2sa[i]]]++;

		for (int i = 1; i < m; i++) Ws[i] += Ws[i - 1];
		for (int i = n - 1; i >= 0; i--)
			sa[--Ws[wv[i]]] = k2sa[i];

	}
}