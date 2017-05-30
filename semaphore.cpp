#include"semaphore.h"

semaphore::semaphore(unsigned long _count) : count(_count) {}

void semaphore::notify() {
	std::unique_lock<std::mutex> lck(mtx);
	count++;
	lck.unlock();
	cv.notify_one();
}

void semaphore::notify(unsigned long _count) {
	std::unique_lock<std::mutex> lck(mtx);
	count = _count;
	lck.unlock();
	cv.notify_all();
}

void semaphore::wait() {
	std::unique_lock<std::mutex> lck(mtx);
	while (!count)
		cv.wait(lck);
	count--;
}

unsigned long semaphore::returnCount() {
	std::unique_lock<std::mutex> lck(mtx);
	return count;
}

bool semaphore::try_wait() {
	std::unique_lock<std::mutex> lck(mtx);
	if (count) {
		count--;
		return true;
	}
	return false;
}
