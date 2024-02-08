class Solution {
public:
    int longestPalindrome(vector<string>& words) {
        unordered_map<string, int> frequency;
        int longest = 0;
        int max_same_char_palindrome = 0;
        bool odd = false;
        for (auto const& word: words) {
            frequency[word]++;
        }

        for (auto const& word: words) {
            string reverse(word.rbegin(), word.rend());
            if (word != reverse) {
                if (frequency.count(reverse)) {
                    longest += (min(1, min(frequency[word], frequency[reverse]))) * 4;
                    if (frequency[word] > 0) {
                        frequency[word]--;
                    }
                    if (frequency[reverse] > 0) {
                        frequency[reverse]--;
                    }
                }
            } else {
                longest += (frequency[word] / 2) * 4;
                frequency[word] %= 2;
                if (frequency[word] % 2) {
                    odd = true;
                }
            }
        }
        if (odd) 
            longest += 2;
        return longest;
    }
};