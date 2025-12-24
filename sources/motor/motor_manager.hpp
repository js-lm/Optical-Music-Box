#pragma once

#include "aliases.hpp"
#include "constants.hpp"

#include <atomic>
#include <queue>

class MotorManager{
private:
    std::atomic<bool> isRunning_{false};
    bool stepState_{false};
    
    units::TimestampUs lastStepToggleTime_{0};
    units::Us currentStepInterval_{constants::motor::MaxStepInterval};
    units::MsRate targetStepRate_{constants::motor::DefaultStepRate};

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