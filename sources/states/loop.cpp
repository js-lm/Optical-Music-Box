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
    /* DEBUG */ {
        const auto colorRow{sensorsManager_.collectSensorData()};

        using namespace constants::color_sensor;
        for(uint8_t instrumentChannel{1}; instrumentChannel <= constants::decoder::NumberOfInstrumentChannel; instrumentChannel++){

            MusicDecoder::Base5<3> base5values{};

            for(int sensorIndex{(instrumentChannel - 1) * 3}, digitIndex{0}; sensorIndex < instrumentChannel * 3; sensorIndex++, digitIndex++){
                DEBUG_PRINT("sensor:%i-%i ", static_cast<int>(colorRow[SensorIndexMap[sensorIndex]]));

                const auto currentColor{colorRow[SensorIndexMap[sensorIndex]]};

                base5values[digitIndex] = static_cast<MusicDecoder::Base5Value>(currentColor); // TODO: This is assuming they are mapped 1:1. Not the safest have to say
            }

            std::optional<midi_command::Command> command{
                musicDecoder_.decode(
                    base5values,
                    instrumentChannel - 1
                )
            };

            if(command && !commandQueue_.isFull()){
                commandQueue_.push(std::move(*command));
            }
        }

        // using namespace constants::color_sensor;
        // for(int sensorIndex{0}; sensorIndex < 9; sensorIndex++){
        //     // DEBUG_PRINT("%i ", static_cast<int>(colorRow[SensorIndexMap[sensorIndex]]));

        //     // const units::midi::Note note{static_cast<units::midi::Note>(60 + sensorIndex)};
        //     // const auto currentColor{colorRow[SensorIndexMap[sensorIndex]]};
        //     // const auto colorIndex{static_cast<uint8_t>(currentColor)};
        //     // const bool isSensorActive{colorIndex != 0};

        //     std::optional<midi_command::Command> command{
        //         musicDecoder_.decode(
        //             MusicDecoder::InstrumentInstruction{

        //             }
        //         )
        //     };

        //     // if(!previousNoteActive_[sensorIndex]){
        //     //     command = midi_command::QueuedNoteOff{0, note};
        //     //     previousNoteActive_[sensorIndex] = std::nullopt;
        //     // }else if(true){
        //     //     command = midi_command::QueuedNoteOn{
        //     //         static_cast<uint8_t>(colorIndex - 1),
        //     //         note,
        //     //         constants::runtime::DefaultNoteVelocity
        //     //     };
        //     //     previousNoteActive_[sensorIndex] = true;
        //     // }

        //     if(command){
        //         if(!commandQueue_.isFull()) commandQueue_.push(std::move(*command));
        //     }
        // }
    } /* DEBUG */

    lightSensorManager_.next();
    motorManager_.start();

    nextState();
}