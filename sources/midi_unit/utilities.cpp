#include "midi_manager.hpp"

#include <pico/stdlib.h>
#include <hardware/uart.h>

#include <variant>

#include "constants.hpp"

void MidiManager::setInstrument(units::midi::Channel channel, const midi_data::Instrument &instrument){
    std::visit([channel](auto &&instrumentValue){
        using InstrumentType = std::decay_t<decltype(instrumentValue)>;

        auto statusByte{
            static_cast<uint8_t>(
                constants::midi::ProgramChangeStatus | (channel & constants::midi::ChannelMask)
            )
        };
        auto programNumber{static_cast<uint8_t>(instrumentValue)};

        // set MT32
        if constexpr(std::is_same_v<InstrumentType, instruments::Mt32>){
            uint8_t controlStatusByte{
                static_cast<uint8_t>(
                    constants::midi::ControlChangeStatus | (channel & constants::midi::ChannelMask)
                )
            };
            
            uart_putc_raw(constants::midi::UartInstance, controlStatusByte);
            uart_putc_raw(constants::midi::UartInstance, constants::midi::BankSelectController);
            uart_putc_raw(constants::midi::UartInstance, constants::midi::AlternativeBankValue);
        }

        uart_putc_raw(constants::midi::UartInstance, statusByte);
        uart_putc_raw(constants::midi::UartInstance, programNumber);
    }, instrument);
}