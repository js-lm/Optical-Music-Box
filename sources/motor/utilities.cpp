#include "motor_manager.hpp"

#include "constants.hpp"

#include <pico/stdlib.h>
#include <algorithm>

void MotorManager::spinMotor(){
    units::TimestampUs currentTime{time_us_64()};

    if(currentTime - lastStepToggleTime_ >= currentStepInterval_){
        stepState_ = !stepState_;

    gpio_put(constants::pins::MotorStep, stepState_);

        lastStepToggleTime_ = currentTime;

        // if(!stepState_ && currentStepInterval_ > constants::motor::TargetStepInterval){
        if(!stepState_){
            units::Us targetInterval{constants::motor::MaxStepInterval};
            const units::StepsPerSecond targetStepRate{targetStepRate_.load()};

            if(targetStepRate > 0){
                const float toggleRate{targetStepRate * 2.0f};

                units::Us computedInterval{
                    static_cast<units::Us>(toggleRate ? (1000000.0f / toggleRate) : .0f)
                };

                if(computedInterval == 0) computedInterval = 1;

                targetInterval = std::min(computedInterval, constants::motor::MaxStepInterval);
            }

            if(currentStepInterval_ > targetInterval){
                currentStepInterval_ = std::max(currentStepInterval_ - constants::motor::AccelerationStep, targetInterval);
            }else if(currentStepInterval_ < targetInterval){
                currentStepInterval_ = std::min(currentStepInterval_ + constants::motor::AccelerationStep, targetInterval);
            }
        }
    }
}