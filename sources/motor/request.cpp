#include "motor_manager.hpp"

#include "constants.hpp"

#include <pico/stdlib.h>

void MotorManager::start(bool isForward){
    isRunning_ = true;

    gpio_put(constants::pins::motor::Enable, 0);
}

void MotorManager::stop(){
    isRunning_ = false;

    gpio_put(constants::pins::motor::Enable, 1);
    gpio_put(constants::pins::motor::Step, 0);
}