#ifndef SIGNAL_INTERFACE_HPP
#define SIGNAL_INTERFACE_HPP
#include <signal.h>
#include <iostream>
#include <vector>
#include <stdexcept>

class SignalInterface {
    private:
    std::vector<int> signals;

    public:
    SignalInterface() {}

    ~SignalInterface() {
        for (int signal : signals) {
            struct sigaction action;
            action.sa_handler = SIG_DFL;
            sigemptyset(&action.sa_mask);
            action.sa_flags = 0;
            if (sigaction(signal, &action, NULL) == -1) {
                std::cerr << "Error: Unable to reset signal handler for " << signal << std::endl;
            }
        }
    }

    void setupSignalHandler(int signum, void (*handler)(int)) {
        struct sigaction action;
        action.sa_handler = handler;
        sigemptyset(&action.sa_mask);
        action.sa_flags = 0;
        if (sigaction(signum, &action, NULL) == -1) {
            std::cerr << "Error: Unable to register signal handler for " << signum << std::endl;
        }
        signals.push_back(signum);
    }

    void setupTerminalSignalHandler(void (*handler)(int)) {
        setupSignalHandler(SIGINT, handler);
        setupSignalHandler(SIGTERM, handler);
    }
};
#endif