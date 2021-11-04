#include <mutex>
#include <condition_variable>
using namespace std;

class RWLock  { 
    mutex rmu, wmu;
    int readCnt = 0;
public:
    RWLock() = default;
    void readLock() {
        rmu.lock();
        readCnt++;
        if (readCnt == 1) wmu.lock();
        rmu.unlock();
    }

    void readUnlock() {
        rmu.lock();
        readCnt--;
        if (readCnt == 0) wmu.unlock();
        rmu.unlock();
    }

    void writeLock() { wmu.lock(); }
    void writeUnlock() { wmu.unlock(); }
};

class RWLock2 {
    mutex mtx;
    condition_variable cond;
    int stat;  // == 0 无锁；> 0 已加读锁个数；< 0 已加写锁
public:
    RWLock2(): stat(0) {}

    void readLock() {
        mtx.lock();
        while (stat < 0)  cond.wait(mtx);
        ++stat;
        mtx.unlock();
    }

    void readUnlock() {
        mtx.lock();
        if (--stat == 0) cond.notify_one(); // 叫醒一个等待的写操作
        mtx.unlock();
    }

    void writeLock() {
        mtx.lock();
        while (stat != 0) cond.wait(mtx);
        stat = -1;
        mtx.unlock();
    }

    void writeUnlock() {
        mtx.lock();
        stat = 0;
        cond.notify_all();   // 叫醒所有等待的读和写操作
        mtx.unlock();
    }
};
