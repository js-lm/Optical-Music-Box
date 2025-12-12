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

    // /* DEBUG */ {
    //     // bool DEBUG_shouldBeRunning{static_cast<int>(std::floor(
    //     //     to_ms_since_boot(get_absolute_time()) / 5000.0f
    //     // )) % 2 == 0};
    //     bool DEBUG_shouldBeRunning{true};

    //     if(DEBUG_shouldBeRunning && !isRunning_){
    //         start();
    //         isRunning_ = true;
    //         stepState_ = false;
    //         gpio_put(constants::pins::MotorStep, 0);
    //         currentStepInterval_ = constants::motor::MaxStepInterval;
    //         lastStepToggleTime_ = time_us_64();
    //     }else if(!DEBUG_shouldBeRunning && isRunning_){
    //         stop();
    //         isRunning_ = false;
    //         stepState_ = false;
    //         currentStepInterval_ = constants::motor::MaxStepInterval;
    //     }


    //     targetStepRate_ = static_cast<units::MsRate>(std::max<float>(1.0f, 
    //         4 * (std::sin(to_ms_since_boot(get_absolute_time()) / 1000.0f) + 1
    //     )));

    // } /* DEBUG */

    if(isRunning_) spinMotor();
}