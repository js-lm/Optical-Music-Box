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

SensorsManager::MuxChannelInfo SensorsManager::calculateMuxInfo(physical::Channel sensorIndex) const{
    physical::I2CAddress muxAddress{sensorIndex < constants::color_sensor::SensorsPerMux ? 
        constants::i2c_address::MuxFront : constants::i2c_address::MuxBack
    };
    physical::Channel muxChannel{static_cast<physical::Channel>(
        sensorIndex % constants::color_sensor::SensorsPerMux
    )};
    return MuxChannelInfo{muxAddress, muxChannel};
}

void SensorsManager::selectSensorMuxChannel(physical::Channel sensorIndex){
    MuxChannelInfo muxInfo{calculateMuxInfo(sensorIndex)};
    selectMuxChannel(i2c0, muxInfo.muxAddress, muxInfo.muxChannel);
}

void SensorsManager::writeColorSensorRegister(physical::Register registerAddress, uint8_t value){
    uint8_t data[2]{registerAddress, value};
    i2c_write_blocking(i2c0, constants::i2c_address::ColorSensor, data, 2, false);
}

SensorsManager::Color SensorsManager::getColor(const ColorReading &color) const{
    if(color.clear < constants::color_sensor::BlackClearThreshold) return Color::Black;

    uint16_t maximumValue{std::max({color.red, color.green, color.blue})};
    uint16_t minimumValue{std::min({color.red, color.green, color.blue})};
    if((maximumValue - minimumValue) < (color.clear * constants::color_sensor::WhiteSaturationThreshold)){
        return Color::None;
    }

    if(color.red > color.blue * constants::color_sensor::YellowRedRatioThreshold 
    && color.green > color.blue * constants::color_sensor::YellowGreenRatioThreshold
    ){
        return Color::Yellow;
    }
    
    if(color.red > color.green && color.red > color.blue){
        return Color::Red;
    }else if(color.green > color.red && color.green > color.blue){
        return Color::Green;
    }else{
        return Color::Blue;
    }
}