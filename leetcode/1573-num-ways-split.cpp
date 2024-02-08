class Solution {
public:
    int numWays(string s) {
        long mod = 1e9+7;
        long n = s.size();
        long one_count = 0;
        for (long i = 0; i < n; i++) {
            if (s[i] == '1') {
                one_count++;
            }
        }
        if (!one_count) {
            return ((((n - 1) * (n - 2)) / 2) % mod);
        } else if (one_count % 3) {
            return 0;
        } else {
            long ones_count_after_first_partition = one_count / 3;
            long ones_count_after_second_partiton = 2 * ones_count_after_first_partition;
            long ones_sofar = 0, cuts_between_first_second = 0, cuts_between_second_third = 0;
            for (long i = 0; i < n; i++) {
                if (s[i] == '1') {
                    ones_sofar++;
                }
                if (ones_sofar == ones_count_after_first_partition) {
                    cuts_between_first_second++;
                } else if (ones_sofar == ones_count_after_second_partiton) {
                    cuts_between_second_third++;
                }
            }
            return ((cuts_between_first_second * cuts_between_second_third)% mod);
        }
    }
};