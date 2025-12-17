#include "music_box.hpp"
#include "constants.hpp"

#include <pico/stdlib.h>
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
    
    DEBUG_PRINT("Music Box Initialized!");
}

void MusicBox::update(){
    // motorManager_.update();
    // lightSensorManager_.update();

    /* DEBUG */ {
        // if(lightSensorManager_.hasArrived()){
        //     motorManager_.stop();

        //     const auto colorRow{sensorsManager_.collectSensorData()};

        //     // TODO: I suspect the issue might be related to colors being collected 
        //     // even while the motor is moving
        //     // I need a state machine

        //     DEBUG_PRINT("%i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i ", 
        //         static_cast<int>(colorRow[0]),
        //         static_cast<int>(colorRow[8]),
        //         static_cast<int>(colorRow[1]),
        //         static_cast<int>(colorRow[9]),
        //         static_cast<int>(colorRow[2]),
        //         static_cast<int>(colorRow[10]),
        //         static_cast<int>(colorRow[3]),
        //         static_cast<int>(colorRow[11]),
        //         static_cast<int>(colorRow[4]),
        //         static_cast<int>(colorRow[12]),
        //         static_cast<int>(colorRow[5]),
        //         static_cast<int>(colorRow[13]),
        //         static_cast<int>(colorRow[6]),
        //         static_cast<int>(colorRow[14]),
        //         static_cast<int>(colorRow[7]),
        //         static_cast<int>(colorRow[15])
        //     );

        //     sleep_ms(200);
        //     lightSensorManager_.next();

        //     motorManager_.start();
        // }

        midiManager_.setInstrument(0, MidiManager::Instrument::Music_Box);
        
        const uint8_t notes[]{60, 62, 64, 65, 67, 69, 71, 72};

        static int instrument{0};

        for(int i{-20}; i < 40; i++){
            // for(const auto &note : notes){
            //     midiManager_.noteOn(0, note + i, 100);
            //     sleep_ms(300);
            //     midiManager_.noteOff(0, note + i);
            //     sleep_ms(50);
            // }
            
            // sleep_ms(500);
            
        
            // // midiManager_.noteOn(0, 60 + i, 80);
            // // midiManager_.noteOn(0, 64 + i, 80);
            // // midiManager_.noteOn(0, 67 + i, 80);
            // // sleep_ms(100);
            // // midiManager_.silence(0);
            // // midiManager_.noteOn(0, 60 + i, 80);
            // // midiManager_.noteOn(0, 64 + i, 80);
            // // midiManager_.noteOn(0, 67 + i, 80);
            // // sleep_ms(100);
            // // midiManager_.silence(0);
            
            // sleep_ms(500);
            
            // midiManager_.setBank(0, true);
            // midiManager_.setInstrument(0, static_cast<MidiManager::Instrument>(std::min(127, instrument)));
            // sleep_ms(100);
            
            for(const auto &note : notes){
                midiManager_.noteOn(0, note + i, 100);
                sleep_ms(150);
                midiManager_.noteOff(0, note + i);
                sleep_ms(25);
            }
            
            midiManager_.setBank(0, false);
            midiManager_.setInstrument(0, static_cast<MidiManager::Instrument>(std::min(127, instrument)));
            
            sleep_ms(250);

            instrument++;
        }
    } /* DEBUG */





}