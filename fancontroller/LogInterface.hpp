#ifndef LOG_INTERFACE_HPP
#define LOG_INTERFACE_HPP
#include <iostream>
#include <fstream>

class LogInterface {
    private:
    std::streambuf *coutbuf;
    std::streambuf *cerrbuf;
    std::ofstream log_file;
    bool initialized = false;
    public:
    LogInterface(const char* log_file_name) {
        log_file.open(log_file_name, std::ios::out | std::ios::app);
        if (!log_file.is_open()) {
            std::cerr << "Error: Unable to open log file" << std::endl;
            throw std::runtime_error("Unable to open log file");
        }
        // Redirect standard output and standard error to the log file
        coutbuf = std::cout.rdbuf();
        cerrbuf = std::cerr.rdbuf();
        std::cout.rdbuf(log_file.rdbuf());
        std::cerr.rdbuf(log_file.rdbuf());
        initialized = true; 
    }
    ~LogInterface() {
        if (!initialized) {
            return;
        }
        std::cout.rdbuf(coutbuf);
        std::cerr.rdbuf(cerrbuf);
        log_file.close();
    }
};

#endif