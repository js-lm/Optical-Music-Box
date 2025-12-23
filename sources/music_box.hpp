#pragma once

#include "motor/motor_manager.hpp"
#include "light_sensor/light_manager.hpp"
#include "color_sensors/sensors_manager.hpp"
#include "midi_unit/midi_manager.hpp"

#include "utilities/enum_map.hpp"

class MusicBox{
private:
    enum class State : uint8_t{
        None,

        Calibrate_Markers,
        Calibrate_Sensors,

        Configure_Metadata,
        Configure_Instruments,

        Seek,
        Wait,
        Process
    } state_;

private:
    MotorManager        motorManager_{};
    LightSensorManager  lightSensorManager_{};
    SensorsManager      sensorsManager_{};
    MidiManager         midiManager_{};

    inline static MotorManager *motorManagerPointer_{nullptr};

private:
    units::TimestampUs lastUpdateTime_{0};
    units::Us timeSinceLastStep_{0};

private:
    enum class Channel : uint8_t{ None, Instrument_1, Instrument_2, Instrument_3, Chord};
    using Instrument = MidiManager::Instrument;
    utilities::EnumMap<Channel, Instrument> channelInstruments_;

public:
    MusicBox() = default;
    ~MusicBox() = default;

    int run();

private:
    void initialize();
    void update();

    static void core1Entry();

private:
    void nextState();
    void updateTimers();

private:
    void updateCalibrateMarkersState();
    void updateCalibrateSensorsState();

    void updateConfigureMetadataState();
    void updateConfigureInstrumentsState();
    
    void updatePreparationState();
    void updateSeekState();
    void updateWaitState();
    void updateProcessState();

private:
    constexpr Channel color2Channel(SensorsManager::Color color) const;
};