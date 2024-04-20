class HitCounter {
private:
    int total;
    std::queue<pair<int, int>> hits;
public:
    HitCounter() {
        this->total = 0;
    }
    
    void hit(int timestamp) {
        if (this->hits.empty() || this->hits.back().first != timestamp) {
            this->hits.push({timestamp, 1});
        } else {
            this->hits.back().second++;
        }
        this->total++;
    }
    
    int getHits(int timestamp) {
        while (!this->hits.empty()) {
            int diff = timestamp - this->hits.front().first;
            if (diff >= 300) {
                this->total -= this->hits.front().second;
                this->hits.pop();
            } else {
                break;
            } 

        }
        return this->total;
    }
};

/**
 * Your HitCounter object will be instantiated and called as such:
 * HitCounter* obj = new HitCounter();
 * obj->hit(timestamp);
 * int param_2 = obj->getHits(timestamp);
 */