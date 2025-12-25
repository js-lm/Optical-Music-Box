#pragma once

#include "constants.hpp"
#include "aliases.hpp"

class MidiManager;

namespace midi_command{

    struct MachineState{
        template<typename Type>
        using InstrumentChannelArray = std::array<
            Type, constants::decoder::NumberOfInstrumentChannel
        >;

        InstrumentChannelArray<midi_data::Instrument> instrumentTypes;
        InstrumentChannelArray<units::midi::Velocity> instrumentVelocities;
        InstrumentChannelArray<units::midi::NoteOffset> instrumentNoteOffsets;

        InstrumentChannelArray<units::midi::Note> lastPlayedNotes;
    };

    struct ExecutionContext{
        MachineState &state;
        MidiManager &midiManager;

        units::midi::Channel channel;
    };

} // namespace midi_command