#include<iostream>
#include<cstdlib>
#include<list>
#include<unordered_map>
#include<climits>
using namespace std;

class lru {
private:
	int capacity;
	list<pair<int,int>> cache;
	unordered_map<int, list<pair<int,int>>::iterator> map; 
	
	int getValueAndRearrangeCache(int key) {
		auto it = map.find(key);
		if (it != map.end()) {
			int value = it->second->second;
			cache.splice(cache.begin(), cache, it->second);
			return value;
		}
		return INT_MIN;
	}

public:
	lru(int capacity) {
		this->capacity = capacity;
	}
	int get(int key) {
		return getValueAndRearrangeCache(key);
	}
	void set(int key, int value) {
		if(get(key) != INT_MIN) {
			cache.front().second = value;
		} else {
			cache.push_front(pair<int, int>(key, value));
			map[key] = cache.begin();
			if (cache.size() > capacity) {
				map.erase(cache.back().first);
				cache.pop_back();
			}
		}
	}

	void printCache() {
		cout << "Printing cache" << endl;
		for (auto it = cache.begin(); it != cache.end(); it++) {
			cout << "Key " <<  it->first << " Store  " << it->second << endl;
		}
	}
};	

int main(int argc, char *argv[]) {
	int capacity = 3;
	if (argc > 1) {
		capacity = atoi(argv[1]);	
	}
 
	lru LRU(capacity);
	for (int i = 0; i < (2*capacity); i++) {
		cout << "Inserting : " << i << " " << i+10 << " " << endl; 
		LRU.set(i, i+10);
	}

	cout << "Verifying the cache" << endl;	
	for (int i = 0; i < (2*capacity); i++) {
		cout << "For key " <<  i << " " << " cache returns " << LRU.get(i) << endl;
	}

	LRU.printCache();

	cout << "Inserting : " << 6 << " " << 100 << " " << endl; 
	LRU.set(6, 100);

	LRU.printCache();

	return 0;
}
