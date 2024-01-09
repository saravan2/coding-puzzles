class Solution {
public:
    int minimizedStringLength(string s) {
        unordered_map<char, int> unique;
        for (int i = 0; i < s.size(); i++) {
            unique[s[i]]++;
        }
        return unique.size();
    }
};
