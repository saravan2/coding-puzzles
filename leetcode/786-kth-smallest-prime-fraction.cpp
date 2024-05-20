class Fraction {
public:
    int num;
    int den;
    unsigned int num_at;
    unsigned int den_at;
    Fraction(int num, int den, int num_at, int den_at) : num(num), den(den), num_at(num_at), den_at(den_at) {}
    ~Fraction() = default;
};

class Compare {
public:
    Compare() = default;
    ~Compare() = default;

    bool operator()(const Fraction& a, const Fraction& b) {
        int x = a.num * b.den;
        int y = b.num * a.den;
        if (a.num != 0 && x / a.num != b.den) {
            // integer overflow 
            return true;
        } else if (b.num != 0 && y / b.num != a.den) {
            // integer overflow
            return true;
        } else {
            return (x > y);
        }
    }

};

class Solution {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) {
        int n = arr.size();

        priority_queue<Fraction, std::vector<Fraction>, Compare> pq;

        for (int i = 0; i < n; i++) {
            pq.push(Fraction(arr[i], arr.back(), i, (n-1)));
        }

        while (--k > 0) {
            Fraction curr = pq.top();
            pq.pop();
            curr.den_at--;
            curr.den = arr[curr.den_at];
            pq.push(curr);
        }

        Fraction kth = pq.top();
        return {arr[kth.num_at], arr[kth.den_at]};
    }
};