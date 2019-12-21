#define _CRT_SECURE_NO_WARNINGS  
#include<iostream>
#include<string>
#include<cmath>
#include<map>
#include<set>
#include<algorithm>
using namespace std;
//multimap中的元素由<关键字，值>组成，每个元素是一个pair对象
class CStudent {
	int id;
	string sName;
	friend void MyQuery();
public:
	CStudent(string &str_, int id_) :sName(str_), id(id_) {}
};
typedef multimap<int, CStudent> MAP_STD;
multimap<int, CStudent> mapCourse;		//所有学生按score排序
void MyAdd() {
	string str_;
	int score_, id_;
	cin >> str_ >> id_ >> score_;
	mapCourse.insert(pair<int, CStudent>(score_, CStudent(str_, id_)));
}
void MyQuery() {
	int score; cin >> score;
	MAP_STD::iterator p = mapCourse.lower_bound(score);	//[begin,p)的人分数<score
	if (p == mapCourse.begin()) {
		cout << "Nobody" << endl; return;
	}
	--p;
	score = p->first;  //下面开始寻找同score下最大的id
	MAP_STD::iterator maxp = p;
	int max_id = p->second.id, stopNextLoop = 0;
	for (; stopNextLoop == 0 && p->first == score; --p) {  //开始遍历同score的记录
		if (p == mapCourse.begin()) stopNextLoop = 1;      //这个Loop到起点了,下次停了！
		if (p->second.id > max_id) {   //找到一个记录，学号比p指向的学号大！
			max_id = p->second.id;
			maxp = p;
		}
	}
	/*if (p->first == score) { //对于因p==mapCourse.begin()而终止的循环，还要看看begin是否符合！
	if (p->second.id > max_id) {
	max_id = p->second.id;
	maxp = p;
	}
	}*/
	cout << maxp->second.sName << " " << maxp->second.id << " " << maxp->first << endl;
}
int main() {
	string exe;
	while (cin >> exe) {
		if (exe == "Add") MyAdd();
		else if (exe == "Query") MyQuery();
		//查询分数小于score_的最高分学生信息
		//如果有多人,输出id最大的学生信息
	}
	return 0;
}


//用map无法做到二级排序(相同score下以Num排序)，只能手动寻找相同关键字中的Max
//用set/multiset也可以完成，只不过查找时需生成一个CStudent类来和set中元素比较
/*
class CStudent {
	int id, score;
	string sName;
	friend void MyQuery();
	friend bool operator<(const CStudent &s1, const CStudent &s2);
public:
	CStudent(string str_, int sN_, int score_) :sName(str_), id(sN_), score(score_) {}
};
bool operator<(const CStudent &s1, const CStudent &s2) {
	if (s1.score != s2.score)return s1.score < s2.score;
	else return s1.id < s2.id;
}
set<CStudent> setCourse;
void MyAdd() {
	string str_;
	int score_, sN_;
	cin >> str_ >> sN_ >> score_;
	setCourse.insert(CStudent(str_, sN_, score_));
}
void MyQuery() {
	int score; cin >> score;
	set<CStudent>::iterator p = setCourse.lower_bound(CStudent("Tmp", 100000, score));
	if (p == setCourse.begin()) { cout << "Nobody" << endl; return; }
	--p;
	cout << p->sName << " " << p->id << " " << p->score << endl;
}
int main() {
	string exe;
	while (cin >> exe) {
		if (exe == "Add") MyAdd();
		else if (exe == "Query") MyQuery();
	}
	return 0;
}*/
