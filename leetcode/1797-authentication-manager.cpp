
class AuthenticationManager {
    
private:
    int timeToLive;
    std::unordered_map<std::string, int> liveTokens;
    struct compareGreaterThan {
        public:
        bool operator()(const std::pair<string, int>& a, const std::pair<string, int>& b) {
            return (a.second > b.second);
        }
    };
    std::priority_queue<std::pair<string, int>, std::vector<std::pair<string, int>>, compareGreaterThan> pq;

    void removeExpiredTokens(int currentTime) {
        while (!pq.empty()) {
            if (pq.top().second <= currentTime) {
                if (liveTokens[pq.top().first] <= currentTime) {
                    liveTokens.erase(pq.top().first);
                }
                pq.pop();
            } else {
                break;
            }
        }
    }

public:
    AuthenticationManager(int timeToLive) : timeToLive(timeToLive) {}
    
    void generate(string tokenId, int currentTime) {
        removeExpiredTokens(currentTime);
        int expire_at = currentTime + timeToLive;
        liveTokens[tokenId] = expire_at;
        pq.push(make_pair(tokenId, expire_at));
    }
    
    void renew(string tokenId, int currentTime) {
        removeExpiredTokens(currentTime);
        if (liveTokens.count(tokenId)) {
            if (liveTokens[tokenId] > currentTime) {
                int expire_at = currentTime + timeToLive;
                liveTokens[tokenId] = expire_at;
                pq.push(make_pair(tokenId, expire_at));
            }
        }
    }
    
    int countUnexpiredTokens(int currentTime) {
        removeExpiredTokens(currentTime);
        return liveTokens.size();
    }
};

/**
 * Your AuthenticationManager object will be instantiated and called as such:
 * AuthenticationManager* obj = new AuthenticationManager(timeToLive);
 * obj->generate(tokenId,currentTime);
 * obj->renew(tokenId,currentTime);
 * int param_3 = obj->countUnexpiredTokens(currentTime);
 */