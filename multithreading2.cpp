#include"semaphore.h"
#include<iostream>
#include<thread>
#include<chrono>
using namespace std;
semaphore t(0);
void printid(int id) {
	cout << "Thread " << id << " Yay ! Just spawned, calling t.wait()" << endl;
	t.wait();
	cout << "Thread " << id << endl;
//	cout << "Thread " << id << " Yay ! Finished job calling t.notify()" << endl;
//	cout << "Thread " << id << " Yay ! Exiting without calling t.notify()" << endl;
//	t.notify();
}
int main(int argc, char* argv[]) {
	thread threads[5];
	cout << "Main thread : Initial Semaphore count is " << t.returnCount() << endl;

	for (int i=0; i<5; i++) {
		threads[i] = thread(printid, i+1);
	}
	cout << "Main thread : Spawned threads !  Now Sleeping for 5 seconds" << endl;
	this_thread::sleep_for (chrono::seconds(5));
	cout << "Main thread : Awake from sleep, now calling t.notify" << endl;
	for (auto& th : threads) {
		t.notify();
	}

	for (auto& th : threads) {
		th.join();
	}
	cout << "Main thread : Final Semaphore count is " << t.returnCount() << endl;
	cout << "Main thread : Initial Semaphore count is " << t.returnCount() << endl;

	for (int i=0; i<5; i++) {
		threads[i] = thread(printid, i+1);
	}
	cout << "Main thread : Spawned threads !  Now Sleeping for 5 seconds" << endl;
	this_thread::sleep_for (chrono::seconds(5));
	cout << "Main thread : Awake from sleep, now calling t.notify(#)" << endl;
	t.notify(5);

	for (auto& th : threads) {
		th.join();
	}
	cout << "Main thread : Final Semaphore count is " << t.returnCount() << endl;
	return 0;
}
