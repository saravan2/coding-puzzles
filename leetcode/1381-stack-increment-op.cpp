class CustomStack {
private:
    int max;
    std::deque<long> stack;
    std::deque<long> increments;
public:
    CustomStack(int maxSize) : max(maxSize) {
    }
    
    void push(int x) {
        if (stack.size() < max) {
            stack.push_front(x);
            increments.push_front(0);
        }
    }
    
    int pop() {
        if (stack.empty()) {
            return -1;
        }
        long increment = increments.front();
        increments.pop_front();
        if (!increments.empty()) {
            increments.front() += increment;
        }
        int value = stack.front() + increment;
        stack.pop_front();
        return value;
    }
    
    void increment(int k, int val) {
        if (k > max) {
            k = max;
        }
        if (!stack.empty()) {
            if (k > stack.size()) {
                k = stack.size();
            }
            int offset = stack.size() - k;
            auto incr_itr = increments.begin() + offset;
            *incr_itr += val;
        }
    }
};

/**
 * Your CustomStack object will be instantiated and called as such:
 * CustomStack* obj = new CustomStack(maxSize);
 * obj->push(x);
 * int param_2 = obj->pop();
 * obj->increment(k,val);
 */