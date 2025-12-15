#pragma once

#include "aliases.hpp"

#include <vector>
#include <queue>

#include <hardware/i2c.h>

class SensorsManager{
public:
    using NoteRow = std::vector<bool>;

    struct ColorReading{
        uint16_t red;
        uint16_t green;
        uint16_t blue;
        uint16_t clear;
    };

private:
    units::TimestampUs lastReadTime_{0};

    std::queue<NoteRow> notesQueue_;

public:
    SensorsManager() = default;
    ~SensorsManager() = default;

    void initialize();
    void update();

    NoteRow getNotes() const;

private:
    void initializeSensors();
    void collectSensorData();

    ColorReading readSensorRGBC(physical::Channel sensorIndex);

    const char *DEBUG_getColorName(const ColorReading &color);

private:
    void selectMuxChannel(i2c_inst_t *i2c, physical::I2CAddress muxAddress, physical::Channel channel);
};