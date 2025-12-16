#include "motor_manager.hpp"

#include "constants.hpp"
#include "aliases.hpp"

#include <pico/stdlib.h>

#include <algorithm>
#include <cmath>
#include <cstdint>

void MotorManager::initialize(){
    gpio_init(constants::pins::MotorDirection);
    gpio_set_dir(constants::pins::MotorDirection, GPIO_OUT);

    gpio_init(constants::pins::MotorStep);
    gpio_set_dir(constants::pins::MotorStep, GPIO_OUT);

    gpio_init(constants::pins::MotorEnable);
    gpio_set_dir(constants::pins::MotorEnable, GPIO_OUT);


    gpio_put(constants::pins::MotorDirection, constants::motor::ForwardDirection);
}

void MotorManager::update(){
    if(isRunning_) spinMotor();
}