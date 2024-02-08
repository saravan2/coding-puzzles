class Solution {
public:
    int countBinarySubstrings(string s) {
        int curr_count = 1;
        int prev_count = 0;
        int count = 0;

        for (int i = 1; i < s.size(); i++) {
            if (s[i] == s[i-1]) {
                curr_count++;
            } else {
                count += (curr_count < prev_count)?curr_count:prev_count;
                prev_count = curr_count;
                curr_count = 1;
            }
        }

        count += (curr_count < prev_count)?curr_count:prev_count;

        return count;
    }
};