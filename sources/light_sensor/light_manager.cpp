#include "light_manager.hpp"

#include <hardware/adc.h>

#include <stdio.h>
#include <pico/stdlib.h>

#include "constants.hpp"

#include "debug_utilities.hpp"

void LightSensorManager::initialize(){
    adc_init();

    adc_gpio_init(constants::pins::LightAnalogOut);

    adc_select_input(constants::adc::LightInputChannel);
    
}

void LightSensorManager::update(){
    // /* DEBUG */ {
    //     adc_select_input(constants::adc::LightInputChannel);

    //     DEBUG_PRINT_TIMED(100, "IR raw: %d, getIrReading(): %.3f, hasArrived_: %b\n", 
    //         adc_read(), getLightReading(), hasArrived_
    //     );

    //     DEBUG_PRINT_IF_CHANGED("isExpectingBlack_: %b\n", isExpectingBlack_);
    //     DEBUG_PRINT_IF_CHANGED("hasArrived_: %b\n", hasArrived_);
    // } /* DEBUG */

    const auto &lightReading{getLightReading()};

    if(isExpectingBlack_){
        hasArrived_ = lightReading < constants::light_sensor::BlackThreshold;
    }else{
        hasArrived_ = lightReading > constants::light_sensor::WhiteThreshold;
    }
}
