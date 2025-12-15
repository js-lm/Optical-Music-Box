#include "sensors_manager.hpp"

#include <hardware/i2c.h>
#include <pico/stdlib.h>

#include <algorithm>

#include "constants.hpp"

void SensorsManager::selectMuxChannel(i2c_inst_t *i2c, physical::I2CAddress muxAddress, physical::Channel channel){
    constexpr uint8_t disableMask{constants::color_sensor::MuxDisableMask};

    i2c_write_blocking(i2c, constants::i2c_address::MuxFront, &disableMask, 1, false);
    i2c_write_blocking(i2c, constants::i2c_address::MuxBack,  &disableMask, 1, false);
    
    uint8_t channelMask{static_cast<uint8_t>(1 << channel)};
    i2c_write_blocking(i2c, muxAddress, &channelMask, 1, false);
}

const char *SensorsManager::DEBUG_getColorName(const ColorReading &color){
    if(color.clear < constants::color_sensor::BlackClearThreshold) return "black";

    uint16_t maximumValue{std::max({color.red, color.green, color.blue})};
    uint16_t minimumValue{std::min({color.red, color.green, color.blue})};
    if((maximumValue - minimumValue) < (color.clear * constants::color_sensor::WhiteSaturationThreshold)){
        return "white";
    }

    if(color.red > color.blue * constants::color_sensor::YellowRedRatioThreshold 
    && color.green > color.blue * constants::color_sensor::YellowGreenRatioThreshold
    ){
        return "yellow";
    }
    
    if(color.red > color.green && color.red > color.blue){
        return "red";
    }else if(color.green > color.red && color.green > color.blue){
        return "green";
    }else{
        return "blue";
    }
    
}