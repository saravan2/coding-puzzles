class Logger {
private:
    int epoch;
    int epoch_duration;
    std::unordered_map<std::string, int> previous_epoch;
    std::unordered_map<std::string, int> current_epoch;
public:
    Logger() : epoch(0), epoch_duration(10) {
    }
    
    bool shouldPrintMessage(int timestamp, string message) {
        if (timestamp >= epoch + epoch_duration) {
            previous_epoch = current_epoch;
            current_epoch.clear();
            epoch = timestamp;
        }

        if (current_epoch.count(message)) {
            return false;
        }

        if (previous_epoch.count(message) && (timestamp < (previous_epoch[message] + epoch_duration))) {
            return false;
        }

        current_epoch[message] = timestamp;
        return true;
    }
};

/**
 * Your Logger object will be instantiated and called as such:
 * Logger* obj = new Logger();
 * bool param_1 = obj->shouldPrintMessage(timestamp,message);
 */