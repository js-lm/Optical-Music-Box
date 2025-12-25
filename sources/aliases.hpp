#pragma once

#include <cstdint>
#include <variant>

#include "music_data/instrument_types.hpp"

namespace units{

    using Ms = uint32_t;
    using Us = uint64_t;

    inline constexpr Us Ms2Us(Ms millisecond){ return static_cast<Us>(millisecond) * 1000;}
    inline constexpr Ms Us2Ms(Us microsecond){ return static_cast<Ms>(microsecond / 1000);}

    using MsRate = uint16_t;
    using UsRate = uint16_t;
    
    using TimestampMs = uint64_t;
    using TimestampUs = uint64_t;

    using Percentage = float;

    namespace midi{

        using Channel   = uint8_t;
        using Note      = uint8_t;
        using NoteOffset= int8_t;
        using Velocity  = uint8_t;
        using Octave    = int8_t;

    } // namespace midi

} // namespace units

namespace midi_data{

    using Instrument = std::variant<instruments::Default, instruments::Mt32>;

    using UniqueEventPointer = std::unique_ptr<midi_command::BaseCommand>;

} // namespace midi_data

namespace physical{

    using Pin           = uint8_t;
    using I2CAddress    = uint8_t;
    using Register      = uint8_t;
    using Channel       = uint8_t;

} // namespace physical