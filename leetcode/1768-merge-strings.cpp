class Solution {
public:
    string mergeAlternately(string word1, string word2) {
        int i = 0, j = 0;
        int n1 = word1.size();
        int n2 = word2.size();
        string answer="";
        for (; i < n1 && j < n2; i++, j++) {
            answer += string(1,word1[i]) + string(1,word2[j]);
        }
        if (i < n1 && j == n2) {
            answer += word1.substr(i);
        } else if (i == n1 && j < n2) {
            answer += word2.substr(j);
        }
        return answer;
    }
};