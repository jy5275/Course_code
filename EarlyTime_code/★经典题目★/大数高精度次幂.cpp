#include<iostream>
#include<cstring>
#include<cmath>    
// http://bailian.openjudge.cn/practice/1001/,  
//整体思路：95.123 12为例，先计算ans=95123*95123，挨个一位一位去乘
using namespace std; 
int main()
{
	char ipt[7], x[200], z[400], tem[400]; int n;
	while (cin.getline(ipt, 7, ' ')) {
		int n, k, i, j = 0, mark = 0, flag = 0;
		cin >> n;  //input=ipt，得到两个数
		for (int i = 5; i >= 0; i--) {
			if (ipt[i] == '.') {
				mark = 5 - i; continue;
			}
			x[j] = ipt[i]; j++;   //这个循环把正序输入的字符串转为倒序char型大数num
		}
		for (; j < strlen(x); j++) x[j] = '0';  //输入到此结束
		strcpy_s(z, x);
		for (k = 1; k < n; k++) {
			//输入两个char型大数x和z，输出char型大数（乘积）z
			int ans[400] = { 0 }, num1[200], num2[200], len1 = strlen(x), len2 = strlen(z);
			for (i = 0; i < 200; i++)
				num1[i] = x[i] - '0';       //1--x
			for (i = 0; i < 200; i++)
				num2[i] = z[i] - '0';   	//2--z
			for (i = 0; i < 200; i++) {
				for (j = 0; j < 200; j++)
					ans[i + j] = ans[i + j] + num1[j] * num2[i];
			}
			for (i = 0; i < 200; i++) {
				ans[i + 1] = ans[i + 1] + ans[i] / 10;
				ans[i] = ans[i] % 10;
			}
			for (i = 0; i < 199; i++)
				tem[i] = ans[i] + '0';
			tem[i] = '\0';
			strcpy_s(z, "");
			strcpy_s(z, tem);
		}
		int xs = mark * n, len = strlen(z);
		//for (i = len - 2; z[i] == '0'; i--) {}      //注意：字符串当数组用要加引号''！
		//if (i < xs) i = xs - 1;      //防止特别小的小数把小数点省略了，特殊情况
		for (j = 0; z[j] == '0'; j++)
			z[j] = 'l';                             //注意：计数变量i要在多个循环节中使用，并且要在循环节间传递重要信息！注意保护计数变量！
		//for (; i >= 0 ; i--) {
			//if (i == xs - 1 ) { 
				//flag = 1; cout << '.';
				////if(z[i - 1] != 'l')
					////cout << '.';  
			//}
			//if (z[i] == 'l') {
				//if (flag == 0)  
					//cout << '0'; 
				//else 
					//break;
		//	}
			//else
				//cout << z[i];			
		//}
		//cout << endl;

		//复杂逻辑分支，要考虑的情况众多，就用程序框图理清思路！高中知识！
		for (i = len - 2;; i--) {
			if (i < xs) {
				if (flag == 1) {
					cout << z[i];
				}
				else {
					cout << '.' << z[i]; flag = 1;
				}
				if (z[i] != '0') break;
			}
			else {
				if (z[i] != '0') {
					cout << z[i]; break;
				}
				else {	}
			}
		}
		i--;
		for (; i >= 0; i--) {
			if (i < xs) {
				if (z[i] == 'l') { break; }
				else {
					if (flag == 0) {
						cout << '.' << z[i]; flag = 1;
					}
					else {
						cout << z[i];
					}
				}
			}
			else {
				if (z[i] == 'l') {
					cout << '0';
				}
				else {
					cout << z[i];
				}
			}
		}
		//复习基本语法！譬如：字符/字符串的输入方式、字符串指针的用法、字符串在函数间的传递等等！
		cout << endl;
		cin.get();
	
	}


	return 0;
}