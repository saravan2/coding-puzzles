class FizzBuzz {
private:
    int n;
    int current;
    mutex l;
    condition_variable cv;

public:
    FizzBuzz(int n) {
        this->n = n;
        this->current = 1;
    }

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz) {
        unique_lock<mutex> lock(l);
        while (current <= n) {
            while ((current <= n) && !(!(current % 3) && (current % 5))) {
                cv.wait(lock);
            }
            if (current <= n) {
                printFizz();
                current++;
            }
            cv.notify_all();
        }
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz) {
        unique_lock<mutex> lock(l);
        while (current <= n) {
            while ((current <= n) && !(!(current % 5) && (current % 3))) {
                cv.wait(lock);
            }
            if (current <= n) {
                printBuzz();
                current++;
            }
            cv.notify_all();
        }
    }

    // printFizzBuzz() outputs "fizzbuzz".
	void fizzbuzz(function<void()> printFizzBuzz) {
        unique_lock<mutex> lock(l);
        while (current <= n) {
            while ((current <= n) && !(!(current % 3) && !(current % 5))) {
                cv.wait(lock);
            }
            if (current <= n) {
                printFizzBuzz();
                current++;
            }
            cv.notify_all();
        }
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber) {
        unique_lock<mutex> lock(l);
        while (current <= n) {
            while ((current <= n) && !((current % 3) && (current % 5))) {
                cv.wait(lock);
            }
            if (current <= n) {
                printNumber(current);
                current++;
            }
            cv.notify_all();
        }
    }
};
