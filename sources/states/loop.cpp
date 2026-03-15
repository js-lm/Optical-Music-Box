#include "music_box.hpp"

#include "debug_utilities.hpp"

#include <optional>

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
    if(timeSinceLastStep_ > units::Ms2Us(constants::runtime::QueueTick)){
        timeSinceLastStep_ = 0;

        while(!commandQueue_.isEmpty()){
            executeNextBufferedCommand();
        }

        nextState();
    }
}

void MusicBox::updateProcessState(){
    const auto colorRow{sensorsManager_.collectSensorData()};

    using namespace constants::color_sensor;
    for(int sensorIndex{0}; sensorIndex < TotalSensorCount; sensorIndex++){
        DEBUG_PRINT("%i ", static_cast<int>(colorRow[SensorIndexMap[sensorIndex]]));

        const units::midi::Note note{static_cast<units::midi::Note>(60 + sensorIndex)};
        const bool isSensorActive{static_cast<uint8_t>(colorRow[SensorIndexMap[sensorIndex]]) != 0};

        std::optional<midi_command::Command> command{};
        if(isSensorActive && !sensorNoteActive_[sensorIndex]){
            command = midi_command::QueuedNoteOn{
                0,
                note,
                constants::runtime::DefaultNoteVelocity
            };
            sensorNoteActive_[sensorIndex] = true;
        }else if(!isSensorActive && sensorNoteActive_[sensorIndex]){
            command = midi_command::QueuedNoteOff{0, note};
            sensorNoteActive_[sensorIndex] = false;
        }

        if(command){
            // if(commandQueue_.isFull()) executeNextBufferedCommand();
            // else commandQueue_.push(std::move(*command));
            if(!commandQueue_.isFull()) commandQueue_.push(std::move(*command));
        }
    }

    lightSensorManager_.next();
    motorManager_.start();

    nextState();
}