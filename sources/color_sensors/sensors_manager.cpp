#include "sensors_manager.hpp"

#include "constants.hpp"
#include "debug_utilities.hpp"

#include <hardware/i2c.h>
#include <pico/stdlib.h>
#include <stdio.h>

void SensorsManager::initialize(){
    i2c_init(i2c0, constants::i2c::Frequency);

    gpio_set_function(constants::pins::MuxData, GPIO_FUNC_I2C);
    gpio_set_function(constants::pins::MuxClock, GPIO_FUNC_I2C);
    gpio_pull_up(constants::pins::MuxData);
    gpio_pull_up(constants::pins::MuxClock);

    initializeSensors();

    lastReadTime_ = time_us_64();
}