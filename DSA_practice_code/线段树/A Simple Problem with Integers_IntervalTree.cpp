/* http://bailian.openjudge.cn/practice/3243/ */
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<limits.h>
#include<algorithm>
#define Left(p) 2*(p)+1
#define Right(p) 2*(p)+2
using namespace std;
/*���ӳٸ��¡�����ʱδ��Ҫ���׸���,�Ƴٵ���ѯʱ��ȥ��������Ӧ����ѯ�Ĳ��� */
const int MAX = 100010;
class CNode {
public:
	int L, R;
	long long sum = 0;	//���´�������ͣ�
	long long inc = 0;	//δ�´�������ͣ�
	int Mid() { return (L + R) / 2; }
}tree[4 * MAX + 10];

void BuildTree(int root, int L, int R) {
	tree[root].L = L;
	tree[root].R = R;
	if (L == R) return;
	int mid = (L + R) / 2;
	BuildTree(Left(root), L, mid);
	BuildTree(Right(root), mid + 1, R);
}

//ÿ�����ġ�sum + inc*len��+�������ϲ�inc�����Ǹ�ʱ����ȷ����ͣ�
void Add(int root, int a, int b, long long c) {		//������[a, b]��Ԫ��ÿ����c
	if (tree[root].L == a && tree[root].R == b) {	//ǡ�ø���==>����inc
		tree[root].inc += c; return;
	}
	//���ܸ���==>���´���
	tree[root].sum += (b + 1 - a)*c;
	if (b <= tree[root].Mid())
		Add(Left(root), a, b, c);
	else if (a > tree[root].Mid())
		Add(Right(root), a, b, c);
	else {
		Add(Left(root), a, tree[root].Mid(), c);
		Add(Right(root), tree[root].Mid() + 1, b, c);
	}
}

//��ȥһ·������inc
long long QuerySum(int root, int a, int b) {	//��root��[a, b]�����
	if (tree[root].L == a && tree[root].R == b)
		return tree[root].inc * (b + 1 - a) + tree[root].sum;
	int len = tree[root].R + 1 - tree[root].L;

	//�ý��incתsum,�´������
	tree[root].sum += tree[root].inc * len;
	tree[Left(root)].inc += tree[root].inc;
	tree[Right(root)].inc += tree[root].inc;
	tree[root].inc = 0;

	if (b <= tree[root].Mid())
		return QuerySum(Left(root), a, b);
	else if (a > tree[root].Mid())
		return QuerySum(Right(root), a, b);
	else
		return QuerySum(Left(root), a, tree[root].Mid()) +
		QuerySum(Right(root), tree[root].Mid() + 1, b);
}

int main() {
	int N, Q, a_, b_, c_;
	long long v_;
	char cmd;
	scanf("%d %d", &N, &Q);
	BuildTree(0, 1, N);
	for (int i = 1; i <= N; i++) {
		scanf("%lld", &v_);
		Add(0, i, i, v_);
	}
	for (int i = 0; i < Q; i++) {
		scanf("\n%c", &cmd);
		if (cmd == 'C') {
			cin >> a_ >> b_ >> c_;
			Add(0, a_, b_, c_);
		}
		else {
			scanf("%d %d", &a_, &b_);
			printf("%lld\n", QuerySum(0, a_, b_));
		}
	}
	return 0;
}