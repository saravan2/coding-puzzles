class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        unsigned int nt = tasks.size();
        if (n <= 0) {
            return (int)nt;
        }
        std::vector<unsigned int> taskDistribution(26, 0);
        for (int i = 0; i < nt; i++) {
            taskDistribution[tasks[i] - 'A'] += 1;
        }
        std::priority_queue<int> tq;
        for (int i = 0; i < taskDistribution.size(); i++) {
            if (taskDistribution[i] > 0) {
                tq.push(taskDistribution[i]);
            }
        }

        int interval = 0;
        while (!tq.empty()) {
            int cycle = n + 1;
            vector<int> updates;
            int count = 0;
            while (cycle-- && !tq.empty()) {
                if (tq.top() > 1) {
                    updates.push_back(tq.top() - 1);
                }
                tq.pop();
                count++;
            }
            for (int &update : updates) {
                tq.push(update);
            }
            if (tq.empty()) {
                interval += count;
            } else {
                interval += n + 1;
            }
        }
        return interval;
    }
};