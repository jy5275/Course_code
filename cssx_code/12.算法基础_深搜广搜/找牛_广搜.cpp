#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stack>
#include<queue>
#include<string>
#include<bitset>
#include<cstring>
#include<cmath>
#include<memory>
#include<stdexcept>
#include<time.h>
#include<algorithm>
#include<iomanip>
#include<fstream>
using namespace std;
const int MAXN = 100000;
int N, K;
bitset<MAXN + 2> visited;
class CStep {
public:
	int x, father, steps;    //currentStepsΪ����x����Ĳ���
	CStep(int x_, int s_, int f_ = -1) :x(x_), steps(s_), father(f_) {
		visited.set(x);
	} 
};
bool operator<(const CStep &s1, const CStep &s2) {
	return s1.x < s2.x;
}
queue<CStep> q;      //open��
stack<CStep> close;
stack<int> result;
int main() {
	cin >> N >> K;   // Go from N to K
	clock_t startTime = clock();
	q.push(CStep(N, 0));
	int currentStep = 1, succeed = 0;
	CStep current = q.front(); 
	while (!q.empty()) {    //ֻҪ���зǿ�,���ܼ�����
		current = q.front();      //1.ȡ���׽ڵ�
		close.push(current);
		currentStep = current.steps;
		if (current.x == K) {     //2.�ж�Ŀ��״̬
			succeed = 1;
			break;
		}   
		if (current.x > 1 && !visited[current.x - 1])      //3.��չ�½ڵ� 
			q.push(CStep(current.x - 1, currentStep, current.x)); //��Ҫ�ݹ�˼·!��ѹ�����
		if (current.x < MAXN && !visited[current.x + 1])   //A currentStep forward from s
			q.push(CStep(current.x + 1, currentStep, current.x));
		if (2 * current.x <= MAXN && !visited[2 * current.x]) //A double currentStep from s
			q.push(CStep(2 * current.x, currentStep, current.x));
		q.pop();           //4.�����׽ڵ�
	}
	if (succeed == 0) {    //5.����ʧ�����    
		cout << "Impossible" << endl;
		return 0;
	}
	else {
		CStep tmp = close.top();     //��������result
		result.push(tmp.x);
		while (!close.empty()) {     //��close������ͳ������ǲ�����������(x=tmp.father)
			if (close.top().x == tmp.father) {    //1.�ж���ʱĿ��״̬,ѹջ
				tmp = close.top();
				result.push(tmp.x);
			}
			close.pop();             //2.�����׽ڵ�
		}
		while (!result.empty()) {
			cout << result.top();
			if (result.size() > 1)cout << " -> ";
			else cout << endl;
			result.pop();
		}
	}
	clock_t endTime = clock();
	cout<< "���������ʱ��:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	return 0;
}
