/*����
Ϊ��ӭ��08��İ��˻ᣬ�ô�Ҹ����˽���ָ��˶���facer�¿���һ����Ѫ�񶷳���
�񶷳�ʵ�л�Ա�ƣ����������Ļ�Ա����Ҫ�����ѣ���ֻҪͬһ���ϻ�Ա��һ����������֤���Լ���ʵ��

���Ǽ���񶷵�ʵ��������һ����������ʾ����Ϊʵ��ֵ�����⣬ÿ���˶���һ��Ψһ��id��Ҳ��������
Ϊ��ʹ�ñ������ÿ���ÿ���¶�Ա����ѡ������ʵ����Ϊ�ӽ����˱�������˫��ʵ��ֵ��ľ���ֵԽСԽ��
����������˵�ʵ��ֵ���������ͬ��������ѡ����������Ǹ�����Ȼ��Ű�˱ر�Ű�ã�

���ҵ��ǣ�Facerһ��С�İѱ�����¼Ū���ˣ��������������Ż�Ա��ע���¼��
���������facer�ָ�������¼������ʱ��˳���������ÿ������˫����id��

����
��һ��һ����n(0 < n <=100000)����ʾ�񶷳������Ļ�Ա����������facer����
�Ժ�n��ÿһ������������������ʱ�������Ա��id��ʵ��ֵ��һ��ʼfacer�ǻ�Ա��idΪ1��
ʵ��ֵ1000000000�����뱣֤���˵�ʵ��ֵ��ͬ��

���
N�У�ÿ����������Ϊÿ������˫����id�����ֵ�idд��ǰ�档*/
#include<iostream>
#include<vector>
#include<string>
#include<set>
#include<list>
#include<map>
#include<algorithm>
using namespace std;
map<int, int> *pMembers = new map<int, int>;
map<int, int>::iterator pNew = pMembers->begin();
int main() {
	int n; cin >> n;
	pMembers->insert(pair<int, int>(1000000000, 1));
	while (n--) {
		int id, strength, anteDelta, postDelta;
		cin >> id >> strength;
		pMembers->insert(pair<int, int>(strength, id));
		pNew = pMembers->find(strength);
		if (pNew == pMembers->begin())     //��������
			++pNew;
		else {
			--pNew; anteDelta = abs(pNew->first - strength);
			++pNew; ++pNew;
			if (pNew == pMembers->end()) {    //����ǿ��
				--pNew; --pNew;
			}
			else {
				postDelta = abs(pNew->first - strength);
				--pNew;
				if (anteDelta > postDelta) ++pNew; //ǰ�ߵ�̫����,����ߵ�ǿ�ִ�
				else --pNew;   //��߹�ǿ��ǰ����һ��,��ǰ�����ִ�
			}
		}
		cout << id << " " << pNew->second << endl;
	}
	return 0;
}