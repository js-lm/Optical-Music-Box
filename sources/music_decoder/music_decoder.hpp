#pragma once

#include "aliases.hpp"
#include "constants.hpp"

#include <array>

class MusicDecoder{
public:
    enum class Base5 : uint8_t{ White, Red, Green, Blue, Black};

    using Instrument = std::array<Base5, constants::decoder::NumberOfInstrumentDigit>;
    using Chord = std::array<Base5, constants::decoder::NumberOfChordDigit>;

private:


public:
    MusicDecoder() = default;
    ~MusicDecoder() = default;

    units::midi::Note decodeInstrument(const Instrument &value) const;
    void decodeAndExecuteChord(const Chord &value);

};