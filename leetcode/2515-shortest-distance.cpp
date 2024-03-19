class Solution {
public:
    int closetTarget(vector<string>& words, string target, int startIndex) {
        if (words.empty()) {
            return -1;
        }
        if (!words.empty() && startIndex < words.size() && words[startIndex] ==  target)
            return 0;
        
        int steps = 1;
        bool found = false;
        int closest = INT_MAX;
        int n = words.size();
        int next = (startIndex + 1 == n)? 0 : startIndex + 1;
        while (next !=  startIndex) {
            if (words[next] == target) {
                found = true;
                break;
            }
            next = (next + 1) % n;
            steps++;
        }

        if (!found) {
            return -1;
        } else {
            closest = min(closest, steps);
        }

        steps = 1;
        next = (startIndex - 1 < 0)? n - 1 : startIndex - 1;
        while (next != startIndex) {
            if (words[next] == target) {
                break;
            }
            next = (next - 1 + n) % n;
            steps++;
        }
        return closest = min(closest, steps);
    }
};