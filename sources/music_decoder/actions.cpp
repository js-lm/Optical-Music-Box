#include "music_decoder.hpp"

midi_data::UniqueEventPointer MusicDecoder::decode(
    const InstrumentInstruction &value,
    const units::midi::Channel channel
) const{

    switch(value[0]){
    case Base5Value::Blue:
    case Base5Value::Black:

    return nullptr;

    default: break;
    }

    return std::make_unique<midi_command::NoteOn>(
        channel, base5ToDecimal(value)
    );
}

midi_data::UniqueEventPointer MusicDecoder::decode(
    const ChordInstruction &value
) const{


    return nullptr;
}