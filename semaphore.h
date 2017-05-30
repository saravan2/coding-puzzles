#ifndef SEMAPHORE_H
#define SEMAPHORE_H
#include<mutex>
#include<condition_variable>

class semaphore {
private:
	std::mutex mtx;
	std::condition_variable cv;
	unsigned long count;
public:
	semaphore(unsigned long _count = 0);
	void notify();
	void notify(unsigned long _count);
	void wait();
	bool try_wait();
	unsigned long returnCount();
};
#endif
