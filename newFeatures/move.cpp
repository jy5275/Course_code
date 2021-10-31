#pragma GCC diagnostic error "-std=c++11"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <utility>
#include "stu.hpp"

using namespace std;

void Print(int &n) {
    cout << "Left Value:" << n << endl;
}

void Print(int &&n) {
    cout << "Right Value:" << n << endl;
}

int main() {
    int a = 12;
    Print(a);
    Print(12);
    Print(move(a)); // Move converts a lval to a tmp rval

    Stu s1(13);     // Constructor called
    Stu s2 = s1;    // Copy constructor called
    Stu s3 = move(s1);  // Move copy constuctor called

    return 0;
}