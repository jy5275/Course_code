/* http://dsa.openjudge.cn/final2018test/3/ */
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<memory.h>
#include<string>
#include<string.h>
#include<bitset>
#include<math.h>
#include<queue>
#include<vector>
#include<set>
#include<map>
using namespace std;
/* 首先想想STL能不能解决问题！轮子不要发明两遍！
 * STL常见函数要背熟！这回用到的m.count()就不知道！
 */
map<string, string> m;
int main() {
	char tmp[24], tmp1[12], tmp2[12];
	string str1, str2;
	for (int j = 0;; j++) {
		fgets(tmp, 30, stdin);
		int len = strlen(tmp);
		if (len <= 1) break;
		int i;
		for (i = 0; i < len; i++)
			if (tmp[i] == ' ')break;
		memcpy(tmp1, tmp, i); tmp1[i] = '\0';
		memcpy(tmp2, tmp + i + 1, len - i - 1); tmp2[len - i - 2] = '\0';
		str1 = tmp1, str2 = tmp2;
		m[str2] = str1;
	}
	while (scanf("%s", tmp) != EOF) {
		if (tmp[0] == '0')break;
		str1 = tmp;
		if (m.count(str1))
			printf("%s\n", m[str1].c_str());
		else printf("eh\n");
	}
	return 0;
}