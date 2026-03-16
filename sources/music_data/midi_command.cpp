#include "midi_command.hpp"

#include "midi_context.hpp"
#include "constants.hpp"
#include "midi_unit/midi_manager.hpp"

#include "debug_utilities.hpp"

#include <variant>

using namespace midi_command;

void midi_command::execute(const Command &command, ExecutionContext &context){
	std::visit([&context](const auto &event){
		using EventType = std::decay_t<decltype(event)>;

		if constexpr(std::is_same_v<EventType, QueuedNoteOn>){
			if(event.channel < context.state.lastPlayedNotes.size()){
				const auto previousNote{context.state.lastPlayedNotes[event.channel]};

				if(previousNote != 0 && previousNote != event.note){
					// DEBUG_PRINT(
					// 	"Note Off channel=%u note=%u (auto)",
					// 	static_cast<unsigned int>(event.channel),
					// 	static_cast<unsigned int>(previousNote)
					// );

					context.midiManager.noteOff(event.channel, previousNote);
				}
			}

			// DEBUG_PRINT(
			// 	"Note On channel=%u note=%u velocity=%u",
			// 	static_cast<unsigned int>(event.channel),
			// 	static_cast<unsigned int>(event.note),
			// 	static_cast<unsigned int>(event.velocity)
			// );

			context.midiManager.noteOn(event.channel, event.note, event.velocity);

			if(event.channel < context.state.lastPlayedNotes.size()){
				context.state.lastPlayedNotes[event.channel] = event.note;
			}
		}else if constexpr(std::is_same_v<EventType, QueuedNoteOff>){
			units::midi::Note noteToTurnOff{event.note};

			if(event.channel < context.state.lastPlayedNotes.size() && noteToTurnOff == 0){
				noteToTurnOff = context.state.lastPlayedNotes[event.channel];
			}

			if(noteToTurnOff != 0){
				// DEBUG_PRINT(
				// 	"Note Off channel=%u note=%u",
				// 	static_cast<unsigned int>(event.channel),
				// 	static_cast<unsigned int>(noteToTurnOff)
				// );

				context.midiManager.noteOff(event.channel, noteToTurnOff);
			}

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