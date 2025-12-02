#pragma once

#include <cstddef>

#include "units.hpp"

namespace constants{

    namespace pins{

        namespace motor{

            constexpr int Direction {15};
            constexpr int Step      {14};
            constexpr int Enable    {13};

        } // namespace motor

        namespace color_sensors{

        } // namespace sensors

    } // namespace pins

    namespace system{

        namespace motor{

            constexpr bool ForwardDirection{1};

            constexpr units::Us MaxStepInterval{800};
            // constexpr units::Us TargetStepInterval{120};
            constexpr units::Us AccelerationStep{10};

        } // namespace motor



    } // namespace system

} // namespace constants