#pragma once

#include "motor/motor_manager.hpp"
#include "ir_sensor/ir_manager.hpp"

class MusicBox{
private:
    MotorManager    motorManager_{};
    IrManager       irManager_{};

public:
    MusicBox() = default;
    ~MusicBox() = default;

    int run();

private:
    void initialize();
    void update();
};