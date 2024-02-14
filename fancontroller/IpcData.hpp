#ifndef IPCDATA_HPP
#define IPCDATA_HPP
#include<vector>
template <class T>
struct IpcData {
    #define MAX_SUBSYSTEMS 10
    unsigned int count;
    T SubsystemData[MAX_SUBSYSTEMS];
    IpcData() : count(0) {}
    size_t getMaxSubsystems() {
        return (size_t)MAX_SUBSYSTEMS;
    }
};
#endif