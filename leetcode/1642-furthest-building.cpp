class Solution {
public:
    int furthestBuilding(vector<int>& heights, int bricks, int ladders) {
        std::priority_queue<int, vector<int>, std::greater<int>> lq;
        size_t n = heights.size();
        for (int i = 0; i < (int)(n - 1); i++) {
            int current = heights[i];
            int next = heights[i+1];
            int climb = next - current;
            if (climb <= 0) {
                continue;
            } else {
                if (ladders) {
                    lq.push(climb);
                    ladders--;
                } else {
                    if (lq.empty()) {
                        bricks -= climb;
                    } else {
                        int smallest = lq.top();
                        if (smallest > climb) {
                            bricks -= climb;
                        } else {
                            lq.pop();
                            lq.push(climb);
                            bricks -= smallest;
                        }
                    }
                    if (bricks < 0) {
                        return i;
                    }
                }
            }
        }
        return (n - 1);
    }
};