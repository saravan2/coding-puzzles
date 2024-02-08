class Solution {
public:
    int beautifulSubstrings(string s, int k) {
        unordered_set<char> vowels({'a', 'e', 'i', 'o', 'u'});
        int count = 0;
        for (int i = 0; i < s.length(); i++) {
            int vowels_sofar = 0, consonents_sofar = 0;
            for (int j = i; j < s.length(); j++) {
                if (auto result = vowels.find(s[j]); result != vowels.end()) {
                    vowels_sofar++;
                } else {
                    consonents_sofar++;
                }
                if ((vowels_sofar == consonents_sofar) && !((vowels_sofar * consonents_sofar) % k)) {
                    count++;
                }
            }
        }
        return count;
    }
};