
#ifndef FAN_INTERFACE_HPP
#define FAN_INTERFACE_HPP
#include "FanRegister.hpp"
#include "FanDutyCycle.hpp"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
class FanInterface {
    private:
    #define DEVICE_FILE "/dev/control_fan"
    FanRegister fan_register;
    FanDutyCycle duty_cycle;

    public:
    FanInterface() {}
    FanInterface(FanRegister _register, FanDutyCycle _duty_cycle) : fan_register(_register), duty_cycle(_duty_cycle) {}
    
    void setDutyCycle(FanDutyCycle duty_cycle) {
        this->duty_cycle = duty_cycle;
    }
    
    FanDutyCycle getDutyCycle() {
        return duty_cycle;
    }
    
    void setDutyCyclePercentage(float duty_cycle_percentage) {
        FanDutyCycle duty_cycle = getDutyCycle();
        duty_cycle.current_pwm_count = (int)(duty_cycle.max_pwm_count * duty_cycle_percentage);
        setDutyCycle(duty_cycle);
    }
    
    float getDutyCyclePercentage() {
        FanDutyCycle duty_cycle = getDutyCycle();
        return (float)duty_cycle.current_pwm_count / (float)duty_cycle.max_pwm_count;
    }
    
    FanRegister getFanRegister() {
        return fan_register;
    }

    int setFanRegister() {
        int fd = open(DEVICE_FILE, O_RDWR);
        if (fd == -1) {
            std::cerr << "Failed to open device file" << std::endl;
            return -1;
        }

        if (ioctl(fd, fan_register.ioctl_number, &duty_cycle.current_pwm_count) == -1) {
            std::cerr << "Failed to set fan duty cycle" << std::endl;
            close(fd);
            return -1;
        }
        close(fd);
        return 0;
    }

    int mock_setFanRegister() {
        std::cout << "Setting fan register " << fan_register.reg \
                  << " with duty cycle factor " << getDutyCyclePercentage() \
                  << " ( " << duty_cycle.current_pwm_count << " )"  << std::endl;
        return 0;
    }   

};
#endif