#include <functional>
#include <iostream>
#include <algorithm>
#include <thread>
#include <memory>
#include <list>
#include <mutex>
#include <unistd.h>
#include <condition_variable>
using namespace std;

template<typename T>
class ProAndCon {
    list<T> m_queue;
    mutex mu;  //全局互斥锁
    condition_variable m_notEmpty; //全局条件变量（不为空）
    condition_variable m_notFull;  //全局条件变量（不为满）
    int m_maxSize;  //队列最大容量

    bool isEmpty() const {
        return m_queue.empty();
    }
    bool isFull() const {
        return m_queue.size() == m_maxSize;
    }

public:
    ProAndCon(int maxSize) {
        this->m_maxSize = maxSize;
    }
    ProAndCon() = default;

    /* Producer:
       1. Acquire global mutex
       2. Wait until not full
       3. Put the obj
       4. Notify that buffer is not empty
    */
    void produceOne(const T& v) {
        unique_lock<mutex> lck(mu);

        while(isFull()) {
            cout << "Buffer is full, waiting..." << endl;
            // 生产者等待"缓冲区不为满"这一条件发生
            m_notFull.wait(lck);
        }
        m_queue.push_back(v);
        m_notEmpty.notify_one();
    }

    T consumeOne() {
        unique_lock<mutex> lck(mu);
        while(isEmpty()) {
            cout << "Buffer is empty, waiting..." << endl;
            // 消费者等待"缓冲区不为空"这一条件发生
            m_notEmpty.wait(lck);
        }
        T v = m_queue.front();
        m_queue.pop_front();
        m_notFull.notify_one();
        return v;
    }
};

int main() {
    const int NUM = 10;
    thread producers[NUM];
    ProAndCon<int> test(3);

    // Launch producers
    for (int i=0; i<NUM; i++) {
        producers[i] = thread(&ProAndCon<int>::produceOne, &test, i*i);
    }

    // Launch one consumer
    function<bool(int)> consumeFun = [&test](int n)->bool{
        for (int i=0; i<n; i++) {
            int v = test.consumeOne();
            sleep(1);
            printf("[%d] num = %d\n", i, v);
        }
        return true;
    };
    auto consumer = thread(consumeFun, NUM);

    // Wait for all threads exit
    for (int i=0; i<NUM; i++) {
        producers[i].join();
    }
    consumer.join();

    printf("Finished\n");
    return 0;
}