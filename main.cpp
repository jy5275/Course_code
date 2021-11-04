#include <unordered_map>
#include <iostream>
#include <ctime>
#include <string>
#include <algorithm>
#include "newFeatures/stu.hpp"
using namespace std;
const int MAX = 20;

int MyHash(const int &x) {
    printf(".");
    if (x == 10) { return 2;}
    return x / 10;
    // return hash<int>()(x);
}

int MyStrHash(const string &s) {
    printf(".");
    return hash<string>()(s);
}

void JumpTest() {
    int lastSz = 2;
    unordered_map<int, int, decltype(&MyHash)> m(lastSz, MyHash);
    m.max_load_factor(2);
    for (int i=0; i<MAX; i++) {
        m.insert(make_pair(i, 101));
        if (m.bucket_count() != lastSz) {  // Scale up here!
            printf("%d: sz=%lu, bucket_count=%lu\n", i, m.size(), m.bucket_count());
            lastSz = m.bucket_count();
        } else {
            printf("%d: sz=%lu\n", i, m.size());
        }
        for (auto it = m.begin(); it != m.end(); ++it) {
            // printf("%d->[%lu], ", it->first, m.bucket(it->first));
        } printf("\n");
        for (int i=0; i<m.bucket_count(); i++) {
            printf("【%d】:%lu, ", i, m.bucket_size(i));
        } printf("\n");
    }
} // Result: 5, 11, 23, 47, 97, 197, 397, 797, 1597, 3203, 6421, 12853, 25717, 51437, ...

void CopyTest() {
    unordered_map<int, Stu> m;
    int tmp = -1;
    for (int i=0; i<MAX; i++) {
        auto p = make_pair(i, Stu(i));
        m.insert(p);
        if (m.bucket_count() != tmp) {  // Scale up here!
            printf("%d: sz=%lu, bucket_count=%lu, ", i, m.size(), m.bucket_count());
            tmp = m.bucket_count();
        }
    }

}

void LatencyTest () {
    unordered_map<int, int> m;
    clock_t start = clock(), p0 = clock(), p1 = clock();
    double latency[MAX+10];

    for (int i=0; i<MAX; i++) {
        m.insert(make_pair(i, 101));
        p0 = p1;
        p1 = clock();
        latency[i] = (double)(p1-p0); // microsecond
    }
    clock_t p = clock();
    printf("Total latency: %.2lf\n", (double)(p-start) / CLOCKS_PER_SEC);
    double lowLimit = min(latency[797], min(latency[1597], min(latency[3203], latency[6421])));
    printf("Lower limit=%.2lf\n", lowLimit);

    for (int i=0; i<MAX; i++) {
        if (latency[i] >= lowLimit) printf("%d: time=%.2lf\n", i, latency[i]);
    }
}

int main() {
    JumpTest();
}