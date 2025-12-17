#pragma once

#include "motor/motor_manager.hpp"
#include "light_sensor/light_manager.hpp"
#include "color_sensors/sensors_manager.hpp"
#include "midi_unit/midi_manager.hpp"

class MusicBox{
private:
    MotorManager        motorManager_{};
    LightSensorManager  lightSensorManager_{};
    SensorsManager      sensorsManager_{};
    MidiManager         midiManager_{};

public:
    MusicBox() = default;
    ~MusicBox() = default;

    int run();

private:
    void initialize();
    void update();
};