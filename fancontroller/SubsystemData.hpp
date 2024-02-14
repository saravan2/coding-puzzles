#ifndef SUBSYSTEMDATA_HPP
#define SUBSYSTEMDATA_HPP
#include <cstring>
struct SubsystemData {
    char subsystem_name[20];
    float temperature;
    SubsystemData() : subsystem_name("__sub__"), temperature(0.0) {}
    SubsystemData(float _temperature) : subsystem_name("__sub__"), temperature(_temperature) {}
    SubsystemData(const char* _subsystem_name, float _temperature) {
        strncpy(subsystem_name, _subsystem_name, 20);
        temperature = _temperature;
    }
};
#endif