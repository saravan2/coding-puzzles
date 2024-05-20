class Solution {
public:
    int shortestWay(string source, string target) {
        std::vector<bool> sourceChars(26, false);
        
        for (const char& ch : source) {
            sourceChars[ch - 'a'] = true;
        }

        for (const char& ch : target) {
            if (!sourceChars[ch - 'a']) {
                return -1;
            }
        }

        int n = source.length();
        int index = 0;
        int count = 0;

        for (const char& ch : target) {

            if (!index) {
                count++;
            }
            
            while (source[index] != ch) {
                index = (index + 1) % n;
                if (!index) {
                    count++;
                }
            }

            index = (index + 1) % n;
        }

        return count;
    }
};