#ifndef IPC_INTERFACE_HPP
#define IPC_INTERFACE_HPP
#include <iostream>
#include <vector>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdexcept>
#include "IpcData.hpp"

template <class T>
class IPCInterface {
    private:
    const char* IPC_KEY = "IpcData";
    const char IPC_ID = 'A';
    IpcData<T>* data;
    bool initialized = false;

    public:
    IPCInterface() {
        key_t key = ftok(IPC_KEY, IPC_ID);
        int shmid = shmget(key, sizeof(T), 0666 | IPC_CREAT);
        if (shmid < 0) {
            std::cerr << "Error: Unable to create shared memory" << std::endl;
            throw std::runtime_error("Unable to create shared memory");
        }
        data = static_cast<IpcData<T>*>(shmat(shmid, (void*)0, 0));
        if (data == reinterpret_cast<IpcData<T>*>(-1)) {
            std::cerr << "Error: Unable to attach shared memory" << std::endl;
            throw std::runtime_error("Unable to attach shared memory");
        }
        initialized = true;
    }

    ~IPCInterface() {
        if (!initialized) {
            return;
        }
        if (shmdt(data) == -1) {
            std::cerr << "Error: Unable to detach shared memory" << std::endl;
        }
    }

    std::vector<T> readData() {
        if (!initialized) {
            std::cerr << "Error: Shared memory not initialized" << std::endl;
            throw std::runtime_error("Shared memory not initialized");
        }
        std::vector<T> newData;
        for (unsigned int i = 0; i < data->count; i++) {
            newData.push_back(data->SubsystemData[i]);
        }
        return newData;
    }

    void writeData(std::vector<T> newData) {
        if (!initialized) {
            std::cerr << "Error: Shared memory not initialized" << std::endl;
            throw std::runtime_error("Shared memory not initialized");
        }
        data->count = newData.size() < data->getMaxSubsystems() ? newData.size() : data->getMaxSubsystems();
        for (unsigned int i = 0; i < data->count; i++) {
            data->SubsystemData[i] = newData[i];
        }
    }

    void clearData() {
        if (!initialized) {
            std::cerr << "Error: Shared memory not initialized" << std::endl;
            throw std::runtime_error("Shared memory not initialized");
        }
        data->count = 0;
    }
};
#endif