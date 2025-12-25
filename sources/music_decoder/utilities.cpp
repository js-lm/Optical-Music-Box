#include "music_decoder.hpp"

template<size_t NumberOfDigit>
MusicDecoder::Base10 MusicDecoder::base5ToDecimal(const Base5<NumberOfDigit> &value) const{
    static_assert(NumberOfDigit < constants::decoder::MaximumNumberOfBase5Digit);

    Base10 result{0};
    Base10 multiplier{1};
    
    for(uint8_t index{value.size()}; index --> 0;){
        result += static_cast<Base10>(value[index]) * multiplier;
        multiplier *= 5;
    }
    
    return result;
}