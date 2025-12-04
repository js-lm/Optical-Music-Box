#include "ir_manager.hpp"

#include "constants.hpp"

#include <hardware/adc.h>

units::Percentage IrManager::getIrReading() const{
    adc_select_input(constants::adc::IrInputChannel); 
    
    return static_cast<float>(adc_read()) / constants::system::MaxAdcValue;
}