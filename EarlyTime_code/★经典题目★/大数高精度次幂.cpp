#include<iostream>
#include<cstring>
#include<cmath>    
// http://bailian.openjudge.cn/practice/1001/,  
//����˼·��95.123 12Ϊ�����ȼ���ans=95123*95123������һλһλȥ��
using namespace std; 
int main()
{
	char ipt[7], x[200], z[400], tem[400]; int n;
	while (cin.getline(ipt, 7, ' ')) {
		int n, k, i, j = 0, mark = 0, flag = 0;
		cin >> n;  //input=ipt���õ�������
		for (int i = 5; i >= 0; i--) {
			if (ipt[i] == '.') {
				mark = 5 - i; continue;
			}
			x[j] = ipt[i]; j++;   //���ѭ��������������ַ���תΪ����char�ʹ���num
		}
		for (; j < strlen(x); j++) x[j] = '0';  //���뵽�˽���
		strcpy_s(z, x);
		for (k = 1; k < n; k++) {
			//��������char�ʹ���x��z�����char�ʹ������˻���z
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
		//for (i = len - 2; z[i] == '0'; i--) {}      //ע�⣺�ַ�����������Ҫ������''��
		//if (i < xs) i = xs - 1;      //��ֹ�ر�С��С����С����ʡ���ˣ��������
		for (j = 0; z[j] == '0'; j++)
			z[j] = 'l';                             //ע�⣺��������iҪ�ڶ��ѭ������ʹ�ã�����Ҫ��ѭ���ڼ䴫����Ҫ��Ϣ��ע�Ᵽ������������
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

		//�����߼���֧��Ҫ���ǵ�����ڶ࣬���ó����ͼ����˼·������֪ʶ��
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
		//��ϰ�����﷨��Ʃ�磺�ַ�/�ַ��������뷽ʽ���ַ���ָ����÷����ַ����ں�����Ĵ��ݵȵȣ�
		cout << endl;
		cin.get();
	
	}


	return 0;
}