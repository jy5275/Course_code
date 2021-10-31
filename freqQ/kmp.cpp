#include<iostream>
#include<list>
#include<deque>
#include<string>
#include<string.h>
#include<stdio.h>
#include<algorithm>
using namespace std;
/*
    pattern string: abxabc

    prev ptr  | node | prev[x]
     ---------> [a]     -1
    |
    |    -----> [b]      0
    |   |
    |   |       [x]      0
    |   |
     ---------- [a]      0
        |
         ------ [b]      1

                [c]      2
    prev[x]: if str[i] fails to match pattern[x], should go 
             to pattern[prev[x]] to match str[i]

*/
int KMP(const char *p, const char *s) {
    int p1 = 0, s1 = 0;
    int prev[100];
    // Build prev arr: prev[i+1] = prev[i]+1
    prev[0] = -1;
    for (int i=0; i<strlen(p) - 1; i++) {
        int pPrev = prev[i];
        while (pPrev != -1 && p[pPrev] != p[i]) {
            pPrev = prev[pPrev];
        }
        prev[i+1] = pPrev + 1;
    }

    printf("arr: ");
    for (int i=0; i<strlen(p); i++) printf("%d, ", prev[i]);
    printf("\n");

    // Match: if not match, j=prev[j], finally ji++
    for (int i=0, j=0; i<strlen(s) && j<strlen(p);) {
        while (j != -1 && s[i] != p[j])
            j = prev[j];
        j++, i++;
        if (j == strlen(p)) {
            return i - j;
        }
    }
    return -1;
}

int main () {
    printf("%d\n", KMP("agctagcagctagctg", "agctagcagctagctagcagctagctg"));
    return 0;
}