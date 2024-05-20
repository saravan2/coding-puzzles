/*
class Coordinate {
public:
    int x;
    int y;
    unsigned int count;
    Coordinate(int x, int y, unsigned int count) : x(x), y(y), count(count) {}
    ~Coordinate() = default;
};

class coordinateCompareGreater {
public:
    bool operator()(const Coordinate& a, const Coordinate& b) {
        unsigned int abs_a = std::abs(a.x - a.y);
        unsigned int abs_b = std::abs(b.x - b.y);
        return abs_a > abs_b;
    }
};

auto pairHash = [](const pair<int, int>& a) -> size_t {return (size_t) a.first << 32 | (unsigned int) a.second;};
*/

class Solution {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        unsigned int n = nums.size();
/*
        priority_queue<Coordinate, std::vector<Coordinate>, coordinateCompareGreater> pq;
        unordered_map<pair<int, int>, unsigned int, decltype(pairHash)> coordinates;
        for (unsigned int i = 0; i < n; i++) {
            for (unsigned int j = (i + 1); j < n; j++) {
                if (coordinates.count({nums[i], nums[j]})) {
                    coordinates[{nums[i], nums[j]}]++;
                } else {
                    coordinates[{nums[i], nums[j]}] = 1;
                }
            }
        }

        for (auto it = coordinates.begin(); it != coordinates.end(); it++) {
            pq.push(Coordinate(it->first.first, it->first.second, it->second));
        }

        while(k > 1) {
            Coordinate curr = pq.top();
            pq.pop();
            if (curr.count > 1) {
                if ((k - 1) >= curr.count) {
                    k = k - curr.count;
                } else if (curr.count > (k - 1)) {
                    curr.count = curr.count - (k - 1);
                    k = 1;
                    pq.push(curr);
                }
            } else {
                k--;
            }
        }

        Coordinate kth = pq.top();
        return std::abs(kth.x - kth.y);
*/
        std::sort(nums.begin(), nums.end());
        int left = 0;
        int right = nums[n-1] - nums[0];

        while (left < right) {
            int mid = left + (right - left)/2;
            int i = 0, j = 0, count = 0;
            while (i < n) {
                while (j < n && (nums[j] - nums[i]) <= mid) {
                    j++;
                }
                count += ((j - i) - 1);
                i++;
            }
            if (count >= k) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }
};