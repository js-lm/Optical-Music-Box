#include "music_box.hpp"
#include "constants.hpp"

#include <pico/stdlib.h>
#include <pico/multicore.h>
#include <stdio.h>

#include "debug_utilities.hpp"

int MusicBox::run(){
    sleep_ms(2000);

    initialize();

    while(true){
        update();
    }

    return 0;
}

void MusicBox::initialize(){
    stdio_init_all();
    
    DEBUG_PRINT("Music Box Initializing...");

    motorManager_.initialize();
    lightSensorManager_.initialize();
    sensorsManager_.initialize();
    midiManager_.initialization();
    
    motorManagerPointer_ = &motorManager_;
    multicore_launch_core1(core1Entry);
    
    DEBUG_PRINT("Music Box Initialized!");
}

void MusicBox::update(){
    lightSensorManager_.update();

    midiManager_.setInstrument(0, MidiManager::Instrument::Music_Box);

    /* DEBUG */ {
        if(lightSensorManager_.hasArrived()){
            motorManager_.stop();

            const auto colorRow{sensorsManager_.collectSensorData()};

            // TODO: I suspect the issue might be related to colors being collected 
            // even while the motor is moving
            // I need a state machine

            DEBUG_PRINT("%i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i ", 
                static_cast<int>(colorRow[0]),
                static_cast<int>(colorRow[8]),
                static_cast<int>(colorRow[1]),
                static_cast<int>(colorRow[9]),
                static_cast<int>(colorRow[2]),
                static_cast<int>(colorRow[10]),
                static_cast<int>(colorRow[3]),
                static_cast<int>(colorRow[11]),
                static_cast<int>(colorRow[4]),
                static_cast<int>(colorRow[12]),
                static_cast<int>(colorRow[5]),
                static_cast<int>(colorRow[13]),
                static_cast<int>(colorRow[6]),
                static_cast<int>(colorRow[14]),
                static_cast<int>(colorRow[7]),
                static_cast<int>(colorRow[15])
            );

            if(static_cast<int>(colorRow[0]) != 0) midiManager_.noteOn(0, 60, 100);
            if(static_cast<int>(colorRow[8]) != 0) midiManager_.noteOn(0, 61, 100);
            if(static_cast<int>(colorRow[1]) != 0) midiManager_.noteOn(0, 62, 100);
            if(static_cast<int>(colorRow[9]) != 0) midiManager_.noteOn(0, 63, 100);
            if(static_cast<int>(colorRow[2]) != 0) midiManager_.noteOn(0, 64, 100);
            if(static_cast<int>(colorRow[10]) != 0) midiManager_.noteOn(0, 65, 100);
            if(static_cast<int>(colorRow[3]) != 0) midiManager_.noteOn(0, 66, 100);
            if(static_cast<int>(colorRow[11]) != 0) midiManager_.noteOn(0, 67, 100);
            if(static_cast<int>(colorRow[4]) != 0) midiManager_.noteOn(0, 68, 100);
            if(static_cast<int>(colorRow[12]) != 0) midiManager_.noteOn(0, 69, 100);
            if(static_cast<int>(colorRow[5]) != 0) midiManager_.noteOn(0, 70, 100);
            if(static_cast<int>(colorRow[13]) != 0) midiManager_.noteOn(0, 71, 100);
            if(static_cast<int>(colorRow[6]) != 0) midiManager_.noteOn(0, 72, 100);
            if(static_cast<int>(colorRow[14]) != 0) midiManager_.noteOn(0, 73, 100);
            if(static_cast<int>(colorRow[7]) != 0) midiManager_.noteOn(0, 74, 100);
            if(static_cast<int>(colorRow[15]) != 0) midiManager_.noteOn(0, 75, 100);

            sleep_ms(200);

            midiManager_.silence(0);

            lightSensorManager_.next();
            motorManager_.start();
        }

    } /* DEBUG */

}

void MusicBox::core1Entry(){
    while(true){
        if(motorManagerPointer_) motorManagerPointer_->update();

        tight_loop_contents();
    }
}