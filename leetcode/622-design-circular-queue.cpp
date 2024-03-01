class MyCircularQueue {
private:
    int head;
    int size;
    int filled;
    vector<int> circular;

public:
    MyCircularQueue(int k) {
        size = k;
        filled = 0;
        head = 0;
        circular.resize(size);    
    }
    
    bool enQueue(int value) {
        if (isFull()) {
            return false;
        }
        circular[(head + filled) % size] = value;
        filled++;
        return true;
    }
    
    bool deQueue() {
        if (isEmpty()) {
            return false;
        }

        head = (head + 1) % size;
        filled--;
        return true;
    }
    
    int Front() {
        if (isEmpty()) {
            return -1;
        }
        return circular[head];
    }
    
    int Rear() {
        if (isEmpty()) {
            return -1;
        }
        return circular[(head + filled - 1) % size];
    }
    
    bool isEmpty() {
        return !filled;
    }
    
    bool isFull() {
        return (filled == size);
    }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */