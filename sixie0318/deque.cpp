#include <atomic>
#include <iostream>
#include <thread>
using namespace std;

class Deque{
    atomic<int> head, tail;
    int arr[100];
public:
    Deque() {
        head.store(0);
        tail.store(0);
    }
    void push(int v) {
        int cur_t = tail.load();
        while(!tail.compare_exchange_strong(cur_t, cur_t+1)) {
            cur_t = tail.load();
        }
        arr[cur_t+1] = v;
    }
    int pop() {
        int cur_h = head.load();
        int cur_t = tail.load();
        if (cur_h >= cur_t) {
            return -1;
        }
        while(!head.compare_exchange_strong(cur_h, cur_h+1)) {
            cur_h = head.load();
            cur_t = tail.load();
            if (cur_h >= cur_t) {
                return -1;
            }
        }
        return arr[cur_h+1];
    }
};

void p(Deque &d, int i) {
    d.push(i);
}

void o(Deque &d) {
    cout << d.pop() << endl;
}

int main () {
    Deque d;
    thread pushs[5];
    for (int i=0; i<5; i++)
        pushs[i] = thread(p, d, i);
    
    for (auto &t:pushs)
        t.join();

    
    return 0;
}