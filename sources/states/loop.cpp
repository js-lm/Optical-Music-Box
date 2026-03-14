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
    midi_command::ExecutionContext executionContext{commandState_, midiManager_, 0};

    using namespace constants::color_sensor;
    for(int sensorIndex{0}; sensorIndex < TotalSensorCount; sensorIndex++){
        DEBUG_PRINT("%i ", static_cast<int>(colorRow[SensorIndexMap[sensorIndex]]));

        const units::midi::Note note{static_cast<units::midi::Note>(60 + sensorIndex)};
        executionContext.channel = 0;

        midi_data::UniqueEventPointer command{};
        if(static_cast<uint8_t>(colorRow[SensorIndexMap[sensorIndex]]) != 0){
            command = std::make_unique<midi_command::NoteOn>(0, note);
        }else{
            command = std::make_unique<midi_command::NoteOff>(0, note);
        }

        if(command){
            command->execute(executionContext);
        }
    }

    lightSensorManager_.next();
    motorManager_.start();

    nextState();
}