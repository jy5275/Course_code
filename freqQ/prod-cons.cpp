#include <functional>
#include <iostream>
#include <algorithm>
#include <thread>
#include <memory>
#include <list>
#include <mutex>
#include <condition_variable>
using namespace std;

template<typename T>
class ProAndCon {
    list<T> m_queue;
    mutex m_mutex;  //全局互斥锁
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

    void produce(const T& v) {
        unique_lock<mutex> lck(m_mutex);

        while(isFull()) {
            cout << "Buffer is full, waiting..." << endl;
            // 生产者等待"缓冲区不为满"这一条件发生
            m_notFull.wait(lck);
        }
        m_queue.push_back(v);
        m_notEmpty.notify_one();
    }

    T consume() {
        unique_lock<mutex> locker(m_mutex);
        while(isEmpty()) {
            cout << "Buffer is empty, waiting..." << endl;
            // 消费者等待"缓冲区不为空"这一条件发生
            m_notEmpty.wait(locker);
        }
        T v = m_queue.front();
        printf("num = %d\n", v);
        m_queue.pop_front();
        m_notFull.notify_one();
        return v;
    }
};

int main() {
    const int NUM = 5;
    thread producers[NUM];
    ProAndCon<int> test(10);
    for (int i=0; i<NUM; i++) {
        producers[i] = thread(&ProAndCon<int>::produce, &test, i);
    }
    function<bool(int)> f = [&test](int n)->bool{
        for (int i=0; i<n; i++) {
            test.consume();
        }
        return true;
    };
    auto consumer = thread(f, NUM);

    for (int i=0; i<NUM; i++) {
        producers[i].join();
    }
    consumer.join();
    printf("Finished\n");
    return 0;
}