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
                const uint32_t toggleRate{static_cast<uint32_t>(targetStepRate) * 2U};
                units::Us computedInterval{
                    toggleRate
                        ? static_cast<units::Us>((1000000ULL + (toggleRate / 2U)) / toggleRate)
                        : 0
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