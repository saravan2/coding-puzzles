#ifndef PARSESUBSYSTEMSCONF_HPP
#define PARSESUBSYSTEMSCONF_HPP
#include <fstream>
#include <string>
#include <vector>
#include "SubsystemInterface.hpp"
#include "SubsystemData.hpp"
class ParseSubsystemConf {
    #define SUBSYSTEM_CONF_FILE "subsystems.conf"
    #define subsystem_start "subsystem config start"
    #define subsystem_end "subsystem config end"
    #define subsystem_name_offset 0
    #define temperature_offset 1
    public:
    // Optimistic parsing for demonstration purposes
    static std::vector<SubsystemInterface<SubsystemData>> parseSubsystemConf(const std::string& filename) {
        std::vector<SubsystemInterface<SubsystemData>> subsystems;
        std::ifstream file(filename);
        bool between = false;
        std::string subsystem_name;
        std::string temperature;
        int offset = 0;
        while(file.eof() == false) {
            std::string line;
            std::getline(file, line);
            if (line == subsystem_start) {
                between = true;
                continue;
            }
            if (between) {
                if (line == subsystem_end) {
                    between = false;
                    subsystems.emplace_back(subsystem_name.c_str(), std::stof(temperature));
                    offset = 0;
                    continue;
                }
                if (offset == subsystem_name_offset) {
                    subsystem_name = line;
                }
                else if (offset == temperature_offset) {
                    temperature = line;
                }
                offset++;
            }
        }
        file.close();
        return subsystems;
    }
};
#endif