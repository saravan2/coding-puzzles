class Solution {
private:
    int lengthOfLIS(vector<int>& sequence) {
        int n = sequence.size();
        if (n <= 1) {
            return n;
        }
        
        vector<int> subseqLength(n, 1);
        int max = 1;
        
        for (int index = 1; index < n; index++) {
            for (int prev = 0; prev < index; prev++) {
                if ((sequence[index] > sequence[prev]) &&
                    (subseqLength[index] < (subseqLength[prev] + 1))
                ) {
                    subseqLength[index] = subseqLength[prev] + 1;
                }
            }
            if (max < subseqLength[index]) {
                max = subseqLength[index];
            }
        } 

        return max;
    }
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        int n = envelopes.size();
        if (n <= 1) {
            return n;
        }
        std::sort(envelopes.begin(), envelopes.end(), [](vector<int> &a, vector<int>& b){
            if (a[0] == b[0]) {
                return (a[1] > b[1]);
            } else {
                return a[0] < b[0];
            }
        });
        //vector<int> heights(n, 0);
        //for (int i = 0; i < n; i++) {
        //    heights[i] = envelopes[i][1];
        //}
        //return lengthOfLIS(heights);
        vector<int> longestIS(1, envelopes[0][1]);
        for (int i = 1; i < n; i++) {
            if (envelopes[i][1] > longestIS.back()) {
                longestIS.push_back(envelopes[i][1]);
            } else {
                //Binary search index to replace
                int l = 0;
                int r = (longestIS.size() - 1);
                while (l < r) {
                    int mid = l + ((r - l)/2);
                    if (longestIS[mid] < envelopes[i][1]) {
                        l = mid + 1;
                    } else {
                        r = mid;
                    }
                }
                longestIS[l] = envelopes[i][1];
            }
        }
        return longestIS.size();
    }
};