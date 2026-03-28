#include "sensors_manager.hpp"

#include <hardware/i2c.h>
#include <pico/stdlib.h>

#include <algorithm>

#include "constants.hpp"
#include "error_bias.hpp"

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

SensorsManager::ColorData SensorsManager::getColorData(
    color_sensor_data::SensorIndex sensorIndex,
    const color_sensor_data::RawColorReading &color
) const{
    ColorData colorData{};

    if(!referenceProfile_
    || sensorIndex >= constants::color_sensor::TotalSensorCount
    ){
        colorData.mostLikelyColor = Color::Error;
        return colorData;
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

    const auto whiteDistance{distance(color, baseValues.white)};
    const auto redDistance  {distance(color, baseValues.red)};
    const auto greenDistance{distance(color, baseValues.green)};
    const auto blueDistance {distance(color, baseValues.blue)};
    const auto blackDistance{distance(color, baseValues.black)};

    colorData.costs[Color::White] = whiteDistance;
    colorData.costs[Color::Red]   = redDistance;
    colorData.costs[Color::Green] = greenDistance;
    colorData.costs[Color::Blue]  = blueDistance;
    colorData.costs[Color::Black] = blackDistance;
    colorData.costs[Color::None]  = 0;
    colorData.costs[Color::Error] = 0;

    auto minimumDistance{distance(color, baseValues.noPaper)};
    Color closestColor{Color::None};

    if(whiteDistance < minimumDistance){
        minimumDistance = whiteDistance;
        closestColor = Color::White;
    }

    if(redDistance < minimumDistance){
        minimumDistance = redDistance;
        closestColor = Color::Red;
    }

    if(greenDistance < minimumDistance){
        minimumDistance = greenDistance;
        closestColor = Color::Green;
    }

    if(blueDistance < minimumDistance){
        minimumDistance = blueDistance;
        closestColor = Color::Blue;
    }

    if(blackDistance < minimumDistance){
        closestColor = Color::Black;
    }

    colorData.mostLikelyColor = closestColor;

    return colorData;
}

uint8_t SensorsManager::checksum(const ColorDataRow &colorDataRow) const{
    uint8_t sum{0};

    for(uint8_t colorDataIndex{0}; 
        colorDataIndex < constants::color_sensor::TotalSensorCount; 
        colorDataIndex++
    ){
        // sum += static_cast<uint8_t>(colorDataRow[colorDataIndex].mostLikelyColor);
        sum += static_cast<uint8_t>(colorDataRow.colorRow[colorDataIndex]);
    }

    return sum % constants::decoder::Radix;
}

SensorsManager::ColorRow SensorsManager::trySoftCorrection(const ColorDataRow &colorDataRow, uint8_t checksumResidue) const{
    ColorRow correctedRow{colorDataRow.colorRow};

    if(checksumResidue == 0) return correctedRow; 

    uint8_t requiredAddition{static_cast<uint8_t>((constants::decoder::Radix - checksumResidue) % constants::decoder::Radix)};

    uint8_t bestSensorIndex{0};
    float lowestAdjustedPenalty{std::numeric_limits<float>::max()};
    Color bestAlternativeColor{Color::Error};

    for(uint8_t sensorIndex{0}; sensorIndex < constants::color_sensor::TotalSensorCount; sensorIndex++){
        Color currentColor{colorDataRow.colorRow[sensorIndex]};
        
        if(currentColor >= Color::None) continue;

        uint8_t currentValue{static_cast<uint8_t>(currentColor)};
        uint8_t alternativeValue{static_cast<uint8_t>((currentValue + requiredAddition) % constants::decoder::Radix)};
        Color alternativeColor{static_cast<Color>(alternativeValue)};

        uint16_t currentCost{colorDataRow.costRow[sensorIndex][currentColor]};
        uint16_t alternativeCost{colorDataRow.costRow[sensorIndex][alternativeColor]};
        
        float basePenalty{
            alternativeCost > currentCost ? static_cast<float>(alternativeCost - currentCost) : .0f
        };

        float adjustedPenalty{
            basePenalty * constants::color_sensor::error_bias::getPenaltyMultiplier(sensorIndex, currentColor, alternativeColor)
        };

        if(adjustedPenalty < lowestAdjustedPenalty){
            lowestAdjustedPenalty = adjustedPenalty;
            bestSensorIndex = sensorIndex;
            bestAlternativeColor = alternativeColor;
        }
    }

    if(bestAlternativeColor != Color::Error) correctedRow[bestSensorIndex] = bestAlternativeColor;

    return correctedRow;
}