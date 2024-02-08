class Solution {
public:
    int videoStitching(vector<vector<int>>& clips, int time) {
        unordered_map<int, int> max_at_time(clips.size());
        for (auto const& clip : clips) {
            max_at_time[clip[0]] = max(max_at_time[clip[0]], clip[1]);
        }
        int selected = -1; 
        int reachable = 0;
        int count = 0;
        for (int i = 0; i <= time; i++) {
            if (reachable >= time || i > reachable)
                break;

            if (max_at_time.count(i)) {
                if (i > selected) {
                    count++;
                    selected = reachable;
                }
                reachable = max(reachable, max_at_time[i]);
            }
        }
        return reachable >= time ? count : -1;
    }
};