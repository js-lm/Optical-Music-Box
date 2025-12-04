#include "motor_manager.hpp"

#include "constants.hpp"

#include <pico/stdlib.h>

void MotorManager::start(bool isForward){
    isRunning_ = true;

    gpio_put(constants::pins::MotorEnable, 0);
}

void MotorManager::stop(){
    isRunning_ = false;

    gpio_put(constants::pins::MotorEnable, 1);
    gpio_put(constants::pins::MotorStep, 0);
}