class Solution {
public:
    vector<int> sameEndSubstringCount(string s, vector<vector<int>>& queries) {
        int n = s.size();
        int q = queries.size();
        
        vector<int> answers(q, 0);
        vector<vector<int>> freq_sofar(n+1, vector<int>(26,0));

        for (int i = 0; i < n; i++) {
            freq_sofar[i+1] = freq_sofar[i];
            freq_sofar[i+1][s[i] - 'a']++;
        }

        for (int i = 0; i < q; i++) {
            int l = queries[i][0];
            int r = queries[i][1];
            for (int j = 0; j < 26; j++) {
                int count = freq_sofar[r+1][j] - freq_sofar[l][j];
                answers[i] += count + count * (count - 1) / 2;
            }
        }
        
        return answers;
    }
};
