class Solution {
public:
    vector<int> closestPrimes(int left, int right) {
        vector<bool> primes(right + 1, true);
        primes[0] = primes [1] = false;
        for (int i = 2; i * i <= right; i++) {
            if (primes[i]) {
                for (int j = i*i; j <= right; j += i) {
                    primes[j] = false;
                }
            }
        }
        int i = left;
        int p1 = -1, p2 = -1, diff = INT_MAX;
        while (i <= right) {
            if (primes[i])
                break;
            i++;
        }
        int j = i+1;
        while (j <= right) {
            if (primes[j]) {
                if ((j - i) < diff) {
                    p1 = i, p2 = j;
                    diff = (j - i);
                }
                i = j;
            }
            j++;
        }
        return {p1, p2};
    }
};