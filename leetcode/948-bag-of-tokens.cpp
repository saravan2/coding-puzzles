class Solution {
public:
    int bagOfTokensScore(vector<int>& tokens, int power) {
        int left = 0;
        int right = (tokens.size() - 1);
        int score = 0;
        sort(tokens.begin(), tokens.end());

        while (left <= right ) {
            if (power >= tokens[left]) {
                power -= tokens[left];
                left++;
                score++;
            } else if ( left < right && score > 0) {
                power += tokens[right];
                right--;
                score--;
            } else {
                return score;
            }
        }

        return score;       
    }
};