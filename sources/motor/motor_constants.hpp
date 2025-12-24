#pragma once

#include <cstdint>

#include "aliases.hpp"

namespace constants::motor{

    constexpr bool ForwardDirection{1};
    constexpr units::Us MaxStepInterval{800};
    constexpr units::Us AccelerationStep{10};

    constexpr uint8_t DefaultStepRate{4};

} // namespace constants::motor
