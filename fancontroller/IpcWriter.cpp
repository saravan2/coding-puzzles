#include <thread>
#include <iostream>
#include <chrono>
#include <ctime>
#include <atomic>
#include "SubsystemInterface.hpp"
#include "IpcInterface.hpp"
#include "LogInterface.hpp"
#include "SignalInterface.hpp"
#include "ParseSubsystemsConf.hpp"

void printTimeStamp() {
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        std::cout << "\n Time: " << std::ctime(&now_c) << std::endl;
}

void randomizeTemperature(std::vector<SubsystemInterface<SubsystemData>>& subsystems) {
    printTimeStamp();
    for (auto& subsystem : subsystems) {
        // Upto 75 degrees
        float temperature = 20.0f + (rand() % 55);
        std::cout << "Randomizing temperature for " << subsystem.getSubsystemData().subsystem_name << " to " << temperature << std::endl;
        subsystem.setTemperature(temperature);
    }
}   

// Signal Handlers
std::atomic<bool> terminalSignalReceived(false);

void new_subsystem_data_handler(int signal) {
    std::cout << "\nRecevied SIGUSR1 : " << signal << std::endl;
}

void terminalSignalHandler(int signal) {
    terminalSignalReceived = true;
    std::cout << "\nReceived terminal signal : " << signal << std::endl;
    std::cout << "Exiting gracefully ..." << std::endl;
}

int main(int argc, char *argv[]) {
    std::string subsystems_conf_path = "subsystems.conf";
    std::string log_path = "logIpcWriter.txt";
    pid_t target_pid = 0;

    if (argc > 1) {
        if (argc != 4 || !std::string(argv[1]).compare("--help") || !std::string(argv[1]).compare("-h")) {
            std::cerr << "Usage: " << argv[0] << " <path to subsystems.conf> "  << " <path to Ipc writer log file> " << "pid of application" << std::endl;
            return -1;
        }
        subsystems_conf_path = argv[1];
        log_path = argv[2];
        target_pid = std::stoi(argv[3]);
    } else {
        std::cerr << "Usage: " << argv[0] << " <path to subsystems.conf> " << " <path to logIpcWriter.txt> " << "pid of application" << std::endl;
        return -1;
    }

    std::cout << "IpcWriter Application Started ! PID: " << getpid() << std::endl;
    std::cout << "Subsystem Configuration File: " << subsystems_conf_path << std::endl;
    std::cout << "Log File: " << log_path << std::endl;
    std::cout << "Target PID: " << target_pid << std::endl;

    try {
        // Set up Signal Handling
        SignalInterface signal_interface;
        signal_interface.setupSignalHandler(SIGUSR1, new_subsystem_data_handler);
        signal_interface.setupTerminalSignalHandler(terminalSignalHandler);

        // Set up IPC
        IPCInterface<SubsystemInterface<SubsystemData>> ipc_interface;

        // Set up Logging
        LogInterface log_interface(log_path.c_str());

        // Parse Configuration File
        std::vector<SubsystemInterface<SubsystemData>> subsystems = ParseSubsystemConf::parseSubsystemConf(subsystems_conf_path);

        while (!terminalSignalReceived) {
            randomizeTemperature(subsystems);
            std::cout << "Writing data to shared memory" << std::endl;
            ipc_interface.writeData(subsystems);
            // Inform reader application
            kill(target_pid, SIGUSR1); 
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}