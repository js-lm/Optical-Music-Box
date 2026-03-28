#pragma once

#include "sensors_manager.hpp"

namespace constants::color_sensor::error_bias{

/*
    Not all sensors and colors are created equal (idk why for sensors)
    Some are more likely to be wrong than others,
    so I created a kinda *magic* fix based on the test results
    
    Hopefully it's temporary and I can find out the true culprit
    
    Multiplier for the penalty:
    - lower = known frequent error (discounts penalty to encourage the correction)
    - higher = rare error (increases penalty to avoid modifying stable sensors)
    - 1 = standard cost
*/

    // TODO: bitwise?
    inline constexpr float getPenaltyMultiplier(
        size_t                  sensorIndex, // the physical order index from left to right
        SensorsManager::Color   fromColor,
        SensorsManager::Color   toColor
    ){
        using Color = SensorsManager::Color;

        switch(sensorIndex){
        case 0:{
            if(fromColor == Color::Blue  && toColor == Color::Green) return .2f;
            if(fromColor == Color::Green && toColor == Color::Red)   return .55f;
            if(fromColor == Color::Blue  && toColor == Color::Black) return .7f;
            return .9f;
        }

        case 1:{
            if(fromColor == Color::Blue  && toColor == Color::Green) return .25f;
            if(fromColor == Color::Green && toColor == Color::Blue)  return .45f;
            if(fromColor == Color::Red   && toColor == Color::Blue)  return .65f;
            return 1.0f;
        }

        case 2:{
            if(fromColor == Color::Blue  && toColor == Color::Green) return 1.2f;
            if(fromColor == Color::Blue  && toColor == Color::Black) return 1.5f;
            if(fromColor == Color::Red   && toColor == Color::Green) return 1.6f;
            return 3.5f;
        }

        case 3:{
            if(fromColor == Color::Blue  && toColor == Color::Green) return .22f;
            if(fromColor == Color::Green && toColor == Color::Blue)  return .45f;
            if(fromColor == Color::Blue  && toColor == Color::Black) return .65f;
            return .95f;
        }

        case 4:{
            if(fromColor == Color::Blue && toColor == Color::Green) return 1.3f;
            if(fromColor == Color::Red  && toColor == Color::Green) return 1.6f;
            return 3.0f;
        }

        case 5:{
            if(fromColor == Color::Blue  && toColor == Color::Black) return .5f;
            if(fromColor == Color::Blue  && toColor == Color::Green) return .7f;
            if(fromColor == Color::Green && toColor == Color::Blue)  return .8f;
            return 1.1f;
        }

        case 6:{
            if(fromColor == Color::Green && toColor == Color::Blue)  return 1.4f;
            if(fromColor == Color::Blue  && toColor == Color::Green) return 2.2f;
            return 6.5f;
        }

        case 7:{
            if(fromColor == Color::Red && toColor == Color::Green) return .8f;
            return 2.8f;
        }

        case 8:{
            if(fromColor == Color::Blue && toColor == Color::Black) return .7f;
            if(fromColor == Color::Red  && toColor == Color::Green) return 1.2f;
            return 1.5f;
        }

        case 9:{
            return 8.0f;
        }

        case 10:{
            if(fromColor == Color::Blue && toColor == Color::Black) return .9f;
            return 2.2f;
        }

        case 11:{
            if(fromColor == Color::Blue  && toColor == Color::Green) return .25f;
            if(fromColor == Color::Green && toColor == Color::Blue)  return .5f;
            return 1.0f;
        }

        case 12:{
            if(fromColor == Color::Blue && toColor == Color::Black) return .9f;
            return 2.0f;
        }

        case 13:{
            if(fromColor == Color::Blue  && toColor == Color::Green) return .3f;
            if(fromColor == Color::Green && toColor == Color::Blue)  return .55f;
            return 1.0f;
        }

        case 14:{
            if(fromColor == Color::Green && toColor == Color::Red)   return .35f;
            if(fromColor == Color::Blue  && toColor == Color::Black) return .45f;
            if(fromColor == Color::Blue  && toColor == Color::Green) return .8f;
            return 1.1f;
        }

        case 15:{
            if(fromColor == Color::Blue  && toColor == Color::Green) return .15f;
            if(fromColor == Color::Red   && toColor == Color::Green) return .55f;
            if(fromColor == Color::Green && toColor == Color::Red)   return .75f;
            return .9f;
        }

        default: break;
        }

        return 2.5f;
    }

} // namespace constants::color_sensor