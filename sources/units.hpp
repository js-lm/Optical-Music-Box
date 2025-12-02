#pragma once

#include <cstdint>

namespace units{

    using Ms = uint32_t;
    using Us = uint32_t;

    inline constexpr Us Ms2Us(Ms millisecond){ return static_cast<Us>(millisecond) * 1000;}
    inline constexpr Ms Us2Ms(Us microsecond){ return static_cast<Ms>(microsecond / 1000.0f);}

    using MsRate = uint16_t;
    using UsRate = uint16_t;
    
    using TimestampMs = uint64_t;
    using TimestampUs = uint64_t;

} // namespace units