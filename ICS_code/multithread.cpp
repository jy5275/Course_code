#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<memory.h>
#include<thread>
#include<string.h>
#include<bitset>
#include<math.h>
#include<atomic>
using namespace std;
atomic_int atoval(0);
int val = 0;
void Add() {
	for (int i = 0; i < 1000000; i++)
		atoval.fetch_add(1);
}
int main() {
	for (int i = 0; i < 100; i++) {
		atoval.fetch_and(0);
		thread t1(Add), t2(Add);
		//this_thread::sleep_for(5s);
		t1.join(); t2.join();
		cout << atoval << endl;
		
	}
	return 0;
}