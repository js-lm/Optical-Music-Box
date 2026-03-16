#pragma once

#include "aliases.hpp"
#include "constants.hpp"

#include <array>
#include <cstdint>

namespace calibrator{

    struct BaseValues{
        color_sensor_data::RawColorReading white;
        color_sensor_data::RawColorReading red;
        color_sensor_data::RawColorReading green;
        color_sensor_data::RawColorReading blue;
        color_sensor_data::RawColorReading black;
        color_sensor_data::RawColorReading noPaper;
    };

    using ReferenceProfile = std::array<BaseValues, constants::color_sensor::TotalSensorCount>;

} // namespace calibrator