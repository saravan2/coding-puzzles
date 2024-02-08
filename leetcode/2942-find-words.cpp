class Solution {
public:
    vector<int> findWordsContaining(vector<string>& words, char x) {
        int n = words.size();
        vector<int> result;
        for (int i = 0; i < words.size(); i++) {
            string word = words[i];
            for (auto const& ch: word) {
                if (ch == x) {
                    result.push_back(i);
                    break;
                }
            }
        }
        return result;
    }
};