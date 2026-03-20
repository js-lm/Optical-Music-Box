#pragma once

#include "reference_profile.hpp"

#include "aliases.hpp"

class Calibrator{
public:
    Calibrator() = default;
    ~Calibrator() = default;

    calibrator::ReferenceProfile getReferenceProfile() const;

// private:
//     static calibrator::RatioColorReading toRatioColorReading(const color_sensor_data::RawColorReading &reading);
//     static calibrator::RatioBaseValues toRatioBaseValues(const calibrator::BaseValues &baseValues);
//     static calibrator::ReferenceProfile toRatioReferenceProfile(const calibrator::ReferenceProfile &referenceProfile);
};