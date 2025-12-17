#include "midi_manager.hpp"

#include <pico/stdlib.h>
#include <hardware/uart.h>

#include "constants.hpp"

void MidiManager::setBank(Channel channel, bool useAlternativeBank){
    if(channel > constants::midi::MaximumChannel) return;

    uint8_t statusByte{
        static_cast<uint8_t>(
            constants::midi::ControlChangeStatus | (channel & constants::midi::ChannelMask)
        )
    };
    uint8_t bankValue{
        useAlternativeBank ? constants::midi::AlternativeBankValue : constants::midi::DefaultBankValue
    };
    
    uart_putc_raw(constants::midi::UartInstance, statusByte);
    uart_putc_raw(constants::midi::UartInstance, constants::midi::BankSelectController);
    uart_putc_raw(constants::midi::UartInstance, bankValue);
}

void MidiManager::setInstrument(Channel channel, Instrument instrument){
    if(channel > constants::midi::MaximumChannel) return;

    uint8_t statusByte{
        static_cast<uint8_t>(
            constants::midi::ProgramChangeStatus | (channel & constants::midi::ChannelMask)
        )
    };

    uint8_t programNumber{static_cast<uint8_t>(instrument)};
    
    uart_putc_raw(constants::midi::UartInstance, statusByte);
    uart_putc_raw(constants::midi::UartInstance, programNumber);
}