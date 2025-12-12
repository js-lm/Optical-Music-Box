#pragma once

#include "motor/motor_manager.hpp"
#include "light_sensor/light_manager.hpp"

class MusicBox{
private:
    MotorManager        motorManager_{};
    LightSensorManager  lightSensorManager_{};

public:
    MusicBox() = default;
    ~MusicBox() = default;

    int run();

private:
    void initialize();
    void update();
};