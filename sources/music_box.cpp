#include "music_box.hpp"
#include "constants.hpp"

#include <pico/stdlib.h>

int MusicBox::run(){
    initialize();

    while(true){
        update();
    }

    return 0;
}

void MusicBox::initialize(){
    motorManager_.initialize();
}

void MusicBox::update(){
    motorManager_.update();
}