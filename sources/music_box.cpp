#include "music_box.hpp"
#include "constants.hpp"

#include <pico/stdlib.h>
#include <stdio.h>

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
    irManager_.initialize();
    
    printf("Music Box Initialized!\n");
}

void MusicBox::update(){
    // motorManager_.update();
    irManager_.update();
}