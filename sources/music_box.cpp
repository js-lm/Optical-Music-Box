#include "music_box.hpp"
#include "constants.hpp"

#include <pico/stdlib.h>
#include <pico/multicore.h>

#include <magic_enum/magic_enum.hpp>

#include "debug_utilities.hpp"

int MusicBox::run(){
    DEBUG_SLEEP_MS(2000);

    initialize();

    while(true){
        update();
    }

    return 0;
}

void MusicBox::initialize(){
    stdio_init_all();
    
    DEBUG_PRINT("Music Box Initializing...");

    lastUpdateTime_ = time_us_64();
    state_ = State::Seek;

    motorManager_.initialize();
    lightSensorManager_.initialize();
    sensorsManager_.initialize();
    midiManager_.initialization();
    
    motorManagerPointer_ = &motorManager_;
    multicore_launch_core1(core1Entry);
    
    DEBUG_PRINT("Music Box Initialized!");

    /* DEBUG */ {
        // channelInstruments_ = {
        //     {Channel::Red, Instrument::Grand_Piano_1},
        //     {Channel::Yellow, Instrument::Marimba},
        //     {Channel::Green, Instrument::Pizzicato_Strings},
        //     {Channel::Blue, Instrument::Flute},
        //     {Channel::Black, Instrument::Tinkle_Bell}
        // };

        // for(const auto &[channel, instrument] : channelInstruments_){
        //     midiManager_.setInstrument(static_cast<uint8_t>(channel), instrument);
        // }
        midiManager_.setInstrument(0, Instrument::Grand_Piano_1);
    } /* DEBUG */
}

void MusicBox::update(){
    updateTimers();

    switch(state_){
    case State::Calibrate_Markers: updateCalibrateMarkersState(); break;
    case State::Calibrate_Sensors: updateCalibrateSensorsState(); break;

    case State::Configure_Metadata:     updateConfigureMetadataState(); break;
    case State::Configure_Instruments:  updateConfigureInstrumentsState(); break;

    case State::Seek:       updateSeekState(); break;
    case State::Wait:       updateWaitState(); break;
    case State::Process:    updateProcessState(); break;

    default: break;
    }

    DEBUG_PRINT_IF_CHANGED("State changed to %s", magic_enum::enum_name(state_));
}

void MusicBox::core1Entry(){
    while(true){
        if(motorManagerPointer_) motorManagerPointer_->update();

        tight_loop_contents();
    }
}

void MusicBox::nextState(){
    constexpr auto values{magic_enum::enum_values<State>()};
    constexpr auto seekIndex{static_cast<uint8_t>(State::Seek)};
    
    auto currentIndex{static_cast<uint8_t>(state_)};
    auto nextIndex{seekIndex + ((currentIndex - seekIndex + 1) % (values.size() - seekIndex))};
    
    state_ = values[nextIndex];
}

void MusicBox::updateTimers(){
    const units::TimestampUs currentTime{time_us_64()};
    const units::Us deltaTime{currentTime - static_cast<units::Us>(lastUpdateTime_)};
    
    timeSinceLastStep_ += deltaTime;
    
    lastUpdateTime_ = currentTime;
}