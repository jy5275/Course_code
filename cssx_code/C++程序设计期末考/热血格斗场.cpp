/*描述
为了迎接08年的奥运会，让大家更加了解各种格斗运动，facer新开了一家热血格斗场。
格斗场实行会员制，但是新来的会员不需要交入会费，而只要同一名老会员打一场表演赛，证明自己的实力

我们假设格斗的实力可以用一个正整数表示，成为实力值。另外，每个人都有一个唯一的id，也是正整数
为了使得比赛更好看，每个新队员都会选择与他实力最为接近的人比赛，即双方实力值差的绝对值越小越好
如果有两个人的实力值与他差别相同，则他会选择比他弱的那个（显然，虐人必被虐好）

不幸的是，Facer一不小心把比赛记录弄丢了，但是他还保留着会员的注册记录。
现在请你帮facer恢复比赛纪录，按照时间顺序依次输出每场比赛双方的id。

输入
第一行一个数n(0 < n <=100000)，表示格斗场新来的会员数（不包括facer）。
以后n行每一行两个数，按照入会的时间给出会员的id和实力值。一开始facer是会员，id为1，
实力值1000000000。输入保证两人的实力值不同。

输出
N行，每行两个数，为每场比赛双方的id，新手的id写在前面。*/
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
		if (pNew == pMembers->begin())     //你最弱！
			++pNew;
		else {
			--pNew; anteDelta = abs(pNew->first - strength);
			++pNew; ++pNew;
			if (pNew == pMembers->end()) {    //你最强！
				--pNew; --pNew;
			}
			else {
				postDelta = abs(pNew->first - strength);
				--pNew;
				if (anteDelta > postDelta) ++pNew; //前边的太弱了,跟后边的强手打
				else --pNew;   //后边过强或前后差别一样,跟前边弱手打
			}
		}
		cout << id << " " << pNew->second << endl;
	}
	return 0;
}