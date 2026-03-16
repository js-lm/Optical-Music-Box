#pragma once

#include "aliases.hpp"
#include "calibrator/reference_profile.hpp"
#include "constants.hpp"

#include "utilities/ring_buffer.hpp"

#include <vector>
#include <queue>
#include <array>
#include <optional>

#include <hardware/i2c.h>

class SensorsManager{
public:
    enum class Color : uint8_t{
        White,
        Red,
        Green,
        Blue,
        Black,
        None,
        Error
    };

    using ColorRow = std::array<Color, constants::color_sensor::TotalSensorCount>;
    using RawColorReadingRow = std::array<
        color_sensor_data::RawColorReading, 
        constants::color_sensor::TotalSensorCount
    >;

private:
    units::TimestampUs lastReadTime_{0};
    std::optional<calibrator::ReferenceProfile> referenceProfile_{};

    utilities::RingBuffer<ColorRow, constants::color_sensor::FrontToBackDistance + 1> colorRowQueue_{};

public:
    SensorsManager() = default;
    ~SensorsManager() = default;

    void initialize();

    void startSampling();
    ColorRow collectSensorData();

public:
    RawColorReadingRow collectSensorRawReadings();
    void setReferenceProfile(const calibrator::ReferenceProfile &referenceProfile);

private:
    void initializeSensors();
    void setSensorEnabled(color_sensor_data::SensorIndex sensorIndex, bool enabled);

    color_sensor_data::RawColorReading readSensorRGBC(color_sensor_data::SensorIndex sensorIndex);

    Color getColor(color_sensor_data::SensorIndex sensorIndex, const color_sensor_data::RawColorReading &color) const;

private:
    struct MuxChannelInfo{
        physical::I2CAddress muxAddress;
        physical::Channel muxChannel;
    };

    MuxChannelInfo calculateMuxInfo(color_sensor_data::SensorIndex sensorIndex) const;
    void selectSensorMuxChannel(color_sensor_data::SensorIndex sensorIndex);
    void writeColorSensorRegister(physical::Register registerAddress, uint8_t value);

    void selectMuxChannel(i2c_inst_t *i2c, physical::I2CAddress muxAddress, physical::Channel channel);
};