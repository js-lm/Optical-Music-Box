#pragma once

#include "aliases.hpp"
#include "constants.hpp"

#include "utilities/ring_buffer.hpp"

#include <vector>
#include <queue>
#include <array>

#include <hardware/i2c.h>

class SensorsManager{
public:
    enum class Color : uint8_t{
        None,
        Red,
        Green,
        Blue,
        Yellow,
        Black
    };

    using ColorRow = std::array<Color, constants::color_sensor::TotalSensorCount>;

private:
    struct ColorReading{
        uint16_t red;
        uint16_t green;
        uint16_t blue;
        uint16_t clear;
    };

    using ColorRowHalf = std::array<Color, constants::color_sensor::SensorsPerMux>;

private:
    units::TimestampUs lastReadTime_{0};

    utilities::RingBuffer<ColorRow, constants::color_sensor::FrontToBackDistance + 1> colorRowQueue_{};
    ColorRow latestColorRow_{};

public:
    SensorsManager() = default;
    ~SensorsManager() = default;

    void initialize();
    void update();

    ColorRow collectSensorData();

    ColorRow getLatestColorRow() const{ return latestColorRow_;}
    void next();

private:
    void initializeSensors();

    ColorReading readSensorRGBC(physical::Channel sensorIndex);

    Color getColor(const ColorReading &color) const;

private:
    void selectMuxChannel(i2c_inst_t *i2c, physical::I2CAddress muxAddress, physical::Channel channel);
};