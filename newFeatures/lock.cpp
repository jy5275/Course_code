#include <mutex>
#include <thread>
#include <chrono>
#include <iostream>
#include <string>
#include <atomic>
using namespace std;

class bank_account {
public:
    string sName;
    int iMoney;
    mutex mMutex;//账户都有一个锁mutex
    explicit bank_account(string name, int money){
        sName = name;
        iMoney = money;
    }
};

void transfer( bank_account &from, bank_account &to, int amount ) {
    unique_lock<mutex> lock1( from.mMutex, defer_lock );//defer_lock表示延迟加锁，此处只管理mutex
    unique_lock<mutex> lock2( to.mMutex, defer_lock );
    lock( lock1, lock2 );//lock一次性锁住多个mutex防止deadlock
    from.iMoney -= amount;
    to.iMoney += amount;
    cout << "Transfer " << amount << " from "<< from.sName << " to " << to.sName << endl;
}

int main(){
    bank_account Account1( "User1", 100 );
    bank_account Account2( "User2", 50 );
    thread t1( [&](){ transfer( Account1, Account2, 10 ); } ); //lambda表达式
    thread t2( [&](){ transfer( Account2, Account1, 5 ); } );
    t1.join();
    t2.join();
}