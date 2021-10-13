#include <iostream>
#include <algorithm>
#include <thread>
#include <memory>
#include <vector>
using namespace std;
class Stu {
public:
    int id;
    Stu() {
        printf("cons --, addr=%p\n", this);
    }
    explicit Stu(int id_): id(id_) {
        printf("cons %d, addr=%p\n", id, this);
    }
    Stu(const Stu &s) {
        printf("copy %d, %p->%p\n", s.id, &s, this);
        id = s.id;
    }
    Stu(const Stu &&s) {
        printf("move copy %d, %p->%p\n", s.id, &s, this);
        id = s.id;
    }
    void operator=(const Stu &s) {
        printf("assign %d, %p->%p\n", s.id, &s, this);
        id = s.id;
    }
    void operator=(const Stu &&s) {
        printf("move assign %d, %p->%p\n", s.id, &s, this);
        id = s.id;
    }
    ~Stu() {
        // printf("des %d\n", id);
    }
};

void EmplaceDemo() {
    vector<Stu> stus;
    for (int i=0; i<5; i++) {
        printf("\ni=%d\n", i);
        stus.emplace_back(i);
    }
}

Stu GetStu(int id) {
    printf("GetStu...\n");
    // Stu s1(id);
    // printf("addr of GetStu::s1 is %p\n", &s1);
    // s1.id++;
    // Stu s2(-id);
    // return id % 2 == 0 ? s1 : s2;
    return Stu(id);
}

int main() {
    register long unsigned rsp asm("rsp");
    printf("main::%%esp=%lx\n", rsp);
    
    Stu s = GetStu(-214);
    
    // printf("main::addr(s)=%p\n", &s);

    printf("Finished\n");
    return 0;
}