#define _CRT_SECURE_NO_WARNINGS  
#include <iostream>
#include <set>
#include <string>
#include <bitset>
using namespace std;
class Member {
public:
	int id, shili;
	Member(int id_, int shili_) :id(id_), shili(shili_) {};
};
bool operator<(const Member &m1, const Member &m2) {
	return m1.shili < m2.shili;
}
int main() {
	set<Member> s;
	s.insert(Member(1, 100000000));
	int n; cin >> n;
	while (n--) {
		int id_, shili_, rival;
		cin >> id_ >> shili_;
		Member newer(id_, shili_);
		s.insert(newer);
		auto it1 = s.lower_bound(newer);
		auto it2 = s.upper_bound(newer);
		if (it1 == s.begin()) {
			rival = it2->id;
		}
		else {
			advance(it1, -1);		//【BUG1】比较的是前后的差值,忘了加abs！！！
			if (newer.shili - it1->shili <= it2->shili - newer.shili)
				rival = it1->id;
			else rival = it2->id;
		}
		cout << id_ << " " << rival << endl;
	}

	return 0;
}