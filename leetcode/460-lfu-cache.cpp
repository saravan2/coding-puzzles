
class LFUCache {
private:
    int capacity;
    unordered_map<int, std::list<std::pair<int, int>>> frequencyToCache;
    unordered_map<int, std::pair<int, std::list<std::pair<int, int>>::iterator>> keyToFrequencyCache; 
    int minFreq;

    void insert(int key, int value, int frequency) {
        frequencyToCache[frequency].push_back({key, value});
        std::list<std::pair<int, int>>::iterator it = std::prev(frequencyToCache[frequency].end());
        keyToFrequencyCache[key] = {frequency, it};
    } 
public:
    LFUCache(int capacity) : capacity(capacity), minFreq(0) {}
    
    int get(int key) {
        const auto & it = keyToFrequencyCache.find(key);
        if (it == keyToFrequencyCache.end()) {
            return -1;
        }

        const int frequency = it->second.first;
        const auto & cacheIter = it->second.second;
        const pair<int, int> kv = *cacheIter;
        frequencyToCache[frequency].erase(cacheIter);
        if (frequencyToCache[frequency].empty()) {
            frequencyToCache.erase(frequency);
            if (minFreq == frequency) {
                ++minFreq;
            }
        }
        insert(key, kv.second, (frequency + 1));
        return kv.second;
    }
    
    void put(int key, int value) {
        if (capacity <= 0) {
            return;
        }

        const auto & it = keyToFrequencyCache.find(key);
        if (it != keyToFrequencyCache.end()) {
            const auto & cacheIter = it->second.second;
            cacheIter->second = value;
            get(key);
            return;
        }

        if (capacity == keyToFrequencyCache.size()) {
            keyToFrequencyCache.erase(frequencyToCache[minFreq].front().first);
            frequencyToCache[minFreq].pop_front();

            if (frequencyToCache[minFreq].empty()) {
                frequencyToCache.erase(minFreq);
            }
        } 

        minFreq = 1;
        insert(key, value, minFreq);    
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */