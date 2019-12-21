锘�#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <algorithm>
using namespace std;
int main(){
	string s1("hello");
	s1.length();
	string s2 = s1.substr(2, 3);
	string s3;
	s3.assign(s1, 2, 3);
	
	int loc = s1.find("lo");
	if (loc == (string::npos)) cout << "Search Failue" << endl;

	for (int i = 0; i < s1.length(); i++)
		cout << s1.at(i) << endl;
	int loc2 = s1.find_first_of("abcde");

	string inp("Input test 123 4.7 A");
	istringstream inpString(inp);
	string str1, str2;
	int i; double d; char c;
	inpString >> str1 >> str2 >> i >> d >> c;
	if (inpString >> d)cout << "not em" << endl;
	else cout << "empty" << endl;

	ostringstream outString;
	int a = 10;
	outString << "This " << a << "OK" << endl;
	cout << outString.str() << endl;

	cout << "Hello World!" << endl;
	return 0;
}
