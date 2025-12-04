#pragma once

#include "aliases.hpp"

#include <vector>
#include <queue>

#include <hardware/i2c.h>

class SensorsManager{
public:
    using NoteRow = std::vector<bool>;

private:
    units::Ms timeSinceInitialization_{0};

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

private:
    void selectMuxChannel(i2c_inst_t *i2c, physical::I2CAddress muxAddress, physical::Channel channel);
};