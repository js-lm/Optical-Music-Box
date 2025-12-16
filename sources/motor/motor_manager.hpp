#pragma once

#include "aliases.hpp"
#include "constants.hpp"

#include <queue>

class MotorManager{
private:
    bool isRunning_{false};
    bool stepState_{false};
    
    units::TimestampUs lastStepToggleTime_{0};
    units::Us currentStepInterval_{constants::motor::MaxStepInterval};
    units::MsRate targetStepRate_{4};

public:
    MotorManager() = default;
    ~MotorManager() = default;

    void initialize();
    void update();

private:
    void spinMotor();

public:
    void start(bool isForward = true);
    void stop();
};