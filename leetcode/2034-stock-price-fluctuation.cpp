class StockPrice {
private:
    int latestTime;
    std::unordered_map<int, int> priceAtTime;
    std::priority_queue<pair<int, int>> maxHeap;
    std::priority_queue<pair<int, int>, vector<pair<int, int>>, std::greater<>> minHeap;
public:
    StockPrice() {
        latestTime = 0;
    }
    
    void update(int timestamp, int price) {
        latestTime = std::max(latestTime, timestamp);
        priceAtTime[timestamp] = price;
        pair<int, int> update = std::make_pair(price, timestamp);
        minHeap.push(update);
        maxHeap.push(update);
    }
    
    int current() {
        return priceAtTime[latestTime];
    }
    
    int maximum() {
        pair<int, int> maximum = maxHeap.top();
        while (priceAtTime[maximum.second] != maximum.first) {
            maxHeap.pop();
            maximum = maxHeap.top();
        }
        return maximum.first;
    }
    
    int minimum() {
        pair<int, int> minimum = minHeap.top();
        while (priceAtTime[minimum.second] != minimum.first) {
            minHeap.pop();
            minimum = minHeap.top();
        }
        return minimum.first;
    }
};

/**
 * Your StockPrice object will be instantiated and called as such:
 * StockPrice* obj = new StockPrice();
 * obj->update(timestamp,price);
 * int param_2 = obj->current();
 * int param_3 = obj->maximum();
 * int param_4 = obj->minimum();
 */