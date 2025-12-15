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
        physical::I2CAddress muxAddress{sensorIndex < constants::color_sensor::SensorsPerMux ? 
            constants::i2c_address::MuxFront : constants::i2c_address::MuxBack
        };
        physical::Channel muxChannel{static_cast<physical::Channel>(
            sensorIndex % constants::color_sensor::SensorsPerMux
        )};

        selectMuxChannel(i2c0, muxAddress, muxChannel);

        uint8_t enableData[2]{
            constants::color_sensor::Enable, 
            constants::color_sensor::EnableValue
        };
        i2c_write_blocking(i2c0, constants::i2c_address::ColorSensor, enableData, 2, false);

        uint8_t timeData[2]{
            constants::color_sensor::IntegrationTime, 
            constants::color_sensor::IntegrationTimeValue
        };
        i2c_write_blocking(i2c0, constants::i2c_address::ColorSensor, timeData, 2, false);

        uint8_t gainData[2]{
            constants::color_sensor::Control, 
            constants::color_sensor::GainValue
        };
        i2c_write_blocking(i2c0, constants::i2c_address::ColorSensor, gainData, 2, false);
    }

    DEBUG_PRINT("Color sensors initialized!");
}

void SensorsManager::collectSensorData(){
    /* DEBUG */ {
        static char outputBuffer[1024];

        int offset{0};

        for(physical::Channel sensorIndex{0}; sensorIndex < 16; sensorIndex++){
            ColorReading color{readSensorRGBC(sensorIndex)};
            
            if(color.clear == 0){ // sensor not responding
                offset += snprintf(outputBuffer + offset, sizeof(outputBuffer) - offset,
                    "[%u](NoSensor)\n", sensorIndex
                );
            }else{
                const char *colorName{DEBUG_getColorName(color)};
                
                offset += snprintf(outputBuffer + offset, sizeof(outputBuffer) - offset,
                    "[%u]%s(R:%u G:%u B:%u C:%u)\n",
                    sensorIndex, colorName, color.red, color.green, color.blue, color.clear
                );
            }
        }

        DEBUG_PRINT_TIMED(500, "%s", outputBuffer);
    } /* DEBUG */
}

SensorsManager::ColorReading SensorsManager::readSensorRGBC(physical::Channel sensorIndex){
    ColorReading result{0, 0, 0, 0};

    physical::I2CAddress muxAddress{sensorIndex < constants::color_sensor::SensorsPerMux ? 
        constants::i2c_address::MuxFront : constants::i2c_address::MuxBack
    };
    physical::Channel muxChannel{static_cast<physical::Channel>(sensorIndex % constants::color_sensor::SensorsPerMux)};

    selectMuxChannel(i2c0, muxAddress, muxChannel);

    // clear: 0x14-0x15, red: 0x16-0x17, green: 0x18-0x19, blue: 0x1A-0x1B
    uint8_t registerAddress{constants::color_sensor::ClearDataLow};
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