class Solution {
public:
    int uniqueMorseRepresentations(vector<string>& words) {
        vector<string> morse_alphabets = {".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."};
        unordered_set<string> unique;
        for (auto const& word : words) {
            string morse = "";
            for (auto const& ch :  word) {
                morse += morse_alphabets[ch - 'a'];
            }
            unique.insert(morse);
        }
        return unique.size();
    }
};
