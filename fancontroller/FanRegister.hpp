#ifndef FANREGISTER_HPP
#define FANREGISTER_HPP
#include <linux/ioctl.h>
struct FanRegister {
    unsigned int reg;
    unsigned int ioctl_number;
    FanRegister() : reg(0x00), ioctl_number(_IOW('k', 0x00, int)) {}
    FanRegister(unsigned int _register) : reg(_register), ioctl_number(_IOW('k', _register, int)) {}
};
#endif