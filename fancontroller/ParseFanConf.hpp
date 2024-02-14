#ifndef PARSEFANCONF_HPP
#define PARSEFANCONF_HPP
#include <fstream>
#include <string>
#include <vector>
#include "FanInterface.hpp"
class ParseFanConf {
    #define FAN_CONF_FILE "fans.conf"
    #define start_fan "fan config start"
    #define end_fan "fan config end"
    #define register_offset 0
    #define pwm_offset 1
    public:
    // Optimistic parsing for demonstration purposes
    static std::vector<FanInterface> parseFanConf(const std::string& filename) {
        std::vector<FanInterface> fans;
        std::ifstream file(filename);
        bool between = false;
        std::string reg;
        std::string pwm_count;
        int offset = 0;
        while(file.eof() == false) {
            std::string line;
            std::getline(file, line);
            if (line == start_fan) {
                between = true;
                continue;
            }
            if (between) {
                if (line == end_fan) {
                    between = false;
                    fans.push_back(FanInterface(FanRegister(std::stoi(reg, 0, 16)), FanDutyCycle(std::stoi(pwm_count))));
                    offset = 0;
                    continue;
                }
                if (offset == register_offset) {
                    reg = line;
                }
                else if (offset == pwm_offset) {
                    pwm_count = line;
                }
                offset++;
            }
        }
        file.close();
        return fans;
    }
};
#endif