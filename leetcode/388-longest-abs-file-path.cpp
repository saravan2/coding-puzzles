class Solution {
public:
    int lengthLongestPath(string input) {
        std::vector<std::string> steps;
        std::istringstream iss(input);
        std::string line;
        
        while(getline(iss, line, '\n')) {
            steps.push_back(line);
        }

        unordered_map<int, int> levelLength = {{0,0}};
        int maxPath = 0;
        for (const auto & step : steps) {
            std::string name = step.substr(step.find_first_not_of('\t'));
            int depth = step.length() - name.length();
            bool file = false;

            if (name.find('.') != std::string::npos) {
                file = true;
            }

            if (file) {
                maxPath = std::max(maxPath, (int)(levelLength[depth] + name.length()));
            } else {
                levelLength[depth + 1] = levelLength[depth] + (int)name.length() + 1;
            }
        }
        return maxPath;
    }
};