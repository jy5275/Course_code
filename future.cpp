// future example
#include <iostream>       // cout
#include <future>         // async, future
#include <chrono>         // chrono::milliseconds
using namespace std;

// a non-optimized way of checking for prime numbers:

void FutureDemo() {
    // call function asynchronously:
	auto is_prime = [](int x)->bool {
		for (int i=2; i<x; ++i) if (x%i==0) return false;
		return true;
	};
    future<bool> fut = async(launch::async, is_prime, 444444443); 

    // do something while waiting for function to set future:
    cout << "checking, please wait" << endl;
    chrono::milliseconds span(100);
    future_status s;
    while (true) {
		s = fut.wait_for(span);
		if (s == future_status::timeout) {
			cout << '.' << flush;
		} else if (s == future_status::ready) {
			cout << "ok" << endl;
			break;
		} else if (s == future_status::deferred) {
			cout << "deferred" << endl;
			break;
		}
    }
    bool x = fut.get();     // retrieve return value
    cout << "444444443 " << (x?"is":"is not") << " prime.\n";
}

void PromiseDemo() {
	promise<int> p;
	future<int> f = p.get_future();

	auto prepFun = [](promise<int> &p) {
		this_thread::sleep_for(chrono::seconds(2));
		p.set_value(47);
	};
	auto consFun = [](future<int> &f) {
		while (f.wait_for(chrono::milliseconds(100)) == future_status::timeout)
			cout << "." << f.valid() << flush;
		cout << endl << f.get() << f.valid() << endl;
	};
	thread prepData(prepFun, ref(p));
	thread consData(consFun, ref(f));
	prepData.join();
	consData.join();
	cout << "Finish" << endl;
}

int main () {
	FutureDemo();
	return 0;
}