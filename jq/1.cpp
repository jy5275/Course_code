#include <iostream>
#include <set>
#include <math.h>

using namespace std;

int Part2(string str) {
    set<string> newCnt;
    if (str.size() <= 3) {
        return 1;
    }
    for (int i=2; i<str.size(); i++) {
        newCnt.insert(str.substr(i-2, 3));
    }
    return newCnt.size();
}

void Part3(string str) {
    int len = str.size();
    int height = ceil(sqrt(len));
    int width = height*2 - 1;
    int idx = 0;
    for (int y=0; y<height; y++) {
        for (int x=0; x<width; x++) {
            if (x + y + 2 > height && (width-x) + y + 1 > height 
                && idx < str.size()) {
                cout << str[idx++];
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }
}

int main () {
    string str = "asdfasdfasdfafafasdsdfsadfasdfgfafasdffasdfasdfafasasfedfafafasdfasd";
    set<char> counter;

    // Part 1
    for (int i=0; i < str.size(); i++) {
        counter.insert(str[i]);
    }
    cout << counter.size() << endl;

    // Part 2
    cout << Part2("abcbcbccccc") << endl;

    // Part 3
    Part3(str);

    return 0;
}