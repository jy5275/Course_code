#include<iostream>
#include<string.h>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;
int min_step, tmp_step, x_start, y_start, x_terminal, y_terminal;
char a[103][103];
int go(int x, int y, int k) {   //��ʼ�����������ʱ���Ѿ��ɹ�����k��������(x,y)
	if (k > min_step)  return 0;               //����Ѿ�����Сֵ�����ˣ��Ǿͻ�ȥЪϢ��
	if (x == x_terminal && y == y_terminal) {  //�����k���������յ�...
		if (k < min_step) min_step = k;        //�ж��ǲ��ǵ�ǰ���·��
		return 0;                              //˳���깤��һ��·�����
	}
	a[x][y] = 'S';              //�ȳ���ӡ����a�е�k������(x,y)��Ϊ'S'
	if (a[x - 1][y] != '#'&&a[x - 1][y] != 'S')   //���������ûײǽ...
		go(x - 1, y, k + 1);    //�Ͱ�������һ����Ϊ��k+1���ɣ�
	if (a[x + 1][y] != '#'&&a[x + 1][y] != 'S')   //��
		go(x + 1, y, k + 1);
	if (a[x][y - 1] != '#'&&a[x][y - 1] != 'S')   //��
		go(x, y - 1, k + 1);
	if (a[x][y + 1] != '#'&&a[x][y + 1] != 'S')   //��
		go(x, y + 1, k + 1);
	a[x][y] = '.';    //�˻ؽ�ӡ
	return 0;
}
int main() {
	int i, j, n, m;
	cin >> n >> m;
	for (i = 0; i <= m + 1; i++)
		a[0][i] = '#';             //�޺���ǽ
	min_step = n * m;
	for (i = 1; i <= n; i++) {
		a[i][0] = '#';             //�޺���ǽ
		for (j = 1; j <= m; j++) {
			cin >> a[i][j];        //����
			if (a[i][j] == 'S')
				x_start = i, y_start = j;
			else if (a[i][j] == 'T')
				x_terminal = i, y_terminal = j;
		}a[i][j] = '#';            //�޺���ǽ
	}
	for (j = 0; j <= m + 1; j++)
		a[i][j] = '#';             //�޺���ǽ
	go(x_start, y_start, 0);
	cout << min_step;
	return 0;
}