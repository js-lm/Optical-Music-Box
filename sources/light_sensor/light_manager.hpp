#pragma once

#include "aliases.hpp"

class LightSensorManager{
private:
    bool canProceed_{false};

    bool isExpectingBlack_;

public:
    LightSensorManager() = default;
    ~LightSensorManager() = default;

    void initialize();
    void update();

    bool canProceedToNextRow() const{ return canProceed_;}

private:
    units::Percentage getLightReading() const;
};
