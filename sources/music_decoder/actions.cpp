#include "music_decoder.hpp"

std::optional<midi_command::Command> MusicDecoder::decode(
    const InstrumentInstruction &value,
    const units::midi::Channel channel
) const{

    switch(value[0]){
    case Base5Value::Blue:
    case Base5Value::Black:

    return std::nullopt;

    default: break;
    }

    return midi_command::QueuedNoteOn{
        channel,
        static_cast<units::midi::Note>(base5ToDecimal(value)),
        constants::runtime::DefaultNoteVelocity
    };
}

std::optional<midi_command::Command> MusicDecoder::decode(
    const ChordInstruction &value
) const{


    return std::nullopt;
}