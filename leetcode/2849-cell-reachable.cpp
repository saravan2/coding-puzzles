class Solution {
public:
    bool isReachableAtTime(int sx, int sy, int fx, int fy, int t) {
        int distance = max(abs(fx - sx), abs(fy - sy));
        if (distance && t >= distance) {
            return true;
        } else if (!distance && (t != 1)){
            return true;
        } else {
            return false;
        }

    }
};