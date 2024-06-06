class Solution {

private:
int countOps(int curr, int target, int lastcp, std::vector<std::vector<int>> &opsToReachTarget) {
    if (curr == target) {
        return 0;
    }

    if (curr + lastcp > target) {
        return INT_MAX;
    }

    if (opsToReachTarget[curr][lastcp] != -1) {
        return opsToReachTarget[curr][lastcp];
    }

    int cp_count = countOps(curr + curr, target, curr, opsToReachTarget);
    int p_count = countOps(curr + lastcp, target, lastcp, opsToReachTarget);
    int cp = (cp_count == INT_MAX ? INT_MAX : (2 + cp_count));
    int p = (p_count == INT_MAX ? INT_MAX : (1 + p_count));

    opsToReachTarget[curr][lastcp] = std::min(cp, p);
    return opsToReachTarget[curr][lastcp];
}

public:
    int minSteps(int n) {
        if (n <= 1) {
            return 0;
        }
        std::vector<std::vector<int>> opsToReachTarget(n+1, std::vector<int>(n+1, -1));
        // We have copied "A" and pasted it to form "AA"
        int ops = 2;
        return ops + countOps(2, n, 1, opsToReachTarget);
    }
};