#pragma once

#include "aliases.hpp"
#include "constants.hpp"

#include "music_data/midi_command.hpp"

#include <array>
#include <memory>

class MusicDecoder{
public:
    enum class Base5Value : uint8_t{ White = 0, Red = 1, Green = 2, Blue = 3, Black = 4};

    template<size_t NumberOfDigit>
    using Base5 = std::array<Base5Value, NumberOfDigit>;
    using Base10 = int32_t;

    using InstrumentInstruction = Base5<constants::decoder::NumberOfInstrumentDigit>;
    using ChordInstruction = Base5<constants::decoder::NumberOfChordDigit>;

private:
    // std::array<midi_data::Instrument, constants::decoder::NumberOfInstrumentChannel> instrumentTypes_;

public:
    MusicDecoder() = default;
    ~MusicDecoder() = default;

    midi_data::UniqueEventPointer decode(
        const InstrumentInstruction &value,
        const units::midi::Channel channel
    ) const;
    midi_data::UniqueEventPointer decode(
        const ChordInstruction &value
    ) const;

private:
    void setInstrument(const midi_data::Instrument &instrument);

    template<size_t NumberOfDigit>
    Base10 base5ToDecimal(const Base5<NumberOfDigit> &value) const;
};