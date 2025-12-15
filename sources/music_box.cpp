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
    
    DEBUG_PRINT("Music Box Initialized!");
}

void MusicBox::update(){
    // motorManager_.update();
    // lightSensorManager_.update();
    sensorsManager_.update();

    // /* DEBUG */ {
    //     if(lightSensorManager_.hasArrived()){
    //         motorManager_.stop();

    //         DEBUG_PRINT("Doing stuffs...");
    //         sleep_ms(250);
    //         lightSensorManager_.next();

    //         motorManager_.start();
    //     }
    // } /* DEBUG */





}