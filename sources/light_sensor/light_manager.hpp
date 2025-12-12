#pragma once

#include "aliases.hpp"

class LightSensorManager{
private:
    bool isExpectingBlack_{true};
    bool hasArrived_{false};

public:
    LightSensorManager() = default;
    ~LightSensorManager() = default;

    void initialize();
    void update();

    bool hasArrived() const{ return hasArrived_;}
    void next();

private:
    units::Percentage getLightReading() const;
};
