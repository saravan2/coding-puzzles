#ifndef SUBSYSTEM_INTERFACE_HPP
#define SUBSYSTEM_INTERFACE_HPP
template <class T>
class SubsystemInterface {
    private: 
    T subsystem_data;
    public:
    SubsystemInterface() {} 
    SubsystemInterface(const char *name, float _temperature) : subsystem_data(name, _temperature) {}
    SubsystemInterface(T _subsystem_data) : subsystem_data(_subsystem_data) {}
    float getTemperature() {
        return subsystem_data.temperature;
    }
    void setTemperature(float _temperature) {
        subsystem_data.temperature = _temperature;
    }   
    T getSubsystemData() {
        return subsystem_data;
    }
};
#endif