class Solution {
//private:
//    int find(std::vector<std::vector<int>>charPositions, char ch, int after) {
//        int charIndex = (ch - 'a');
//        if (charPositions[charIndex].empty()) {
//            return -1;
//        }
//        int l = 0;
//        int r = charPositions[charIndex].size() - 1;
//        int index = -1;
//        while (l <= r) {
//            int mid = l + (r - l)/2;
//            if (charPositions[charIndex][mid] > after) {
//                index = charPositions[charIndex][mid];
//                r = mid - 1;
//            } else {
//                l = mid + 1;
//            }
//        }
//        return index;
//    }

public:
    int numMatchingSubseq(string s, vector<string>& words) {
        std::vector<std::vector<int>> charPositions(26, std::vector<int>());
        for (int i = 0; i < s.length(); i++) {
            charPositions[s[i] - 'a'].push_back(i);
        }
        int count = 0;
        for (const string& word: words) {
//            if (seen.count(word)) {
//                if (seen[word]) {
//                    count++;
//                }
//               continue;
//            }
            int after = -1;
            bool validSubsequence = true;
            for (int i = 0; i < word.length(); i++) {
                int charIndex = word[i] - 'a';
                if (charPositions[charIndex].empty()) {
                    validSubsequence = false;
                    break;
                }
                auto it = upper_bound(charPositions[charIndex].begin(), charPositions[charIndex].end(), after);
                if (it == charPositions[charIndex].end()) {
                    validSubsequence = false;
                    break;
                } else {
                    after = *it;
                }
//                after = find(charPositions, word[i], after);
//                if (after == -1) {
//                    validSubsequence = false;
//                    break;
//                }
            }
            if (validSubsequence) {
//                seen[word] = true;
                count++;
//            } else {
//                seen[word] = false;
            }
        }
        return count;
    }
};