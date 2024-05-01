//Credit : https://www.reddit.com/r/cpp/comments/6coxue/implementing_a_thread_pool_in_c/
//Credit : http://coliru.stacked-crooked.com/a/0e37a97e43def6be
#include <cstddef>
#include <thread>
#include <deque>
#include <vector>
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <functional>

class Threadpool {
	public:
		using task_t = std::function<void(void)>;
	private:
		std::vector<std::thread> threads;
		std::atomic_bool	stopFlag{false};
		std::deque<task_t>	tasks;
		std::mutex	mtx;
		std::condition_variable	cv;

		void worker_main() {
			std::unique_lock<std::mutex> lock(mtx);
			while (1) {
				cv.wait(lock);
				while(!tasks.empty()) {
					task_t t = std::move(tasks.front());
					tasks.pop_front();
					lock.unlock();
					t();
					lock.lock();
				}
				if (stopFlag)
					break;
			}
		}
	public:
		Threadpool() {
			size_t tCount = std::max<size_t>(std::thread::hardware_concurrency(), 1);
			threads.reserve(tCount);
			for (size_t i = 0; i < tCount; i++) {
				threads.emplace_back(&Threadpool::worker_main, this);
			}
		}
		~Threadpool() {
			stopFlag = true;
			{
				std::lock_guard<std::mutex> lock(mtx);
				tasks.clear();
			}
			cv.notify_all();
			for (auto& t : threads) {
				t.join();
			}
		}
		Threadpool(const Threadpool&) = delete;
		Threadpool& operator=(const Threadpool&) = delete;
		void submit_task(task_t task) {
			{
				std::lock_guard<std::mutex> lock(mtx);
				tasks.push_back(std::move(task));
			}
			cv.notify_one();

		}
};

class Job {
	private:
		std::condition_variable cv;
		std::mutex mtx;
		std::atomic<size_t> tc{0};
		void on_task_complete() {
			if (--tc == 0) {
				std::lock_guard<std::mutex> lock(mtx);
			}
			cv.notify_one();
		}
	public:
		Job() = default;
		
		~Job() {
			wait_to_complete();
		}
		
		bool is_complete() const {
			return tc == 0;
		}

		void wait_to_complete() {
			if (!is_complete()) {
				std::unique_lock<std::mutex> lock(mtx);
				cv.wait(lock, [this] { return this->is_complete(); });
			}
		}
		void submit_task(Threadpool& pool, Threadpool::task_t task) {
			tc++;
			pool.submit_task([this, t = std::move(task)] {
					t();
					this->on_task_complete();
				});
		}
};
