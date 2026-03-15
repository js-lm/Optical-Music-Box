#include "motor_manager.hpp"

#include "constants.hpp"

#include <pico/stdlib.h>
#include <algorithm>

void MotorManager::start(bool isForward){
    isRunning_ = true;

    gpio_put(constants::pins::MotorEnable, 0);
}

void MotorManager::stop(){
    isRunning_ = false;

    gpio_put(constants::pins::MotorEnable, 1);
    gpio_put(constants::pins::MotorStep, 0);
}

void MotorManager::setTargetStepRate(units::StepsPerSecond targetStepRate){
    targetStepRate_.store(std::clamp(
        targetStepRate,
        constants::runtime::MinimumStepRate,
        constants::runtime::MaximumStepRate
    ));
}

units::StepsPerSecond MotorManager::targetStepRate() const{
    return targetStepRate_.load();
}