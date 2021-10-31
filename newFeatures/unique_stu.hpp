#pragma GCC diagnostic error "-std=c++11"
#include <iostream>
#include <algorithm>
#include <memory>
#include <vector>
#include <stdio.h>
using namespace std;

class Stu {
public:
    int id;
    Stu() {printf("cons --, addr=%p\n", this);}
    explicit Stu(int id_): id(id_) {printf("cons Stu(%d), addr=%lx\n", id_, ((long unsigned)this)%(16*16*16));}

    Stu(const Stu &s) = delete;
    Stu(Stu &&s) {    // Move copy
        printf("move copy %d, %p->%p\n", s.id, &s, this);
        id = s.id;
        s.id = -1;
    }
    Stu& operator=(const Stu &s) = delete;
    Stu& operator=(Stu &&s) { // Move assign
        printf("move assign %d, %p->%p\n", s.id, &s, this);
        id = s.id;
        s.id = -1;
        return *this;
    }
    ~Stu() {
        printf("des %d\n", id);
    }
};