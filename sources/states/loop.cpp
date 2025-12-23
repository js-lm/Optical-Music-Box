#include "music_box.hpp"

#include "debug_utilities.hpp"

void MusicBox::updateSeekState(){
    lightSensorManager_.update();

    if(lightSensorManager_.hasArrived()){
        motorManager_.stop();
        sensorsManager_.startSampling();
        nextState();
    }
}

void MusicBox::updateWaitState(){
    // DEBUG
    if(timeSinceLastStep_ > units::Ms2Us(200)){
        timeSinceLastStep_ = 0;
        nextState();
    }
}

void MusicBox::updateProcessState(){
    const auto colorRow{sensorsManager_.collectSensorData()};

    using namespace constants::color_sensor;
    for(int sensorIndex{0}; sensorIndex < TotalSensorCount; sensorIndex++){
        DEBUG_PRINT("%i ", static_cast<int>(colorRow[SensorIndexMap[sensorIndex]]));

        if(static_cast<uint8_t>(colorRow[SensorIndexMap[sensorIndex]]) != 0){
            midiManager_.noteOn(0, 60 + sensorIndex, 100);
        }
    }

    lightSensorManager_.next();
    motorManager_.start();

    nextState();
}