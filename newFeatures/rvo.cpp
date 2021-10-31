#pragma GCC diagnostic error "-std=c++11"
#include <iostream>
#include <algorithm>
#include <memory>
#include <vector>
#include <stdio.h>
#include <utility>
#include "stu.hpp"
using namespace std;

void EmplaceDemo() {
    vector<Stu> stus;
    for (int i=0; i<5; i++) {
        printf("\ni=%d\n", i);
        // stus.emplace_back(i);
    }
}

/*
  No RVO if cannot determine which obj to be returned:
             ---------------
            |   caller's    |
            |    frame      | <---
     main   |               |     |
  ---------------------------------------
    GetStu  |   Stu(-id)    |     |
            | (to be        |    COPY
            |   destructed) |     |
             ---------------      |
            |   Stu(id)     |     |
            | (to be        | ----
            |   destructed) |
             ---------------
*/
Stu GetStuWithBranch(int id) {
    register long unsigned rsp asm("rsp");
    printf("GetStu::%%esp=%lx\n", rsp%(16*16*16));
    Stu s1(id);
    Stu s2(-id);
    return id % 2 == 0 ? s1 : s2;
}

Stu&& GetStuMoved(int id = -1) {
    Stu s(id);
    return move(s);
}

int main() {
    Stu s = GetStuWithBranch(12);
    printf("Finished, stu=%d, sizeof(Stu)=%ld\n", s.id, sizeof(s));
    return 0;
}