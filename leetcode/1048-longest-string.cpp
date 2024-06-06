class Solution {
private:
    int dfs_chain_length(unordered_set<string> &setOfWords, 
        unordered_map<string, int> &knownChainLengths,
        const string &word) {
            if (knownChainLengths.count(word)) {
                return knownChainLengths[word];
            }

            int maxlen = 1;

            for (int i = 0; i < word.length(); i++) {
                string newWord = word.substr(0, i) + word.substr(i+1);
                if (setOfWords.find(newWord) != setOfWords.end()) {
                    maxlen = std::max(maxlen,
                    (1 + dfs_chain_length(setOfWords, knownChainLengths, newWord)));
                }
            }
            knownChainLengths[word] = maxlen;
            return maxlen;
        }
public:
    int longestStrChain(vector<string>& words) {
        unordered_map<string, int> knownChainLengths;
        unordered_set<string> setOfWords;

        for (const string &word: words) {
            setOfWords.insert(word);
        }

        int longest = 0;

        for (const string &word: words) {
            longest = std::max(longest, dfs_chain_length(setOfWords, knownChainLengths, word));
        }
        
        return longest;
    }
};