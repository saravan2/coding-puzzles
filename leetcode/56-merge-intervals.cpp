class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.size() == 1) {
            return intervals;
        }
        vector<pair<int, int>> segments;
        vector<vector<int>> merged;
        for (int i = 0; i < intervals.size(); i++) {
            segments.push_back({intervals[i][0], intervals[i][1]});
        }
        sort(segments.begin(), segments.end());
        int start = segments[0].first;
        int end = segments[0].second;
        for (int i = 0; i < segments.size() - 1; i++) {
            vector<int> merge(2, 0);
            if (end >= segments[i + 1].first) {
                end = max(end, segments[i+1].second);
            } else {
                merge[0] = start;
                merge[1] = end;
                start = segments[ i + 1].first;
                end = segments[i + 1].second;
                merged.push_back(merge);
            }
        }
        merged.push_back({start, end});
        return merged;
    }
};