// you can use includes, for example:
// #include <algorithm>
#include <unordered_map>
#include <iostream>
using namespace std;
// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

int solution(vector<int> &A) {
    // write your code in C++14 (g++ 6.2.0)
    vector<int> arr;
    unordered_map<int, int> idx, cnt;
    int tmpMax = 1;
    for (int i=1; i<A.size(); i++) {
        arr.push_back(A[i-1] + A[i]);
    }
    for (int i=0; i<arr.size(); i++) {
        int val = arr[i];
        auto it = idx.find(val);
        if (it == idx.end()) {
            // New value
            cnt[i] = 1;
            idx[val] = i;
        } else {
            if (it->second == i-1) {
                // Two adjancent nums are equal
                cnt[i] = cnt[it->second];
                tmpMax = max(tmpMax, cnt[i]);
            } else {
                // Different
                cnt[i] = cnt[it->second] + 1;
                tmpMax = max(tmpMax, cnt[i]);
                idx[val] = i;
            }
        }
        // printf("cnt[%d] set to %d\n", i, cnt[i]);
    }
    return tmpMax;
}
