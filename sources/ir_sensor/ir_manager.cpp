#include "ir_manager.hpp"

#include <hardware/adc.h>

#include <stdio.h>
#include <pico/stdlib.h>

#include "constants.hpp"

#include "debug_utilities.hpp"

void IrManager::initialize(){
    adc_init();

    adc_gpio_init(constants::pins::IrAnalogOut);

    adc_select_input(constants::adc::IrInputChannel);
    
}

void IrManager::update(){
    /* DEBUG */ {
        adc_select_input(constants::adc::IrInputChannel);

        DEBUG_PRINT_TIMED(100, "IR raw: %d, getIrReading(): %.3f\n", adc_read(), getIrReading());
    } /* DEBUG */
}