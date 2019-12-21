/* http://bailian.openjudge.cn/practice/3438/
����N����A1,A2 �� AN, Q������һ����[Ai, Aj]�����������С���Ĳ�
*/
//�п�����״��������
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<limits.h>
#include<algorithm>
#define Left(p) 2*(p)+1
#define Right(p) 2*(p)+2
using namespace std;
const int MAX = 800010;
int maxValue = INT_MIN, minValue = INT_MAX;
class CNode {       //һ����������ֻ�����ھ�̬����,������������������Ӷȸ���
public:
	int L, R, maxV = INT_MIN, minV = INT_MAX;
	int Mid() { return (L + R) / 2; }  //Mid��ýڵ��Ӧ������ֵ
}tree[MAX];
void BuildTree(int root, int L, int R) {   //����
	tree[root].L = L;
	tree[root].R = R;
	if (L == R)return;
	int mid = (L + R) / 2;
	BuildTree(Left(root), L, mid);
	BuildTree(Right(root), mid + 1, R);
}
void Insert(int root, int i, int v) {     //��ֵΪv�ĵ�i����������rootΪ�����߶���
	if (tree[root].L == tree[root].R) {   //����Ҷ�ӽ��,���Ը�ֵ��
		tree[root].minV = tree[root].maxV = v; return;
	}
	tree[root].minV = min(tree[root].minV, v);  //������tree[root]��ֵ,
	tree[root].maxV = max(tree[root].maxV, v);  //û�꣡��Ҫ�������¸���
	if (i <= tree[root].Mid()) Insert(Left(root), i, v);  //��i�����v�嵽��������
	else Insert(Right(root), i, v);    //��i�����v�嵽��������
}
void Query(int root, int s, int e) {   //��ѯ����[s, e]�������Сֵ,��¼��ȫ�ֱ�����
	if (tree[root].minV >= minValue && tree[root].maxV <= maxValue) return;  //��֦
	if (tree[root].L == s && tree[root].R == e) {
		maxValue = max(maxValue, tree[root].maxV);
		minValue = min(minValue, tree[root].minV);
		return;
	}
	if (e <= tree[root].Mid()) Query(Left(root), s, e);
	else if (s >= tree[root].Mid() + 1) Query(Right(root), s, e);
	else {
		Query(Left(root), s, tree[root].Mid());
		Query(Right(root), tree[root].Mid() + 1, e);
	}
}
int main() {
	int Q, N, h;
	scanf("%d %d", &N, &Q);
	BuildTree(0, 1, N);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &h);
		Insert(0, i, h);
	}
	for (int i = 1; i <= Q; i++) {
		int s, e;
		scanf("%d %d", &s, &e);
		minValue = INT_MAX; maxValue = INT_MIN;
		Query(0, s, e);
		printf("%d\n", maxValue - minValue);
	}
	return 0;
}