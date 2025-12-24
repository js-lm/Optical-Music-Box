#pragma once

#include "aliases.hpp"

namespace constants::light_sensor{

    constexpr units::Percentage NoPaperThreshold{.9f};
    constexpr units::Percentage WhiteThreshold{.8f}; // above
    constexpr units::Percentage BlackThreshold{.3f}; // below

} // namespace constants::light_sensor
