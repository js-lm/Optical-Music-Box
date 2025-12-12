#include "music_box.hpp"
#include "constants.hpp"

#include <pico/stdlib.h>
#include <stdio.h>

#include "debug_utilities.hpp"

int MusicBox::run(){
    initialize();

    while(true){
        update();
    }

    return 0;
}

void MusicBox::initialize(){
    stdio_init_all();
    
    printf("Music Box Initializing...\n");

    motorManager_.initialize();
    lightSensorManager_.initialize();
    
    printf("Music Box Initialized!\n");
}

void MusicBox::update(){
    motorManager_.update();
    lightSensorManager_.update();


    /* Debug */ {
        if(lightSensorManager_.hasArrived()){
            motorManager_.stop();

            DEBUG_PRINT("Doing stuffs...");
            sleep_ms(75);
            lightSensorManager_.next();

            motorManager_.start();
        }
    } /* Debug */





}