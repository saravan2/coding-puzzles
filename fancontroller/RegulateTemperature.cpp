#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <atomic>
#include "SubsystemInterface.hpp"
#include "FanInterface.hpp"
#include "IpcData.hpp"
#include "IpcInterface.hpp"
#include "LogInterface.hpp"
#include "SignalInterface.hpp"
#include "ParseSubsystemsConf.hpp"
#include "ParseFanConf.hpp"

template <class T, class U>
class RegulateTemperature {
    private:
    constexpr static float TWENTY_PERCENT_DUTY_CYCLE_TEMPERATURE = 25.0;
    constexpr static float HUNDRED_PERCENT_DUTY_CYCLE_TEMPERATURE= 75.0;
    constexpr static float DUTY_CYCLE_TEMPERATURE_RANGE = HUNDRED_PERCENT_DUTY_CYCLE_TEMPERATURE - TWENTY_PERCENT_DUTY_CYCLE_TEMPERATURE;
    std::vector<T> subsystems;
    std::vector<U> fans;
    float current_duty_cycle_percentage;

    void recordTimeStamp() {
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        std::cout << "\n Time: " << std::ctime(&now_c) << std::endl;
    }

    float computeFansDutyCyclePercentage() {
        auto max_entry = std::max_element(subsystems.begin(), subsystems.end(), [](SubsystemInterface<SubsystemData>& a, SubsystemInterface<SubsystemData>& b) { return a.getTemperature() < b.getTemperature(); });
        if (max_entry->getTemperature() <= TWENTY_PERCENT_DUTY_CYCLE_TEMPERATURE) {
            return 0.2;
        } else if (max_entry->getTemperature() >= HUNDRED_PERCENT_DUTY_CYCLE_TEMPERATURE) {
            return 1.0;
        } else {
            return (0.2 + (max_entry->getTemperature() - TWENTY_PERCENT_DUTY_CYCLE_TEMPERATURE) / (DUTY_CYCLE_TEMPERATURE_RANGE) * 0.8);
        }
    }
    
    public:
    // Constructors
    RegulateTemperature(std::vector<T> _subsystems, std::vector<U> _fans) : subsystems(_subsystems), fans(_fans) {}

    // Member functions
    void updateSubsystems(std::vector<T>& _subsystems) {
        subsystems = _subsystems;
    }

    // Member function 
    void setFanSpeed() {
        recordTimeStamp();
        current_duty_cycle_percentage = computeFansDutyCyclePercentage();
        for (auto fan : fans) {
            fan.setDutyCyclePercentage(current_duty_cycle_percentage);
            //fan.setFanRegister();
            fan.mock_setFanRegister();
        }       
    }
};

// Signal Handlers
std::atomic<bool> terminalSignalReceived = false;

void new_subsystem_data_handler(int signal) {
    std::cout << "\nReceived Signal : " << signal << " Fetching Subsystem Data via shared memory" << std::endl;
}

void terminalSignalHandler(int signal) {
    terminalSignalReceived = true;
    std::cout << "Terminal Signal "<< signal <<" Received !" << std::endl;
    std::cout << "RegulateTemperature Application gracefully exiting ..." << std::endl;
}

int main(int argc, char* argv[]) {
    
    std::string subsystems_conf_path = "subsystems.conf";
    std::string fans_conf_path = "fans.conf";
    std::string log_path = "log.txt";
    
    if (argc > 1) {
        if (argc != 4 || !std::string(argv[1]).compare("--help") || !std::string(argv[1]).compare("-h")) {
            std::cerr << "Usage: " << argv[0] << " <path to subsystems.conf> <path to fans.conf> <path to log.txt>" << std::endl;
            return -1;
        }
        subsystems_conf_path = argv[1];
        fans_conf_path = argv[2];
        log_path = argv[3];
    }
    std::cout << "RegulateTemperature Application Started ! PID: " << getpid() << std::endl;
    std::cout << "Subsystem Configuration File: " << subsystems_conf_path << std::endl;
    std::cout << "Fan Configuration File: " << fans_conf_path << std::endl;
    std::cout << "Log File: " << log_path << std::endl;

    try {
        // Set up Signal Handling
        SignalInterface signal_interface;
        signal_interface.setupSignalHandler(SIGUSR1, new_subsystem_data_handler);
        signal_interface.setupTerminalSignalHandler(terminalSignalHandler);

        // Set up Logging
        LogInterface log_interface(log_path.c_str());

        // Set up IPC
        IPCInterface<SubsystemInterface<SubsystemData>> ipc_interface; 

        // Parse Configuration Files
        std::vector<SubsystemInterface<SubsystemData>> subsystems = ParseSubsystemConf::parseSubsystemConf(subsystems_conf_path);
        std::vector<FanInterface> fans = ParseFanConf::parseFanConf(fans_conf_path);

        RegulateTemperature regulate_temperature(subsystems, fans);

        while (!terminalSignalReceived) {
            regulate_temperature.setFanSpeed();
            pause();
            if (terminalSignalReceived) {
                break;
            }
            auto new_subsystems_data = ipc_interface.readData();
            ipc_interface.clearData();
            regulate_temperature.updateSubsystems(new_subsystems_data);
        }
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}