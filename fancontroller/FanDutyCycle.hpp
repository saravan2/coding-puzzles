#ifndef FANDUTYCYCLE_HPP
#define FANDUTYCYCLE_HPP
struct FanDutyCycle {
    int current_pwm_count;
    int max_pwm_count;
    FanDutyCycle() : current_pwm_count(0), max_pwm_count(0) {}
    FanDutyCycle(int max_pwm_count) : current_pwm_count(0), max_pwm_count(max_pwm_count) {}
};
#endif