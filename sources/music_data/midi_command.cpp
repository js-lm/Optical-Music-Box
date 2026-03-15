#include "midi_command.hpp"

#include "midi_context.hpp"
#include "constants.hpp"
#include "midi_unit/midi_manager.hpp"

#include <variant>

using namespace midi_command;

// BaseCommand::~BaseCommand() = default;

void midi_command::execute(const Command &command, ExecutionContext &context){
	std::visit([&context](const auto &event){
		using EventType = std::decay_t<decltype(event)>;

		if constexpr(std::is_same_v<EventType, QueuedNoteOn>){
			context.midiManager.noteOn(event.channel, event.note, event.velocity);

			if(event.channel < context.state.lastPlayedNotes.size()){
				context.state.lastPlayedNotes[event.channel] = event.note;
			}
		}else if constexpr(std::is_same_v<EventType, QueuedNoteOff>){
			context.midiManager.noteOff(event.channel, event.note);

			if(event.channel < context.state.lastPlayedNotes.size()){
				context.state.lastPlayedNotes[event.channel] = 0;
			}
		}
	}, command);
}


// void NoteOn::execute(ExecutionContext &context){
// 	context.midiManager.noteOn(channel_, note_, constants::runtime::DefaultNoteVelocity);

// 	if(channel_ < context.state.lastPlayedNotes.size()){
// 		context.state.lastPlayedNotes[channel_] = note_;
// 	}


// }

// void NoteOff::execute(ExecutionContext &context){
// 	context.midiManager.noteOff(channel_, note_);

// 	if(channel_ < context.state.lastPlayedNotes.size()){
// 		context.state.lastPlayedNotes[channel_] = 0;
// 	}

    
// }