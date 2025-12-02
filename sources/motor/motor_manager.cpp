#include "motor_manager.hpp"

#include "constants.hpp"
#include "units.hpp"

#include <pico/stdlib.h>

#include <algorithm>
#include <cmath>
#include <cstdint>

void MotorManager::initialize(){
    gpio_init(constants::pins::motor::Direction);
    gpio_set_dir(constants::pins::motor::Direction, GPIO_OUT);

    gpio_init(constants::pins::motor::Step);
    gpio_set_dir(constants::pins::motor::Step, GPIO_OUT);

    gpio_init(constants::pins::motor::Enable);
    gpio_set_dir(constants::pins::motor::Enable, GPIO_OUT);


    gpio_put(constants::pins::motor::Direction, constants::system::motor::ForwardDirection);
}

void MotorManager::update(){

    /* DEBUG */ {
        // bool DEBUG_shouldBeRunning{static_cast<int>(std::floor(
        //     to_ms_since_boot(get_absolute_time()) / 5000.0f
        // )) % 2 == 0};
        bool DEBUG_shouldBeRunning{true};

        if(DEBUG_shouldBeRunning && !isRunning_){
            start();
            isRunning_ = true;
            stepState_ = false;
            gpio_put(constants::pins::motor::Step, 0);
            currentStepInterval_ = constants::system::motor::MaxStepInterval;
            lastStepToggleTime_ = time_us_64();
        }else if(!DEBUG_shouldBeRunning && isRunning_){
            stop();
            isRunning_ = false;
            stepState_ = false;
            currentStepInterval_ = constants::system::motor::MaxStepInterval;
        }


        targetStepRate_ = static_cast<units::MsRate>(std::max<float>(1.0f, 
            4 * (std::sin(to_ms_since_boot(get_absolute_time()) / 1000.0f) + 1
        )));

    } /* DEBUG */

    if(isRunning_) spinMotor();
}