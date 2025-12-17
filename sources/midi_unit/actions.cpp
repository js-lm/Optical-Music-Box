#include "midi_manager.hpp"

#include <pico/stdlib.h>
#include <hardware/uart.h>

#include "constants.hpp"

void MidiManager::noteOn(Channel channel, Note note, Velocity velocity){
    if(channel > constants::midi::MaximumChannel
    || note > constants::midi::MaximumNote
    || velocity > constants::midi::MaximumVelocity
    ){
        return;
    }
    
    uint8_t statusByte{
        static_cast<uint8_t>(
            constants::midi::NoteOnStatus | (channel & constants::midi::ChannelMask)
        )
    };
    
    uart_putc_raw(constants::midi::UartInstance, statusByte);
    uart_putc_raw(constants::midi::UartInstance, note);
    uart_putc_raw(constants::midi::UartInstance, velocity);
}

void MidiManager::noteOff(Channel channel, Note note){
    if(channel > constants::midi::MaximumChannel || note > constants::midi::MaximumNote){
        return;
    }
    
    uint8_t statusByte{
        static_cast<uint8_t>(
            constants::midi::NoteOffStatus | (channel & constants::midi::ChannelMask)
        )
    };
    
    uart_putc_raw(constants::midi::UartInstance, statusByte);
    uart_putc_raw(constants::midi::UartInstance, note);
    uart_putc_raw(constants::midi::UartInstance, 0);
}

void MidiManager::playChord(Channel channel, Chord chord, Style style, BPM bpm){

}

void MidiManager::stopChord(Channel channel){

}

void MidiManager::silence(Channel channel){
    if(channel > constants::midi::MaximumChannel) return;

    uint8_t statusByte{
        static_cast<uint8_t>(
            constants::midi::ControlChangeStatus | (channel & constants::midi::ChannelMask)
        )
    };
    
    uart_putc_raw(constants::midi::UartInstance, statusByte);
    uart_putc_raw(constants::midi::UartInstance, constants::midi::AllSoundOffController); 
    uart_putc_raw(constants::midi::UartInstance, constants::midi::ControllerValueOff);
}