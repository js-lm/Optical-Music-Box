#pragma once

#include "reference_profile.hpp"

class Calibrator{
public:
    Calibrator() = default;
    ~Calibrator() = default;

    calibrator::ReferenceProfile getReferenceProfile() const;
};