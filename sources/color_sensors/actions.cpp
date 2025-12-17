#include "sensors_manager.hpp"

#include "constants.hpp"
#include "debug_utilities.hpp"

#include <hardware/i2c.h>
#include <pico/stdlib.h>
#include <stdio.h>

void SensorsManager::initializeSensors(){
    DEBUG_PRINT("Initializing color sensors...");
    
    int successCount{0};
    
    for(physical::Channel sensorIndex{0}; sensorIndex < constants::color_sensor::TotalSensorCount; sensorIndex++){
        selectSensorMuxChannel(sensorIndex);

        writeColorSensorRegister(constants::color_sensor::Enable, constants::color_sensor::EnableValue);
        writeColorSensorRegister(constants::color_sensor::IntegrationTime, constants::color_sensor::IntegrationTimeValue);
        writeColorSensorRegister(constants::color_sensor::Control, constants::color_sensor::GainValue);
    }

    DEBUG_PRINT("Color sensors initialized!");
}

void SensorsManager::setSensorEnabled(physical::Channel sensorIndex, bool enabled){
    selectSensorMuxChannel(sensorIndex);

    uint8_t enableValue{enabled ? constants::color_sensor::EnableValue : static_cast<uint8_t>(0x01)};
    writeColorSensorRegister(constants::color_sensor::Enable, enableValue);
}

void SensorsManager::startSampling(){
    for(physical::Channel sensorIndex{0}; sensorIndex < constants::color_sensor::TotalSensorCount; sensorIndex++){
        setSensorEnabled(sensorIndex, true);
    }
}

SensorsManager::ColorRow SensorsManager::collectSensorData(){
    // front sensors
    ColorRow colorRow{};
    for(physical::Channel sensorIndex{0}; sensorIndex < constants::color_sensor::SensorsPerMux; sensorIndex++){
        colorRow[sensorIndex] = getColor(readSensorRGBC(sensorIndex));
    }
    colorRowQueue_.push(colorRow);

    ColorRow latestColorRow{};

    if(colorRowQueue_.size() > constants::color_sensor::FrontToBackDistance){
        latestColorRow = colorRowQueue_.pop();

        // back sensors
        for(physical::Channel sensorIndex{constants::color_sensor::SensorsPerMux}; sensorIndex < constants::color_sensor::TotalSensorCount; sensorIndex++){
            latestColorRow[sensorIndex] = getColor(readSensorRGBC(sensorIndex));
        }
    }

    return latestColorRow;
}

SensorsManager::ColorReading SensorsManager::readSensorRGBC(physical::Channel sensorIndex){
    ColorReading result{0, 0, 0, 0};

    selectSensorMuxChannel(sensorIndex);

    // clear: 0x14-0x15, red: 0x16-0x17, green: 0x18-0x19, blue: 0x1A-0x1B
    physical::Register registerAddress{constants::color_sensor::ClearDataLow};
    uint8_t rgbcData[constants::color_sensor::RgbcDataByteCount]{};

    int writeResult{i2c_write_blocking(i2c0, constants::i2c_address::ColorSensor, &registerAddress, 1, true)};
    if(writeResult < 0) return result;
    
    int readResult{i2c_read_blocking(
        i2c0, constants::i2c_address::ColorSensor, rgbcData, constants::color_sensor::RgbcDataByteCount, false
    )};
    if(readResult < 0) return result;

    result.clear = static_cast<uint16_t>(rgbcData[0] | (rgbcData[1] << 8));
    result.red   = static_cast<uint16_t>(rgbcData[2] | (rgbcData[3] << 8));
    result.green = static_cast<uint16_t>(rgbcData[4] | (rgbcData[5] << 8));
    result.blue  = static_cast<uint16_t>(rgbcData[6] | (rgbcData[7] << 8));

    return result;
}