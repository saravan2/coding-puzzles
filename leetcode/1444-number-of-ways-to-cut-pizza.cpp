class Solution {
public:
    int ways(vector<string>& pizza, int k) {
        int mod = 1e9 + 7;
        int m = pizza.size();
        int n = pizza[0].size();
        vector<vector<int>> distribution(m+1, vector<int>(n+1, 0));
        vector<vector<vector<int>>> dp(m+1, vector<vector<int>>(n+1, vector<int>(k, 0)));
//        for (int i = m-1; i >= 0; i--) {
//            for (int j = n-1; j >=0; j--) {
//                distribution[i][j] = distribution[i][j+1] + distribution[i+1][j] - distribution[i+1][j+1];
//                if (pizza[i][j] == 'A')
//                    distribution[i][j]++;
//            }
//        }
        for (int i = m-1; i >=0 ; i--) {
            for (int j = n-1; j >=0; j--) {
                distribution[i][j] = distribution[i][j+1] + distribution[i+1][j] - distribution[i+1][j+1];
                if (pizza[i][j] == 'A')
                    distribution[i][j]++;
                for (int l = 0; l < k; l++) {
                    if (l == 0) {
                        if (distribution[i][j])
                            dp[i][j][l] = 1;
                        continue;
                    }
                    for (int p = i + 1; p < m; p++) {
                        if (distribution[i][j] - distribution[p][j]) {
                            dp[i][j][l] = (dp[i][j][l] + dp[p][j][l-1]) % mod;
                        }
                    }
                    for (int q = j + 1; q < n; q++) {
                        if (distribution[i][j] - distribution[i][q]) {
                            dp[i][j][l] = (dp[i][j][l] + dp[i][q][l-1]) % mod;
                        }
                    }
                }
            }
        }
        return dp[0][0][k-1];
    }
};