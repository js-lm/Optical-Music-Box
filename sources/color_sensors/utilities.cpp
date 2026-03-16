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

SensorsManager::MuxChannelInfo SensorsManager::calculateMuxInfo(color_sensor_data::SensorIndex sensorIndex) const{
    physical::I2CAddress muxAddress{sensorIndex < constants::color_sensor::SensorsPerMux ? 
        constants::i2c_address::MuxFront : constants::i2c_address::MuxBack
    };
    physical::Channel muxChannel{static_cast<physical::Channel>(
        sensorIndex % constants::color_sensor::SensorsPerMux
    )};
    return MuxChannelInfo{muxAddress, muxChannel};
}

void SensorsManager::selectSensorMuxChannel(color_sensor_data::SensorIndex sensorIndex){
    MuxChannelInfo muxInfo{calculateMuxInfo(sensorIndex)};
    selectMuxChannel(i2c0, muxInfo.muxAddress, muxInfo.muxChannel);
}

void SensorsManager::writeColorSensorRegister(physical::Register registerAddress, uint8_t value){
    uint8_t data[2]{registerAddress, value};
    i2c_write_blocking(i2c0, constants::i2c_address::ColorSensor, data, 2, false);
}

void SensorsManager::setReferenceProfile(const calibrator::ReferenceProfile &referenceProfile){
    referenceProfile_ = referenceProfile;
}

SensorsManager::Color SensorsManager::getColor(
    color_sensor_data::SensorIndex sensorIndex, 
    const color_sensor_data::RawColorReading &color
) const{
    if(!referenceProfile_ 
    || sensorIndex >= constants::color_sensor::TotalSensorCount
    ){
        return Color::Error;
    }

    const calibrator::BaseValues &baseValues{referenceProfile_.value()[sensorIndex]};

    auto absoluteDifference{[](uint16_t leftValue, uint16_t rightValue)->uint16_t{
        return leftValue >= rightValue ? leftValue - rightValue : rightValue - leftValue;
    }};

    auto distance{[&absoluteDifference](
        const color_sensor_data::RawColorReading &leftValue, 
        const color_sensor_data::RawColorReading &rightValue
    )->uint16_t{
        return absoluteDifference(leftValue.red, rightValue.red)
             + absoluteDifference(leftValue.green, rightValue.green)
             + absoluteDifference(leftValue.blue, rightValue.blue)
             + absoluteDifference(leftValue.clear, rightValue.clear);
    }};

    auto minimumDistance{distance(color, baseValues.noPaper)};
    Color closestColor{Color::None};

    const auto whiteDistance{distance(color, baseValues.white)};
    if(whiteDistance < minimumDistance){
        minimumDistance = whiteDistance;
        closestColor = Color::White;
    }

    const auto redDistance{distance(color, baseValues.red)};
    if(redDistance < minimumDistance){
        minimumDistance = redDistance;
        closestColor = Color::Red;
    }

    const auto greenDistance{distance(color, baseValues.green)};
    if(greenDistance < minimumDistance){
        minimumDistance = greenDistance;
        closestColor = Color::Green;
    }

    const auto blueDistance{distance(color, baseValues.blue)};
    if(blueDistance < minimumDistance){
        minimumDistance = blueDistance;
        closestColor = Color::Blue;
    }

    const auto blackDistance{distance(color, baseValues.black)};
    if(blackDistance < minimumDistance){
        closestColor = Color::Black;
    }

    return closestColor;
}