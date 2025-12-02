#pragma once

#include "units.hpp"
#include "constants.hpp"

#include <queue>

class MotorManager{
private:

    // std::queue<Request> requests_;

    bool isRunning_{false};
    bool stepState_{false};
    units::TimestampUs lastStepToggleTime_{0};
    units::Us currentStepInterval_{constants::system::motor::MaxStepInterval};
    units::MsRate targetStepRate_{4};

public:
    MotorManager() = default;
    ~MotorManager() = default;

    void initialize();
    void update();

private:
    void spinMotor();

private:
    void start(bool isForward = true);
    void stop();

    // void addRequest(bool isForward, units::Ms duration);
    // void nextRequest();
    // void clearRequest();
};