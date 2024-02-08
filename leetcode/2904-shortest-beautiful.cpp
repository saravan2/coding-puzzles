class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        string shortest = "";
        for (int i = 0; i < s.length(); i++) {
            int one_count = 0;
            string substring = "";
            for (int j = i; j < s.length(); j++) {
                if (s[j] == '1')
                    one_count++;
                substring += s[j];
                if (one_count == k) {
                    if (shortest == "") {
                        shortest = substring;
                    } else if (shortest.length() > substring.length()) {
                        shortest = substring;
                    } else if (shortest.length() == substring.length()) {
                        for (int k = 0; k < shortest.length(); k++) {
                             if (shortest[k] != substring[k]) {
                                if (shortest[k] > substring[k]) 
                                    shortest = substring;
                                break;
                            }
                        }
                    }
                    break;
                }
            }
        }
        return shortest;
    }
};