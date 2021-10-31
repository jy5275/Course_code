#include <iostream>
#include <algorithm>
#include <mutex>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <atomic>
#include <thread>

using namespace std;

// Both kinds of singleton init are OK.
// V0 depends on the compiler version though.
class SingNodeV0 {
    int val;
    static int cnt;
    SingNodeV0(int _val = -1) {
        sleep(1);
        val = _val;
        this->cnt++;
    }
public:
    static int get_cnt() {return cnt;}
    static SingNodeV0* GetInstance() {
        static SingNodeV0 *p = new SingNodeV0(15);
        return p;
    }
};

class SingNodeV1 {
    static SingNodeV1 *p;
    int val;
    static int cnt;
    SingNodeV1(int _val = -1) {
        sleep(1);
        val = _val;
        this->cnt++;
    }
public:
    static int get_cnt() {return cnt;}
    static SingNodeV1* GetInstance() {
        static atomic_bool done(false);
        static mutex mu;
        if (!done.load()) {
            mu.lock();
            if (!done.load()) {
                p = new SingNodeV1(12);
                done.store(true);
            }
            mu.unlock();
        }
        return p;
    }
};

int SingNodeV1::cnt = 0;
SingNodeV1* SingNodeV1::p = NULL;
int SingNodeV0::cnt = 0;

void FuncV0() {
    SingNodeV0 *p = SingNodeV0::GetInstance();
    printf("cnt=%d, obj_addr=%p\n", p->get_cnt(), p);
}

void FuncV1() {
    SingNodeV1 *p = SingNodeV1::GetInstance();
    printf("cnt=%d, obj_addr=%p\n", p->get_cnt(), p);
}

int main() {
    const int THNUM = 20;
    thread ths[THNUM];
    for (int i=0; i<THNUM; i++) {
        ths[i] = thread(FuncV0);
    }
    for (int i=0; i<THNUM; i++) {
        ths[i].join();
    }

    printf("finish\n");
    return 0;
}