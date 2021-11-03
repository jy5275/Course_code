#include <mutex>
#include <condition_variable>
using namespace std;

class RWLock  { 
    mutex rmu;  
    mutex wmu;  
    int readCnt = 0;

public:  
    RWLock() = default;
    void readLock() {
        rmu.lock();
        readCnt++;
        if (readCnt == 1)
            wmu.lock();
        rmu.unlock();  
    }
  
    void readUnlock() {
        rmu.lock();
        readCnt--;
        if (readCnt == 0)
            wmu.unlock();  
        rmu.unlock();
    }
  
    void writeLock() {
        wmu.lock();  
    }
  
    void writeUnlock() {
        wmu.unlock();  
    }
};  
