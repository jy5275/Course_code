/* http://dapractise.openjudge.cn/2018hw4/1/ */
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<limits.h>
#include<set>
#include<stack>
#include<bitset>
#include<memory.h>
#include<vector>
#include<algorithm>
using namespace std;
/* ���Ǹ�����Ϊ�Ƚ��ѵ�һ����
����ɢ�������N�ź���,����2N���˵�,��Щ�˵��ǽ���ֳ�2N-1����λ����,����
�˵㱾��һ�����ɷֳ�4N����λ���䡣���ڣ�
1. ÿ����λ����Ҫô��ȫ�����ǡ�,Ҫô��ȫ��¶����;
2. û���ĸ��˵������һ����λ�����ڲ�;
3. ÿ�ź���һ�������������ɸ�������λ���䡣
�������ǶԵ�λ����(���Ǵ�ש����)�����߶���,�����ͼ����˶��������,�������Ч��

��ɢ��֮��,��ʵ������һ���򵥵��������(�������൱��ÿ������ȥexposure),����
���(�Ѻ���ռ������exposure������,0Ϊ��ȫ����,��0��֮)��

Query��Changeͬʱ����,���Զ�������������ֻдһ������,����ע��˳��֤����ڼ�ȥ
exposure֮ǰ���С�Query��Change�ֳ��������������ô�ͳ�����������֪�᲻��TLE
*/
const int MAX = 10000010, MAX_POST = 10010;
int newTree[MAX];      //��i���ש�ǵ�newTree[i]�����������ʼ��ַ
bitset<MAX> visited;
class CNode {
public:
	int L, R, exposure;
	int Mid() { return (L + R) / 2; }
}Wall[4 * MAX_POST + 4];
int Left(int n) { return 2 * n + 1; }
int Right(int n) { return 2 * n + 2; }

void BuildTree(int root, int L, int R) {
	Wall[root].L = L, Wall[root].R = R, Wall[root].exposure = R - L + 1;
	if (L == R)return;         //Ҷ�ӽ�� (Wall[root].R == Wall[root].L == R == L)
	BuildTree(Left(root), L, (L + R) / 2);
	BuildTree(Right(root), (L + R) / 2 + 1, R);
}

int Paste(int root, int s, int e) {    //��poster[s, e]����root��Ӧ����expose�ĸ���
	if (Wall[root].exposure <= 0) return 0;   //��֦
	if (Wall[root].L == s && Wall[root].R == e) {
		int ret = Wall[root].exposure; //һ��match,�Ͱ���ε�exposure����,
		Wall[root].exposure = 0;       //..���ĵͼ����ȫ���Զ�����,46�з���
		return ret;
	}
	int exposure_sub;
	if (e <= Wall[root].Mid()) exposure_sub = Paste(Left(root), s, e);
	else if (s >= Wall[root].Mid() + 1) exposure_sub = Paste(Right(root), s, e);
	else exposure_sub = Paste(Left(root), s, Wall[root].Mid()) +
		Paste(Right(root), Wall[root].Mid() + 1, e);
	Wall[root].exposure -= exposure_sub;   //��Bug2�����ȫ��s~e,ֻ���ӽ��exposure����
	return exposure_sub;
}

int main() {
	int C;	cin >> C;
	while (C--) {
		memset(newTree, 0, sizeof(newTree));  //��BUG0��ע��ÿ��case��ʼ��ȫ�ֱ���
		visited.reset();
		int cnt = 0, N;
		vector<int> v;
		int s[MAX_POST], e[MAX_POST];
		cin >> N;

		//��¼����ĺ���,�������
		for (int i = 1; i <= N; i++) {
			int s_, e_;
			scanf("%d %d", &s_, &e_);
			s[N + 1 - i] = s_, e[N + 1 - i] = e_;  //������ķ�se���,������ķ�seǰ��
			v.push_back(s_); v.push_back(e_);
		}

		//������ɢ��,��newTree������{ MAX }Ԫ��ӳ�䵽����{ 4N }��,�����������
		sort(v.begin(), v.end());
		auto it = v.begin();
		for (int i = -1; it != v.end(); ++it) { //��BUG1��ע������/�غ϶˵����������Ҫ��
			if (visited[*it]) {  }              //newTree[*it]�Ѿ������ʹ���,ɶҲ������
			else if (visited[(*it) - 1] || i == -1) {  //newTree�е�*it-1���ѱ����ʹ�
				i++;
				newTree[*it] = i;
				visited.set(*it);
			}
			else {    //newTree��*itǰһ��Ԫ�ػ�û�б����ʹ�
				i = i + 2;
				newTree[*it] = i;
				visited.set(*it);
			}
		}         //     { MAX } ---newTree--> { 4*N } (��ϣ��)
		BuildTree(0, 0, 4 * N);

		//������
		for (int i = 1; i <= N; i++) {
			int expose = Paste(0, newTree[s[i]], newTree[e[i]]);
			if (expose) cnt++;
		}
		cout << cnt << endl;
	}
	return 0;
}/* ����Wrong Answer��ô��,�߼�̫����,��ָ��ֻͨ��������debug��
 1. �������,���߽�����(���鿪С�ˣ�)���������(0,������)
 2. �Լ��������Լ����ܿ�,����������ʹ����...���ڳ����ˣ���ϲ��
 */