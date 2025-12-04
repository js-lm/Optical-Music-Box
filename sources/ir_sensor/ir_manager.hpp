#pragma once

#include "aliases.hpp"

class IrManager{
private:
    bool canProceed_{false};

    bool isExpectingBlack_;

public:
    IrManager() = default;
    ~IrManager() = default;

    void initialize();
    void update();

    bool canProceedToNextRow() const{ return canProceed_;}

private:
    units::Percentage getIrReading() const;
};