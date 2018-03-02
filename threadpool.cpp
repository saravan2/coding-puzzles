//Credit : https://www.reddit.com/r/cpp/comments/6coxue/implementing_a_thread_pool_in_c/
//Credit : http://coliru.stacked-crooked.com/a/0e37a97e43def6be
#include "threadpool.h"
#include <chrono>
#include <cstdio>

int main(int argc, char *argvp[]) {
	Threadpool tp;
	Job j;
	j.submit_task(tp, []{\
			printf("1\n");\
			std::this_thread::sleep_for(std::chrono::seconds(2));\
			printf("2\n");\
			});
	j.submit_task(tp, []{\
			printf("3\n");\
			std::this_thread::sleep_for(std::chrono::seconds(1));\
			printf("4\n");\
			});
	printf("Done\n");
	return 0;
}
