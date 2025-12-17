#include "midi_manager.hpp"

#include <pico/stdlib.h>
#include <hardware/uart.h>

#include "constants.hpp"

void MidiManager::initialization(){
    uart_init(constants::midi::UartInstance, constants::midi::BaudRate);
    
    gpio_set_function(constants::pins::MidiTransmit, GPIO_FUNC_UART);
    gpio_set_function(constants::pins::MidiReceive, GPIO_FUNC_UART);
    
    uart_set_hw_flow(constants::midi::UartInstance, false, false);
    
    uart_set_format(
        constants::midi::UartInstance,
        constants::midi::DataBits,
        constants::midi::StopBits,
        UART_PARITY_NONE
    );
}