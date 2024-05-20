class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        std::unordered_map<char, int> uniqElemAtIndex;
        int count = 0;

        for (int j = 0, i = 0; j < (int)s.length(); j++) {
            if (uniqElemAtIndex.count(s[j])) {
                i = std::max((uniqElemAtIndex[s[j]] + 1), i);
            }
            count = std::max(count, (j - i) + 1);
            uniqElemAtIndex[s[j]] = j;
        }

        return count;
    }
};