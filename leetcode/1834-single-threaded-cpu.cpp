class Solution {
public:
    vector<int> getOrder(vector<vector<int>>& tasks) {
        int i = 0, n = tasks.size();
        vector<int> order;
        for (i = 0; i < n; i++) {
            tasks[i].push_back(i);
        }
        sort(tasks.begin(), tasks.end(), [](vector<int>& a, vector<int>& b) {
            return a[0] < b[0];
        });
        auto compare = [](vector<int> const& a, vector<int> const& b) -> bool {
            if (a[1] == b[1]) {
                return a[2] > b[2];
            } else {
                return a[1] > b[1];
            } 
        };
        priority_queue<vector<int>, vector<vector<int>>, decltype(compare)> pq(compare);
        i = 0;
        long long currentTime = 0;
        while ((i < n) || !pq.empty()) {
            if (pq.empty() && currentTime < tasks[i][0]) {
                currentTime = tasks[i][0];
            }

            while((i < n) && (tasks[i][0] <= currentTime)) {
                pq.push(tasks[i]);
                i++;
            }

            currentTime += pq.top()[1];
            order.push_back(pq.top()[2]);
            pq.pop();
        }

        return order;

    }
};