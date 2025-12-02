#pragma once

#include "motor/motor_manager.hpp"

class MusicBox{
private:
    MotorManager motorManager_{};

public:
    MusicBox() = default;
    ~MusicBox() = default;

    int run();

private:
    void initialize();
    void update();
};